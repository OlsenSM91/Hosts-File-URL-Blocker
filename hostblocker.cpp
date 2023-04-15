#include "hostblocker.h"
#include "ui_hostblocker.h"
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QProcess>

HostBlocker::HostBlocker(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::HostBlocker) {
    ui->setupUi(this);
}

HostBlocker::~HostBlocker() {
    delete ui;
}

void HostBlocker::on_addUrlsButton_clicked() {
    QString inputUrls = ui->urlsTextEdit->toPlainText();
    QStringList urlsList = inputUrls.split("\n");
    addUrlsToHostsFile(urlsList);

    QMessageBox::information(this, "Success", "URLs added to the hosts file.");
}

// Added Flush DNS function

void HostBlocker::on_flushDnsButton_clicked()
{
    QProcess process;
    process.start("ipconfig", QStringList() << "/flushdns");
    process.waitForFinished();
    QMessageBox::information(this, "Flush DNS", "DNS cache has been flushed.");
}

void HostBlocker::on_importUrlsButton_clicked() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Text Files (*.txt);;All Files (*)"));

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::warning(this, "Error", "Unable to open the file.");
            return;
        }

        QTextStream in(&file);
        QStringList urlsList;

        while (!in.atEnd()) {
            QString line = in.readLine();
            urlsList << line;
        }

        file.close();
        addUrlsToHostsFile(urlsList);

        QMessageBox::information(this, "Success", "URLs from the file added to the hosts file.");
    }
}

void HostBlocker::addUrlsToHostsFile(const QStringList &urls) {
    QString hostsFilePath = "C:/Windows/System32/drivers/etc/hosts";

    QFile hostsFile(hostsFilePath);
    if (!hostsFile.open(QIODevice::Append | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Unable to open the hosts file.");
        return;
    }

    QTextStream out(&hostsFile);

    for (const QString &url : urls) {
        out << "127.0.0.1 " << url.trimmed() << "\n";
    }

    hostsFile.close();
}
