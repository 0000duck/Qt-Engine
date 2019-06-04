#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_rendering.h"
#include "ComponentWidget/inspectorwidget.h"
#include "ComponentWidget/hierarchywidget.h"
#include "ui_hierarchywidget.h"
#include "ComponentWidget/shaperendererwidget.h"
#include "Scene/scene.h"
#include "GameObject/gameobject.h"
#include "Component/meshrenderer.h"

#include <QListWidget>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>
#include <QStandardPaths>
#include <QFileDialog>
#include <QMessageBox>
#include <QMimeData>
#include <QUrl>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    uiMainWindow(new Ui::MainWindow)
{
    uiMainWindow->setupUi(this);

    // All tab position on top of the docking area
    setTabPosition(Qt::AllDockWidgetAreas,QTabWidget::TabPosition::North);

    // Create the Inspector Widget and add it to the Inspector
    uiInspector = new InspectorWidget();
    uiMainWindow->Inspector->setWidget(uiInspector);

    // Create the Hierarchy Widget and add it to the Hierarchy
    uiHierarchy = new HierarchyWidget();
    uiMainWindow->Hierarchy->setWidget(uiHierarchy);

    // Get Scenes
    scene = new Scene();
    openGLScene = uiMainWindow->openGLWidget;

    openGLScene->GetScene(scene);


    // Connect all the actions
    connect(uiMainWindow->actionOpenProject, SIGNAL(triggered()), this, SLOT(openProject()));
    connect(uiMainWindow->actionSaveProject, SIGNAL(triggered()), this, SLOT(saveProject()));
    connect(uiMainWindow->actionExit, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(uiHierarchy->uiHierarchy->AddEntity, SIGNAL(clicked()),this,SLOT(addGameObject()));
    connect(uiHierarchy->uiHierarchy->RemoveEntity,SIGNAL(clicked()),this,SLOT(removeGameObject()));
    connect(uiHierarchy->uiHierarchy->listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(showGameObjectInspector(QListWidgetItem*)));
    connect(uiInspector,SIGNAL(MainUpdate()),this,SLOT(updateMain()));

    connect(uiMainWindow->actionCube, SIGNAL(triggered()),this, SLOT(createCube()));
    connect(uiMainWindow->actionSphere, SIGNAL(triggered()),this, SLOT(createSphere()));
    connect(uiMainWindow->actionPlane, SIGNAL(triggered()),this, SLOT(createPlane()));
    connect(uiMainWindow->actionPatrick, SIGNAL(triggered()),this, SLOT(createPatrick()));

    connect(uiMainWindow->renderView, SIGNAL(currentIndexChanged(int)), this, SLOT(changeRenderView(int)));
    connect(uiMainWindow->ppEffect, SIGNAL(currentIndexChanged(int)), this, SLOT(changePPEffect(int)));
    connect(uiMainWindow->lightIntensity, SIGNAL(valueChanged(int)), this, SLOT(updateLightIntensity(int)));
    connect(uiMainWindow->blurIntensity, SIGNAL(valueChanged(int)), this, SLOT(updateBlurIntensity(int)));
    connect(uiMainWindow->glowIntensity, SIGNAL(valueChanged(int)), this, SLOT(updateGlowIntensity(int)));

    connect(uiMainWindow->restoreValues,SIGNAL(clicked()),this,SLOT(restoreSliderValues()));

    //connect(uiMainWindow->actionSaveScreenShot,SIGNAL(triggered()),uiMainWindow->widget, SLOT(TakeScreenShot()));
    //connect(uiMainWindow->actionUndo, SIGNAL(triggered()), this, SLOT(undo()));
    //connect(uiMainWindow->actionRedo, SIGNAL(triggered()), this, SLOT(redo()));

    setAcceptDrops(true);
}

MainWindow::~MainWindow()
{
    delete uiMainWindow;
}

void MainWindow::openProject()
{
    printf("Open project\n");

    QString fileName = QFileDialog::getOpenFileName(this,
           tr("Open Scene"), "",
           tr("JSON (*.json);;All Files (*)"));

    if(fileName.isEmpty())
        return;
    else
    {
        QFile file(fileName);
        if(!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::information(this, tr("Unable to open file"),
                                     file.errorString());
            return;
        }
        else
        {
            QByteArray saveData = file.readAll();
            QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

            scene->Read(loadDoc.object());
        }
    }

    updateMain();
}

void MainWindow::saveProject()
{
    printf("Save project\n");

    QString fileName = QFileDialog::getSaveFileName(this,
         tr("Save Scene"),"",
         tr("JSON (*.json);;All Files (*)"));

    if (fileName.isEmpty())
        return;
    else
    {
        QFile file(fileName);
        if(!file.open(QIODevice::WriteOnly))
        {
            QMessageBox::information(this, tr("Unable to open file"),
                                     file.errorString());
            return;
        }
        else
        {
            QJsonObject sceneObject;
            scene->Write(sceneObject);

            QJsonDocument saveDoc(sceneObject);

            file.write(saveDoc.toJson());
        }
    }
}

void MainWindow::undo()
{
    printf("Undo\n");
}

void MainWindow::redo()
{
    printf("Redo\n");
}

void MainWindow::createCube()
{
    printf("Create Cube\n");

    if(scene==nullptr)
        return;

    GameObject *go = new GameObject();
    TryChangeName(*go);

    go->AddMesh(Shape::CUBE);

    scene->gameObjects.push_back(go);
    updateMain();
}

void::MainWindow::createSphere()
{
    printf("Create Sphere\n");

    if(scene==nullptr)
        return;

    GameObject *go = new GameObject();
    TryChangeName(*go);

    go->AddMesh(Shape::SPHERE);

    scene->gameObjects.push_back(go);
    updateMain();
}

void::MainWindow::createPlane()
{
    printf("Create Plane\n");

    if(scene==nullptr)
        return;

    GameObject *go = new GameObject();
    TryChangeName(*go);

    go->AddMesh(Shape::PLANE);

    scene->gameObjects.push_back(go);
    updateMain();
}

void::MainWindow::createPatrick()
{
    printf("Create Patrick\n");

    if(scene==nullptr)
        return;

    GameObject *go = new GameObject();
    TryChangeName(*go);

    go->AddMesh(Shape::CUSTOM, "Patrick.obj");

    scene->gameObjects.push_back(go);
    updateMain();
}

void MainWindow::changeRenderView(int index)
{
    openGLScene->SetRenderView(index);
}

void MainWindow::changePPEffect(int index)
{
    openGLScene->SetPPEffect(index);
}

void MainWindow::updateLightIntensity(int index)
{
    openGLScene->UpdateLightIntensity(index);
}

void MainWindow::updateBlurIntensity(int index)
{
    openGLScene->UpdateBlurIntensity(index);
}

void MainWindow::updateGlowIntensity(int index)
{
    float value = (float)index/10;
    openGLScene->UpdateGlowIntensity(value);
}

void MainWindow::restoreSliderValues()
{
    uiMainWindow->lightIntensity->setValue(1);
    uiMainWindow->blurIntensity->setValue(2);
    uiMainWindow->glowIntensity->setValue(8);

    //openGLScene->UpdateLightIntensity(1);
    //openGLScene->UpdateBlurIntensity(2);
    //openGLScene->UpdateGlowIntensity(8);

}

void MainWindow::addGameObject()
{
    printf("addGameObject\n");

    if(scene==nullptr)
        return;

    createCube();
}


void MainWindow::removeGameObject()
{
    printf("removeGameObject\n");
    if(scene==nullptr)
        return;
   int index = uiHierarchy->uiHierarchy->listWidget->currentRow();
   if(index<0||index >scene->gameObjects.count() )
       return;

   uiInspector->DeleteLayout();
   GameObject *go= scene->gameObjects.at(index);
   scene->gameObjects.removeAt(index);
   delete go;
   uiHierarchy->UpdateHierarchy(scene);
}

void MainWindow::TryChangeName(GameObject &go)
{
    int count = 1;
    while(ChangeName(go, count))
    {
        count++;
    }
}

bool MainWindow::ChangeName(GameObject &go, int num)
{
    for(int i = 0;i<scene->gameObjects.count();i++)
    {
        if(scene->gameObjects[i]->name == go.name)
        {
            QString stringNum= QString::number(num);

            go.name = "GameObject ("+stringNum+")";
            return true;
        }

    }
    return false;
}

void MainWindow::updateMain()
{
    uiHierarchy->UpdateHierarchy(scene);
    openGLScene->needsUpdate = true;

}

void MainWindow::showGameObjectInspector(QListWidgetItem* item)
{
    if(scene==nullptr)
    {
        printf("scene is nullptr\n");
        return;
    }
    if(scene->gameObjects.count()<item->listWidget()->currentRow())
    {
        printf("Index out of bounds\n");
        return;
    }
    openGLScene->selected = scene->gameObjects[item->listWidget()->currentRow()];
    uiInspector->UpdateInspector(openGLScene->selected);
}

void MainWindow::CreateUndoView()
{
    undoView = new QUndoView(undoStack);
    undoView->setWindowTitle(tr("Command List"));
    undoView->show();
    undoView->setAttribute(Qt::WA_QuitOnClose,false);
}

void MainWindow::CreateAction()
{
    undoAction=undoStack->createUndoAction(this,tr("&Undo"));
    undoAction->setShortcut(QKeySequence::Undo);

    redoAction=undoStack->createRedoAction(this,tr("&Redo"));
    redoAction->setShortcut(QKeySequence::Redo);
}

void MainWindow::dragEnterEvent(QDragEnterEvent* e)
{
    printf("Drag Enter Event\n");
    if (e->mimeData()->hasUrls())
    {
        e->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent* e)
{
    printf("Drop Event\n");
    QStringList acceptedTypes;
    acceptedTypes << "obj" /*"fbx"*/;

    foreach(const QUrl& url, e->mimeData()->urls())
    {
        QString fname = url.toLocalFile();

        QFileInfo info(fname);
        if (info.exists())
        {
            if (acceptedTypes.contains(info.suffix().trimmed(), Qt::CaseInsensitive))
            {
                printf("Model %s dropped\n", fname.toStdString().c_str());
                DropModel(fname);
            }
        }
    }
}

void MainWindow::DropModel(const QString &file)
{
    if(scene==nullptr)
        return;

    // Copy the file into the Models directory
    QFileInfo fileInfo(file);
    QString fileName = fileInfo.fileName();
    QString modelsPath = "Models/" + fileName;

    if (!QFile::exists(modelsPath))
    {
        printf("Copy file\n");
        QFile::copy(file, modelsPath);
    }
    else
    {
        printf("Not Copy file\n");
    }

    // Generate new model
    GameObject *go = new GameObject();
    TryChangeName(*go);

    go->AddMesh(Shape::CUSTOM, fileName.toStdString().c_str());

    scene->gameObjects.push_back(go);
    updateMain();

    printf("Final Drop\n");

}
