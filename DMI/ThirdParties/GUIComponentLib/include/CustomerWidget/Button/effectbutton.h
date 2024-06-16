#ifndef EFFECTBUTTON_H
#define EFFECTBUTTON_H
#include "GUIComponentLib_global.h"

#include <QPushButton>
#include <QObject>
#include <QGraphicsDropShadowEffect>
#include <QMap>

class GUICOMPONENTLIB_EXPORT EffectInfo
{
public:
    QPointF offset = QPointF(0, 0);
    QString color = "#FFFFFF";
    int blurRadius = 1;
};

class GUICOMPONENTLIB_EXPORT EffectButton : public QPushButton
{
    Q_OBJECT
public:
    enum Status
    {
        Normal,
        Hover,
        Pressed,
        Disabled,
    };
    Q_ENUM(Status)

    explicit EffectButton(QWidget *parent = nullptr);
    ~EffectButton();

    bool event(QEvent *e) override;
    void SetEffectInfo(Status status, int offset_x, int offset_y, QString color, int blur);
    void SetEffectStatus(bool on);

public:
    QGraphicsDropShadowEffect *effect;

protected:
    virtual void setColor_Toggled(bool r);
    virtual void setColor_Pressed();
    virtual void setColor_Released();
    virtual void changeDisplayStatus();

    bool isHover = false;
    bool isPressed = false;
    QMap<Status, EffectInfo> dic_EffectInfos;
    void setEffectStatus(Status status);
    bool bEffectOn = false;

private:
    void setEffectInfo(Status status, int offset_x, int offset_y, QString color, int blur);

};

#endif // EFFECTBUTTON_H
