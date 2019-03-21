#include "ui_hierarchywidget.h"
#include "hierarchywidget.h"
#include "Scene/scene.h"
#include "GameObject/gameobject.h"
#include "Main/mainwindow.h"
#include <QStandardItemModel>
#include <QStandardItem>

HierarchyWidget::HierarchyWidget(QWidget *parent) :
    QWidget(parent),
    uiHierarchy(new Ui::HierarchyWidget)
{
    uiHierarchy->setupUi(this);

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
