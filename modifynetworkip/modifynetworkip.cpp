#include "modifynetworkip.h"
#include <QDebug>
#include <QHostAddress>
#include <QThread>

ModifyNetworkIP::ModifyNetworkIP(QObject *parent) :
    QObject(parent)
{
}
ModifyNetworkIP::ModifyNetworkIP(QString name, quint32 ipAddr, quint32 netmask, quint32 gateway, QObject *parent) :
    QObject(parent)
{
    m_name = name;
    m_ipAddr = ipAddr;
    m_netmask = netmask;
    m_gateway = gateway;
}

void ModifyNetworkIP::setParameter(QString name, quint32 ipAddr)  // 设置参数
{
    qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << name << QHostAddress(ipAddr).toString() ;

    m_name = name;                                              // 网络名称
    m_ipAddr = ipAddr;                                          // IP地址
    m_netmask = QHostAddress("255.255.255.0").toIPv4Address();  // 子网掩码
    m_gateway = 0;                                              // 子网掩码
}
void ModifyNetworkIP::setParameter(QString name, quint32 ipAddr, quint32 netmask, quint32 gateway)  // 设置参数
{
    qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << name << QHostAddress(ipAddr).toString() << netmask << gateway;

    m_name = name;          // 网络名称
    m_ipAddr = ipAddr;      // IP地址
    m_netmask = netmask;    // 子网掩码
    m_gateway = gateway;    // 子网掩码
}

void ModifyNetworkIP::executeComman()          // 执行命令
{
    QProcess cmd(this);

    QString qstrName = m_name;                                 // 网络名称
    QString qstrAddr = QHostAddress(m_ipAddr).toString();      // IP地址
    QString qstrNetmask = QHostAddress(m_netmask).toString();  // 子网掩码
    QString qstrGateway = (m_gateway!=0) ? QHostAddress(m_gateway).toString() : "";  // 网关
    qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << qstrName << qstrAddr << qstrNetmask << qstrGateway;

    // netsh interface ipv4 set address name = "以太网" source = static
    // address = 192.168.0.106 mask = 255.255.255.0 gateway = 192.168.0.1 gwmetric = 0
    QString command = "netsh interface ipv4 set address name = \""
        + qstrName + "\" source = static address = " + qstrAddr
        + " mask = " + qstrNetmask + " gateway = " + qstrGateway;
    // 执行命令
    cmd.start(command);
    if(cmd.waitForFinished()) {
        emit signal_modifIpOk(m_name, m_ipAddr, 1);     // 发送执行结果
    }
    else {
        emit signal_modifIpOk(m_name, m_ipAddr, 0);     // 发送执行结果
    }
}

