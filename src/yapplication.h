#pragma once

#include <QApplication>
class CentralWidget;
#if defined(yApp)
#undef yApp
#endif

#define yApp (qobject_cast<YApplication *>(QCoreApplication::instance())) // global qvapplication object

class YApplication : public QApplication
{
    Q_OBJECT

  public:
    explicit YApplication(int &argc, char **argv);
    ~YApplication() override;

    CentralWidget *getMainWindow();
};