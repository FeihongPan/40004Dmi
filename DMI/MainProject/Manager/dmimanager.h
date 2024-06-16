/***********************************************************************
* Copyright (C) 2024, iStar.
*
* File Name:        dmimanager.h
* Description:      Dmi干涉仪下发和接收来自控制层的指令和数据
* Version:          V1.0.0
* Author:           Feihong Pan
* Date:             2024-3-18
* Modify Record：
***********************************************************************/

#ifndef DMIMANAGER_H
#define DMIMANAGER_H

#include "MainProject/Command/cmd_dmi.h"
#include "MainProject/Data/s_dmi.h"
#include "MainProject/Driver/dmidrive.h"

#include "Communication/MQTT/imqttclient.h"

class DmiManager : public IMqttClient
{
    Q_OBJECT

public:
    /// <summary>
    /// 析构函数
    /// </summary>
    ~DmiManager();

    /// <summary>
    /// 单例
    /// </summary>
    static DmiManager *getInstance();

private:
    /// <summary>
    /// 构造函数
    /// </summary>
    DmiManager(const QString &strName, QObject *parent = nullptr);

    /// <summary>
    /// 拷贝构造函数和赋值构造函数
    /// </summary>
    DmiManager(const DmiManager &instance) = delete;
    DmiManager &operator=(const DmiManager &instance) = delete;

    /// <summary>
    /// 接受来自MC的消息
    /// </summary>
    virtual void decoding(const QString &task, bool result, const QByteArray &msg, const QByteArray &errMsg) override;

    /// <summary>
    /// 接受来自MC的消息
    /// </summary>
    void setConnection();

private:
    static DmiManager* self;

    DmiDriver* m_Driver = &DmiDriver::getInstance();
};

#endif // DMIMANAGER_H
