#include "configdialog.h"
#include "ui_configdialog.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

ConfigDialog::ConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigDialog)
{
    ui->setupUi(this);

    QFile file("./config.ini");

    if(!file.open(QFile::ReadOnly))
        return;

    QTextStream in(&file);
    QString addr;
    quint16 port;
    quint16 localPort;

    in >> addr >> port >> localPort;
    ui->lineEditServerAddr->setText(addr);
    ui->spinBoxServerPort->setValue(port);
    ui->spinBoxLocalPort->setValue(localPort);
    file.close();
}

ConfigDialog::~ConfigDialog()
{
    delete ui;
}

void ConfigDialog::on_pushButtonSave_clicked()
{
    if(ui->lineEditServerAddr->text().trimmed().isEmpty())
    {
        QMessageBox::information(this, "提示", "服务端地址不能为空");
        ui->lineEditServerAddr->selectAll();
        ui->lineEditServerAddr->setFocus();
        return;
    }

    QString addr = ui->lineEditServerAddr->text().trimmed();
    quint16 port = ui->spinBoxServerPort->value();
    quint16 localPort = ui->spinBoxLocalPort->value();
    QFile file("./config.ini");

    if(!file.open(QFile::WriteOnly | QFile::Truncate))
    {
        QMessageBox::information(this, "提示", "配置文件写入失败");
        return;
    }

    QTextStream out(&file);

    out << addr << " " << port << " " << localPort;
    file.close();
    QMessageBox::information(this, "提示", "配置保存成功");
    this->close();
}
