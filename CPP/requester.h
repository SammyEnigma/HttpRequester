#ifndef REQUESTER_H
#define REQUESTER_H

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkProxy>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QObject>
#include <QStandardItem>
#include <QTime>
#include <QUrlQuery>

using Downloader = QNetworkAccessManager;
using Request = QNetworkRequest;
using Reply = QNetworkReply;
using Query = QUrlQuery;
using Proxy = QNetworkProxy;

enum State
{
	BaseState,
	LoadingState,
	LoadedState
};

class Requester : public QObject
{
	Q_OBJECT

	int m_timeout;
	QString m_url;
	QHash<QByteArray, QByteArray> m_postData;

	bool m_done;  // true for success. false for failure
	State m_state;
	QTime m_timer;
	int m_elapsed;
	QByteArray m_data;
	Downloader m_downloader;

private slots:
	void readReply(Reply *R);

public:
	explicit Requester(QObject *parent = nullptr);

	void start();

	bool done() const;
	State state() const;
	int elapsed() const;
	const QByteArray &data() const;

	void setTimeout(int timeout);
	void setUrl(const QString &url);
	void setProxy(const Proxy &proxy);
	void setPostData(const QHash<QByteArray, QByteArray> &postData);

signals:
	void stateChanged(State state);

public slots:
	void setState(State state);
};

#endif  // REQUESTER_H
