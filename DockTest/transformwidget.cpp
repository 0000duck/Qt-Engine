#include "transformwidget.h"
#include "ui_transformwidget.h"
#include "transform.h"
TransformWidget::TransformWidget(Transform* transform,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TransformWidget)
{


    ui->setupUi(this);

    if(transform!=nullptr)
    {
        this->transform = transform;
        ui->TranslationX->setValue(transform->position.x());
        ui->TranslationY->setValue(transform->position.y());
        ui->RotationX->setValue(transform->rotation.x());
        ui->RotationY->setValue(transform->rotation.y());
        ui->ScaleX->setValue(transform->scale.x());
        ui->ScaleY->setValue(transform->scale.y());
    }

    connect(ui->TranslationX, SIGNAL(valueChanged(int)), this, SLOT(ChangeTranslationX(int)));
    connect(ui->TranslationY, SIGNAL(valueChanged(int)), this, SLOT(ChangeTranslationY(int)));
    connect(ui->RotationX, SIGNAL(valueChanged(int)), this, SLOT(ChangeRotationX(int)));
    connect(ui->RotationY, SIGNAL(valueChanged(int)), this, SLOT(ChangeRotationY(int)));
    connect(ui->ScaleX, SIGNAL(valueChanged(int)), this, SLOT(ChangeScaleX(int)));
    connect(ui->ScaleY, SIGNAL(valueChanged(int)), this, SLOT(ChangeScaleY(int)));
}

TransformWidget::~TransformWidget()
{
    delete ui;
}


void TransformWidget::ChangeTranslationX(int value)
{
    if(transform==nullptr)
    {
        printf("Transform is null!\n");
        return;
    }
    transform->position.setX(value);
    emit InspectorUpdate();
}
void TransformWidget::ChangeTranslationY(int value)
{
    if(transform==nullptr)
    {
        printf("Transform is null!\n");
        return;
    }
    transform->position.setY(value);
    emit InspectorUpdate();
}
void TransformWidget::ChangeRotationX(int value)
{
    if(transform==nullptr)
    {
        printf("Transform is null!\n");
        return;
    }
    transform->rotation.setX(value);
    emit InspectorUpdate();
}
void TransformWidget::ChangeRotationY(int value)
{
    if(transform==nullptr)
    {
        printf("Transform is null!\n");
        return;
    }
    transform->rotation.setY(value);
    emit InspectorUpdate();
}
void TransformWidget::ChangeScaleX(int value)
{
    if(transform==nullptr)
    {
        printf("Transform is null!\n");
        return;
    }
    transform->scale.setX(value);
    emit InspectorUpdate();
}
void TransformWidget::ChangeScaleY(int value)
{
    if(transform==nullptr)
    {
        printf("Transform is null!\n");
        return;
    }
    transform->scale.setY(value);
    emit InspectorUpdate();
}
