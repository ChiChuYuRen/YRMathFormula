#pragma once

// Qt
#include <QListWidget>
#include <QListWidgetItem>
#include <QObject>
#include <QPainter>
#include <QPlainTextEdit>

// KSyntaxHighlighting
#include <KSyntaxHighlighting/Repository>

// #include "edit/completelistwidget.h"

namespace KSyntaxHighlighting
{
class SyntaxHighlighter;
}
class TexEditorSidebar;

class TexEditor : public QPlainTextEdit
{
    Q_OBJECT

  public:
    explicit TexEditor(QWidget *parent = nullptr);
    ~TexEditor() override;

    void openFile(const QString &fileName);

  protected:
    void contextMenuEvent(QContextMenuEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

  private:
    friend class TexEditorSidebar;
    void setTheme(const KSyntaxHighlighting::Theme &theme);
    int sidebarWidth() const;
    void sidebarPaintEvent(QPaintEvent *event);
    void updateSidebarGeometry();
    void updateSidebarArea(const QRect &rect, int dy);
    void highlightCurrentLine();

     QTextBlock blockAtPosition(int y) const;
     bool isFoldable(const QTextBlock &block) const;
     bool isFolded(const QTextBlock &block) const;
    void toggleFold(const QTextBlock &block);

    KSyntaxHighlighting::Repository m_repository;
    KSyntaxHighlighting::SyntaxHighlighter *m_highlighter;
    TexEditorSidebar *m_sideBar;
};
class TexEditorSidebar : public QWidget
{
    Q_OBJECT
  public:
    explicit TexEditorSidebar(TexEditor *editor);
    QSize sizeHint() const override;

  protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

  private:
    TexEditor *m_codeEditor;
};

