#include "meshrendererwidget.h"
#include "Component/meshrenderer.h"
#include "ui_meshrendererwidget.h"
#include "Mesh/mesh.h"
#include "Mesh/submesh.h"
#include <QDir>
#include <QVector>
#include <QComboBox>
#include <QVBoxLayout>
#include <QOpenGLTexture>
#include <QHBoxLayout>
#include <QLabel>


MeshRendererWidget::MeshRendererWidget(MeshRenderer* meshRenderer, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MeshRendererWidget)
{
    ui->setupUi(this);

    // Get Models
    QDir dir;
    dir.setPath("Models");
    dir.setNameFilters(QStringList("*.obj"));
    dir.setFilter(QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks);

    models = dir.entryList();
    ui->comboBox->clear();
    ui->comboBox->addItem("Cube");
    ui->comboBox->addItem("Sphere");
    ui->comboBox->addItem("Plane");
    ui->comboBox->addItems(models);

    // --------- MODEL MANAGEMENT ---------
    if(meshRenderer != nullptr)
    {
        this->meshRenderer = meshRenderer;

        // Update Mesh Combobox
        ui->comboBox->setCurrentText(QString(this->meshRenderer->meshName.c_str()));

    }

    connect(ui->comboBox, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(ChangeMesh(const QString&)));

    // --------- TEXTURE MANAGEMENT ---------
    UpdateTextures();
}

void remove ( QLayout* layout )
{
    QLayoutItem* child;
    while ( layout->count() != 0 ) {
        child = layout->takeAt ( 0 );
        if ( child->layout() != 0 ) {
            remove ( child->layout() );
        } else if ( child->widget() != 0 ) {
            delete child->widget();
        }

        delete child;
    }
}

void MeshRendererWidget::UpdateTextures()
{
    // Delete all ComboBoxes
    if(ui->SubmeshesLayout != nullptr)
    {
        remove(ui->SubmeshesLayout);

        /*QLayoutItem* item;
        while ( ( item = ui->SubmeshesLayout->takeAt( 0 ) ) != NULL )
        {
           delete item->layout();
           //delete item->widget();
           delete item;
        }*/
    }

    // Get Models
    QDir dir;
    dir.setPath("Textures");
    dir.setNameFilters(QStringList("*.png"));
    dir.setFilter(QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks);
    models = dir.entryList();

    for(int i = 0; i < meshRenderer->GetMesh()->GetSubMeshes().count(); i++)
    {
        auto hb = new QHBoxLayout();

        const char* name = meshRenderer->GetMesh()->GetSubMeshes().at(i)->meshName.c_str();
        auto nl = new QLabel(QString(name));
        nl->setStyleSheet("font-style: normal");

        auto cb = new QComboBox();
        cb->setObjectName(QString::fromStdString(std::to_string(i)));
        cb->addItem("-");
        cb->addItems(models);
        cb->setStyleSheet("font-style: normal");      
        cb->setCurrentText(QString(meshRenderer->GetMesh()->GetSubMeshes().at(i)->textureName.c_str()));

        hb->addWidget(nl);
        hb->addWidget(cb);

        connect(cb, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(ChangeTexture(const QString&)));

        ui->SubmeshesLayout->addLayout(hb);
        //ui->SubmeshesLayout->addWidget(nl);
        //ui->SubmeshesLayout->addWidget(cb);
    }
}

void MeshRendererWidget::ChangeTexture(const QString &texture)
{
    int index = std::stoi(sender()->objectName().toStdString());

    std::string path = "Textures/";
    path += texture.toStdString();

    delete meshRenderer->GetMesh()->GetSubMeshes().at(index)->texture;
    meshRenderer->GetMesh()->GetSubMeshes().at(index)->texture = new QOpenGLTexture(QImage(path.c_str()));
    meshRenderer->GetMesh()->GetSubMeshes().at(index)->textureName = texture.toStdString();

    emit InspectorUpdate();
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
