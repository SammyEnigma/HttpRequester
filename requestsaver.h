#ifndef REQUESTSAVER_H
#define REQUESTSAVER_H

#include <QObject>

class RequestSaver : public QObject
{
	Q_OBJECT
public:
	explicit RequestSaver(QObject *parent = nullptr);

signals:

public slots:
};

#endif // REQUESTSAVER_H