#ifndef REQUESTSAVER_H
#define REQUESTSAVER_H

#include "requestholder.h"

#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QObject>
#include <QStandardPaths>
#include <QtSql>

using QSP = QStandardPaths;

enum ListRoles
{
	IDRole = Qt::UserRole + 1,
	TitleRole = Qt::UserRole + 2,
	DescRole = Qt::UserRole + 3,
	TimeRole = Qt::UserRole + 4
};

class RequestSaver : public QObject
{
	Q_OBJECT

	QmlModel *m_model;
	QSqlQuery *m_query;
	QSqlDatabase m_database;

	QString m_tempDir;
	QString m_databasePath;

	void createTables();
	void createDatabase();

	int saveRequestTable();
	int saveGeneralTable();
	int saveProxyTable();
	void saveHeaderTable(int rid);
	void savePostTable(int rid);

	void loadRequestTable(int rid);
	void loadGeneralTable(int gid);
	void loadProxyTable(int pid);
	void loadPostTable(int rid);
	void loadHeaderTable(int rid);

	void fillModel();
	QString tempFilePath();

public:
	static RequestHolder *Holder;

	explicit RequestSaver(QObject *parent = nullptr);
	~RequestSaver();

	QmlModel *model() const;

public slots:
	void saveToFile(const QString &content);

	void saveRequest();
	void loadRequest(int id);
};

#endif  // REQUESTSAVER_H
