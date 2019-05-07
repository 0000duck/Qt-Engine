#include "meshrendererwidget.h"
#include "Component/meshrenderer.h"
#include "ui_meshrendererwidget.h"
#include "Mesh/mesh.h"
#include "Mesh/submesh.h"
#include <QDir>
#include <QVector>
#include <QComboBox>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QOpenGLTexture>

MeshRendererWidget::MeshRendererWidget(MeshRenderer* meshRenderer, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MeshRendererWidget)
{
    ui->setupUi(this);

    // --------- MODEL MANAGEMENT ---------
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

    connect(ui->comboBox, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(ChangeMesh(const QString&)));

    // --------- TEXTURE MANAGEMENT ---------
    UpdateTextures();
}

void MeshRendererWidget::UpdateTextures()
{
    // Delete all ComboBoxes
    if(ui->SubmeshesLayout != nullptr)
    {
        QLayoutItem* item;
        while ( ( item = ui->SubmeshesLayout->takeAt( 0 ) ) != NULL )
        {
           delete item->widget();
           delete item;
        }
    }

    // Get Models
    QDir dir;
    dir.setPath("Textures");
    dir.setNameFilters(QStringList("*.png"));
    dir.setFilter(QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks);
    models = dir.entryList();

    for(int i = 0; i < meshRenderer->GetMesh()->GetSubMeshes().count(); i++)
    {
        auto cb = new QComboBox();

        cb->setObjectName(QString::fromStdString(std::to_string(i)));
        cb->addItems(models);
        cb->setStyleSheet("font-style: normal");

        connect(cb, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(ChangeTexture(const QString&)));

        ui->SubmeshesLayout->addWidget(cb);
    }
}

void MeshRendererWidget::ChangeTexture(const QString &texture)
{
    printf("Changing TEXTURE\n");
    int index = std::stoi(sender()->objectName().toStdString());

    std::string path = "Textures/";
    path += texture.toStdString();

    delete meshRenderer->GetMesh()->GetSubMeshes().at(index)->texture;
    meshRenderer->GetMesh()->GetSubMeshes().at(index)->texture = new QOpenGLTexture(QImage(path.c_str()));
    printf("Changed TEXTURE\n");
}


void MeshRendererWidget::ChangeMesh(const QString& meshName)
{
    meshRenderer->Clear();
    meshRenderer->ChangeShape(meshName);
    UpdateTextures();

    emit InspectorUpdate();
}

MeshRendererWidget::~MeshRendererWidget()
{
    delete ui;
}
