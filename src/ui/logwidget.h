#pragma once
#include <QWidget>

class QPlainTextEdit;
class LogWidgetPrivate;
class LogWidget : public QWidget
{
    Q_OBJECT

  public:
    explicit LogWidget(QWidget *parent = nullptr);
    ~LogWidget();

  public:
    void setMaxRow(uint32_t newMaxRow);
    uint32_t getMaxRow() const;

    void clear();
    void append(const QString &text);

  private:
    LogWidgetPrivate *d_ptr;
    friend class LogWidgetPrivate;
};