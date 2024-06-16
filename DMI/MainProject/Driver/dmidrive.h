#ifndef DMIDRIVE_H
#define DMIDRIVE_H

#include <QObject>
#include <QList>
#include <QUdpSocket>

class DmiDriver : public QObject
{
    Q_OBJECT

public:
    ~DmiDriver();
    static DmiDriver &getInstance();

    /// <summary>
    /// 返回当前点double数组
    /// </summary>
    /// <returns>返回所有当前点的double数组</returns>
    inline double *GetArrPos() const;

    /// <summary>
    /// 返回200个点平均值double数组
    /// </summary>
    /// <returns>返回所有当前点的double数组</returns>
    inline double *GetArrAveragePos() const;

    /// <summary>
    /// 给SelfgroupAddress赋值
    /// </summary>
    /// <param name="strSelfgroupAddress">strSelfgroupAddress的地址</param>
    inline void SetLocalIP(const QString &strSelfgroupAddress);

    /// <summary>
    /// 给采集个数赋值
    /// </summary>
    /// <param name="nCollectNumber">采集个数</param>
    inline void SetCollectNumber(const int &nCollectNumber);

    /// <summary>
    /// 给转换系数赋值
    /// </summary>
    /// <param name="nCollectNumber">转换系数</param>
    inline void SetTransferCoefficient(const double &dTransferCoefficient);

    bool Connect(const QString &strTargetIP, const int &nHostport, const int &nDstport, const int &nAxisNum);

    void Disconnect();

    void Start();

    void Stop();

    void SetZero();

    void SetFrequency(const int &f);

private:
    explicit DmiDriver(QObject *parent = nullptr);
    DmiDriver(const DmiDriver &) = delete;
    DmiDriver &operator=(const DmiDriver &) = delete;

    void collectOnce();

    void dataRecived();

    void decoding();

    qint64 bytesToInt(const QByteArray &src, const int &offset);

signals:
    void sig_SendRawDataFor4Axial(const double &x0, const double &x1, const double &x2, const double &x3, const double &x4);
    void sig_SendRawDataFor6Axial(const double &x0, const double &x1, const double &x2, const double &x3, const double &x4, const double &x5);
    void sig_SendPosDataFor4Axial(const double &pos0, const double &pos1, const double &pos2, const double &pos3, const double &pos4);
    void sig_SendPosDataFor6Axial(const double &pos0, const double &pos1, const double &pos2, const double &pos3, const double &pos4, const double &pos5);
    void sig_SendAverageData(const double &x, const double &y);

    void sig_SendResultData(const QList<double> &lst_RawData, const QList<double> &lst_PosData, const QList<double> &lst_AveragePos);

private:
    double *m_arrPos;
    double *m_arrAveragePos; // 200times

    QList<double> m_lst_RawData;
    QList<double> m_lst_PosData;
    QList<double> m_lst_AveragePos;

    QString m_strLocalIP;                           // 本地IP
    QString m_strTargetIP;                          // 连接IP
    QHostAddress m_TargetAddress;
    QByteArray m_Datagram;                          // 数据传输
    QUdpSocket m_udpSocket;

    int m_nCount = 0;
    int m_nCollectNumber = 200;
    int m_nLocalPort;                               // 本地端口
    int m_nTargetPort;                              // 连接端口
    int m_nAxialNumber = 4;
    int m_nFrequency = 0x01;
    double m_dTransferCoefficient = 0.039;
    bool m_bConnected = false;
    bool m_bRunning = false;
    bool m_bAxialNumberEqual4;
};

inline double *DmiDriver::GetArrPos() const
{
    return m_arrPos;
}

inline double *DmiDriver::GetArrAveragePos() const
{
    return m_arrAveragePos;
}

inline void DmiDriver::SetLocalIP(const QString &strLocalIP)
{
    m_strLocalIP = strLocalIP;
}

inline void DmiDriver::SetCollectNumber(const int &nCollectNumber)
{
    m_nCollectNumber = nCollectNumber;
}

inline void DmiDriver::SetTransferCoefficient(const double &dTransferCoefficient)
{
    m_dTransferCoefficient = dTransferCoefficient;
}

#endif // DMIDRIVE_H
