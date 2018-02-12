#ifndef REQUESTHOLDER_H
#define REQUESTHOLDER_H

#include "model.h"

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

	Q_PROPERTY(bool hasPostData READ hasPostData WRITE setHasPostData NOTIFY
				   hasPostDataChanged)

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

	QmlModel *m_postModel;

	bool m_addressType;
	QString m_addressUrl;
	QString m_addressIp;
	QString m_addressPort;
	bool m_hasPostData;
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

public:
	explicit RequestHolder(QObject *parent = nullptr);

	QmlModel *postModel() const;

	bool addressType() const;
	QString addressUrl() const;
	QString addressIp() const;
	QString addressPort() const;
	bool hasPostData() const;
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

public slots:
	void reset();

	void setAddressType(bool addressType);
	void setAddressUrl(const QString &addressUrl);
	void setAddressIp(const QString &addressIp);
	void setAddressPort(const QString &addressPort);
	void setHasPostData(bool hasPostData);
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

signals:
	void addressTypeChanged(bool addressType);
	void addressUrlChanged(QString addressUrl);
	void addressIpChanged(QString addressIp);
	void addressPortChanged(QString addressPort);
	void hasPostDataChanged(bool hasPostData);
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
};

#endif  // REQUESTHOLDER_H
