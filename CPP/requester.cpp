#include "requester.h"

Requester::Requester(QObject *parent) : QObject(parent)
{
	m_done = false;
	setState(BaseState);
	m_data = QByteArray();

	connect(&m_downloader, &Downloader::finished, this, &Requester::readReply);
}

void Requester::readReply(Reply *R)
{
	m_data = R->readAll();
	setState(LoadedState);
	m_done = true;
	m_elapsed = m_timer.elapsed();
}

void Requester::setState(State state)
{
	if (m_state == state) return;

	m_state = state;
	emit stateChanged(m_state);
}

void Requester::start()
{
	setState(BaseState);

	bool hasPostData = !m_postData.isEmpty();
	Request R = Request(QUrl(m_url));
	QUrlQuery Q;

	if (hasPostData)
		for (const auto &K : m_postData.keys())
			Q.addQueryItem(K, m_postData[K]);

	if (hasPostData)
		m_downloader.post(R, Q.toString(QUrl::FullyEncoded).toUtf8());
	else
		m_downloader.get(R);

	setState(LoadingState);
	m_timer.restart();
}

void Requester::setPostData(const QHash<QByteArray, QByteArray> &postData)
{
	m_postData = postData;
}

int Requester::elapsed() const { return m_elapsed; }
void Requester::setUrl(const QString &url) { m_url = url; }
void Requester::setTimeout(int timeout) { m_timeout = timeout; }
void Requester::setProxy(const Proxy &proxy) { m_downloader.setProxy(proxy); }

bool Requester::done() const { return m_done; }
State Requester::state() const { return m_state; }
const QByteArray &Requester::data() const { return m_data; }
