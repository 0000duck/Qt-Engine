#include "shaperendererwidget.h"
#include "ui_shaperendererwidget.h"
#include <QColorDialog>
#include <QColor>

ShapeRendererWidget::ShapeRendererWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShapeRendererWidget)
{
    ui->setupUi(this);

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(FillColor()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(StrokeColor()));
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
        ui->pushButton->setStyleSheet(qss);
    }

    //Todo apply color to the gameobject

}

void ShapeRendererWidget::StrokeColor()
{
    QColor color = QColorDialog::getColor(Qt::white, this,"Choose Color");
    if(color.isValid())
    {
        QString qss = QString("background-color:%1").arg(color.name());
        ui->pushButton_2->setStyleSheet(qss);
    }

    //Todo apply color to the gameobject

}

