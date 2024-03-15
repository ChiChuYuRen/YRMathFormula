#include "logwidget.h"
#include <QDateTime>
#include <QPlainTextEdit>
#include <QVBoxLayout>

class LogWidgetPrivate
{
  public:
    LogWidgetPrivate(LogWidget *p) : m_this(p)
    {
        auto box = new QVBoxLayout(m_this);
        box->setSpacing(0);
        box->setMargin(3);

        m_edit = new QPlainTextEdit(m_this);
        m_edit->setReadOnly(false);
        m_edit->setUndoRedoEnabled(false);
        box->addWidget(m_edit);
    }

    void clear();
    void append(const QString &text, const QString &type = QString("Info"),
                const QColor &color = QColor(100, 184, 255));
    LogWidget *m_this;

    QVBoxLayout *m_centralLay;
    uint32_t m_totalRow = 0;
    uint32_t m_maxRow = 1000;
    QPlainTextEdit *m_edit = nullptr;
    QTextCharFormat fmt;
};
LogWidget::LogWidget(QWidget *parent) : QWidget(parent),d_ptr(new LogWidgetPrivate(this))
{

    setContentsMargins(2, 10, 2, 10);
}

LogWidget::~LogWidget()
{
}
void LogWidget::setMaxRow(uint32_t newMaxRow)
{
    d_ptr->m_maxRow = newMaxRow;
}

uint32_t LogWidget::getMaxRow() const
{
    return d_ptr->m_maxRow;
}

void LogWidget::clear()
{
    d_ptr->m_totalRow = 0;
    d_ptr->m_edit->clear();
}

void LogWidgetPrivate::append(const QString &text, const QString &type, const QColor &color)
{
    auto time = QTime::currentTime().toString("HH:mm:ss zzz");
    fmt.setForeground(QBrush(color));
    m_edit->mergeCurrentCharFormat(fmt);

    QString content = QString("[%1][%2]%3").arg(time, type, text);
    m_edit->appendPlainText(content);
    m_edit->moveCursor(QTextCursor::End); // 移动光标到最后一行
    m_totalRow++;
    if (m_totalRow >= m_maxRow)
    {
        auto cursor = m_edit->textCursor();
        cursor.setPosition(0);
        cursor.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
        cursor.movePosition(QTextCursor::Down, QTextCursor::KeepAnchor);
        cursor.movePosition(QTextCursor::StartOfLine, QTextCursor::KeepAnchor);
        cursor.removeSelectedText();
    }
}

void LogWidget::append(const QString &text)
{
    d_ptr->append(text);
}