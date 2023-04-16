#ifndef HOSTBLOCKER_H
#define HOSTBLOCKER_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>

QT_BEGIN_NAMESPACE
namespace Ui { class HostBlocker; }
QT_END_NAMESPACE

class HostBlocker : public QMainWindow {
    Q_OBJECT
    bool isHostsFileLocked();

public:
    explicit HostBlocker(QWidget *parent = nullptr);
    ~HostBlocker();

private slots:
    void on_addUrlsButton_clicked();
    void on_importUrlsButton_clicked(); //Added Import TXT button
    void on_flushDnsButton_clicked(); // Added Flush DNS button
    void on_padlockButton_clicked(); // Added Hosts file status indicator
    void on_urlListsComboBox_currentIndexChanged(int index); // Added online URL list dropdown
    void loadUrlLists();
    void handleUrlListResponse(QNetworkReply *reply);
    void handleImportUrlsResponse(QNetworkReply *reply);


private:
    Ui::HostBlocker *ui;

    void addUrlsToHostsFile(const QStringList &urls);
    void updatePadlockIcon();
};

#endif // HOSTBLOCKER_H
