#include "requester.h"

Requester::Requester(QObject *parent) : QObject(parent)
{
	m_done = false;
	setState(BaseState);
	m_data = QByteArray();
	m_elapsed = 0;
	m_statusCode = -1;

	m_knownHeaders << "Content-Type"
				   << "Content-Length"
				   << "Cookie"
				   << "User-Agent";

	connect(&m_downloader, &Downloader::finished, this, &Requester::readReply);
}

void Requester::setHeaders(const QHash<QByteArray, QByteArray> &headers)
{
	m_headers = headers;
}

const QString &Requester::replyHeaders() const { return m_replyHeaders; }

int Requester::statusCode() const { return m_statusCode; }

const QString &Requester::statusMessage() const { return m_statusMessage; }

void Requester::readReply(Reply *R)
{
	m_data = R->readAll();
	m_done = R->error() == Reply::NoError;
	m_elapsed = m_timer.elapsed();

	m_replyHeaders.clear();
	for (const auto &P : R->rawHeaderPairs())
		m_replyHeaders += P.first + ": " + P.second + "\n";
	m_replyHeaders.remove(m_replyHeaders.size() - 1, 1);

	m_statusCode =
		R->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

	m_statusMessage =
		R->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toByteArray();

	setState(LoadedState);
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

	Request R = Request(QUrl(m_url));
	fixHeaders(R);

	QUrlQuery Q;
	bool hasPostData = !m_postData.isEmpty();

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

void Requester::fixHeaders(Request &request)
{
	if (m_headers.contains("Content-Type"))
		request.setHeader(Request::ContentTypeHeader,
						  m_headers["Content-Type"]);
	if (m_headers.contains("Content-Length"))
		request.setHeader(Request::ContentLengthHeader,
						  m_headers["Content-Length"]);
	if (m_headers.contains("Cookie"))
		request.setHeader(Request::CookieHeader, m_headers["Cookie"]);
	if (m_headers.contains("User-Agent"))
		request.setHeader(Request::UserAgentHeader, m_headers["User-Agent"]);

	for (const auto &key : m_headers.keys())
	{
		if (m_knownHeaders.contains(key)) continue;
		request.setRawHeader(key, m_headers[key]);
	}
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
