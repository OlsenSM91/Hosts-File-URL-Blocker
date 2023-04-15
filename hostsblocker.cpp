#include "hostsblocker.h"
#include "ui_hostsblocker.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

HostsBlocker::HostsBlocker(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::HostsBlocker)
{
    ui->setupUi(this);
}

HostsBlocker::~HostsBlocker()
{
    delete ui;
}

QString HostsBlocker::getHostsPath()
{
#ifdef Q_OS_WIN
    return "C:/Windows/System32/drivers/etc/hosts";
#else
    return "/etc/hosts";
#endif
}

void HostsBlocker::on_addUrlsButton_clicked()
{
    QString urls = ui->urlInput->toPlainText();
    QStringList urlList = urls.split("\n");

    if (urlList.isEmpty()) {
        QMessageBox::critical(this, "Error", "No URLs provided.");
        return;
    }

    QFile hostsFile(getHostsPath());

    if (!hostsFile.open(QIODevice::Append | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Failed to update the hosts file.");
        return;
    }

    QTextStream stream(&hostsFile);

    for (const QString &url : urlList) {
        if (!url.isEmpty()) {
            stream << "127.0.0.1 " << url << "\n";
        }
    }

    hostsFile.close();
    QMessageBox::information(this, "Success", "URLs added to the hosts file.");
}
