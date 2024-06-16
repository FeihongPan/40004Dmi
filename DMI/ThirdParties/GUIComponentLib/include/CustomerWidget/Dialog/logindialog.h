#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include "GUIComponentLib_global.h"

#include <QDialog>

namespace Ui
{
    class LoginDialog;
}

class GUICOMPONENTLIB_EXPORT LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

    virtual void reject() override;

public slots:
    //0 OK,1 userName Error,2 pwd error
    void RecivedLoginInfo(int res);
signals:
    void SendLoginInfo(QString userName, QString password);

private:
    Ui::LoginDialog *ui;
    //    QWidget *parent;
    QString userName;
    QString password;
};

#endif // LOGINDIALOG_H
