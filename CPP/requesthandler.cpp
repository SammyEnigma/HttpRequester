#include "requesthandler.h"

RequestHolder *RequestHandler::Holder = nullptr;

RequestHandler::RequestHandler(QObject *parent) : QObject(parent)
{
	m_model = new QmlModel(this);
	m_model->addRoles(
		{Add(ElapsedRole), Add(InfoRole), Add(FinishedRole), Add(HeadersRole)});

	m_requester.setParent(this);
	setState(BaseState);

	connect(&m_requester, &Requester::stateChanged, this,
			&RequestHandler::requestDone);

	setRequestsCount(0);
	setCurrentRequest(0);
	setSingleElapsed(0);
	setSingleInfo("");
	setSingleFinished(false);
}

QmlModel *RequestHandler::model() const { return m_model; }

QString RequestHandler::singleHeaders() const { return m_singleHeaders; }

void RequestHandler::setupRequester()
{
	setupRequesterUrl();
	setupRequesterPost();
	setupRequesterProxy();
}

void RequestHandler::setupRequesterProxy()
{
	Proxy P;
	if (Holder->proxyType() == 0)
	{
		P.setType(Proxy::NoProxy);
		m_requester.setProxy(P);
		return;
	}
	else if (Holder->proxyType() == 1)
		P.setType(Proxy::HttpProxy);
	else if (Holder->proxyType() == 2)
		P.setType(Proxy::Socks5Proxy);

	P.setHostName(Holder->proxyHost());
	P.setPort(Holder->proxyHost().toInt());

	if (Holder->proxyHasUser())
	{
		P.setUser(Holder->proxyUsername());
		P.setPassword(Holder->proxyPassword());
	}

	m_requester.setProxy(P);
}

void RequestHandler::setupRequesterPost()
{
	QHash<QByteArray, QByteArray> hash;
	auto *model = Holder->postModel();

	if (!Holder->hasPostData())
	{
		m_requester.setPostData(hash);
		return;
	}

	for (int i = 0; i < model->rowCount(); ++i)
	{
		auto *item = model->item(i);
		hash[item->data(NameRole).toByteArray()] =
			item->data(DataRole).toByteArray();
	}

	m_requester.setPostData(hash);
}

void RequestHandler::setupRequesterHeader()
{
	QHash<QByteArray, QByteArray> hash;
	auto *model = Holder->headerModel();

	if (!Holder->hasHeader())
	{
		m_requester.setPostData(hash);
		return;
	}

	for (int i = 0; i < model->rowCount(); ++i)
	{
		auto *item = model->item(i);
		hash[item->data(NameRole).toByteArray()] =
			item->data(DataRole).toByteArray();
	}

	m_requester.setHeaders(hash);
}

void RequestHandler::setupRequesterUrl()
{
	if (!Holder->addressType())
	{
		auto url = Holder->addressUrl();
		url = url.trimmed();

		if (!url.startsWith("http://") || url.startsWith("https://"))
			url.prepend("http://");

		m_requester.setUrl(url);
	}
	else
		m_requester.setUrl("http://" + Holder->addressIp() + ":" +
						   Holder->addressPort() + "/");
}

void RequestHandler::requestDone()
{
	if (m_requester.state() != LoadedState) return;

	if (Holder->requestCount() == 1)
	{
		qDebug() << m_requester.done();

		setState(LoadedState);
		setSingleElapsed(m_requester.elapsed());
		setSingleFinished(m_requester.done());
		setSingleInfo(m_requester.data());
		setSingleHeaders(m_requester.replyHeaders());
		return;
	}

	QStandardItem *item = new QStandardItem();

	item->setData(m_requester.data(), InfoRole);
	item->setData(m_requester.done(), FinishedRole);
	item->setData(m_requester.elapsed(), ElapsedRole);
	item->setData(m_requester.replyHeaders(), HeadersRole);

	m_model->appendRow(item);

	if (m_currentRequest == m_requestsCount - 1)
		setState(LoadedState);
	else
	{
		setCurrentRequest(m_currentRequest + 1);
		m_requester.start();
	}
}

void RequestHandler::begin()
{
	setState(LoadingState);

	setRequestsCount(Holder->requestCount());
	setCurrentRequest(0);

	setSingleElapsed(0);
	setSingleFinished(false);
	setSingleInfo("");

	setupRequester();
	m_requester.start();
}

void RequestHandler::setRequestsCount(int requestsCount)
{
	if (m_requestsCount == requestsCount) return;

	m_requestsCount = requestsCount;
	emit requestsCountChanged(m_requestsCount);
}

void RequestHandler::setCurrentRequest(int currentRequest)
{
	if (m_currentRequest == currentRequest) return;

	m_currentRequest = currentRequest;
	emit currentRequestChanged(m_currentRequest);
}

void RequestHandler::setState(int state)
{
	if (m_state == state) return;

	m_state = state;
	emit stateChanged(m_state);
}

void RequestHandler::setSingleElapsed(int singleElapsed)
{
	if (m_singleElapsed == singleElapsed) return;

	m_singleElapsed = singleElapsed;
	emit singleElapsedChanged(m_singleElapsed);
}

void RequestHandler::setSingleInfo(QString singleInfo)
{
	if (m_singleInfo == singleInfo) return;

	m_singleInfo = singleInfo;
	emit singleInfoChanged(m_singleInfo);
}

void RequestHandler::setSingleFinished(bool singleFinished)
{
	if (m_singleFinished == singleFinished) return;

	m_singleFinished = singleFinished;
	emit singleFinishedChanged(m_singleFinished);
}

void RequestHandler::setSingleHeaders(QString singleHeaders)
{
	if (m_singleHeaders == singleHeaders) return;

	m_singleHeaders = singleHeaders;
	emit singleHeadersChanged(m_singleHeaders);
}

int RequestHandler::requestsCount() const { return m_requestsCount; }
int RequestHandler::currentRequest() const { return m_currentRequest; }
int RequestHandler::state() const { return m_state; }
int RequestHandler::singleElapsed() const { return m_singleElapsed; }
QString RequestHandler::singleInfo() const { return m_singleInfo; }
bool RequestHandler::singleFinished() const { return m_singleFinished; }
