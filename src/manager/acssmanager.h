#pragma once

// acss
#define ACSS_STATIC
#include <QtAdvancedStylesheet.h>

// Qt

class ACSSManager : public acss::QtAdvancedStylesheet
{
    Q_OBJECT
  public:
    explicit ACSSManager(QObject *parent = nullptr);
    // static ACSSManager *_instance;

    void init();
    void defaultInit();
    // 检查style文件夹下的文件是否齐全
    bool checkStyleFiles();

    bool parseThemeJsonFile();

    bool saveJsonFile() const;

    void changeFont(const QString &family, int size);

    void changeLineHeight(int height);

    void update();

  private:
    QString m_defaultTheme;
    QString m_fontSize;
    QString m_fontFamily;
    QString m_lineHeight;
};
