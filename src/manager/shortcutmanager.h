#pragma once

#include <QMutex>
#include <QObject>
class QAbstractButton;
class QKeySequence;
class QAction;
class ShortcutManager : public QObject
{
  private:
    explicit ShortcutManager(QObject *parent = nullptr);
    static ShortcutManager *_instance;
    QMap<QString, QKeySequence> *m_btnShortcutList;
    QMap<QString, QKeySequence> *m_actionShortcutList;

  public:
    static ShortcutManager *getInstance()
    {
        static QMutex mutex;
        if (!_instance)
        {
            QMutexLocker locker(&mutex);
            if (!_instance)
            {
                _instance = new ShortcutManager;
            }
        }
        return _instance;
    }
    void setShortcut(QAbstractButton *p_btn, const QKeySequence &p_key);
    void changeShortcut(QAbstractButton *p_btn, const QKeySequence &p_key);
    [[nodiscard]] QMap<QString, QKeySequence> *getBtnShortcutList() const;
    void setShortcut(QAction *p_action, const QKeySequence &p_key);
    void changeShortcut(QAction *p_action, const QKeySequence &p_key);
    [[nodiscard]] QMap<QString, QKeySequence> *getActionShortcutList() const;
};