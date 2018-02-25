#include "requestholder.h"

RequestHolder::RequestHolder(QObject *parent) : QObject(parent)
{
	m_postModel = new QmlModel(this);
	m_postModel->addRoles({Add(NameRole), Add(DataRole)});
	reset();
}

void RequestHolder::setAddressType(bool addressType)
{
	if (m_addressType == addressType) return;

	m_addressType = addressType;
	emit addressTypeChanged(m_addressType);
}

void RequestHolder::setAddressUrl(const QString &addressUrl)
{
	if (m_addressUrl == addressUrl) return;

	m_addressUrl = addressUrl;
	emit addressUrlChanged(m_addressUrl);
}

void RequestHolder::setAddressIp(const QString &addressIp)
{
	if (m_addressIp == addressIp) return;

	m_addressIp = addressIp;
	emit addressIpChanged(m_addressIp);
}

void RequestHolder::setAddressPort(const QString &addressPort)
{
	if (m_addressPort == addressPort) return;

	m_addressPort = addressPort;
	emit addressPortChanged(m_addressPort);
}

void RequestHolder::setHasPostData(bool hasPostData)
{
	if (m_hasPostData == hasPostData) return;

	m_hasPostData = hasPostData;
	emit hasPostDataChanged(m_hasPostData);
}

void RequestHolder::setProxyType(int proxyType)
{
	if (m_proxyType == proxyType) return;

	m_proxyType = proxyType;
	emit proxyTypeChanged(m_proxyType);
}

void RequestHolder::setProxyHost(const QString &proxyHost)
{
	if (m_proxyHost == proxyHost) return;

	m_proxyHost = proxyHost;
	emit proxyHostChanged(m_proxyHost);
}

void RequestHolder::setProxyPort(const QString &proxyPort)
{
	if (m_proxyPort == proxyPort) return;

	m_proxyPort = proxyPort;
	emit proxyPortChanged(m_proxyPort);
}

void RequestHolder::setProxyUsername(const QString &proxyUsername)
{
	if (m_proxyUsername == proxyUsername) return;

	m_proxyUsername = proxyUsername;
	emit proxyUsernameChanged(m_proxyUsername);
}

void RequestHolder::setProxyPassword(const QString &proxyPassword)
{
	if (m_proxyPassword == proxyPassword) return;

	m_proxyPassword = proxyPassword;
	emit proxyPasswordChanged(m_proxyPassword);
}

void RequestHolder::setRequestCount(int requestCount)
{
	if (m_requestCount == requestCount) return;

	m_requestCount = requestCount;
	emit requestCountChanged(m_requestCount);
}

void RequestHolder::setRequestTimeout(int requestTimeout)
{
	if (m_requestTimeout == requestTimeout) return;

	m_requestTimeout = requestTimeout;
	emit requestTimeoutChanged(m_requestTimeout);
}

void RequestHolder::setRequestDescription(QString requestDescription)
{
	if (m_requestDescription == requestDescription) return;

	m_requestDescription = requestDescription;
	emit requestDescriptionChanged(m_requestDescription);
}

void RequestHolder::setProxyHasUser(bool proxyHasUser)
{
	if (m_proxyHasUser == proxyHasUser) return;

	m_proxyHasUser = proxyHasUser;
	emit proxyHasUserChanged(m_proxyHasUser);
}

void RequestHolder::setRequestName(QString requestName)
{
	if (m_requestName == requestName) return;

	m_requestName = requestName;
	emit requestNameChanged(m_requestName);
}

void RequestHolder::reset()
{
	setAddressType(false);
	setAddressUrl("");
	setAddressIp("");
	setAddressPort("");
	setHasPostData(false);
	setProxyType(0);
	setProxyHost("");
	setProxyPort("");
	setProxyUsername("");
	setProxyPassword("");
	setRequestCount(1);
	setRequestTimeout(30);
	setRequestName("");
	setRequestDescription("");
	setProxyHasUser(false);
}

void RequestHolder::removePostParameter(int index)
{
	m_postModel->removeRow(index);
}

void RequestHolder::addPostParameter(const QString &key, const QString &value)
{
	QStandardItem *item = new QStandardItem;
	item->setData(key, NameRole);
	item->setData(value, DataRole);
	m_postModel->appendRow(item);
}

QString RequestHolder::requestDescription() const
{
	return m_requestDescription;
}

bool RequestHolder::proxyHasUser() const { return m_proxyHasUser; }
QmlModel *RequestHolder::postModel() const { return m_postModel; }
bool RequestHolder::addressType() const { return m_addressType; }
QString RequestHolder::addressUrl() const { return m_addressUrl; }
QString RequestHolder::addressIp() const { return m_addressIp; }
QString RequestHolder::addressPort() const { return m_addressPort; }
bool RequestHolder::hasPostData() const { return m_hasPostData; }
int RequestHolder::proxyType() const { return m_proxyType; }
QString RequestHolder::proxyHost() const { return m_proxyHost; }
QString RequestHolder::proxyPort() const { return m_proxyPort; }
QString RequestHolder::proxyUsername() const { return m_proxyUsername; }
QString RequestHolder::proxyPassword() const { return m_proxyPassword; }
int RequestHolder::requestCount() const { return m_requestCount; }
int RequestHolder::requestTimeout() const { return m_requestTimeout; }
QString RequestHolder::requestName() const { return m_requestName; }
