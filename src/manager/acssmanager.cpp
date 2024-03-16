

#include "acssmanager.h"
// ACSS
#include <QtAdvancedStylesheet.h>

#include "yapplication.h"
// ACSSManager *ACSSManager::_instance = nullptr;
ACSSManager::ACSSManager(QObject *parent) : m_stylesheet(new acss::QtAdvancedStylesheet(this))
{
}

void ACSSManager::updateStyleSheet()
{
    m_stylesheet->updateStylesheet();
}

void ACSSManager::init()
{
    QString AppDir = qApp->applicationDirPath();

    //// TODO: Release时修改加载style的路径
    QString StylesDir = AppDir + "/share/styles";
    // QString StylesDir = "D:/myprogram/YRMathType/src/resources/styles";
    // m_stylesheet = new acss::QtAdvancedStylesheet(this);
    m_stylesheet->setStylesDirPath(StylesDir);
    m_stylesheet->setOutputDirPath(AppDir + "/output");
    m_stylesheet->setCurrentStyle("qt_material");
    m_stylesheet->setDefaultTheme();
    m_stylesheet->updateStylesheet();
    //// setWindowIcon(d->AdvancedStyleSheet->styleIcon());
    qApp->setStyleSheet(m_stylesheet->styleSheet());
    // QObject::connect(m_advancedStyleSheet, SIGNAL(stylesheetChanged()), m_this,
    //                  SLOT(onStyleManagerStylesheetChanged()));

    // createThemeColorDockWidget();
    // fillThemeMenu();
}
