#ifndef HOSTBLOCKER_H
#define HOSTBLOCKER_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class HostBlocker; }
QT_END_NAMESPACE

class HostBlocker : public QMainWindow {
    Q_OBJECT

public:
    explicit HostBlocker(QWidget *parent = nullptr);
    ~HostBlocker();

private slots:
    void on_addUrlsButton_clicked();
    void on_importUrlsButton_clicked(); //Added Import TXT button
    void on_flushDnsButton_clicked(); // Added Flush DNS button

private:
    Ui::HostBlocker *ui;

    void addUrlsToHostsFile(const QStringList &urls);
};

#endif // HOSTBLOCKER_H
