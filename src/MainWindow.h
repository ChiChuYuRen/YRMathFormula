#pragma once

#include "qmenubar.h"
#include <QMainWindow>

class MainWindowPrivate;
class QMenuBar;
class MainWindow : public QMainWindow
{
    Q_OBJECT
  public:
    // explicit MainWindow(QWidget *parent = nullptr);
    explicit MainWindow(QApplication *parent = nullptr);
    ~MainWindow() override;
    QMenuBar *getMenuBar() const;

  private:
    QApplication *app;
    MainWindowPrivate *d_ptr; // pimpl
    friend class MainWindowPrivate;

  private slots:
    void onThemeActionTriggered();
    void onStyleManagerStylesheetChanged();
    void onThemeColorButtonClicked();
};
