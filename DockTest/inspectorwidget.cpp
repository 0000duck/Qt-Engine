#include "inspectorwidget.h"
#include "transformwidget.h"
#include "shaperendererwidget.h"

#include <QLayout>
#include <QVBoxLayout>
#include <QSpacerItem>
#include "gameobject.h"
#include "component.h"
InspectorWidget::InspectorWidget(QWidget *parent) : QWidget(parent)
{
    /*
    // Create subwidgets independently
    TransformWidget *transformWidget = new TransformWidget();
    ShapeRendererWidget *shapeRendererWidget = new ShapeRendererWidget();


    QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Create a vertical layout for this widget
    QVBoxLayout *layout = new QVBoxLayout();

    // Add all elements to the layout
    layout->addWidget(transformWidget);
    layout->addWidget(shapeRendererWidget);
    layout->addItem(spacer);

    // Set the layout for this widget
    setLayout(layout);
*/

}

InspectorWidget::~InspectorWidget()
{

}

void InspectorWidget::UpdateInspector(GameObject* go)
{
    DeleteLayout();
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
void InspectorWidget::DeleteLayout()
{

    QLayout * layout = new QVBoxLayout();

    // ... create complicated layout ...

    // completely delete layout and sublayouts
    QLayoutItem * item;
    QLayout * sublayout;
    QWidget * widget;
    while ((item = layout->takeAt(0))) {
        if ((sublayout = item->layout()) != 0) {/* do the same for sublayout*/}
        else if ((widget = item->widget()) != 0) {widget->hide(); delete widget;}
        else {delete item;}
    }

    // then finally
    delete layout;
}
QWidget* InspectorWidget::GetWidget(Component* component)
{
    switch (component->type) {
    case Type::COMP_TRANSFORM:
        return new TransformWidget((Transform*)component);
        break;
    default:
        break;
    }
}
