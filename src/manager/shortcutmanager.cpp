#include "shortcutmanager.h"
#include "yapplication.h"

#include <QAbstractButton>
#include <QAction>
#include <QKeySequence>

ShortcutManager *ShortcutManager::_instance = nullptr;
ShortcutManager::ShortcutManager(QObject * /*unused*/)
    : QObject(yApp), m_btnShortcutList(new QMap<QString, QKeySequence>()),
      m_actionShortcutList(new QMap<QString, QKeySequence>())
{
}
void ShortcutManager::setShortcut(QAbstractButton *p_btn, const QKeySequence &p_key)
{
    p_btn->setShortcut(p_key);
    m_btnShortcutList->insert(p_btn->objectName(), p_key);
}

void ShortcutManager::changeShortcut(QAbstractButton *p_btn, const QKeySequence &p_key)
{
    p_btn->setShortcut(p_key);
    m_btnShortcutList->insert(p_btn->objectName(), p_key);
}

QMap<QString, QKeySequence> *ShortcutManager::getBtnShortcutList() const
{
    return m_btnShortcutList;
}

void ShortcutManager::setShortcut(QAction *p_action, const QKeySequence &p_key)
{
    p_action->setShortcut(p_key);
    m_actionShortcutList->insert(p_action->objectName(), p_key);
}

void ShortcutManager::changeShortcut(QAction *p_action, const QKeySequence &p_key)
{
    p_action->setShortcut(p_key);
    m_actionShortcutList->insert(p_action->objectName(), p_key);
}

QMap<QString, QKeySequence> *ShortcutManager::getActionShortcutList() const
{
    return m_actionShortcutList;
}
