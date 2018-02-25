#include <QGuiApplication>
#include <QNetworkProxy>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQuickControls2/QQuickStyle>

#include <CPP/requesthandler.h>
#include <CPP/requestholder.h>
#include <CPP/requestsaver.h>

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

	RequestSaver Saver;
	RequestHolder Holder;
	RequestHandler Handler;

	RequestSaver::Holder = &Holder;
	RequestHandler::Holder = &Holder;

	QGuiApplication app(argc, argv);
	QQuickStyle::setStyle("Material");

	QQmlApplicationEngine engine;

	auto R = engine.rootContext();

	R->setContextProperty("RequestHolder", &Holder);
	R->setContextProperty("RequestHandler", &Handler);
	R->setContextProperty("RequestSaver", &Saver);

	R->setContextProperty("RequestSaverModel", Saver.model());
	R->setContextProperty("RequestHolderPostModel", Holder.postModel());
	R->setContextProperty("RequestHandlerModel", Handler.model());

	engine.load(QUrl(QStringLiteral("qrc:/QML/main.qml")));
	if (engine.rootObjects().isEmpty()) return -1;

	return app.exec();
}
