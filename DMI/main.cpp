#include "MainProject/Manager/dmimanager.h"
#include "MainProject/View/dmiwidget.h"

#include "Logger/loggermanager.h"
#include "FileSystem/fileoperatormanager.h"
#include "AppConfig/Manager/appconfigmanager.h"
#include "Communication/MQTT/mqttclientmanager.h"
#include "NetworkEquipmentMonitor/Manage/heartbeat.h"
#include "Communication/MQTT/mqttclientmanager.h"

#include <QApplication>

using namespace NS_Log;

#define USEFORDEBUG

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#ifdef USEFORDEBUG
    DmiWidget w;
    w.Initialize();
    w.show();
#endif

    // MqttClient
    AppConfigManager::getInstance()->SetPath(m_AppConfig.appDataPath + "NetMonitorConfig", m_AppConfig.appDataPath_Backup
            + "NetMonitorConfig", "appConfig.json", m_AppConfig.appDataPath + "CommunicationCommand");
    AppConfigManager::getInstance()->Initialize(); // Read Config Data
    MqttClientManager::getInstance()->AddClient(0, "DMI");

    // AppConfig
    AppConfig config;
    if (AppConfigManager::getInstance()->IsInitialized())
    {
        config = AppConfigManager::getInstance()->GetAppConfig();
        MqttClientManager::getInstance()->Connect(0, config.serverAdd.IP, config.serverAdd.port);
    }
    LOG()->Initialize_DebugLogger("D:/");
    LOG()->Log_Debug("Server.IP = " + config.serverAdd.IP.toStdString());
    LOG()->Log_Debug("Server.Port = " + std::to_string(config.serverAdd.port));
    LOG()->Log_Debug("Local IP = " + config.LocalIP.toStdString());

    // Publish IP
    DmiManager::getInstance()->LinkToPublishClient(MqttClientManager::getInstance()->GetClient(0), "Driver", "DMI");

    // HeartBeat
    HeartBeat::getInstance()->LinkHeartBeatToPublishClient(MqttClientManager::getInstance()->GetClient(0), "DMI");

    // Subscribe
    DmiManager::getInstance()->LinkToSubscribeClient(MqttClientManager::getInstance()->GetClient(0));
    DmiManager::getInstance()->Subscribe("MC_DMI"); // subscribe MC

    return a.exec();
}
