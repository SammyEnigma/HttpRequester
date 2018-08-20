#ifndef REQUESTHOLDER_H
#define REQUESTHOLDER_H

#include "model.h"

#include <QFile>
#include <QObject>

enum PostRoles
{
	NameRole = Qt::UserRole + 1,
	DataRole = Qt::UserRole + 2
};

class RequestHolder : public QObject
{
	Q_OBJECT

	Q_PROPERTY(bool addressType READ addressType WRITE setAddressType NOTIFY
				   addressTypeChanged)

	Q_PROPERTY(QString addressUrl READ addressUrl WRITE setAddressUrl NOTIFY
				   addressUrlChanged)

	Q_PROPERTY(QString addressIp READ addressIp WRITE setAddressIp NOTIFY
				   addressIpChanged)

	Q_PROPERTY(QString addressPort READ addressPort WRITE setAddressPort NOTIFY
				   addressPortChanged)

	Q_PROPERTY(int requestType READ requestType WRITE setRequestType NOTIFY
				   requestTypeChanged)

	Q_PROPERTY(
		int proxyType READ proxyType WRITE setProxyType NOTIFY proxyTypeChanged)

	Q_PROPERTY(QString proxyHost READ proxyHost WRITE setProxyHost NOTIFY
				   proxyHostChanged)

	Q_PROPERTY(QString proxyPort READ proxyPort WRITE setProxyPort NOTIFY
				   proxyPortChanged)

	Q_PROPERTY(QString proxyUsername READ proxyUsername WRITE setProxyUsername
				   NOTIFY proxyUsernameChanged)

	Q_PROPERTY(QString proxyPassword READ proxyPassword WRITE setProxyPassword
				   NOTIFY proxyPasswordChanged)

	Q_PROPERTY(bool proxyHasUser READ proxyHasUser WRITE setProxyHasUser NOTIFY
				   proxyHasUserChanged)

	Q_PROPERTY(int requestCount READ requestCount WRITE setRequestCount NOTIFY
				   requestCountChanged)

	Q_PROPERTY(int requestTimeout READ requestTimeout WRITE setRequestTimeout
				   NOTIFY requestTimeoutChanged)

	Q_PROPERTY(QString requestName READ requestName WRITE setRequestName NOTIFY
				   requestNameChanged)

	Q_PROPERTY(QString requestDescription READ requestDescription WRITE
				   setRequestDescription NOTIFY requestDescriptionChanged)

	Q_PROPERTY(bool hasHeader READ hasHeader WRITE setHasHeader NOTIFY
				   hasHeaderChanged)

	Q_PROPERTY(
		QByteArray putData READ putData WRITE setPutData NOTIFY putDataChanged)

	QmlModel *m_postModel;
	QmlModel *m_headerModel;

	bool m_addressType;
	QString m_addressUrl;
	QString m_addressIp;
	QString m_addressPort;
	int m_proxyType;
	QString m_proxyHost;
	QString m_proxyPort;
	QString m_proxyUsername;
	QString m_proxyPassword;
	int m_requestCount;
	int m_requestTimeout;
	QString m_requestName;
	QString m_requestDescription;
	bool m_proxyHasUser;
	bool m_hasHeader;
	int m_requestType;
	QByteArray m_putData;

public:
	explicit RequestHolder(QObject *parent = nullptr);

	QmlModel *postModel() const;
	QmlModel *headerModel() const;

	bool addressType() const;
	QString addressUrl() const;
	QString addressIp() const;
	QString addressPort() const;
	int proxyType() const;
	QString proxyHost() const;
	QString proxyPort() const;
	QString proxyUsername() const;
	QString proxyPassword() const;
	int requestCount() const;
	int requestTimeout() const;
	QString requestName() const;
	QString requestDescription() const;
	bool proxyHasUser() const;
	bool hasHeader() const;
	int requestType() const;
	QByteArray putData() const;

public slots:
	void reset();
	void removePostParameter(int index);
	void addPostParameter(const QString &key, const QString &value);

	void removeHeader(int index);
	void addHeader(const QString &key, const QString &value);

	void readPutDataFromFile(QString file);

	void setAddressType(bool addressType);
	void setAddressUrl(const QString &addressUrl);
	void setAddressIp(const QString &addressIp);
	void setAddressPort(const QString &addressPort);
	void setProxyType(int proxyType);
	void setProxyHost(const QString &proxyHost);
	void setProxyPort(const QString &proxyPort);
	void setProxyUsername(const QString &proxyUsername);
	void setProxyPassword(const QString &proxyPassword);
	void setRequestCount(int requestCount);
	void setRequestTimeout(int requestTimeout);
	void setRequestName(QString requestName);
	void setRequestDescription(QString requestDescription);
	void setProxyHasUser(bool proxyHasUser);
	void setHasHeader(bool hasHeader);
	void setRequestType(int requestType);
	void setPutData(const QByteArray &putData);

signals:
	void addressTypeChanged(bool addressType);
	void addressUrlChanged(QString addressUrl);
	void addressIpChanged(QString addressIp);
	void addressPortChanged(QString addressPort);
	void proxyTypeChanged(int proxyType);
	void proxyHostChanged(QString proxyHost);
	void proxyPortChanged(QString proxyPort);
	void proxyUsernameChanged(QString proxyUsername);
	void proxyPasswordChanged(QString proxyPassword);
	void requestCountChanged(int requestCount);
	void requestTimeoutChanged(int requestTimeout);
	void requestNameChanged(QString requestName);
	void requestDescriptionChanged(QString requestDescription);
	void proxyHasUserChanged(bool proxyHasUser);
	void hasHeaderChanged(bool hasHeader);
	void requestTypeChanged(int requestType);
	void putDataChanged(QByteArray putData);
};

#endif  // REQUESTHOLDER_H
