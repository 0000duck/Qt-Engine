#include "shaperendererwidget.h"
#include "ui_shaperendererwidget.h"
#include <QColorDialog>
#include <QColor>

ShapeRendererWidget::ShapeRendererWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShapeRendererWidget)
{
    ui->setupUi(this);

    connect(ui->fillButton, SIGNAL(clicked()), this, SLOT(FillColor()));
    connect(ui->strokeButton, SIGNAL(clicked()), this, SLOT(StrokeColor()));
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
    }

    //Todo apply color to the gameobject

}

void ShapeRendererWidget::StrokeColor()
{
    QColor color = QColorDialog::getColor(Qt::white, this,"Choose Color");
    if(color.isValid())
    {
        QString qss = QString("background-color:%1").arg(color.name());
        ui->strokeButton->setStyleSheet(qss);
    }

    //Todo apply color to the gameobject

}

