#ifndef STRUCTS_H
#define STRUCTS_H

#include <QHash>

enum RequestType
{
	GetRequest,
	HeadRequest,
	DeleteRequest,
	PostRequest,
	PutRequest
};

class RequesterInput
{
public:
	RequesterInput() { requestType = 0; }

	QString url;
	int requestType;

	QByteArray putData;
	QHash<QByteArray, QByteArray> headers;
	QHash<QByteArray, QByteArray> postData;
};

class RequesterOutput
{
public:
	RequesterOutput()
	{
		elapsed = 0;
		done = false;
		statusCode = -1;
	}

	bool done;  // true for success. false for failure
	int elapsed;
	int statusCode;

	QByteArray data;
	QString replyHeaders;
	QString statusMessage;
};

#endif  // STRUCTS_H
