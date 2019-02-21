#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUndoStack>
#include <QUndoView>

namespace Ui {
class MainWindow;
class Rendering;
}

class InspectorWidget;
class HierarchyWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void openProject();
    void saveProject();
    void undo();
    void redo();

private:
    void CreateAction();
    void CreateUndoView();

    Ui::MainWindow *uiMainWindow;
    Ui::Rendering *uiRendering;
    InspectorWidget *uiInspector;
    HierarchyWidget *uiHierarchy;

    QAction* undoAction;
    QAction* redoAction;

    QUndoStack *undoStack;
    QUndoView *undoView;
};

#endif // MAINWINDOW_H
