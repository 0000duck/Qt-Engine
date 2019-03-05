#include "inspectorwidget.h"
#include "transformwidget.h"
#include "shaperendererwidget.h"
#include "infowidget.h"
#include "gameobject.h"
#include "component.h"
#include <QLayout>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QTextEdit>



InspectorWidget::InspectorWidget(QWidget *parent) : QWidget(parent)
{
    // Create subwidgets independently
    TransformWidget *transformWidget = new TransformWidget();
    ShapeRendererWidget *shapeRendererWidget = new ShapeRendererWidget();
    InfoWidget* infoWidget = new InfoWidget();

    // Create a vertical layout for this widget
    QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding);
    QVBoxLayout *layout = new QVBoxLayout();

    // Add all elements to the layout
    layout->addWidget(infoWidget);
    layout->addWidget(transformWidget);
    layout->addWidget(shapeRendererWidget);
    layout->addItem(spacer);

    // Set the layout for this widget
    setLayout(layout);

    //delete layout();

}

InspectorWidget::~InspectorWidget()
{

}

void InspectorWidget::UpdateInspector(GameObject* go)
{

    QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding);
    QVBoxLayout *layout = new QVBoxLayout();

    for(int i =0;i<go->components.size();i++)
    {
        Component* component = go->components[i];
        layout->addWidget(GetWidget(component));
    }
    layout->addItem(spacer);
    setLayout(layout);

}
QWidget* InspectorWidget::GetWidget(Component* component)
{
    switch (component->type) {
    case Type::COMP_TRANSFORM:
        return new TransformWidget();
        break;
    default:
        break;
    }
}
