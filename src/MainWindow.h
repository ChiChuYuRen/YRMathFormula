#pragma once

#include <QMainWindow>

class MainWindowPrivate;
class MainWindow : public QMainWindow
{
    Q_OBJECT
  public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

  private:
    

    MainWindowPrivate *d_ptr; // pimpl
    friend class MainWindowPrivate;


  private slots:
    void onThemeActionTriggered();
    void onStyleManagerStylesheetChanged();
    void onThemeColorButtonClicked();
};
