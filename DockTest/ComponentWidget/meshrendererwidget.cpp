#include "meshrendererwidget.h"
#include "Component/meshrenderer.h"
#include "ui_meshrendererwidget.h"
#include <QDir>

MeshRendererWidget::MeshRendererWidget(MeshRenderer* meshRenderer, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MeshRendererWidget)
{
    ui->setupUi(this);

    if(meshRenderer != nullptr)
    {
        this->meshRenderer = meshRenderer;

        switch(meshRenderer->shape)
        {
        case Shape::CUBE:
            ui->comboBox->setCurrentIndex(0);
        break;

        case Shape::SPHERE:
            ui->comboBox->setCurrentIndex(1);
        break;

        case Shape::PLANE:
            ui->comboBox->setCurrentIndex(2);

        break;
        }
    }


    // Get Models
    QDir dir;
    dir.setPath("Models");
    dir.setNameFilters(QStringList("*.obj"));
    dir.setFilter(QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks);

    models = dir.entryList();
    ui->comboBox->addItems(models);

    connect(ui->comboBox, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(changeMesh(const QString&)));


}

void MeshRendererWidget::changeMesh(const QString& meshName)
{
    meshRenderer->Clear();
    meshRenderer->ChangeShape(meshName);

    emit InspectorUpdate();
}

MeshRendererWidget::~MeshRendererWidget()
{
    delete ui;
}
