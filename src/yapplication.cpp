#include "yapplication.h"
#include "yapplication.h"
#include "MainWindow.h"
#include "manager/debugmanager.h"

#include <QDesktopWidget>

YApplication::YApplication(int& argc, char** argv) : SingleApplication(argc, argv)
{
	DebugManager::manageDebugOutput();
	DebugManager::pauseDebugOutput();
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
	//程序居中 TODO:解决不同显示器,不同分辨率下程序位置和大小
	m_mainWindow->resize(1920, 1080);
	m_mainWindow->move((desktop()->width() - m_mainWindow->width()) / 2,
	                   (desktop()->height() - m_mainWindow->height()) / 2);
	m_mainWindow->show();

	DebugManager::resumeDebugOutput();
}

void YApplication::sendInfoToPrimaryInstance()
{
	QByteArray buffer;
	QDataStream stream(&buffer, QIODevice::WriteOnly);

	stream << arguments();
	sendMessage(buffer);
}

/*
  QDesktopWidget * desktop = QApplication::desktop();

	//获取程序所在屏幕是第几个屏幕
	int current_screen = desktop->screenNumber(this);
	//获取程序所在屏幕的尺寸
	QRect rect = desktop->screenGeometry(current_screen);
	//获取所有屏幕总大小
	QRect rectA = desktop->geometry();
	//获取所有屏幕的个数
	int screen_count = desktop->screenCount();
	//获取主屏幕是第几个
	int prim_screen = desktop->primaryScreen();

	QString temp = "total screen size = " + QString::number(screen_count);
	temp = temp + "\ncurrent screen num = " + QString::number(current_screen);
	temp = temp + "\ncurrent screen rect " + QString::number(rect.width()) + "*" + QString::number(rect.height());
	temp = temp + "\nwhole screen rect " + QString::number(rectA.width()) + "*" + QString::number(rectA.height());

 */
