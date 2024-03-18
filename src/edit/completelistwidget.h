#ifndef COMPLETELISTWIDGET_H
#define COMPLETELISTWIDGET_H

#include <QApplication>
#include <QListWidget>
#include <QObject>
#include <QPlainTextEdit>
#include <QWidget>
#include <string>
#include <vector>
using std::min;
using std::string;
using std::vector;
class CompleteListWidget : public QListWidget
{
  public:
    CompleteListWidget(QWidget *parent = 0);
    static int ldistance(const string source, const string target);

  protected:
    void keyPressEvent(QKeyEvent *event) override;

  private:
    QPlainTextEdit *p;
    QColor backgroundColor;
    QColor highlightColor;
};

#endif // COMPLETELISTWIDGET_H
