#ifndef MESSAGEDIALOG_H
#define MESSAGEDIALOG_H

#include "GUIComponentLib_global.h"

#include <QDialog>
#include <QMap>
#include <QGraphicsBlurEffect>
namespace Ui
{
    class MessageDialog;
}

class GUICOMPONENTLIB_EXPORT MessageDialog : public QDialog
{
    Q_OBJECT

public:
    enum NoticeType
    {
        Success,
        Attention,
        Error,
    };
    Q_ENUM(NoticeType)

    explicit MessageDialog(NoticeType type, QWidget *parent = nullptr, const QString msg = QString());
    ~MessageDialog();

    virtual void showEvent(QShowEvent *event) override;
    virtual void hideEvent(QHideEvent *event) override;
    virtual void accept() override;
    virtual void reject() override;

    void SetNoticeColor(QString success, QString attention, QString error);
    void SetNoticeIcon(QString success, QString attention, QString error);

signals:
    void Showed();
    void Hided();

private:
    Ui::MessageDialog *ui;
    NoticeType noticeType;
    QMap<NoticeType, QString> dic_NoticeColor;
    QMap<NoticeType, QString> dic_NoticeIcon;
};

#endif // MESSAGEDIALOG_H
