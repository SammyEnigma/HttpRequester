#ifndef REQUESTSAVER_H
#define REQUESTSAVER_H

#include "requestholder.h"

#include <QDateTime>
#include <QDebug>
#include <QObject>
#include <QtSql>

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
	QString m_databasePath;
	QSqlDatabase m_database;

	void createTables();
	void createDatabase();

	int saveRequestTable();
	int saveGeneralTable();
	int saveProxyTable();
	void savePostTable(int rid);

	void loadRequestTable(int rid);
	void loadGeneralTable(int gid);
	void loadProxyTable(int pid);
	void loadPostTable(int rid);

	void fillModel();

public:
	static RequestHolder *Holder;

	explicit RequestSaver(QObject *parent = nullptr);
	~RequestSaver();

	QmlModel *model() const;

public slots:
	void saveRequest();
	void loadRequest(int id);
};

#endif  // REQUESTSAVER_H
