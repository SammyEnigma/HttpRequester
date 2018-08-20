#include "requester.h"

Requester::Requester(QObject *parent) : QObject(parent)
{
	setState(BaseState);

	m_knownHeaders << "Content-Type"
				   << "Content-Length"
				   << "Cookie"
				   << "User-Agent";

	connect(&m_timer, &QTimer::timeout, this, &Requester::cancelRequest);
	connect(&m_downloader, &Downloader::finished, this, &Requester::readReply);
}

void Requester::readReply(Reply *R)
{
	m_output.data = R->readAll();
	m_output.done = R->error() == Reply::NoError;
	m_output.elapsed = m_time.elapsed();

	m_timer.stop();

	m_output.replyHeaders.clear();
	for (const auto &P : R->rawHeaderPairs())
		m_output.replyHeaders += P.first + ": " + P.second + "\n";
	m_output.replyHeaders.remove(m_output.replyHeaders.size() - 1, 1);

	m_output.statusCode =
		R->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

	m_output.statusMessage =
		R->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toByteArray();

	setState(LoadedState);
}

void Requester::cancelRequest() { m_reply->abort(); }

void Requester::setState(State state)
{
	if (m_state == state) return;

	m_state = state;
	emit stateChanged(m_state);
}

void Requester::start()
{
	setState(BaseState);

	Request R = Request(QUrl(m_input.url));
	fixHeaders(R);

	if (m_input.requestType == GetRequest)
		m_reply = m_downloader.get(R);
	else if (m_input.requestType == HeadRequest)
		m_reply = m_downloader.head(R);
	else if (m_input.requestType == DeleteRequest)
		m_reply = m_downloader.deleteResource(R);
	else if (m_input.requestType == PostRequest)
	{
		QUrlQuery Q;

		for (const auto &K : m_input.postData.keys())
			Q.addQueryItem(K, m_input.postData[K]);

		m_reply = m_downloader.post(R, Q.toString(QUrl::FullyEncoded).toUtf8());
	}
	else if (m_input.requestType == PutRequest)
	{
		m_input.putData = "name: 'new product name'";
		m_downloader.put(R, m_input.putData);
		qDebug() << "Putting " << m_input.putData;
	}

	setState(LoadingState);
	if (m_timer.interval() >= 0) m_timer.start();

	m_time.restart();
}

void Requester::fixHeaders(Request &request)
{
	if (m_input.headers.contains("Content-Type"))
		request.setHeader(Request::ContentTypeHeader,
						  m_input.headers["Content-Type"]);
	if (m_input.headers.contains("Content-Length"))
		request.setHeader(Request::ContentLengthHeader,
						  m_input.headers["Content-Length"]);
	if (m_input.headers.contains("Cookie"))
		request.setHeader(Request::CookieHeader, m_input.headers["Cookie"]);
	if (m_input.headers.contains("User-Agent"))
		request.setHeader(Request::UserAgentHeader,
						  m_input.headers["User-Agent"]);

	for (const auto &key : m_input.headers.keys())
	{
		if (m_knownHeaders.contains(key)) continue;
		request.setRawHeader(key, m_input.headers[key]);
	}
}

const RequesterOutput &Requester::output() const { return m_output; }
void Requester::setInput(const RequesterInput &input) { m_input = input; }

State Requester::state() const { return m_state; }
void Requester::setTimeout(int timeout) { m_timer.setInterval(timeout); }
void Requester::setProxy(const Proxy &proxy) { m_downloader.setProxy(proxy); }
