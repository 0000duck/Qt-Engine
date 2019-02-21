#include "inspectorwidget.h"
#include "transformwidget.h"
//#include "meshrendererwidget.h"
#include <QLayout>
#include <QVBoxLayout>
#include <QSpacerItem>

InspectorWidget::InspectorWidget(QWidget *parent) : QWidget(parent)
{
    // Create subwidgets independently
    TransformWidget *transformWidget = new TransformWidget;
    //MeshRenderWidget *meshRendererWidget = new MeshRendererWidget;
    QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Create a vertical layout for this widget
    QVBoxLayout *layout = new QVBoxLayout;

    // Add all elements to the layout
    layout->addWidget(transformWidget);
    //layout->addWidget(meshRendererWidget);
    layout->addItem(spacer);

    // Set the layout for this widget
    setLayout(layout);

}

InspectorWidget::~InspectorWidget()
{
}
