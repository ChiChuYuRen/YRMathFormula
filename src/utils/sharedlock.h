#pragma once

#include <QSharedMemory>
#include <QString>



class SharedLock
{
  public:
    SharedLock(const QString &id);

    bool hasLock() const
    {
        return hasLock_;
    }

  private:
    QSharedMemory mutex_;
    bool hasLock_;
};

