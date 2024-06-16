#include "s_dmi.h"

S_DmiParameter::S_DmiParameter()
{
    strLocalIP = "192.168.1.103";
    strTargetIP = "192.168.1.103";
    nLocalPort = 8000;
    nTargetPort = 5000;
    nAxialNumber = 4;
    nFrequency = 0x01;
    nCollectNumber = 200;
    dTransferCoefficient = 0.039;
}

S_DmiParameter::S_DmiParameter(const S_DmiParameter &instance)
{
    strLocalIP = instance.strLocalIP;
    strTargetIP = instance.strTargetIP;
    nLocalPort = instance.nLocalPort;
    nTargetPort = instance.nTargetPort;
    nAxialNumber = instance.nAxialNumber;
    nFrequency = instance.nFrequency;
    nCollectNumber = instance.nCollectNumber;
    dTransferCoefficient = instance.dTransferCoefficient;
}

S_DmiParameter &S_DmiParameter::operator=(const S_DmiParameter &instance)
{
    strLocalIP = instance.strLocalIP;
    strTargetIP = instance.strTargetIP;
    nLocalPort = instance.nLocalPort;
    nTargetPort = instance.nTargetPort;
    nAxialNumber = instance.nAxialNumber;
    nFrequency = instance.nFrequency;
    nCollectNumber = instance.nCollectNumber;
    dTransferCoefficient = instance.dTransferCoefficient;

    return *this;
}

S_DmiResult::S_DmiResult()
{

}

S_DmiResult::S_DmiResult(const S_DmiResult &instance)
{
    lst_RawData = instance.lst_RawData;
    lst_PosData = instance.lst_PosData;
    lst_AveragePos = instance.lst_AveragePos;
}

S_DmiResult &S_DmiResult::operator=(const S_DmiResult &instance)
{
    lst_RawData = instance.lst_RawData;
    lst_PosData = instance.lst_PosData;
    lst_AveragePos = instance.lst_AveragePos;

    return *this;
}

S_Dmi::S_Dmi()
{

}

S_Dmi::S_Dmi(const S_Dmi &instance)
{
    Paramater = instance.Paramater;
    Result = instance.Result;
}

S_Dmi &S_Dmi::operator=(const S_Dmi &instance)
{
    Paramater = instance.Paramater;
    Result = instance.Result;

    return *this;
}
