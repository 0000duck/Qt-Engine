#include "myopenglwidget.h"
#include "ui_myopenglwidget.h"

MyOpenGlWidget::MyOpenGlWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyOpenGlWidget)
{
    ui->setupUi(this);
}

MyOpenGlWidget::~MyOpenGlWidget()
{
    delete ui;
}
