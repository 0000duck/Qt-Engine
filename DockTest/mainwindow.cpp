#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_rendering.h"
#include "inspectorwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    uiMainWindow(new Ui::MainWindow),
    uiRendering(new Ui::Rendering)
{
    uiMainWindow->setupUi(this);

    // All tab position on top of the docking area
    setTabPosition(Qt::AllDockWidgetAreas,QTabWidget::TabPosition::North);

    // Create rendering widget
    QWidget *renderingWidget = new QWidget();
    uiRendering->setupUi(renderingWidget);
    renderingWidget->show();

    // Add it to Rendering Dock
    uiMainWindow->Rendering->setWidget(renderingWidget);

    uiMainWindow->Rendering->setFloating(false);
    tabifyDockWidget(uiMainWindow->Rendering, uiMainWindow->Inspector);

    // Add Lightning widget
    QDockWidget *dockWidget = new QDockWidget;
    dockWidget->setWindowTitle("Lightning");
    this->addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, dockWidget);
    tabifyDockWidget(uiMainWindow->Rendering, dockWidget);

    // Create the inspector widget and add it to the inspector
    uiInspector = new InspectorWidget();
    uiMainWindow->Inspector->setWidget(uiInspector);

     connect(uiMainWindow->actionOpenProject, SIGNAL(triggered()), this, SLOT(openProject()));
     connect(uiMainWindow->actionSaveProject, SIGNAL(triggered()), this, SLOT(saveProject()));
     connect(uiMainWindow->actionExit, SIGNAL(triggered()), qApp, SLOT(quit()));
}

MainWindow::~MainWindow()
{
    delete uiMainWindow;
    delete uiRendering;
}

void MainWindow::openProject()
{
    printf("Open project\n");
}

void MainWindow::saveProject()
{
    printf("Save project\n");
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
