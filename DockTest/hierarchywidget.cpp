#include "hierarchywidget.h"
#include "ui_hierarchywidget.h"

#include <QStandardItemModel>
#include <QStandardItem>


HierarchyWidget::HierarchyWidget(QWidget *parent) :
    QWidget(parent),
    uiHierarchy(new Ui::HierarchyWidget)
{
    uiHierarchy->setupUi(this);

    // Link Add/Remove Entry functions to Buttons
    connect(uiHierarchy->AddEntity,SIGNAL(clicked()), this, SLOT(addEntity()));
    connect(uiHierarchy->RemoveEntity,SIGNAL(clicked()), this, SLOT(removeEntity()));
}

HierarchyWidget::~HierarchyWidget()
{
    delete uiHierarchy;
}

void HierarchyWidget::addEntity()
{
    QListWidgetItem *item = new QListWidgetItem();
    item->setText("Entity");
    uiHierarchy->listWidget->insertItem(0, item);
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
