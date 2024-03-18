#pragma once

// acss
#include "qjsonobject.h"
#define ACSS_STATIC
#include <QtAdvancedStylesheet.h>

// Qt
#include <QMutex>
#include <QObject>

class ACSSManager : public acss::QtAdvancedStylesheet
{
    Q_OBJECT
  public:
    explicit ACSSManager(QObject *parent = nullptr);
    // static ACSSManager *_instance;

  public:
    void init();

    bool parseThemeJsonFile();

	bool saveJsonFile() const;

    void changeFont(const QString &family,int size);


    void changeLineHeight(int height);

    
    void update();

  private:
    QString m_defaultTheme;
    QString m_fontSize;
    QString m_fontFamily;
    QString m_lineHeight;
};
