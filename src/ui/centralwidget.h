#pragma once
// Qt
#include <QHBoxLayout>
#include <QWidget>

class CentralWidgetPrivate;
class CentralWidget : public QWidget
{
    Q_OBJECT

  public:
    explicit CentralWidget(QWidget *parent = nullptr);
    ~CentralWidget();

  private:
    friend class CentralWidgetPrivate;
    CentralWidgetPrivate *d_ptr; // pimpl
    
protected slots:

  void nextClicked();

  void renderClicked();

  void saveClicked();

  void fontSizeChanged(int size);

};