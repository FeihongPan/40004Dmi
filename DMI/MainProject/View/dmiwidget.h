#ifndef DMIWIDGET_H
#define DMIWIDGET_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class InterferometerWidget;
}
QT_END_NAMESPACE

class DmiWidget : public QMainWindow
{
    Q_OBJECT

public:
    DmiWidget(QWidget *parent = nullptr);
    ~DmiWidget();

    void Initialize();

private slots:
    void on_btn_Connect_clicked();

    void on_btn_Disconnect_clicked();

    void on_btn_Start_clicked();

    void on_btn_Stop_clicked();

    void on_btn_SetZero_clicked();

private:
    void setWidgetStyleSheet();
    void setConnections();

private:
    Ui::InterferometerWidget *ui;
};
#endif // DMIWIDGET_H
