﻿/***********************************************************************
* Copyright (C) 2024, iStar.
*
* File Name:        appconfig.h
* Description:      AppConfig模块数据类型
* Version:          V1.0.0
* Author:           Feihong Pan
* Date:             2024-2-19
* Modify Record：
***********************************************************************/

#ifndef APPCONFIG_H
#define APPCONFIG_H

#include "BasicValue/others.h"
#include "Serializer/QSerializer"

/// <summary>
/// AppConfig配置文件和数据结构
/// </summary>
class AppConfig : public QSerializer
{
    Q_GADGET
    QS_SERIALIZABLE

    QS_FIELD(QString, appDataPath)          // App_Data文件夹地址
    QS_FIELD(QString, appDataPath_Backup)   // App_Data文件夹备用地址
    QS_FIELD(QString, LocalIP)              // 本地IP地址
    QS_OBJECT(S_IPAddress, serverAdd)       // 服务端的IP地址和端口

public:
    AppConfig();
    AppConfig(const AppConfig& instance);
    AppConfig& operator=(const AppConfig& instance);
};

static AppConfig m_AppConfig;               // AppConfig文件全局变量

#endif // APPCONFIG_H
