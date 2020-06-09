#ifndef FRMMODIFYNETWORKIP_H
#define FRMMODIFYNETWORKIP_H

#include <QDialog>
#include "modifynetworkip.h"

QT_BEGIN_NAMESPACE
namespace Ui { class frmModifyNetworkIP; }
QT_END_NAMESPACE

class frmModifyNetworkIP : public QDialog
{
    Q_OBJECT

public:
    frmModifyNetworkIP(QWidget *parent = nullptr);
    ~frmModifyNetworkIP();

private slots:
    void on_pushButton_clicked();

private:
    void getNetworkInterface();     // 获取本机网络信息

private:
    Ui::frmModifyNetworkIP *ui;

    ModifyNetworkIP *m_mnip;
};
#endif // FRMMODIFYNETWORKIP_H
