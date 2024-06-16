#include "dmidrive.h"
#include <QtConcurrent/QtConcurrent>

DmiDriver::DmiDriver(QObject *parent) : QObject(parent)
{

}

DmiDriver::~DmiDriver()
{
    if(m_bConnected)
    {
        m_bConnected = false;
        m_udpSocket.disconnect();
    }
}

DmiDriver &DmiDriver::getInstance()
{
    static DmiDriver INSTANCE;
    return INSTANCE;
}

bool DmiDriver::Connect(const QString &strTargetIP, const int &nHostport, const int &nDstport, const int &nAxisNumber)
{
    m_nLocalPort = nHostport;
    m_nAxialNumber = nAxisNumber;
    m_bAxialNumberEqual4 = (m_nAxialNumber == 4) ? true : false;

    m_strTargetIP = strTargetIP;
    m_TargetAddress.setAddress(m_strTargetIP);
    m_nTargetPort = nDstport;

    QHostAddress LocalAddress(m_strLocalIP);
    m_bConnected = m_udpSocket.bind(LocalAddress, m_nLocalPort, QUdpSocket::ShareAddress);
    if(m_bConnected)
    {
        connect(&m_udpSocket, &QUdpSocket::readyRead, this, &DmiDriver::dataRecived);
    }
    return m_bConnected;
}

void DmiDriver::Disconnect()
{
    m_udpSocket.disconnect();
}

void DmiDriver::Start()
{
    QByteArray ba;
    ba.resize(24);
    for(int i = 0; i < 24; i++)
    {
        ba[i] = 0;
    }
    ba[0] = 0xa3;
    ba[3] = m_nFrequency;
    m_udpSocket.writeDatagram(ba, ba.size(), m_TargetAddress, m_nTargetPort);
    m_bRunning = true;
}

void DmiDriver::Stop()
{
    QByteArray ba;
    ba.resize(24);
    for(int i = 0; i < 24; i++)
    {
        ba[i] = 0;
    }
    ba[0] = 0xa4;
    m_udpSocket.writeDatagram(ba, ba.size(), m_TargetAddress, m_nTargetPort);
    m_bRunning = false;
}

void DmiDriver::SetZero()
{
    QByteArray ba;
    ba.resize(24);
    for(int i = 0; i < 24; i++)
    {
        ba[i] = 0;
    }
    ba[0] = 0xa1;
    ba[5] = 0x01;
    ba[6] = 0x0c;
    ba[9] = 0x40;
    m_udpSocket.writeDatagram(ba, ba.size(), m_TargetAddress, m_nTargetPort);
}

void DmiDriver::SetFrequency(const int &f)
{
    if(f <= 200)
    {
        m_nFrequency = 0x00;
    }
    else if(f < 2000)
    {
        m_nFrequency = 0x01;
    }
    else
    {
        m_nFrequency = 0x02;
    }
}

void DmiDriver::collectOnce()
{
    QByteArray ba;
    ba.resize(24);
    for(int i = 0; i < 24; i++)
    {
        ba[i] = 0;
    }
    ba[0] = 0xa5;
    m_udpSocket.writeDatagram(ba, ba.size(), m_TargetAddress, m_nTargetPort);
}

void DmiDriver::dataRecived()
{
    while (m_udpSocket.hasPendingDatagrams())
    {
        m_Datagram.resize(m_udpSocket.pendingDatagramSize());
        m_udpSocket.readDatagram(m_Datagram.data(), m_Datagram.size());
        decoding();
    }
}

