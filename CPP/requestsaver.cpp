#include "requestsaver.h"

RequestHolder *RequestSaver::Holder = nullptr;

RequestSaver::RequestSaver(QObject *parent) : QObject(parent)
{
	m_model = new QmlModel(this);
	m_model->addRoles(
		{Add(IDRole), Add(TitleRole), Add(DescRole), Add(TimeRole)});

	// TODO correct this

	auto sep = QDir::separator();
	auto dataPath = QSP::writableLocation(QSP::AppDataLocation);

	if (!QDir(dataPath).exists() && !QDir().mkdir(dataPath))
		qCritical() << "failed to create data directory";

	m_tempDir = dataPath;
	m_databasePath = dataPath + sep + "database";

	createDatabase();
	createTables();
	fillModel();
}

RequestSaver::~RequestSaver() { delete m_query; }

void RequestSaver::saveRequest()
{
	auto rid = saveRequestTable();
	auto gid = saveGeneralTable();
	auto prid = saveProxyTable();
	savePostTable(rid);
	saveHeaderTable(rid);

	QString name = !Holder->requestName().isEmpty()
					   ? Holder->requestName()
					   : (!Holder->addressType() ? Holder->addressUrl()
												 : Holder->addressIp() + ":" +
													   Holder->addressPort());

	auto epoch = QDateTime::currentSecsSinceEpoch();

	m_query->prepare("INSERT INTO main VALUES(?, ?, ?, ?, ?);");
	m_query->bindValue(0, name);
	m_query->bindValue(1, rid);
	m_query->bindValue(2, gid);
	m_query->bindValue(3, prid);
	m_query->bindValue(4, epoch);
	m_query->exec();

	auto id = m_query->lastInsertId().toInt();
	auto time = QDateTime::fromSecsSinceEpoch(epoch).toString();

	auto *item = new QStandardItem;
	item->setData(id, IDRole);
	item->setData(name, TitleRole);
	item->setData(time, TimeRole);
	m_model->insertRow(0, item);
}

void RequestSaver::loadRequest(int id)
{
	m_query->prepare("SELECT * FROM main WHERE rowid=?;");
	m_query->bindValue(0, id);
	m_query->exec();

	if (!m_query->first())
	{
		qDebug() << "Couldn't Load Main Info";
		return;
	}

	auto R = m_query->record();
	int rid = R.value("rid").toInt();
	int gid = R.value("gid").toInt();
	int prid = R.value("prid").toInt();

	loadRequestTable(rid);
	loadGeneralTable(gid);
	loadProxyTable(prid);
	loadPostTable(rid);
	loadHeaderTable(rid);
}

QmlModel *RequestSaver::model() const { return m_model; }

QString RequestSaver::tempFilePath()
{
	auto path = m_tempDir;
	auto sep = QDir::separator();
	if (!path.endsWith(sep)) path += sep;

	path += "temp.html";
	return path;
}

void RequestSaver::saveToFile(const QString &content)
{
	QFile F(tempFilePath());
	auto x = F.open(QIODevice::WriteOnly);
	if (!x) qDebug() << "Failed to open file for writing";

	F.write(content.toUtf8());
	F.flush();
	F.close();
}

