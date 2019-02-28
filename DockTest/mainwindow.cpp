#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_rendering.h"
#include "inspectorwidget.h"
#include "hierarchywidget.h"
#include "shaperendererwidget.h"

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


     // Connect all the actions
     connect(uiMainWindow->actionOpenProject, SIGNAL(triggered()), this, SLOT(openProject()));
     connect(uiMainWindow->actionSaveProject, SIGNAL(triggered()), this, SLOT(saveProject()));
     connect(uiMainWindow->actionUndo, SIGNAL(triggered()), this, SLOT(undo()));
     connect(uiMainWindow->actionRedo, SIGNAL(triggered()), this, SLOT(redo()));
     connect(uiMainWindow->actionExit, SIGNAL(triggered()), qApp, SLOT(quit()));
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
