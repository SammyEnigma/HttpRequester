#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H

#include "requester.h"
#include "requestholder.h"

#include <QObject>

enum RequestRoles
{
	ElapsedRole = Qt::UserRole + 1,
	InfoRole = Qt::UserRole + 2,
	FinishedRole = Qt::UserRole + 3
};

class RequestHandler : public QObject
{
	Q_OBJECT

	Q_ENUM(State)

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

	Requester m_requester;
	QmlModel *m_model;

	void setupRequester();
	void setupRequesterProxy();
	void setupRequesterPost();
	void setupRequesterUrl();

	int m_requestsCount;
	int m_currentRequest;
	int m_state;
	int m_singleElapsed;
	QString m_singleInfo;
	bool m_singleFinished;

private slots:
	void requestDone();

public:
	static RequestHolder *Holder;

	explicit RequestHandler(QObject *parent = nullptr);

	int requestsCount() const;
	int currentRequest() const;
	int state() const;
	int singleElapsed() const;
	QString singleInfo() const;
	bool singleFinished() const;

	QmlModel *model() const;

public slots:
	void begin();

	void setRequestsCount(int requestsCount);
	void setCurrentRequest(int currentRequest);
	void setState(int state);
	void setSingleElapsed(int singleElapsed);
	void setSingleInfo(QString singleInfo);
	void setSingleFinished(bool singleFinished);

signals:
	void requestsCountChanged(int requestsCount);
	void currentRequestChanged(int currentRequest);
	void stateChanged(int state);
	void singleElapsedChanged(int singleElapsed);
	void singleInfoChanged(QString singleInfo);  // TODO: remove args?
	void singleFinishedChanged(bool singleFinished);
};

#endif  // REQUESTHANDLER_H
