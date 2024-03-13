#ifndef ICONHELPER_H
#define ICONHELPER_H

#include <QFont>

#include <QMutex>
#include <QObject>

/* Usage:example
    IconHelper::Instance()->SetIcon(ui->closeBtn, QChar(0xf00d), 10);
    IconHelper::Instance()->SetIcon(ui->maxBtn, QChar(0xf096), 10);
    IconHelper::Instance()->SetIcon(ui->minimumBtn, QChar(0xf068), 10);
*/
class QLabel;
class QAbstractButton;
class IconManager : public QObject
{
  private:
    explicit IconManager(QObject *parent = nullptr);
    QFont iconFont;
    static IconManager *_instance;

  public:
    static IconManager *getInstance()
    {
        static QMutex mutex;
        if (!_instance)
        {
            QMutexLocker locker(&mutex);
            if (!_instance)
            {
                _instance = new IconManager;
            }
        }
        return _instance;
    }

    void SetIcon(QLabel *lab, QChar c, int size = 10);
    void SetIcon(QAbstractButton *btn, QChar c, int size = 10);
};

#endif // ICONHELPER_H