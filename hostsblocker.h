#ifndef HOSTSBLOCKER_H
#define HOSTSBLOCKER_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class HostsBlocker; }
QT_END_NAMESPACE

class HostsBlocker : public QMainWindow
{
    Q_OBJECT

public:
    HostsBlocker(QWidget *parent = nullptr);
    ~HostsBlocker();

private slots:
    void on_addUrlsButton_clicked();

private:
    Ui::HostsBlocker *ui;
    QString getHostsPath();
};

#endif // HOSTSBLOCKER_H
