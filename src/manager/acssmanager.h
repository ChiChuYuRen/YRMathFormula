#pragma once

// acss
#include "qobjectdefs.h"
#include <QtAdvancedStylesheet.h>

// Qt
#include <QMutex>
#include <QObject>

class ACSSManager : QObject
{
    Q_OBJECT
  private:
    explicit ACSSManager(QObject *parent = nullptr);
    static ACSSManager *_instance;

  public:
    static ACSSManager *getInstance()
    {
        static QMutex mutex;
        if (!_instance)
        {
            QMutexLocker locker(&mutex);
            if (!_instance)
            {
                _instance = new ACSSManager;
            }
        }
        return _instance;
    }

    void init();
  public slots:
    void updateStyleSheet();

  private:
    acss::QtAdvancedStylesheet *m_stylesheet;
};
