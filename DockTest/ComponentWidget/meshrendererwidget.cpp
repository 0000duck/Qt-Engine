#include "meshrendererwidget.h"
#include "ui_meshrendererwidget.h"

MeshRendererWidget::MeshRendererWidget(MeshRenderer* meshRenderer, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MeshRendererWidget)
{
    ui->setupUi(this);
    this->meshRenderer = meshRenderer;
}

MeshRendererWidget::~MeshRendererWidget()
{
    delete ui;
}
