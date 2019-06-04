#include "ui_infowidget.h"
#include "infowidget.h"
#include "GameObject/gameobject.h"

InfoWidget::InfoWidget(GameObject* go,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InfoWidget)
{
    ui->setupUi(this);
    this->go = go;
    if(this->go!=nullptr)
    {
        ui->goName->setText(this->go->name);
    }
    connect(ui->goName, SIGNAL(textChanged(QString)), this, SLOT(SetName(QString)));
}

InfoWidget::~InfoWidget()
{
    delete ui;
}

void InfoWidget::SetName(QString name)
{
    if(go->name == name)
        return;
    go->name = name;
    emit InspectorUpdate();
}

void InfoWidget::SetActive(bool active)
{
    if(go->active == active)
        return;
    go->active = active;
    emit InspectorUpdate();
}

void InfoWidget::SetVisible(bool active)
{
    if(go->visible == active)
        return;
    go->visible = active;
    emit InspectorUpdate();
}
