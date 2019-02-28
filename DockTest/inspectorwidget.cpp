#include "inspectorwidget.h"
#include "transformwidget.h"
#include "shaperendererwidget.h"

#include <QLayout>
#include <QVBoxLayout>
#include <QSpacerItem>

InspectorWidget::InspectorWidget(QWidget *parent) : QWidget(parent)
{
    // Create subwidgets independently
    TransformWidget *transformWidget = new TransformWidget;
    ShapeRendererWidget *shapeRendererWidget = new ShapeRendererWidget;


    QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Create a vertical layout for this widget
    QVBoxLayout *layout = new QVBoxLayout;

    // Add all elements to the layout
    layout->addWidget(transformWidget);
    layout->addWidget(shapeRendererWidget);
    layout->addItem(spacer);

    // Set the layout for this widget
    setLayout(layout);

}

InspectorWidget::~InspectorWidget()
{
}
