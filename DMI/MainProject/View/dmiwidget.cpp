#include "dmiwidget.h"
#include "ui_dmiwidget.h"
#include "MainProject/Driver/dmidrive.h"

#include <StyleSheet/stylesheet.h>

#include <QString>

DmiWidget::DmiWidget(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::InterferometerWidget)
{
    ui->setupUi(this);
}

DmiWidget::~DmiWidget()
{
    delete ui;
}

void DmiWidget::Initialize()
{
    setWidgetStyleSheet();
    setConnections();
}

void DmiWidget::setWidgetStyleSheet()
{
    // QPushbutton
    ui->btn_Connect->setStyleSheet(Style()->Button_Border + Style()->fontStyle_normal_12);
    ui->btn_Disconnect->setStyleSheet(Style()->Button_Border + Style()->fontStyle_normal_12);

    ui->btn_SetZero->setStyleSheet(Style()->Button_Border + Style()->fontStyle_normal_12);
    ui->btn_Start->setStyleSheet(Style()->Button_Border + Style()->fontStyle_normal_12);
    ui->btn_Stop->setStyleSheet(Style()->Button_Border + Style()->fontStyle_normal_12);

    // label
    ui->lbl_Self->setStyleSheet(Style()->fontStyle_normal_12);
    ui->lbl_AxisNum->setStyleSheet(Style()->fontStyle_normal_12);
    ui->lbl_Dstport->setStyleSheet(Style()->fontStyle_normal_12);
    ui->lbl_Frequency->setStyleSheet(Style()->fontStyle_normal_12);
    ui->lbl_Hostport->setStyleSheet(Style()->fontStyle_normal_12);
    ui->lbl_Target->setStyleSheet(Style()->fontStyle_normal_12);
    ui->lbl_CollectNum->setStyleSheet(Style()->fontStyle_normal_12);
    ui->lbl_Transfer->setStyleSheet(Style()->fontStyle_normal_12);

    ui->lbl_AvePos1->setStyleSheet(Style()->fontStyle_normal_12);
    ui->lbl_AvePos2->setStyleSheet(Style()->fontStyle_normal_12);
    ui->lbl_Pos1->setStyleSheet(Style()->fontStyle_normal_12);
    ui->lbl_Pos2->setStyleSheet(Style()->fontStyle_normal_12);
    ui->lbl_Pos3->setStyleSheet(Style()->fontStyle_normal_12);
    ui->lbl_Pos4->setStyleSheet(Style()->fontStyle_normal_12);
    ui->lbl_Pos5->setStyleSheet(Style()->fontStyle_normal_12);
    ui->lbl_Pos6->setStyleSheet(Style()->fontStyle_normal_12);
    ui->lbl_OriginalPos1->setStyleSheet(Style()->fontStyle_normal_12);
    ui->lbl_OriginalPos2->setStyleSheet(Style()->fontStyle_normal_12);
    ui->lbl_OriginalPos3->setStyleSheet(Style()->fontStyle_normal_12);
    ui->lbl_OriginalPos4->setStyleSheet(Style()->fontStyle_normal_12);
    ui->lbl_OriginalPos5->setStyleSheet(Style()->fontStyle_normal_12);
    ui->lbl_OriginalPos6->setStyleSheet(Style()->fontStyle_normal_12);

    const QString LineEdit_Light = "QLineEdit{border:1px solid #EEEEEE;padding:5px 2px;background-color:#FFFFFF;border-radius:10px;color:#000000;}"
                                   "QLineEdit:hover{border:1px solid #A4B7FF;}"
                                   "QLineEdit:focus{border:1px solid #4C70FA;}"
                                   "QLineEdit:disabled{background-color:#C8C8C8;color:#FFFFFF;}";

    // lineEdit
    ui->led_AxisNum->setStyleSheet(LineEdit_Light + Style()->fontStyle_normal_12);
    ui->led_Targetport->setStyleSheet(LineEdit_Light + Style()->fontStyle_normal_12);
    ui->led_Frequency->setStyleSheet(LineEdit_Light + Style()->fontStyle_normal_12);
    ui->led_Localport->setStyleSheet(LineEdit_Light + Style()->fontStyle_normal_12);
    ui->led_LocalIP->setStyleSheet(LineEdit_Light + Style()->fontStyle_normal_12);
    ui->led_TargetIP->setStyleSheet(LineEdit_Light + Style()->fontStyle_normal_12);
    ui->led_CollectNum->setStyleSheet(LineEdit_Light + Style()->fontStyle_normal_12);
    ui->led_Transfer->setStyleSheet(LineEdit_Light + Style()->fontStyle_normal_12);

    ui->led_AvePos1->setStyleSheet(Style()->LineEdit_Dark + Style()->fontStyle_normal_12);
    ui->led_AvePos2->setStyleSheet(Style()->LineEdit_Dark + Style()->fontStyle_normal_12);
    ui->led_Pos1->setStyleSheet(Style()->LineEdit_Dark + Style()->fontStyle_normal_12);
    ui->led_Pos2->setStyleSheet(Style()->LineEdit_Dark + Style()->fontStyle_normal_12);
    ui->led_Pos3->setStyleSheet(Style()->LineEdit_Dark + Style()->fontStyle_normal_12);
    ui->led_Pos4->setStyleSheet(Style()->LineEdit_Dark + Style()->fontStyle_normal_12);
    ui->led_Pos5->setStyleSheet(Style()->LineEdit_Dark + Style()->fontStyle_normal_12);
    ui->led_Pos6->setStyleSheet(Style()->LineEdit_Dark + Style()->fontStyle_normal_12);
    ui->led_OriginalPos1->setStyleSheet(Style()->LineEdit_Dark + Style()->fontStyle_normal_12);
    ui->led_OriginalPos2->setStyleSheet(Style()->LineEdit_Dark + Style()->fontStyle_normal_12);
    ui->led_OriginalPos3->setStyleSheet(Style()->LineEdit_Dark + Style()->fontStyle_normal_12);
    ui->led_OriginalPos4->setStyleSheet(Style()->LineEdit_Dark + Style()->fontStyle_normal_12);
    ui->led_OriginalPos5->setStyleSheet(Style()->LineEdit_Dark + Style()->fontStyle_normal_12);
    ui->led_OriginalPos6->setStyleSheet(Style()->LineEdit_Dark + Style()->fontStyle_normal_12);
}

