#ifndef TRANSFORMWIDGET_H
#define TRANSFORMWIDGET_H

#include <QWidget>

class Transform;
namespace Ui
{
class TransformWidget;
}

class TransformWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TransformWidget(Transform* transform=nullptr, QWidget *parent = 0);
    ~TransformWidget();

public slots:
    void ChangeTranslationX(int value);
    void ChangeTranslationY(int value);
    void ChangeRotationX(int value);
    void ChangeRotationY(int value);
    void ChangeScaleX(int value);
    void ChangeScaleY(int value);

signals:
    void InspectorUpdate();

private:
    Ui::TransformWidget *ui;
    Transform* transform = nullptr;
};

#endif // TRANSFORMWIDGET_H
