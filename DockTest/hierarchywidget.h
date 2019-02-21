#ifndef HIERARCHYWIDGET_H
#define HIERARCHYWIDGET_H

#include <QWidget>

namespace Ui {
class HierarchyWidget;
}

class HierarchyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HierarchyWidget(QWidget *parent = 0);
    ~HierarchyWidget();

public slots:
    void addEntity();
    void removeEntity();

private:
    Ui::HierarchyWidget *uiHierarchy;
};

#endif // HIERARCHYWIDGET_H
