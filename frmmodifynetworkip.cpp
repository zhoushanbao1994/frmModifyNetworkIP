#include "frmmodifynetworkip.h"
#include "ui_frmmodifynetworkip.h"
#include <QHostAddress>
#include <QNetworkInterface>

frmModifyNetworkIP::frmModifyNetworkIP(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::frmModifyNetworkIP)
{
    ui->setupUi(this);

    this->getNetworkInterface();    // 获取本机网络信息

    ui->lineEdit_ip->setText("192.168.1.253");
    ui->lineEdit_mask->setText("255.255.255.0");
    ui->lineEdit_gateway->setText("");

    m_mnip = new ModifyNetworkIP();
    m_mnip->setParameter(QString("以太网"), QHostAddress("192.168.1.250").toIPv4Address());
    QObject::connect(m_mnip, &ModifyNetworkIP::signal_modifIpOk,
                     [&](QString name, quint32 ip, quint32 s) {
        QString str = name + " " + QHostAddress(ip).toString() + " " + QString::number(s);
        qDebug() << str;
        ui->label->setText(str);
    });
}

frmModifyNetworkIP::~frmModifyNetworkIP()
{
    delete ui;
}

void frmModifyNetworkIP::getNetworkInterface()    // 获取本机网络信息
{
    QList<QNetworkInterface> ifaceList = QNetworkInterface::allInterfaces();
    for (int i = 0; i < ifaceList.count(); i++)
    {
        QNetworkInterface var = ifaceList.at(i);
        ui->comboBox->addItem(var.humanReadableName());
        qDebug() << (QString("############################## 设备%1 ################################").arg(i));
        qDebug() << (QString("接口名称：%1").arg(var.humanReadableName()));
        qDebug() << (QString("设备名称：%1").arg(var.name()));
        qDebug() << (QString("硬件地址：%1").arg(var.hardwareAddress()));

        qDebug() << (QString("IP地址列表："));
        // 读取一个IP地址的关联信息列表
        QList<QNetworkAddressEntry> entryList = var.addressEntries();
        for(int j = 0; j < entryList.count(); j++)
        {
            QNetworkAddressEntry entry = entryList.at(j);
            qDebug() << (QString("  %1_地址：").arg(j));
            qDebug() << (QString("    IP地址：%1").arg(entry.ip().toString()));
            qDebug() << (QString("    子网掩码：%1").arg(entry.netmask().toString()));
            qDebug() << (QString("    广播地址：%1").arg(entry.broadcast().toString()));
        }
    }
}

void frmModifyNetworkIP::on_pushButton_clicked()
{
    ui->label->setText("");

    QString name    = ui->comboBox->currentText();
    QString ip      = ui->lineEdit_ip->text();
    QString mask    = ui->lineEdit_mask->text();
    QString gateway = ui->lineEdit_gateway->text();
    qDebug() << name << ip << mask << gateway;

    m_mnip->setParameter(QString(name),
                         QHostAddress(ip).toIPv4Address(),
                         QHostAddress(mask).toIPv4Address(),
                         QHostAddress(gateway).toIPv4Address());
    m_mnip->executeComman();
}
