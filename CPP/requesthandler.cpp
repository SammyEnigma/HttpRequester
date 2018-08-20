#include "requesthandler.h"

#ifdef Q_OS_ANDROID
#include <QColor>
#include <QtAndroidExtras/QAndroidJniObject>
#include <QtAndroidExtras/QtAndroid>
#define FLAG_TRANSLUCENT_STATUS 0x04000000
#define FLAG_DRAWS_SYSTEM_BAR_BACKGROUNDS 0x80000000
#endif

RequestHolder *RequestHandler::Holder = nullptr;

RequestHandler::RequestHandler(QObject *parent) : QObject(parent)
{
	m_model = new QmlModel(this);

	m_model->addRoles({Add(ElapsedRole), Add(InfoRole), Add(FinishedRole),
					   Add(HeadersRole), Add(StatusCodeRole),
					   Add(StatusMessageRole)});

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

int RequestHandler::singleStatusCode() const { return m_singleStatusCode; }

QString RequestHandler::singleStatusMessage() const
{
	return m_singleStatusMessage;
}

QString RequestHandler::singleHeaders() const { return m_singleHeaders; }

RequesterInput RequestHandler::setupRequester()
{
	RequesterInput Input;

	setupRequesterUrl(Input);
	setupRequesterPost(Input);
	setupRequesterProxy(Input);
	setupRequesterHeader(Input);

	return Input;
}

void RequestHandler::setupRequesterProxy(RequesterInput &Input)
{
	Q_UNUSED(Input);

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
	P.setPort(ushort(Holder->proxyHost().toInt()));

	if (Holder->proxyHasUser())
	{
		P.setUser(Holder->proxyUsername());
		P.setPassword(Holder->proxyPassword());
	}

	m_requester.setProxy(P);
}

void RequestHandler::setupRequesterPost(RequesterInput &Input)
{
	QHash<QByteArray, QByteArray> &hash = Input.postData;
	hash.clear();

	if (Holder->requestType() != PostRequest) return;

	auto *model = Holder->postModel();
	for (int i = 0; i < model->rowCount(); ++i)
	{
		auto *item = model->item(i);
		hash[item->data(NameRole).toByteArray()] =
			item->data(DataRole).toByteArray();
	}
}

void RequestHandler::setupRequesterHeader(RequesterInput &Input)
{
	QHash<QByteArray, QByteArray> &hash = Input.headers;
	hash.clear();

	if (!Holder->hasHeader()) return;

	auto *model = Holder->headerModel();
	for (int i = 0; i < model->rowCount(); ++i)
	{
		auto *item = model->item(i);
		hash[item->data(NameRole).toByteArray()] =
			item->data(DataRole).toByteArray();
	}
}

void RequestHandler::setupRequesterUrl(RequesterInput &Input)
{
	if (!Holder->addressType())
	{
		QString &url = Input.url;
		url = Holder->addressUrl();
		url = url.trimmed();

		if (!url.startsWith("http://") || url.startsWith("https://"))
			url.prepend("http://");
	}
	else
		Input.url =
			"http://" + Holder->addressIp() + ":" + Holder->addressPort() + "/";

	Input.putData = Holder->putData();
	Input.requestType = Holder->requestType();
	m_requester.setTimeout(Holder->requestTimeout() * 1000);
}

void RequestHandler::requestDone()
{
	if (m_requester.state() != LoadedState) return;
	const auto &Output = m_requester.output();

	if (Holder->requestCount() == 1)
	{
		setState(LoadedState);
		setSingleInfo(Output.data);
		setSingleFinished(Output.done);
		setSingleElapsed(Output.elapsed);
		setSingleHeaders(Output.replyHeaders);
		setSingleStatusCode(Output.statusCode);
		setSingleStatusMessage(Output.statusMessage);
		return;
	}

	QStandardItem *item = new QStandardItem();

	item->setData(Output.data, InfoRole);
	item->setData(Output.done, FinishedRole);
	item->setData(Output.elapsed, ElapsedRole);
	item->setData(Output.replyHeaders, HeadersRole);
	item->setData(Output.statusCode, StatusCodeRole);
	item->setData(Output.statusMessage, StatusMessageRole);

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

	auto Input = setupRequester();
	m_requester.setInput(Input);
	m_requester.start();
}

void RequestHandler::setTopColor(const QColor &color)
{
#ifdef Q_OS_ANDROID
	QtAndroid::runOnAndroidThread([=]() {
		QAndroidJniObject window =
			QtAndroid::androidActivity().callObjectMethod(
				"getWindow", "()Landroid/view/Window;");
		window.callMethod<void>("addFlags", "(I)V",
								FLAG_DRAWS_SYSTEM_BAR_BACKGROUNDS);
		window.callMethod<void>("clearFlags", "(I)V", FLAG_TRANSLUCENT_STATUS);
		window.callMethod<void>("setStatusBarColor", "(I)V", color.rgba());
		window.callMethod<void>("setNavigationBarColor", "(I)V", color.rgba());
	});
#else
	Q_UNUSED(color)
#endif
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

void RequestHandler::setSingleStatusCode(int singleStatusCode)
{
	if (m_singleStatusCode == singleStatusCode) return;

	m_singleStatusCode = singleStatusCode;
	emit singleStatusCodeChanged(m_singleStatusCode);
}

void RequestHandler::setSingleStatusMessage(QString singleStatusMessage)
{
	if (m_singleStatusMessage == singleStatusMessage) return;

	m_singleStatusMessage = singleStatusMessage;
	emit singleStatusMessageChanged(m_singleStatusMessage);
}

int RequestHandler::requestsCount() const { return m_requestsCount; }
int RequestHandler::currentRequest() const { return m_currentRequest; }
int RequestHandler::state() const { return m_state; }
int RequestHandler::singleElapsed() const { return m_singleElapsed; }
QString RequestHandler::singleInfo() const { return m_singleInfo; }
bool RequestHandler::singleFinished() const { return m_singleFinished; }
