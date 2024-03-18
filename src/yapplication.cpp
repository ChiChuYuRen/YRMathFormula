#include "yapplication.h"
#include "MainWindow.h"

YApplication::YApplication(int &argc, char **argv) : SingleApplication(argc, argv)
{
}

YApplication::~YApplication()
{
     //m_acssManager->saveJsonFile();
    delete m_acssManager;
    delete m_mainWindow;
}

void YApplication::init()
{
    m_acssManager = new ACSSManager(this);
    m_acssManager->init();
    m_mainWindow = new MainWindow(this);

    m_mainWindow->show();
}

void YApplication::sendInfoToPrimaryInstance()
{
    QByteArray buffer;
    QDataStream stream(&buffer, QIODevice::WriteOnly);

    stream << arguments();
    sendMessage(buffer);
}