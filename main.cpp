#include <QApplication>
#include <QTextCodec>
#include "configdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    ConfigDialog w;
    w.show();
    
    return a.exec();
}
