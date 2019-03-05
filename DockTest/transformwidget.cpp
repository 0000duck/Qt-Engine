#include "transformwidget.h"
#include "ui_transformwidget.h"
#include "transform.h"
TransformWidget::TransformWidget(Transform* transform,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TransformWidget)
{
    if(transform!=nullptr)
    {
        ui->spinBox->setValue(transform->position.x());
        ui->spinBox_2->setValue(transform->position.y());
        ui->spinBox_3->setValue(transform->rotation.x());
        ui->spinBox_4->setValue(transform->rotation.y());
        ui->spinBox_5->setValue(transform->scale.x());
        ui->spinBox_6->setValue(transform->scale.y());
    }
    ui->setupUi(this);
}

TransformWidget::~TransformWidget()
{
    delete ui;
}
