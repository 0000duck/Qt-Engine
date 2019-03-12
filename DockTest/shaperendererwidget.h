#ifndef SHAPERENDERERWIDGET_H
#define SHAPERENDERERWIDGET_H

#include <QWidget>
class ShapeRenderer;
namespace Ui {
class ShapeRendererWidget;
}

class ShapeRendererWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ShapeRendererWidget(ShapeRenderer* shapeRenderer,QWidget *parent = nullptr);
    ~ShapeRendererWidget();

private slots:
    void FillColor();
    void StrokeColor();
    void ChangeSize(int);
    void ChangeTickness(int);
    void ChangeShape(int);
    void ChangeStyle(int);
signals:
    void InspectorUpdate();
public:
    ShapeRenderer *shapeRenderer = nullptr;
private:
    Ui::ShapeRendererWidget *ui;
};

#endif // SHAPERENDERERWIDGET_H
