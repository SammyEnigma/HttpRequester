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
#include <QTimer>
#include <QUrlQuery>

#include "structs.h"

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

	QTime m_time;
	State m_state;
	QTimer m_timer;

	Reply *m_reply;
	Downloader m_downloader;
	QStringList m_knownHeaders;

	RequesterInput m_input;
	RequesterOutput m_output;

private slots:
	void cancelRequest();
	void readReply(Reply *R);

public:
	explicit Requester(QObject *parent = nullptr);

	void start();
	void fixHeaders(Request &request);

	State state() const;
	void setTimeout(int timeout);
	void setProxy(const Proxy &proxy);

	const RequesterOutput &output() const;
	void setInput(const RequesterInput &input);

signals:
	void stateChanged(State state);

public slots:
	void setState(State state);
};

#endif  // REQUESTER_H
