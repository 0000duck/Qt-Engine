#ifndef TRANSFORMWIDGET_H
#define TRANSFORMWIDGET_H

#include <QWidget>

class Transform;
namespace Ui {
class TransformWidget;
}

class TransformWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TransformWidget(Transform* transform=nullptr, QWidget *parent = 0);

    ~TransformWidget();

private:
    Ui::TransformWidget *ui;
};

#endif // TRANSFORMWIDGET_H
