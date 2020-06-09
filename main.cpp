#include "frmmodifynetworkip.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    frmModifyNetworkIP w;
    w.show();
    return a.exec();
}
