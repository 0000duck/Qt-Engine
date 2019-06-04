#include "inspectorwidget.h"
#include "transformwidget.h"
#include "shaperendererwidget.h"
#include "meshrendererwidget.h"
#include "Component/infowidget.h"
#include "GameObject/gameobject.h"
#include "Component/component.h"
#include <QLayout>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QTextEdit>


InspectorWidget::InspectorWidget(QWidget *parent) : QWidget(parent)
{

}

InspectorWidget::~InspectorWidget()
{

}

void InspectorWidget::UpdateInspector(GameObject* go)
{
    DeleteLayout();

    QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout = new QVBoxLayout();

    QWidget* widget = new InfoWidget(go);

    connect(widget,SIGNAL(InspectorUpdate()),this,SIGNAL(MainUpdate()));

    layout->addWidget(widget);

    for(int i =0;i<go->components.size();i++)
    {
        Component* component = go->components[i];
        layout->addWidget(GetWidget(component));
    }
    layout->addItem(spacer);
    setLayout(layout);

}

void InspectorWidget::DeleteLayout()
{
    if(layout==nullptr)
        return;

    // Completely delete layout and sublayouts
    QLayoutItem * item;
    QLayout * sublayout;
    QWidget * widget;

    while ((item = layout->takeAt(0)))
    {
        if ((sublayout = item->layout()) != 0) { /* do the same for sublayout*/ }
        else if ((widget = item->widget()) != 0) { widget->hide(); delete widget; }
        else { delete item; }
    }

    // then finally
    delete layout;

    layout = nullptr;
}

QWidget* InspectorWidget::GetWidget(Component* component)
{
    switch (component->type)
    {
    case Type::COMP_TRANSFORM:
    {
        TransformWidget* widget = new TransformWidget((Transform*)component);
        connect(widget, SIGNAL(InspectorUpdate()), this, SIGNAL(MainUpdate()));
        return widget;
    }
    case Type::COMP_MESH_RENDERER:
    {
        MeshRendererWidget* widget = new MeshRendererWidget((MeshRenderer*)component);
        connect(widget, SIGNAL(InspectorUpdate()), this, SIGNAL(MainUpdate()));
        return widget;
    }
    default:
        break;
    }

    return nullptr;
}
