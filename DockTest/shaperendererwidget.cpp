#include "shaperendererwidget.h"
#include "ui_shaperendererwidget.h"
#include <QColorDialog>
#include <QColor>

ShapeRendererWidget::ShapeRendererWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShapeRendererWidget)
{
    ui->setupUi(this);

    connect(ui->pushButton, SIGNAL(triggered()), this, SLOT(on_actionFillColor_triggered()));

}

ShapeRendererWidget::~ShapeRendererWidget()
{
    delete ui;
}

void ShapeRendererWidget::on_actionFillColor_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white, this,"Choose Color");
    if(color.isValid())
    {
    }
}
