#pragma once

#include <QWidget>
class RenderOptionWidgetPrivate;
class QTextEdit;

class RenderOptionWidget : public QWidget
{
	Q_OBJECT

public:
	explicit RenderOptionWidget(QWidget* parent = nullptr);
	~RenderOptionWidget();
	void setTexEdit(QTextEdit* p_edit);

protected slots:
	void updateStyle();
	void nextClicked();

	void renderClicked();

	void saveClicked();

    void fontSizeChanged(int size);

    void fontChanged(const QString& font);

private:
	RenderOptionWidgetPrivate* d_ptr;
	friend class RenderOptionWidgetPrivate;
};
