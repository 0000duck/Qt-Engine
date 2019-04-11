#include "meshrendererwidget.h"
#include "ui_meshrendererwidget.h"

MeshRendererWidget::MeshRendererWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MeshRendererWidget)
{
    ui->setupUi(this);
}

MeshRendererWidget::~MeshRendererWidget()
{
    delete ui;
}
