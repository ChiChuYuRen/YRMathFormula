#pragma once
#include <QDockWidget>
class DebugLogDockPrivate;
class DebugLogDock : public QDockWidget
{
    Q_OBJECT

  public:
    explicit DebugLogDock(QWidget *parent = nullptr);
    ~DebugLogDock();

  private:
    DebugLogDockPrivate *d_ptr;
    friend class DebugLogDockPrivate;
};
