#ifndef GROUPBOX_H
#define GROUPBOX_H

#include "GUIComponentLib_global.h"

#include <QGroupBox>
#include <QGraphicsDropShadowEffect>

namespace Ui
{
    class GroupBox;
}

class GUICOMPONENTLIB_EXPORT GroupBox : public QGroupBox
{
    Q_OBJECT

public:
    explicit GroupBox(QWidget *parent = nullptr);
    ~GroupBox();
    void resizeEvent(QResizeEvent *event) override;

    void SetDecorateColor(QString color);
    void SetHeaderText(QString text);
    void SetheaderFontSize(int size);
    void SetHeaderFontColor(QString color);
private:
    Ui::GroupBox *ui;
};

#endif // GROUPBOX_H
