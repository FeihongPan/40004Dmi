﻿#ifndef PERIODPUBLISHINFO_H
#define PERIODPUBLISHINFO_H

#include "Task.h"

#include <functional>

struct PeriodPublishInfo
{
    QString topic;
    TaskInfo taskInfo;
    std::function<QByteArray(bool &)> deleObj;
    int elapsed;
    int period;
};

#endif // PERIODPUBLISHINFO_H
