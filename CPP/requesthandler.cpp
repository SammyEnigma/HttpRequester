#include "requesthandler.h"

RequestHolder *RequestHandler::Holder = nullptr;

RequestHandler::RequestHandler(QObject *parent) : QObject(parent) {}
