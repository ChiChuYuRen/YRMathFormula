#include "iconmanager.h"
#include "yapplication.h"

#include <QAbstractButton>
#include <QFontDatabase>
#include <QLabel>

IconManager *IconManager::_instance = nullptr;
IconManager::IconManager(QObject * /*unused*/) : QObject(yApp)
{
    /*int fontId = QFontDatabase::addApplicationFont(":/image/fontawesome-webfont.ttf");
    QString fontName = QFontDatabase::applicationFontFamilies(fontId).at(0);
    iconFont = QFont(fontName);*/
}

void IconManager::SetIcon(QLabel *lab, QChar c, int size)
{
    iconFont.setPointSize(size);
    lab->setFont(iconFont);
    lab->setText(c);
}

void IconManager::SetIcon(QAbstractButton *btn, QChar c, int size)
{
    iconFont.setPointSize(size);
    btn->setFont(iconFont);
    btn->setText(c);
}
