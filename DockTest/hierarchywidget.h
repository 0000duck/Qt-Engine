#ifndef HIERARCHYWIDGET_H
#define HIERARCHYWIDGET_H

#include <QWidget>


namespace Ui {
class HierarchyWidget;
}

class Scene;

class HierarchyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HierarchyWidget(QWidget *parent = 0);
    ~HierarchyWidget();

    void UpdateHierarchy(Scene* scene);


public slots:
    void addEntity();
    void removeEntity();

public:
    Ui::HierarchyWidget *uiHierarchy;

private:
    int entityCounter = 0;
};

#endif // HIERARCHYWIDGET_H
