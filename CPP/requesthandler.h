#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H

#include "requester.h"
#include "requestholder.h"

#include <QObject>

enum RequestRoles
{
	ElapsedRole = Qt::UserRole + 1,
	InfoRole = Qt::UserRole + 2,
	FinishedRole = Qt::UserRole + 3,
	HeadersRole = Qt::UserRole + 4,
	StatusCodeRole = Qt::UserRole + 5,
	StatusMessageRole = Qt::UserRole + 6
};

class RequestHandler : public QObject
{
	Q_OBJECT

	Q_ENUM(State)

	// TODO remove setters from properties

	Q_PROPERTY(int requestsCount READ requestsCount WRITE setRequestsCount
				   NOTIFY requestsCountChanged)
	Q_PROPERTY(int currentRequest READ currentRequest WRITE setCurrentRequest
				   NOTIFY currentRequestChanged)
	Q_PROPERTY(int state READ state WRITE setState NOTIFY stateChanged)

	Q_PROPERTY(int singleElapsed READ singleElapsed WRITE setSingleElapsed
				   NOTIFY singleElapsedChanged)
	Q_PROPERTY(QString singleInfo READ singleInfo WRITE setSingleInfo NOTIFY
				   singleInfoChanged)
	Q_PROPERTY(bool singleFinished READ singleFinished WRITE setSingleFinished
				   NOTIFY singleFinishedChanged)
	Q_PROPERTY(QString singleHeaders READ singleHeaders WRITE setSingleHeaders
				   NOTIFY singleHeadersChanged)
	Q_PROPERTY(int singleStatusCode READ singleStatusCode WRITE
				   setSingleStatusCode NOTIFY singleStatusCodeChanged)
	Q_PROPERTY(QString singleStatusMessage READ singleStatusMessage WRITE
				   setSingleStatusMessage NOTIFY singleStatusMessageChanged)

	Requester m_requester;
	QmlModel *m_model;

	RequesterInput setupRequester();
	void setupRequesterProxy(RequesterInput &Input);
	void setupRequesterPost(RequesterInput &Input);
	void setupRequesterHeader(RequesterInput &Input);
	void setupRequesterUrl(RequesterInput &Input);

	int m_state;
	int m_requestsCount;
	int m_currentRequest;

	int m_singleElapsed;
	QString m_singleInfo;
	bool m_singleFinished;
	QString m_singleHeaders;
	int m_singleStatusCode;
	QString m_singleStatusMessage;

private slots:
	void requestDone();

public:
	static RequestHolder *Holder;

	explicit RequestHandler(QObject *parent = nullptr);

	int state() const;
	int requestsCount() const;
	int currentRequest() const;

	int singleElapsed() const;
	QString singleInfo() const;
	bool singleFinished() const;
	QString singleHeaders() const;
	int singleStatusCode() const;
	QString singleStatusMessage() const;

	QmlModel *model() const;

public slots:
	void begin();
	void setTopColor(const QColor &color);

	void setState(int state);
	void setRequestsCount(int requestsCount);
	void setCurrentRequest(int currentRequest);

	void setSingleElapsed(int singleElapsed);
	void setSingleInfo(QString singleInfo);
	void setSingleFinished(bool singleFinished);
	void setSingleHeaders(QString singleHeaders);
	void setSingleStatusCode(int singleStatusCode);
	void setSingleStatusMessage(QString singleStatusMessage);

signals:
	void stateChanged(int state);
	void requestsCountChanged(int requestsCount);
	void currentRequestChanged(int currentRequest);

	void singleElapsedChanged(int singleElapsed);
	void singleInfoChanged(QString singleInfo);  // TODO: remove args?
	void singleFinishedChanged(bool singleFinished);
	void singleHeadersChanged(QString singleHeaders);
	void singleStatusCodeChanged(int singleStatusCode);
	void singleStatusMessageChanged(QString singleStatusMessage);
};

#endif  // REQUESTHANDLER_H
