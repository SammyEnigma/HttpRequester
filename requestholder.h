#ifndef REQUESTHOLDER_H
#define REQUESTHOLDER_H

#include <QObject>

class RequestHolder : public QObject
{
	Q_OBJECT
public:
	explicit RequestHolder(QObject *parent = nullptr);

signals:

public slots:
};

#endif // REQUESTHOLDER_H