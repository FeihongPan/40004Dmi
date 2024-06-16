﻿#ifndef TIMESYNCSUBSCRIBER_H
#define TIMESYNCSUBSCRIBER_H

#include "Communication/MQTT/isubscriber.h"

#include <QObject>

class TimeSyncSubscriber : public ISubscriber
{
    Q_OBJECT

public:
    ~TimeSyncSubscriber();

    static TimeSyncSubscriber *getInstance();

private:
    TimeSyncSubscriber(const QString &name, QObject *parent = nullptr);
    TimeSyncSubscriber(const TimeSyncSubscriber &) = delete;
    TimeSyncSubscriber &operator=(const TimeSyncSubscriber &) = delete;

    virtual void decoding(const QString &topic, const QByteArray &message) override;

private:
    static TimeSyncSubscriber *self;
};

#endif // TIMESYNCSUBSCRIBER_H
