

#include "acssmanager.h"
// ACSS
#include <QtAdvancedStylesheet.h>

#include "yapplication.h"
ACSSManager *ACSSManager::_instance = nullptr;
ACSSManager::ACSSManager(QObject* parent):m_stylesheet(new acss::QtAdvancedStylesheet(yApp))
{
}

void ACSSManager::updateStyleSheet()
{
	m_stylesheet->updateStylesheet();
}

void ACSSManager::init()
{
	// QString AppDir = qApp->applicationDirPath();

 //// TODO: Release时修改加载style的路径
 //// StylesDir = AppDir + "/resources/styles";
 //QString StylesDir = "D:/myprogram/YRMathType/src/resources/styles";
 //m_advancedStyleSheet = new acss::QtAdvancedStylesheet(m_this);
 //m_advancedStyleSheet->setStylesDirPath(StylesDir);
 //m_advancedStyleSheet->setOutputDirPath(AppDir + "/output");
 //m_advancedStyleSheet->setCurrentStyle("qt_material");
 //m_advancedStyleSheet->setDefaultTheme();
 //m_advancedStyleSheet->updateStylesheet();
 //// setWindowIcon(d->AdvancedStyleSheet->styleIcon());
 //qApp->setStyleSheet(m_advancedStyleSheet->styleSheet());
 //QObject::connect(m_advancedStyleSheet, SIGNAL(stylesheetChanged()), m_this,
 //                 SLOT(onStyleManagerStylesheetChanged()));

 //createThemeColorDockWidget();
 //fillThemeMenu();
}
