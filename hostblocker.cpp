#include "hostblocker.h"
#include "ui_hostblocker.h"
#include <QFileDialog>
#include <QFile>
#include <QFileInfo>
#include <QMessageBox>
#include <QTextStream>
#include <QProcess>
#include <QPixmap>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

HostBlocker::HostBlocker(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::HostBlocker) {
    ui->setupUi(this);
    updatePadlockIcon();

    ui->urlListComboBox->addItem("None", "");
    ui->urlListComboBox->addItem("EasyList Ads", "https://raw.githubusercontent.com/OlsenSM91/Hosts-File-URL-Blocker/main/URL%20Lists/EasyListAds.txt");
    ui->urlListComboBox->addItem("Malicious", "https://raw.githubusercontent.com/OlsenSM91/Hosts-File-URL-Blocker/main/URL%20Lists/Malicious.txt");
    ui->urlListComboBox->addItem("OneLaunch", "https://raw.githubusercontent.com/OlsenSM91/Hosts-File-URL-Blocker/main/URL%20Lists/OneLaunch.txt");
    ui->urlListComboBox->addItem("Phishing", "https://raw.githubusercontent.com/OlsenSM91/Hosts-File-URL-Blocker/main/URL%20Lists/Phishing.txt");
    ui->urlListComboBox->addItem("Porn", "https://raw.githubusercontent.com/OlsenSM91/Hosts-File-URL-Blocker/main/URL%20Lists/PornList.txt");
    ui->urlListComboBox->addItem("Ransomeware", "https://raw.githubusercontent.com/OlsenSM91/Hosts-File-URL-Blocker/main/URL%20Lists/Ransomware.txt");
    ui->urlListComboBox->addItem("Scam Sites", "https://raw.githubusercontent.com/OlsenSM91/Hosts-File-URL-Blocker/main/URL%20Lists/Scam%20Sites.txt");
    // Add additional URL web links here

    // Connect the signal and slot
    connect(ui->urlListComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(on_urlListsComboBox_currentIndexChanged(int)));
}

HostBlocker::~HostBlocker() {
    delete ui;
}

void HostBlocker::loadUrlLists() {
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    connect(manager, &QNetworkAccessManager::finished, this, &HostBlocker::handleUrlListResponse);

    manager->get(QNetworkRequest(QUrl("https://api.github.com/repos/OlsenSM91/Hosts-File-URL-Blocker/contents/URL%20Lists")));
}

void HostBlocker::handleUrlListResponse(QNetworkReply *reply) {
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray response = reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(response);

        if (jsonResponse.isArray()) {
            QJsonArray jsonArray = jsonResponse.array();
            for (const QJsonValue &value : jsonArray) {
                if (value.isObject()) {
                    QJsonObject obj = value.toObject();
                    QString name = obj["name"].toString();
                    QString downloadUrl = obj["download_url"].toString();
                    if (!name.isEmpty() && !downloadUrl.isEmpty()) {
                        ui->urlListComboBox->addItem(name, downloadUrl);
                    }
                }
            }
        }
    } else {
        QMessageBox::warning(this, "Error", "Unable to load URL lists from GitHub.");
    }

    reply->deleteLater();
}

void HostBlocker::on_addUrlsButton_clicked() {
    QString inputUrls = ui->urlsTextEdit->toPlainText();
    QStringList urlsList = inputUrls.split("\n");
    addUrlsToHostsFile(urlsList);
    updatePadlockIcon();

    QMessageBox::information(this, "Success", "URLs added to the hosts file.");
}

// Added hosts status check function

void HostBlocker::on_padlockButton_clicked()
{
    static bool locked = true;
    QIcon newIcon;
    QString hostsFilePath = "C:/Windows/System32/drivers/etc/hosts";
    QFile hostsFile(hostsFilePath);

    if (locked) {
        newIcon = QIcon(":/assets/assets/unlocked.png");
        ui->padlockButton->setIcon(newIcon);
        ui->statusLabel->setText("Hosts is: Unlocked");

        // Code to change the attributes of the hosts file from read-only to not read-only
        hostsFile.setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner | QFileDevice::ReadGroup | QFileDevice::ReadOther);
    } else {
        newIcon = QIcon(":/assets/assets/locked.png");
        ui->padlockButton->setIcon(newIcon);
        ui->statusLabel->setText("Hosts is: Locked");

        // Code to change the attributes of the hosts file to read-only
        hostsFile.setPermissions(QFileDevice::ReadOwner | QFileDevice::ReadGroup | QFileDevice::ReadOther);
    }

    locked = !locked;
}

bool HostBlocker::isHostsFileLocked() {
    QString hostsFilePath = "C:/Windows/System32/drivers/etc/hosts";
    QFile hostsFile(hostsFilePath);
    if (!hostsFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Unable to open the hosts file.");
        return false;
    }

    bool isLocked = !(hostsFile.permissions() & QFileDevice::WriteUser);
    hostsFile.close();
    return isLocked;
}

void HostBlocker::updatePadlockIcon()
{
    QPixmap lockedPixmap(":/assets/assets/locked.png");
    QPixmap unlockedPixmap(":/assets/assets/unlocked.png");

    if (isHostsFileLocked()) {
        ui->padlockButton->setIcon(lockedPixmap);
        ui->statusLabel->setText("Hosts is: Locked");
    } else {
        ui->padlockButton->setIcon(unlockedPixmap);
        ui->statusLabel->setText("Hosts is: Unlocked");
    }
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

void HostBlocker::on_urlListsComboBox_currentIndexChanged(int index)
{
    if (index == -1)
        return;

    QString url = ui->urlListComboBox->itemData(index).toString();

    if (!url.isEmpty()) {
        QNetworkAccessManager *manager = new QNetworkAccessManager(this);
        connect(manager, &QNetworkAccessManager::finished, this, &HostBlocker::handleImportUrlsResponse);
        manager->get(QNetworkRequest(QUrl(url)));
    } else {
        QMessageBox::warning(this, "Error", "No URL list selected.");
    }
}

void HostBlocker::handleImportUrlsResponse(QNetworkReply *reply) {
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray response = reply->readAll();
        QString content = QString::fromUtf8(response);
        QStringList urlsList = content.split("\n", Qt::SkipEmptyParts);

        addUrlsToHostsFile(urlsList);
        QMessageBox::information(this, "Success", "URLs from the selected list added to the hosts file.");
    } else {
        QMessageBox::warning(this, "Error", "Unable to load URLs from the selected list.");
    }

    reply->deleteLater();
}

void HostBlocker::addUrlsToHostsFile(const QStringList &urlsList) {
    QString hostsFilePath = "C:/Windows/System32/drivers/etc/hosts";
    QFile hostsFile(hostsFilePath);

    if (!hostsFile.open(QIODevice::Append | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Unable to open the hosts file.");
        return;
    }

    QTextStream out(&hostsFile);

    for (const QString &url : urlsList) {
        QString trimmedUrl = url.trimmed();
        if (!trimmedUrl.isEmpty() && !trimmedUrl.startsWith('#')) {
            out << "\n" << "127.0.0.1" << " " << trimmedUrl;
        }
    }

    hostsFile.close();
}
