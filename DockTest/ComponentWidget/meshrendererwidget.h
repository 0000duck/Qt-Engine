#ifndef MESHRENDERERWIDGET_H
#define MESHRENDERERWIDGET_H

#include <QWidget>

namespace Ui {
class MeshRendererWidget;
}

class MeshRendererWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MeshRendererWidget(QWidget *parent = nullptr);
    ~MeshRendererWidget();

signals:
    void InspectorUpdate();
public:
    //MeshRenderer *meshRenderer = nullptr;
private:
    Ui::MeshRendererWidget *ui;
};

#endif // MESHRENDERERWIDGET_H
