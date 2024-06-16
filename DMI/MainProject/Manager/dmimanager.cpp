/***********************************************************************
* Copyright (C) 2024, iStar.
*
* File Name:        dmimanager.cpp
* Description:      Dmi干涉仪下发和接收来自控制层的指令和数据
* Version:          V1.0.0
* Author:           Feihong Pan
* Date:             2024-3-18
* Modify Record：
***********************************************************************/

#include "dmimanager.h"

#include "Converter/enumconverter.h"
#include "Logger/loggermanager.h"

using namespace NS_Log;

DmiManager *DmiManager::self = nullptr;

DmiManager::DmiManager(const QString &strName, QObject *parent)
    : IMqttClient(strName, parent)
{
    setConnection();
}

DmiManager::~DmiManager()
{
    DmiDriver::getInstance().~DmiDriver();
}

DmiManager *DmiManager::getInstance()
{
    if(nullptr == self)
    {
        static QMutex mutex;
        QMutexLocker locker(&mutex);
        if(nullptr == self)
        {
            self = new DmiManager("DmiManager");
        }
    }
    return self;
}

void DmiManager::decoding(const QString &task, bool result, const QByteArray &msg, const QByteArray &errMsg)
{
    CMD_Dmi::Command cmd = EnumConverter::ConvertStringToEnum<CMD_Dmi::Command>(task);

    S_DmiParameter data_Parameter;

    switch (cmd)
    {
        case CMD_Dmi::Command::CMD_Connect:
        {
            data_Parameter.fromJson(msg);
            m_Driver->SetLocalIP(data_Parameter.strLocalIP);
            m_Driver->SetFrequency(data_Parameter.nFrequency);
            m_Driver->SetCollectNumber(data_Parameter.nCollectNumber);
            m_Driver->SetTransferCoefficient(data_Parameter.dTransferCoefficient);
            m_Driver->Connect(data_Parameter.strTargetIP, data_Parameter.nLocalPort, data_Parameter.nTargetPort, data_Parameter.nAxialNumber);
        }
        break;
        case CMD_Dmi::Command::CMD_Disconnect:
        {
            m_Driver->Disconnect();
        }
        break;
        case CMD_Dmi::Command::CMD_Start:
        {
            m_Driver->Start();
        }
        break;
        case CMD_Dmi::Command::CMD_Stop:
        {
            m_Driver->Stop();
        }
        break;
        case CMD_Dmi::Command::CMD_SetZero:
        {
            m_Driver->SetZero();
        }
        break;

        default:
            break;
    }
}

void DmiManager::setConnection()
{
    connect(&DmiDriver::getInstance(), &DmiDriver::sig_SendResultData, this, [&](const QList<double> &lst_RawData,
            const QList<double> &lst_PosData, const QList<double> &lst_AveragePos)
    {
        S_DmiResult data_Result;
        data_Result.lst_RawData = lst_RawData;
        data_Result.lst_PosData = lst_PosData;
        data_Result.lst_AveragePos = lst_AveragePos;

        Publish(EnumConverter::ConvertToString(CMD_Dmi::CMD_Result), true, data_Result.toRawJson());
    });
}
