#ifndef MESHRENDERERWIDGET_H
#define MESHRENDERERWIDGET_H

#include <QWidget>

class MeshRenderer;

namespace Ui
{
class MeshRendererWidget;
}

class MeshRendererWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MeshRendererWidget(MeshRenderer *meshRenderer, QWidget *parent = nullptr);
    ~MeshRendererWidget();

signals:
    void InspectorUpdate();
public:
    MeshRenderer *meshRenderer = nullptr;
private:
    Ui::MeshRendererWidget *ui;
};

#endif // MESHRENDERERWIDGET_H