void RequestSaver::createTables()
{
	m_query = new QSqlQuery(m_database);

	bool x = m_query->exec(
		"CREATE TABLE IF NOT EXISTS main("
		"name STRING, rid INTEGER, gid INTEGER, "
		"prid INTEGER, time INTEGER);");
	if (!x) qDebug() << "Couldn't Create Main Table;";

	x = m_query->exec(
		"CREATE TABLE IF NOT EXISTS request("
		"type INTEGER, url STRING, ip STRING, port STRING);");
	if (!x) qDebug() << "Couldn't Create Request Table;";

	x = m_query->exec(
		"CREATE TABLE IF NOT EXISTS general("
		"name STRING, desc STRING, count INTEGER, "
		"timeout INTEGER, rtype INTEGER, putdata STRING);");
	if (!x) qDebug() << "Couldn't Create General Table;";

	x = m_query->exec(
		"CREATE TABLE IF NOT EXISTS proxy("
		"type INTEGER, host STRING, port STRING, "
		"hasuser INTEGER, user STRING, pass STRING);");
	if (!x) qDebug() << "Couldn't Create Proxy Table;";

	x = m_query->exec(
		"CREATE TABLE IF NOT EXISTS post("
		"rid INTEGER, key STRING, value STRING);");
	if (!x) qDebug() << "Couldn't Create Post Table;";

	x = m_query->exec(
		"CREATE TABLE IF NOT EXISTS header("
		"rid INTEGER, key STRING, value STRING);");
	if (!x) qDebug() << "Couldn't Create Header Table;";
}

void RequestSaver::createDatabase()
{
	m_database = QSqlDatabase::addDatabase("QSQLITE");
	m_database.setDatabaseName(m_databasePath);
	if (!m_database.open()) qDebug() << "Couldn't Create Database";
}

int RequestSaver::saveRequestTable()
{
	m_query->prepare("INSERT INTO request VALUES(?, ?, ?, ?);");

	m_query->bindValue(0, Holder->addressType());
	m_query->bindValue(1, Holder->addressUrl());
	m_query->bindValue(2, Holder->addressIp());
	m_query->bindValue(3, Holder->addressPort());

	m_query->exec();
	return m_query->lastInsertId().toInt();
}

int RequestSaver::saveGeneralTable()
{
	m_query->prepare("INSERT INTO general VALUES(?, ?, ?, ?, ?, ?);");

	m_query->bindValue(0, Holder->requestName());
	m_query->bindValue(1, Holder->requestDescription());
	m_query->bindValue(2, Holder->requestCount());
	m_query->bindValue(3, Holder->requestTimeout());
	m_query->bindValue(4, Holder->requestType());
	m_query->bindValue(5, Holder->putData());

	m_query->exec();
	return m_query->lastInsertId().toInt();
}

int RequestSaver::saveProxyTable()
{
	m_query->prepare("INSERT INTO proxy VALUES(?, ?, ?, ?, ?, ?);");

	m_query->bindValue(0, Holder->proxyType());
	m_query->bindValue(1, Holder->proxyHost());
	m_query->bindValue(2, Holder->proxyPort());
	m_query->bindValue(3, Holder->proxyHasUser());
	m_query->bindValue(4, Holder->proxyUsername());
	m_query->bindValue(5, Holder->proxyPassword());

	m_query->exec();
	return m_query->lastInsertId().toInt();
}

void RequestSaver::saveHeaderTable(int rid)
{
	auto *model = Holder->headerModel();
	if (!model->rowCount()) return;

	QVariantList rids;
	QVariantList keys;
	QVariantList values;

	for (int i = 0; i < model->rowCount(); ++i)
	{
		auto *item = model->item(i);

		rids << rid;
		keys << item->data(NameRole);
		values << item->data(DataRole);
	}

	m_query->exec("BEGIN TRANSACTION;");

	m_query->prepare("INSERT INTO header VALUES(?, ?, ?);");
	m_query->bindValue(0, rids);
	m_query->bindValue(1, keys);
	m_query->bindValue(2, values);

	m_query->execBatch();
	m_query->exec("COMMIT;");
}

void RequestSaver::savePostTable(int rid)
{
	auto *model = Holder->postModel();
	if (!model->rowCount()) return;

	QVariantList rids;
	QVariantList keys;
	QVariantList values;

	for (int i = 0; i < model->rowCount(); ++i)
	{
		auto *item = model->item(i);

		rids << rid;
		keys << item->data(NameRole);
		values << item->data(DataRole);
	}

	m_query->exec("BEGIN TRANSACTION;");

	m_query->prepare("INSERT INTO post VALUES(?, ?, ?);");
	m_query->bindValue(0, rids);
	m_query->bindValue(1, keys);
	m_query->bindValue(2, values);

	m_query->execBatch();
	m_query->exec("COMMIT;");
}