void DmiWidget::setConnections()
{
    connect(&DmiDriver::getInstance(), &DmiDriver::sig_SendRawDataFor4Axial, this,
            [&](const double & x0, const double & x1, const double & x2, const double & x3, const double & x4)
    {
        ui->led_OriginalPos1->setText(QString::number(x0));
        ui->led_OriginalPos2->setText(QString::number(x1));
        ui->led_OriginalPos3->setText(QString::number(x2));
        ui->led_OriginalPos4->setText(QString::number(x3));
        ui->led_OriginalPos5->setText(QString::number(x4));
    });

    connect(&DmiDriver::getInstance(), &DmiDriver::sig_SendPosDataFor4Axial, this,
            [&](const double & pos0, const double & pos1, const double & pos2, const double & pos3, const double & pos4)
    {
        ui->led_Pos1->setText(QString::number(pos0));
        ui->led_Pos2->setText(QString::number(pos1));
        ui->led_Pos3->setText(QString::number(pos2));
        ui->led_Pos4->setText(QString::number(pos3));
        ui->led_Pos5->setText(QString::number(pos4));
    });

    connect(&DmiDriver::getInstance(), &DmiDriver::sig_SendRawDataFor6Axial, this,
            [&](const double & x0, const double & x1, const double & x2, const double & x3, const double & x4, const double & x5)
    {
        ui->led_OriginalPos1->setText(QString::number(x0));
        ui->led_OriginalPos2->setText(QString::number(x1));
        ui->led_OriginalPos3->setText(QString::number(x2));
        ui->led_OriginalPos4->setText(QString::number(x3));
        ui->led_OriginalPos5->setText(QString::number(x4));
        ui->led_OriginalPos6->setText(QString::number(x5));
    });

    connect(&DmiDriver::getInstance(), &DmiDriver::sig_SendPosDataFor6Axial, this,
            [&](const double & pos0, const double & pos1, const double & pos2, const double & pos3, const double & pos4, const double & pos5)
    {
        ui->led_Pos1->setText(QString::number(pos0));
        ui->led_Pos2->setText(QString::number(pos1));
        ui->led_Pos3->setText(QString::number(pos2));
        ui->led_Pos4->setText(QString::number(pos3));
        ui->led_Pos5->setText(QString::number(pos4));
        ui->led_Pos6->setText(QString::number(pos5));
    });


    connect(&DmiDriver::getInstance(), &DmiDriver::sig_SendAverageData, this, [&](const double & x, const double & y)
    {
        ui->led_AvePos1->setText(QString::number(x));
        ui->led_AvePos2->setText(QString::number(y));
    });
}

void DmiWidget::on_btn_Connect_clicked()
{
    DmiDriver::getInstance().SetLocalIP(ui->led_LocalIP->text());
    DmiDriver::getInstance().Connect(ui->led_TargetIP->text(), ui->led_Localport->text().toInt(), ui->led_Targetport->text().toInt(), ui->led_AxisNum->text().toInt());
    DmiDriver::getInstance().SetFrequency(ui->led_Frequency->text().toInt());
    DmiDriver::getInstance().SetCollectNumber(ui->led_CollectNum->text().toInt());
    DmiDriver::getInstance().SetTransferCoefficient(ui->led_Transfer->text().toDouble());

    auto bAxialNumberEqual4 = ui->led_AxisNum->text().toInt() == 4 ? true : false;
    if (bAxialNumberEqual4)
    {
        ui->lbl_OriginalPos6->hide();
        ui->led_OriginalPos6->hide();
        ui->lbl_Pos6->hide();
        ui->led_Pos6->hide();
    }
    else
    {
        ui->lbl_OriginalPos6->show();
        ui->led_OriginalPos6->show();
        ui->lbl_Pos6->show();
        ui->led_Pos6->show();
    }
}

void DmiWidget::on_btn_Disconnect_clicked()
{
    DmiDriver::getInstance().Disconnect();
}

void DmiWidget::on_btn_Start_clicked()
{
    DmiDriver::getInstance().Start();
}

void DmiWidget::on_btn_Stop_clicked()
{
    DmiDriver::getInstance().Stop();
}

void DmiWidget::on_btn_SetZero_clicked()
{
    DmiDriver::getInstance().SetZero();
}

