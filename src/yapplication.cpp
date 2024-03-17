#include "yapplication.h"
#include "MainWindow.h"
#include "manager/acssmanager.h"

YApplication::YApplication(int &argc, char **argv) : SingleApplication(argc, argv)
{
}

YApplication::~YApplication()
{
    delete m_acssManager;
    delete m_mainWindow;
}

void YApplication::init()
{
    m_acssManager = new ACSSManager(this);
    m_mainWindow = new MainWindow(this);
    m_mainWindow->show();
    m_acssManager->init();
}

void YApplication::sendInfoToPrimaryInstance()
{
    QByteArray buffer;
    QDataStream stream(&buffer, QIODevice::WriteOnly);

    stream << arguments();
    sendMessage(buffer);
}