#ifndef S_DMI_H
#define S_DMI_H

#include <Serializer/QSerializer>

class S_DmiParameter : public QSerializer
{
    Q_GADGET
    QS_SERIALIZABLE

    QS_FIELD(QString, strLocalIP);
    QS_FIELD(QString, strTargetIP);
    QS_FIELD(int, nLocalPort);
    QS_FIELD(int, nTargetPort);
    QS_FIELD(int, nAxialNumber);
    QS_FIELD(int, nFrequency);
    QS_FIELD(int, nCollectNumber);
    QS_FIELD(double, dTransferCoefficient);

public:
    S_DmiParameter();
    S_DmiParameter(const S_DmiParameter &instance);
    S_DmiParameter &operator=(const S_DmiParameter &instance);
};

class S_DmiResult : public QSerializer
{
    Q_GADGET
    QS_SERIALIZABLE

    QS_COLLECTION(QList, double, lst_RawData)
    QS_COLLECTION(QList, double, lst_PosData)
    QS_COLLECTION(QList, double, lst_AveragePos)

public:
    S_DmiResult();
    S_DmiResult(const S_DmiResult &instance);
    S_DmiResult &operator=(const S_DmiResult &instance);
};

class S_Dmi : public QSerializer
{
    Q_GADGET
    QS_SERIALIZABLE

    QS_OBJECT(S_DmiParameter, Paramater)
    QS_OBJECT(S_DmiResult, Result)

public:
    S_Dmi();
    S_Dmi(const S_Dmi &instance);
    S_Dmi &operator=(const S_Dmi &instance);
};

#endif // S_DMI_H
