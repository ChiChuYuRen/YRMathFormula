#pragma once

#include <QTextEdit>

class TexEdit : public QTextEdit
{
    Q_OBJECT
  public:
    explicit TexEdit(QWidget *parent = nullptr);
    ~TexEdit();
};
