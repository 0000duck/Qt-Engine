#include "hierarchywidget.h"
#include "ui_hierarchywidget.h"
#include "scene.h"
#include <QStandardItemModel>
#include <QStandardItem>
#include "gameobject.h"

HierarchyWidget::HierarchyWidget(QWidget *parent) :
    QWidget(parent),
    uiHierarchy(new Ui::HierarchyWidget)
{
    uiHierarchy->setupUi(this);

    // Link Add/Remove Entry functions to Buttons
    connect(uiHierarchy->AddEntity,SIGNAL(clicked()), this, SLOT(addEntity()));
    connect(uiHierarchy->RemoveEntity,SIGNAL(clicked()), this, SLOT(removeEntity()));

    entityCounter = 0;
}

HierarchyWidget::~HierarchyWidget()
{
    delete uiHierarchy;
}

void HierarchyWidget::UpdateHierarchy(Scene* scene)
{
    uiHierarchy->listWidget->clear();
    for(int i=0;i<scene->gameObjects.count();i++)
    {
        GameObject* item = scene->gameObjects[i];
        uiHierarchy->listWidget->addItem(item->name);
    }
}



void HierarchyWidget::addEntity()
{
    QListWidgetItem *item = new QListWidgetItem();
    QString entityName = "Entity " + QString::number(entityCounter);
    item->setText(entityName);
    uiHierarchy->listWidget->insertItem(entityCounter, item);
    entityCounter++;
}

void HierarchyWidget::removeEntity()
{
    QList<QListWidgetItem*> items = uiHierarchy->listWidget->selectedItems();

    foreach(QListWidgetItem* item, items)
    {
        uiHierarchy->listWidget->removeItemWidget(item);
        delete item;
    }
}
