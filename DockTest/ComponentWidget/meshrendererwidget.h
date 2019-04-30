#ifndef MESHRENDERERWIDGET_H
#define MESHRENDERERWIDGET_H

#include <QWidget>
#include <QString>

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

    void Clear();

signals:
    void InspectorUpdate();

public slots:
    void changeMesh(const QString& mesh);


public:
    MeshRenderer *meshRenderer = nullptr;

private:
    Ui::MeshRendererWidget *ui;
};

#endif // MESHRENDERERWIDGET_H
