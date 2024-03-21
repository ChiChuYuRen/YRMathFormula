#include "texeditor.h"

#include <KSyntaxHighlighting/Definition>
#include <KSyntaxHighlighting/FoldingRegion>
#include <KSyntaxHighlighting/SyntaxHighlighter>
#include <KSyntaxHighlighting/Theme>

#include <QActionGroup>
#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QFontDatabase>
#include <QMenu>
#include <QPainter>
#include <QPalette>



TexEditorSidebar::TexEditorSidebar(TexEditor *editor) : QWidget(editor), m_codeEditor(editor)
{
}

QSize TexEditorSidebar::sizeHint() const
{
    return QSize(m_codeEditor->sidebarWidth(), 0);
}

void TexEditorSidebar::paintEvent(QPaintEvent *event)
{
    m_codeEditor->sidebarPaintEvent(event);
}

void TexEditorSidebar::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->pos().x() >= width() - m_codeEditor->fontMetrics().lineSpacing())
    {
        auto block = m_codeEditor->blockAtPosition(event->pos().y());
        if (!block.isValid() || !m_codeEditor->isFoldable(block))
        {
            return;
        }
        m_codeEditor->toggleFold(block);
    }
    QWidget::mouseReleaseEvent(event);
}

TexEditor::TexEditor(QWidget *parent)
    : QPlainTextEdit(parent), m_highlighter(new KSyntaxHighlighting::SyntaxHighlighter(document())),
      m_sideBar(new TexEditorSidebar(this))
{
    setFont(QFontDatabase::systemFont(QFontDatabase::FixedFont));

    setTheme((palette().color(QPalette::Base).lightness() < 128)
                 ? m_repository.defaultTheme(KSyntaxHighlighting::Repository::DarkTheme)
                 : m_repository.defaultTheme(KSyntaxHighlighting::Repository::LightTheme));

    connect(this, &QPlainTextEdit::blockCountChanged, this, &TexEditor::updateSidebarGeometry);
    connect(this, &QPlainTextEdit::updateRequest, this, &TexEditor::updateSidebarArea);
    connect(this, &QPlainTextEdit::cursorPositionChanged, this, &TexEditor::highlightCurrentLine);

    updateSidebarGeometry();
    highlightCurrentLine();
}

TexEditor::~TexEditor()
{
}

void TexEditor::openFile(const QString &fileName)
{
    QFile f(fileName);
    if (!f.open(QFile::ReadOnly))
    {
        qWarning() << "Failed to open" << fileName << ":" << f.errorString();
        return;
    }

    clear();

    const auto def = m_repository.definitionForFileName(fileName);
    m_highlighter->setDefinition(def);

    setWindowTitle(fileName);
    setPlainText(QString::fromUtf8(f.readAll()));
}

void TexEditor::contextMenuEvent(QContextMenuEvent *event)
{
    auto menu = createStandardContextMenu(event->pos());
    menu->addSeparator();
    auto openAction = menu->addAction(QStringLiteral("Open File..."));
    connect(openAction, &QAction::triggered, this, [this]() {
        const auto fileName = QFileDialog::getOpenFileName(this, QStringLiteral("Open File"));
        if (!fileName.isEmpty())
        {
            openFile(fileName);
        }
    });

    // syntax selection
    auto hlActionGroup = new QActionGroup(menu);
    hlActionGroup->setExclusive(true);
    auto hlGroupMenu = menu->addMenu(QStringLiteral("Syntax"));
    QMenu *hlSubMenu = hlGroupMenu;
    QString currentGroup;
    for (const auto &def : m_repository.definitions())
    {
        if (def.isHidden())
        {
            continue;
        }
        if (currentGroup != def.section())
        {
            currentGroup = def.section();
            hlSubMenu = hlGroupMenu->addMenu(def.translatedSection());
        }

        Q_ASSERT(hlSubMenu);
        auto action = hlSubMenu->addAction(def.translatedName());
        action->setCheckable(true);
        action->setData(def.name());
        hlActionGroup->addAction(action);
        if (def.name() == m_highlighter->definition().name())
        {
            action->setChecked(true);
        }
    }
    connect(hlActionGroup, &QActionGroup::triggered, this, [this](QAction *action) {
        const auto defName = action->data().toString();
        const auto def = m_repository.definitionForName(defName);
        m_highlighter->setDefinition(def);
    });

    // theme selection
    auto themeGroup = new QActionGroup(menu);
    themeGroup->setExclusive(true);
    auto themeMenu = menu->addMenu(QStringLiteral("Theme"));
    for (const auto &theme : m_repository.themes())
    {
        auto action = themeMenu->addAction(theme.translatedName());
        action->setCheckable(true);
        action->setData(theme.name());
        themeGroup->addAction(action);
        if (theme.name() == m_highlighter->theme().name())
        {
            action->setChecked(true);
        }
    }
    connect(themeGroup, &QActionGroup::triggered, this, [this](QAction *action) {
        const auto themeName = action->data().toString();
        const auto theme = m_repository.theme(themeName);
        setTheme(theme);
    });

    menu->exec(event->globalPos());
    delete menu;
}

void TexEditor::resizeEvent(QResizeEvent *event)
{
    QPlainTextEdit::resizeEvent(event);
    updateSidebarGeometry();
}

void TexEditor::setTheme(const KSyntaxHighlighting::Theme &theme)
{
    auto pal = qApp->palette();
    if (theme.isValid())
    {
        pal.setColor(QPalette::Base, theme.editorColor(KSyntaxHighlighting::Theme::BackgroundColor));
        pal.setColor(QPalette::Highlight, theme.editorColor(KSyntaxHighlighting::Theme::TextSelection));
    }
    setPalette(pal);

    m_highlighter->setTheme(theme);
    m_highlighter->rehighlight();
    highlightCurrentLine();
}