qint64 DmiDriver::bytesToInt(const QByteArray &src, const int &offset)
{
    qint64 res = 0;
    int bNegative = false;
    QByteArray arr;
    arr[0] = src.at(offset);
    int aa = (arr[0] & 0xF0) >> 4;
    if(aa % 2 == 1)
    {
        bNegative = true;
    }
    res = static_cast<qint64>(src[offset - 4] & 0xFF);
    res |= static_cast<qint64>(src[offset - 3] & 0xFF) << 8;
    res |= static_cast<qint64>(src[offset - 2] & 0xFF) << 16;
    res |= static_cast<qint64>(src[offset - 1] & 0xFF) << 24;
    res |= static_cast<qint64>(src[offset] & 0x0F) << 32;
    if(bNegative)
    {
        res = 0x1000000000 - res;
        res = res * -1;
    }
    return res;
}

void DmiDriver::decoding()
{
    if((m_Datagram[0] & 0xFF) == 0xa3 && (m_Datagram[6] & 0xFF) == 1)
    {
        auto x0 = static_cast<double>(bytesToInt(m_Datagram, 11));
        auto x1 = static_cast<double>(bytesToInt(m_Datagram, 17));
        auto x2 = static_cast<double>(bytesToInt(m_Datagram, 23));
        auto x3 = static_cast<double>(bytesToInt(m_Datagram, 29));
        auto x4 = static_cast<double>(bytesToInt(m_Datagram, 35));

        m_arrPos[0] = x0 * m_dTransferCoefficient / 1000000;
        m_arrPos[1] = x1 * m_dTransferCoefficient / 1000000;
        m_arrPos[2] = x2 * m_dTransferCoefficient / 1000000;
        m_arrPos[3] = x3 * m_dTransferCoefficient / 1000000;
        m_arrPos[4] = x4 * m_dTransferCoefficient / 1000000;

        if (m_bAxialNumberEqual4)
        {
            emit sig_SendRawDataFor4Axial(x0, x1, x2, x3, x4);
            emit sig_SendPosDataFor4Axial(m_arrPos[0], m_arrPos[1], m_arrPos[2], m_arrPos[3], m_arrPos[4]);
            m_lst_RawData[0] = x0;
            m_lst_RawData[1] = x1;
            m_lst_RawData[2] = x2;
            m_lst_RawData[3] = x3;
            m_lst_RawData[4] = x4;
            for (int i = 0; i < 5; ++i)
            {
                m_lst_PosData[i] = m_arrPos[i];
            }
        }
        else
        {
            auto x5 = static_cast<double>(bytesToInt(m_Datagram, 41));
            m_arrPos[5] = x5 * m_dTransferCoefficient / 1000000;
            emit sig_SendRawDataFor6Axial(x0, x1, x2, x3, x4, x5);
            emit sig_SendPosDataFor6Axial(m_arrPos[0], m_arrPos[1], m_arrPos[2], m_arrPos[3], m_arrPos[4], m_arrPos[5]);
            m_lst_RawData[0] = x0;
            m_lst_RawData[1] = x1;
            m_lst_RawData[2] = x2;
            m_lst_RawData[3] = x3;
            m_lst_RawData[4] = x4;
            m_lst_RawData[5] = x5;
            for (int i = 0; i < 6; ++i)
            {
                m_lst_PosData[i] = m_arrPos[i];
            }
        }

        m_nCount++;
        m_arrAveragePos[0] += (m_arrPos[0] + m_arrPos[1]);
        m_arrAveragePos[1] += (m_arrPos[2] + m_arrPos[3]);

        if(m_nCount == m_nCollectNumber)
        {
            m_lst_PosData[0] = m_arrAveragePos[0];
            m_lst_PosData[1] = m_arrAveragePos[1];
            emit sig_SendAverageData(m_arrAveragePos[0] / m_nCollectNumber / 2, m_arrAveragePos[1] / m_nCollectNumber / 2);
            emit sig_SendResultData(m_lst_RawData, m_lst_PosData, m_lst_AveragePos);
            m_arrAveragePos[0] = 0;
            m_arrAveragePos[1] = 0;
            m_nCount = 0;
            m_lst_RawData.clear();
            m_lst_PosData.clear();
            m_lst_AveragePos.clear();
        }
    }
}


