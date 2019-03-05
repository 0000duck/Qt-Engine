#ifndef INSPECTORWIDGET_H
#define INSPECTORWIDGET_H

#include <QWidget>

class GameObject;
class Component;

class InspectorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit InspectorWidget(QWidget *parent = nullptr);
    ~InspectorWidget();

    void UpdateInspector(GameObject* go);
    QWidget* GetWidget(Component* component);

};

#endif // INSPECTORWIDGET_H
