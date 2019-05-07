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
    void UpdateTextures();

signals:
    void InspectorUpdate();

public slots:
    void ChangeMesh(const QString& mesh);
    void ChangeTexture(int index, const QString& texture);


public:
    MeshRenderer *meshRenderer = nullptr;
    QStringList models;

private:
    Ui::MeshRendererWidget *ui;
};

#endif // MESHRENDERERWIDGET_H
