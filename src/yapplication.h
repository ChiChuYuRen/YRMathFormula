#pragma once

#include "manager/acssmanager.h"
#include "manager/microtexmanager.h"

#include <QApplication>
#include <QElapsedTimer >
#include <QFile>
#include <SingleApplication>

#if defined(yApp)
#undef yApp
#endif

#define yApp (qobject_cast<YApplication *>(QCoreApplication::instance())) // global qvapplication objects
class MainWindow;

class YApplication : public SingleApplication
{
    Q_OBJECT

    enum YRStyle
    {
        DARK,
        LIGHT
    };

  public:
    explicit YApplication(int &argc, char **argv);
    ~YApplication() override;
    void init();

    void timerStart();
    double elapseTime();
    ACSSManager *getACSSManager()
    {
        return m_acssManager;
    }
    MainWindow *getMainWindow()
    {
        return m_mainWindow;
    }

    void sendInfoToPrimaryInstance();
    void setStyle(YRStyle &p_style);

  private slots:
    void onStyleManagerStylesheetChanged();

  private:
    ACSSManager *m_acssManager;
    MicroTexManager *m_mTeXManager;
    MainWindow *m_mainWindow = Q_NULLPTR;

    QElapsedTimer m_timer;
    QFile m_light;
    QFile m_dark;
    YRStyle m_style;

    void loadStyle();
};