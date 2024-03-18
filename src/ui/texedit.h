#pragma once

#include <QListWidget>
#include <QListWidgetItem>
#include <QObject>
#include <QPainter>
#include <QPlainTextEdit>

#include "edit/completelistwidget.h"
class TexEdit : public QPlainTextEdit
{
    Q_OBJECT
  public:
    explicit TexEdit(QWidget *parent = nullptr);
    ~TexEdit();

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();
    void setUpCompleteList();

  protected:
    void resizeEvent(QResizeEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

  private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &, int);
    void showCompleteWidget();
    // void completeWidgetKeyDown();

  private:
    QWidget *lineNumberArea;
    QColor lineColor;
    QColor editorColor;
    QStringList completeList; // 储存自动填充的关键字
    // QListWidget *completeWidget;
    CompleteListWidget *completeWidget;
    QString getWordOfCursor();
    int completeState;
    int getCompleteWidgetX();
};

class LineNumberArea : public QWidget
{
  public:
    LineNumberArea(TexEdit *editor) : QWidget(editor)
    {
        codeEditor = editor;
    }

    QSize sizeHint() const override
    {
        return QSize(codeEditor->lineNumberAreaWidth(), 0);
    }

  protected:
    void paintEvent(QPaintEvent *event) override
    {
        codeEditor->lineNumberAreaPaintEvent(event);
    }

  private:
    TexEdit *codeEditor;
};
enum CompleteState
{
    Ignore = 0,
    Showing = 1,
    Hide = 2
};
