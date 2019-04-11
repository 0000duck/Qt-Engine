#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_rendering.h"
#include "ComponentWidget/inspectorwidget.h"
#include "ComponentWidget/hierarchywidget.h"
#include "ui_hierarchywidget.h"
#include "ComponentWidget/shaperendererwidget.h"
#include "Scene/scene.h"
#include "GameObject/gameobject.h"

#include <QListWidget>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>
#include <QStandardPaths>
#include <QFileDialog>
#include <QMessageBox>

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
    scene = new Scene();

    uiMainWindow->openGLWidget->GetScene(scene);

    // Connect all the actions
    connect(uiMainWindow->actionOpenProject, SIGNAL(triggered()), this, SLOT(openProject()));
    connect(uiMainWindow->actionSaveProject, SIGNAL(triggered()), this, SLOT(saveProject()));
    connect(uiMainWindow->actionExit, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(uiHierarchy->uiHierarchy->AddEntity,SIGNAL(clicked()),this,SLOT(addGameObject()));
    connect(uiHierarchy->uiHierarchy->RemoveEntity,SIGNAL(clicked()),this,SLOT(removeGameObject()));
    connect(uiHierarchy->uiHierarchy->listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(showGameObjectInspector(QListWidgetItem*)));
    connect(uiInspector,SIGNAL(MainUpdate()),this,SLOT(updateMain()));

    //connect(uiMainWindow->actionSaveScreenShot,SIGNAL(triggered()),uiMainWindow->widget, SLOT(TakeScreenShot()));
    //connect(uiMainWindow->actionUndo, SIGNAL(triggered()), this, SLOT(undo()));
    //connect(uiMainWindow->actionRedo, SIGNAL(triggered()), this, SLOT(redo()));
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

void MainWindow:: createCube()
{

}

void MainWindow::addGameObject()
{
    printf("addGameObject\n");
    if(scene==nullptr)
        return;
    GameObject *go = new GameObject();
    TryChangeName(*go);
    scene->gameObjects.push_back(go);
    uiHierarchy->UpdateHierarchy(scene);
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
    uiInspector->UpdateInspector(scene->gameObjects[item->listWidget()->currentRow()]);
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
