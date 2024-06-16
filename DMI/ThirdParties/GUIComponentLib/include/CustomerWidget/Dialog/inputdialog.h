#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

#include "GUIComponentLib_global.h"

#include <QDialog>

class QLineEdit;

class GUICOMPONENTLIB_EXPORT InputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InputDialog(const QString &title, const QStringList &labels, const QStringList &contents = QStringList(), const QStringList &regExp = QStringList(), QWidget *parent = nullptr);
    ~InputDialog();

    virtual void reject() override;

    static QStringList getText(const QString &title, const QStringList &labels, const QStringList &contents = QStringList(),
                               bool *ok = nullptr, QWidget *parent = nullptr, const QStringList &regExp = QStringList());

    static QList<double> getDouble(const QString &title, const QStringList &labels, const QList<double> &contents = {},
                                   bool *ok = nullptr, QWidget *parent = nullptr);

    static QList<int> getInt(const QString &title, const QStringList &labels, const QList<int> &contents = {},
                             bool *ok = nullptr, QWidget *parent = nullptr);

protected:
    virtual void closeEvent(QCloseEvent *) override;

private:
    static std::vector<QLineEdit *> m_vecLinePtr;
};

#endif // INPUTDIALOG_H
