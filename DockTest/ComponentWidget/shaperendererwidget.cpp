#include "shaperendererwidget.h"
#include "Component/shaperenderer.h"
#include "ui_shaperendererwidget.h"
#include <QColorDialog>
#include <QColor>

ShapeRendererWidget::ShapeRendererWidget(ShapeRenderer* shapeRenderer, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShapeRendererWidget)
{
    ui->setupUi(this);
    this->shapeRenderer = shapeRenderer;

    if(this->shapeRenderer != nullptr)
    {
        QString fillColor = QString("background-color:%1").arg(this->shapeRenderer->fillColor.name());
        ui->fillButton->setStyleSheet(fillColor);

        QString stokeColor = QString("background-color:%1").arg(this->shapeRenderer->strokeColor.name());
        ui->strokeButton->setStyleSheet(stokeColor);

        ui->size->setValue(this->shapeRenderer->size);
        ui->strokeThickness->setValue(this->shapeRenderer->thickness);

        ui->strokeStyle->setCurrentIndex(this->shapeRenderer->style);

        ui->shape->setCurrentIndex(this->shapeRenderer->form);
    }

    connect(ui->size, SIGNAL(valueChanged(int)), this, SLOT(ChangeSize(int)));
    connect(ui->fillButton, SIGNAL(clicked()), this, SLOT(FillColor()));
    connect(ui->strokeButton, SIGNAL(clicked()), this, SLOT(StrokeColor()));
    connect(ui->shape, SIGNAL(currentIndexChanged(int)), this, SLOT(ChangeShape(int)));
    connect(ui->strokeStyle, SIGNAL(currentIndexChanged(int)), this, SLOT(ChangeStyle(int)));
    connect(ui->strokeThickness, SIGNAL(valueChanged(int)), this, SLOT(ChangeThickness(int)));

}

ShapeRendererWidget::~ShapeRendererWidget()
{
    delete ui;
}

void ShapeRendererWidget::FillColor()
{
    QColor color = QColorDialog::getColor(Qt::white, this,"Choose Color");
    if(color.isValid())
    {
        QString qss = QString("background-color:%1").arg(color.name());
        ui->fillButton->setStyleSheet(qss);

        if(shapeRenderer == nullptr)
            return;

        shapeRenderer->fillColor = color;

    }
    emit InspectorUpdate();
}

void ShapeRendererWidget::StrokeColor()
{
    QColor color = QColorDialog::getColor(Qt::white, this,"Choose Color");
    if(color.isValid())
    {
        QString qss = QString("background-color:%1").arg(color.name());
        ui->strokeButton->setStyleSheet(qss);

        if(shapeRenderer == nullptr)
            return;

        shapeRenderer->strokeColor = color;

    }
    emit InspectorUpdate();
}

void ShapeRendererWidget::ChangeSize(int size)
{
    if(shapeRenderer == nullptr)
        return;
    shapeRenderer->size = size;
    emit InspectorUpdate();
}

void ShapeRendererWidget::ChangeThickness(int thickness)
{
    if(shapeRenderer == nullptr)
        return;
    shapeRenderer->thickness = thickness;
    emit InspectorUpdate();
}

void ShapeRendererWidget::ChangeShape(int index)
{
    if(shapeRenderer == nullptr)
        return;

    shapeRenderer->form = static_cast<ShapeForm>(index);
    emit InspectorUpdate();
}

void ShapeRendererWidget::ChangeStyle(int index)
{
    if(shapeRenderer == nullptr)
        return;

    shapeRenderer->style = static_cast<StrokeStyle>(index);
    emit InspectorUpdate();
}
