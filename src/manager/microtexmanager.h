#pragma once


#include <QObject>
#include <QMutex>
#include <QThread>

class MicroTexManager : QObject
{
	public:
	explicit MicroTexManager(QObject *parent = nullptr);
	~MicroTexManager();

private:
	static void init();
	/*void setDefautlFont();
	void setOutSideFont();*/

	static void release();

	//默认字体
	QString m_defaultClm;
	QString m_defaultFont;
	//用户自定义的字体
	QString m_outsideClm;
	QString m_outsideFont;
};