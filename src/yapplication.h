#pragma once

#include <QApplication>
#include <SingleApplication>

#include "manager/acssmanager.h"
#if defined(yApp)
#undef yApp
#endif

#define yApp (qobject_cast<YApplication *>(QCoreApplication::instance())) // global qvapplication objects
class MainWindow;
class YApplication : public SingleApplication
{
    Q_OBJECT

  public:
    explicit YApplication(int &argc, char **argv);
    ~YApplication() override;
    void init();
    ACSSManager *getACSSManager()
    {
        return m_acssManager;
    }
    MainWindow *getMainWindow()
    {
        return m_mainWindow;
    }

    void sendInfoToPrimaryInstance();

  private:
    ACSSManager *m_acssManager;
    MainWindow *m_mainWindow = Q_NULLPTR;
};