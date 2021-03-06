#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUndoStack>
#include <QUndoView>

namespace Ui
{
class MainWindow;
}
class QListWidgetItem;
class InspectorWidget;
class HierarchyWidget;
class ShapeRendererWidget;
class OpenGLScene;
class Scene;
class GameObject;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    enum SaveFormat
    {
        Json,
        Binary
    }; 

public slots:
    void openProject();
    void saveProject();
    void undo();
    void redo();
    void addGameObject();
    void removeGameObject();
    void showGameObjectInspector(QListWidgetItem*);
    void updateMain();

private:
    void TryChangeName(GameObject &go);
    bool ChangeName(GameObject &go, int num);
    void CreateAction();
    void CreateUndoView();

private:
    Ui::MainWindow *uiMainWindow;
    InspectorWidget *uiInspector;
    HierarchyWidget *uiHierarchy;
    OpenGLScene *openGLScene;
    QAction* undoAction;
    QAction* redoAction;
    QAction* createGameObjectAction;
    QAction* removeGameObjectAction;

    QUndoStack *undoStack;
    QUndoView *undoView;

    // Logic Variables
    Scene *scene = nullptr;

};

#endif // MAINWINDOW_H
