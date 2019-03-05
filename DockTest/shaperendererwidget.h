#ifndef SHAPERENDERERWIDGET_H
#define SHAPERENDERERWIDGET_H

#include <QWidget>

namespace Ui {
class ShapeRendererWidget;
}

class ShapeRendererWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ShapeRendererWidget(QWidget *parent = nullptr);
    ~ShapeRendererWidget();

private slots:
    void FillColor();
    void StrokeColor();

private:
    Ui::ShapeRendererWidget *ui;
};

#endif // SHAPERENDERERWIDGET_H