int TexEditor::sidebarWidth() const
{
    int digits = 1;
    auto count = blockCount();
    while (count >= 10)
    {
        ++digits;
        count /= 10;
    }
    return 4 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits + fontMetrics().lineSpacing();
}

void TexEditor::sidebarPaintEvent(QPaintEvent *event)
{
    QPainter painter(m_sideBar);
    painter.fillRect(event->rect(), m_highlighter->theme().editorColor(KSyntaxHighlighting::Theme::IconBorder));

    auto block = firstVisibleBlock();
    auto blockNumber = block.blockNumber();
    int top = blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + blockBoundingRect(block).height();
    const int currentBlockNumber = textCursor().blockNumber();

    const auto foldingMarkerSize = fontMetrics().lineSpacing();

    while (block.isValid() && top <= event->rect().bottom())
    {
        if (block.isVisible() && bottom >= event->rect().top())
        {
            const auto number = QString::number(blockNumber + 1);
            painter.setPen(m_highlighter->theme().editorColor((blockNumber == currentBlockNumber)
                                                                  ? KSyntaxHighlighting::Theme::CurrentLineNumber
                                                                  : KSyntaxHighlighting::Theme::LineNumbers));
            painter.drawText(0, top, m_sideBar->width() - 2 - foldingMarkerSize, fontMetrics().height(), Qt::AlignRight,
                             number);
        }

        // folding marker
        if (block.isVisible() && isFoldable(block))
        {
            QPolygonF polygon;
            if (isFolded(block))
            {
                polygon << QPointF(foldingMarkerSize * 0.4, foldingMarkerSize * 0.25);
                polygon << QPointF(foldingMarkerSize * 0.4, foldingMarkerSize * 0.75);
                polygon << QPointF(foldingMarkerSize * 0.8, foldingMarkerSize * 0.5);
            }
            else
            {
                polygon << QPointF(foldingMarkerSize * 0.25, foldingMarkerSize * 0.4);
                polygon << QPointF(foldingMarkerSize * 0.75, foldingMarkerSize * 0.4);
                polygon << QPointF(foldingMarkerSize * 0.5, foldingMarkerSize * 0.8);
            }
            painter.save();
            painter.setRenderHint(QPainter::Antialiasing);
            painter.setPen(Qt::NoPen);
            painter.setBrush(QColor(m_highlighter->theme().editorColor(KSyntaxHighlighting::Theme::CodeFolding)));
            painter.translate(m_sideBar->width() - foldingMarkerSize, top);
            painter.drawPolygon(polygon);
            painter.restore();
        }

        block = block.next();
        top = bottom;
        bottom = top + blockBoundingRect(block).height();
        ++blockNumber;
    }
}

void TexEditor::updateSidebarGeometry()
{
    setViewportMargins(sidebarWidth(), 0, 0, 0);
    const auto r = contentsRect();
    m_sideBar->setGeometry(QRect(r.left(), r.top(), sidebarWidth(), r.height()));
}

void TexEditor::updateSidebarArea(const QRect &rect, int dy)
{
    if (dy)
    {
        m_sideBar->scroll(0, dy);
    }
    else
    {
        m_sideBar->update(0, rect.y(), m_sideBar->width(), rect.height());
    }
}

void TexEditor::highlightCurrentLine()
{
    QTextEdit::ExtraSelection selection;
    selection.format.setBackground(QColor(m_highlighter->theme().editorColor(KSyntaxHighlighting::Theme::CurrentLine)));
    selection.format.setProperty(QTextFormat::FullWidthSelection, true);
    selection.cursor = textCursor();
    selection.cursor.clearSelection();

    QList<QTextEdit::ExtraSelection> extraSelections;
    extraSelections.append(selection);
    setExtraSelections(extraSelections);
}

QTextBlock TexEditor::blockAtPosition(int y) const
{
    auto block = firstVisibleBlock();
    if (!block.isValid())
    {
        return QTextBlock();
    }

    int top = blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + blockBoundingRect(block).height();
    do
    {
        if (top <= y && y <= bottom)
        {
            return block;
        }
        block = block.next();
        top = bottom;
        bottom = top + blockBoundingRect(block).height();
    } while (block.isValid());
    return QTextBlock();
}

bool TexEditor::isFoldable(const QTextBlock &block) const
{
    return m_highlighter->startsFoldingRegion(block);
}

bool TexEditor::isFolded(const QTextBlock &block) const
{
    if (!block.isValid())
    {
        return false;
    }
    const auto nextBlock = block.next();
    if (!nextBlock.isValid())
    {
        return false;
    }
    return !nextBlock.isVisible();
}

void TexEditor::toggleFold(const QTextBlock &startBlock)
{
    // we also want to fold the last line of the region, therefore the ".next()"
    const auto endBlock = m_highlighter->findFoldingRegionEnd(startBlock).next();

    if (isFolded(startBlock))
    {
        // unfold
        auto block = startBlock.next();
        while (block.isValid() && !block.isVisible())
        {
            block.setVisible(true);
            block.setLineCount(block.layout()->lineCount());
            block = block.next();
        }
    }
    else
    {
        // fold
        auto block = startBlock.next();
        while (block.isValid() && block != endBlock)
        {
            block.setVisible(false);
            block.setLineCount(0);
            block = block.next();
        }
    }

    // redraw document
    document()->markContentsDirty(startBlock.position(), endBlock.position() - startBlock.position() + 1);

    // update scrollbars
    Q_EMIT document() -> documentLayout()->documentSizeChanged(document()->documentLayout()->documentSize());
}
