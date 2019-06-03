#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUndoStack>
#include <QUndoView>
#include <QDragEnterEvent>

namespace Ui
{
class MainWindow;
}
class QListWidgetItem;
class InspectorWidget;
class HierarchyWidget;
class ShapeRendererWidget;
class MeshRendererWidget;
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

    void createCube();
    void createSphere();
    void createPlane();
    void createPatrick();

    void changeRenderView(int index);
    void changePPEffect(int index);
    void updateLightIntensity(int index);
    void updateBlurIntensity(int index);
    void updateGlowIntensity(int index);

    void showGameObjectInspector(QListWidgetItem*);
    void updateMain();

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;

private:
    void TryChangeName(GameObject &go);
    bool ChangeName(GameObject &go, int num);
    void CreateAction();
    void CreateUndoView();
    void DropModel(const QString& file);


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