void RequestSaver::loadRequestTable(int rid)
{
	m_query->prepare("SELECT * FROM request WHERE rowid=?;");
	m_query->bindValue(0, rid);
	m_query->exec();

	if (!m_query->first())
	{
		qDebug() << "Couldn't Load Request Info";
		return;
	}

	auto R = m_query->record();
	Holder->setAddressType(R.value("type").toInt());
	Holder->setAddressUrl(R.value("url").toString());
	Holder->setAddressIp(R.value("ip").toString());
	Holder->setAddressPort(R.value("port").toString());
}

void RequestSaver::loadGeneralTable(int gid)
{
	m_query->prepare("SELECT * FROM general WHERE rowid=?;");
	m_query->bindValue(0, gid);
	m_query->exec();

	if (!m_query->first())
	{
		qDebug() << "Couldn't Load General Info";
		return;
	}

	auto R = m_query->record();
	Holder->setRequestName(R.value("name").toString());
	Holder->setRequestDescription(R.value("desc").toString());
	Holder->setRequestCount(R.value("count").toInt());
	Holder->setRequestTimeout(R.value("timeout").toInt());
	Holder->setRequestType(R.value("rtype").toInt());
	Holder->setPutData(R.value("putdata").toByteArray());
}

void RequestSaver::loadProxyTable(int pid)
{
	m_query->prepare("SELECT * FROM proxy WHERE rowid=?;");
	m_query->bindValue(0, pid);
	m_query->exec();

	if (!m_query->first())
	{
		qDebug() << "Couldn't Load Proxy Info";
		return;
	}

	auto R = m_query->record();
	Holder->setProxyType(R.value("type").toInt());
	Holder->setProxyHost(R.value("host").toString());
	Holder->setProxyPort(R.value("port").toString());
	Holder->setProxyHasUser(R.value("hasuser").toInt());
	Holder->setProxyUsername(R.value("user").toString());
	Holder->setProxyPassword(R.value("pass").toString());
}

void RequestSaver::loadPostTable(int rid)
{
	m_query->prepare("SELECT * FROM post WHERE rid=? ORDER BY rowid ASC;");
	m_query->bindValue(0, rid);
	m_query->exec();

	auto *model = Holder->postModel();
	model->clear();

	while (m_query->next())
	{
		auto R = m_query->record();
		auto *item = new QStandardItem;

		item->setData(R.value("key"), NameRole);
		item->setData(R.value("value"), DataRole);

		model->appendRow(item);
	}
}

void RequestSaver::loadHeaderTable(int rid)
{
	m_query->prepare("SELECT * FROM header WHERE rid=? ORDER BY rowid ASC;");
	m_query->bindValue(0, rid);
	m_query->exec();

	auto *model = Holder->headerModel();
	model->clear();

	while (m_query->next())
	{
		auto R = m_query->record();
		auto *item = new QStandardItem;

		item->setData(R.value("key"), NameRole);
		item->setData(R.value("value"), DataRole);

		model->appendRow(item);
	}

	Holder->setHasHeader(model->rowCount());
}

void RequestSaver::fillModel()
{
	m_model->clear();

	m_query->exec(
		"SELECT rowid,name,time FROM main ORDER BY rowid DESC Limit 100;");

	while (m_query->next())
	{
		auto R = m_query->record();
		auto *item = new QStandardItem;
		auto time = QDateTime::fromSecsSinceEpoch(R.value("time").toLongLong())
						.toString();

		item->setData(R.value("rowid"), IDRole);
		item->setData(R.value("name"), TitleRole);
		item->setData(time, TimeRole);

		m_model->appendRow(item);
	}
}
