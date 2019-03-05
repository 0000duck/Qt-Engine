#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_rendering.h"
#include "inspectorwidget.h"
#include "hierarchywidget.h"
#include "ui_hierarchywidget.h"
#include "shaperendererwidget.h"
#include "scene.h"
#include "gameobject.h"
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

     // Connect all the actions
     connect(uiMainWindow->actionOpenProject, SIGNAL(triggered()), this, SLOT(openProject()));
     connect(uiMainWindow->actionSaveProject, SIGNAL(triggered()), this, SLOT(saveProject()));
     connect(uiMainWindow->actionUndo, SIGNAL(triggered()), this, SLOT(undo()));
     connect(uiMainWindow->actionRedo, SIGNAL(triggered()), this, SLOT(redo()));
     connect(uiMainWindow->actionExit, SIGNAL(triggered()), qApp, SLOT(quit()));
     connect(uiHierarchy->uiHierarchy->AddEntity,SIGNAL(clicked()),this,SLOT(addGameObject()));
     connect(uiHierarchy->uiHierarchy->RemoveEntity,SIGNAL(clicked()),this,SLOT(removeGameObject()));

     //connect(uiMainWindow->actionSaveScreenShot,SIGNAL(triggered()),uiMainWindow->openGLScene,SLOT(TakeScreenShot()));
}

MainWindow::~MainWindow()
{
    delete uiMainWindow;
}

void MainWindow::openProject()
{
    printf("Open project\n");
}

void MainWindow::saveProject()
{
    printf("Save project\n");
}

void MainWindow::undo()
{
    printf("Undo\n");
}

void MainWindow::redo()
{
    printf("Redo\n");
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
   GameObject *go= scene->gameObjects.back();
   scene->gameObjects.pop_back();
   delete go;
   uiHierarchy->UpdateHierarchy(scene);

}
void MainWindow::removeGameObject(int index)
{
    printf("removeGameObject\n");
    if(scene==nullptr)
        return;
   GameObject *go= scene->gameObjects.back();
   scene->gameObjects.removeAt(index);
   delete go;
   uiHierarchy->UpdateHierarchy(scene);
}
void MainWindow::TryChangeName(GameObject &go)
{
    int count = 0;
    while(ChangeName(go,count))
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
