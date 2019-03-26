#include "Widgets/infowidget.h"
#include "Scene/gameobject.h"
#include "ui_infowidget.h"

InfoWidget::InfoWidget(GameObject* go,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InfoWidget)
{
    ui->setupUi(this);
    this->go = go;

    if(this->go!=nullptr)
    {
        ui->goName->setText(this->go->name);
        ui->isActive->setChecked(this->go->active);
        ui->isVisible->setChecked(this->go->visible);
    }

    connect(ui->goName, SIGNAL(textChanged(QString)), this, SLOT(SetName(QString)));
    connect(ui->isActive, SIGNAL(clicked(bool)), this, SLOT(SetActive(bool)));
    connect(ui->isVisible, SIGNAL(clicked(bool)), this, SLOT(SetVisible(bool)));
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
