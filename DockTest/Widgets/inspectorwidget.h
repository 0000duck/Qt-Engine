#ifndef INSPECTORWIDGET_H
#define INSPECTORWIDGET_H

#include <QWidget>

class GameObject;
class Component;
class QVBoxLayout;

class InspectorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit InspectorWidget(QWidget *parent = nullptr);
    ~InspectorWidget();

    void UpdateInspector(GameObject* go);
    void DeleteLayout();

signals:
    void MainUpdate();

private:
    QWidget* GetWidget(Component* component);

private:
    QVBoxLayout *layout=nullptr;
};

#endif // INSPECTORWIDGET_H
