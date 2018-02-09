#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H

#include "requestholder.h"

#include <QObject>

class RequestHandler : public QObject
{
	Q_OBJECT

public:
	static RequestHolder *Holder;

	explicit RequestHandler(QObject *parent = nullptr);
};

#endif  // REQUESTHANDLER_H
