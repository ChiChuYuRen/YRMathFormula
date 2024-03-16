#pragma once

#include <QApplication>

#if defined(yApp)
#undef yApp
#endif

#define yApp (qobject_cast<YApplication *>(QCoreApplication::instance())) // global qvapplication object
class ACSSManager;
class MainWindow;
class YApplication : public QApplication
{
    Q_OBJECT

  public:
    explicit YApplication(int &argc, char **argv);
    ~YApplication() override;

    ACSSManager *getACSSManager()
    {
        return m_acssManager;
    }
    MainWindow *getMainWindow()
    {
        return m_mainWindow;
    }
    void init();

  private:
    ACSSManager *m_acssManager;
    MainWindow *m_mainWindow = Q_NULLPTR;
};