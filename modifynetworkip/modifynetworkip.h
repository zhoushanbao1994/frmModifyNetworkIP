#ifndef MODIFYNETWORKIP_H
#define MODIFYNETWORKIP_H

#include <QObject>
#include <QProcess>
#include <QThread>

class ModifyNetworkIP : public QObject
{
    Q_OBJECT
public:
    explicit ModifyNetworkIP(QObject *parent = nullptr);
    explicit ModifyNetworkIP(QString name, quint32 ipAddr, quint32 netmask, quint32 gateway, QObject *parent = nullptr);
    void setParameter(QString name, quint32 ipAddr);  // 设置参数
    void setParameter(QString name, quint32 ipAddr, quint32 netmask, quint32 gateway);  // 设置参数
    void executeComman();

signals: //信号
    void signal_modifIpOk(QString name, quint32 ipAddr, int s);           // 修改IP OK

private:
    QString m_name;          // 网络名称
    quint32 m_ipAddr;        // IP地址
    quint32 m_netmask;       // 子网掩码
    quint32 m_gateway;       // 网关
};

#endif // MODIFYNETWORKIP_H
