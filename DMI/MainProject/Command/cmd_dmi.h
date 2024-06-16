#ifndef CMD_DMI_H
#define CMD_DMI_H

#include <QObject>

class CMD_Dmi : public QObject
{
    Q_OBJECT

public:
    enum Command
    {
        CMD_Connect,
        CMD_Disconnect,
        CMD_Start,
        CMD_Stop,
        CMD_SetZero,
        CMD_Result,
    };
    Q_ENUM(Command)
};

#endif // CMD_DMI_H
