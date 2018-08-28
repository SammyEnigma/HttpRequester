#include <QGuiApplication>
#include <QNetworkProxy>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <QtQuickControls2/QQuickStyle>
#include <QtWebView/QtWebView>

#include <CPP/requesthandler.h>
#include <CPP/requestholder.h>
#include <CPP/requestsaver.h>

// TODO add the option of saving the response data
// TODO save temp file with the right suffix

int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

	qRegisterMetaType<QList<QStringList>>("QList<QStringList>");

	QGuiApplication app(argc, argv);
	app.setWindowIcon(QIcon(":/Images/icon.png"));

	QQuickStyle::setStyle("Material");
	QtWebView::initialize();

	RequestSaver Saver;
	RequestHolder Holder;
	RequestHandler Handler;

	RequestSaver::Holder = &Holder;
	RequestHandler::Holder = &Holder;

	app.setApplicationName("HttpRequester");
	app.setOrganizationName("HttpRequester");
	app.setApplicationVersion("0.90");

	QQmlApplicationEngine engine;
	auto R = engine.rootContext();

	R->setContextProperty("RequestHolder", &Holder);
	R->setContextProperty("RequestHandler", &Handler);
	R->setContextProperty("RequestSaver", &Saver);

	R->setContextProperty("RequestSaverModel", Saver.model());
	R->setContextProperty("RequestHolderPostModel", Holder.postModel());
	R->setContextProperty("RequestHolderHeaderModel", Holder.headerModel());
	R->setContextProperty("RequestHandlerModel", Handler.model());

	engine.load(QUrl(QStringLiteral("qrc:/QML/Main/main.qml")));
	if (engine.rootObjects().isEmpty()) return -1;

	return app.exec();
}
