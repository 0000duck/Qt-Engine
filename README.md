# Qt-Engine
This is a simple scenes editor made of vector shapes, where you can create figures 
(circles, triangles...) and apply some modifications (change color, size...) on them.

![](https://github.com/Jordior97/Qt-Engine/blob/master/QtScreenshots/MainWindow.png?raw=true)

## Authors:
- Andreu Rojas
- Jodi Oña

## Features:
### 1) Hierarchy System
Through this window you can Add or Remove elements of the scene by clicking the respective buttons.

![](https://github.com/Jordior97/Qt-Engine/blob/master/QtScreenshots/Hierarchy.png?raw=true)

### 2) Inspector window
Every Game Object in the scene can be edited through this window. You can click in any element 
on the Hierarchy Window to see and edit its variables. We can observe 3 sub-sections (Components):
- **Info:** the basic characteristics of the game object.
- **Transform:** to modify its position inside the scene.
- **Shape Render:** to edit its colors, size, form, and the outline.

![](https://github.com/Jordior97/Qt-Engine/blob/master/QtScreenshots/Inspector.png?raw=true)

### 3) Render scene
Central window where all the Game Objects are visualized.

![](https://github.com/Jordior97/Qt-Engine/blob/master/QtScreenshots/Scene.png?raw=true)

### 4) Save/Load Project
- **Save (Ctr+S):** you can click the toolbar icon or go to "File->Save Project" to save the actual 
scene into a .json file.
- **Load (Ctr+O):** you can click the toolbar icon or go to "File->Open Project" to open a 
previously saved scene.

![](https://github.com/Jordior97/Qt-Engine/blob/master/QtScreenshots/SaveLoad.png?raw=true)

## Qt Features:

- **MainWindow:** it contains all actions that involves the UI interaction (Open/Save Project, 
Add/Remove Entity, Show Inspector...)

- **Components:** we have stablished  a GameObject - Component structure (Unity-like). Each
component is linked with a QT Widget to visualize and modify its parameters. For example, 
the position of the transform is modified through its linked Transform Widget. 
Also, when a component is modified, we send a signal to the Inspector who, in turn, sends another
signal to the MainWindow to to update all the main Widgets.

- **Dialogs:** we have implemented two types of dialogs: 
  - **Open/Save Project**.
  - **Choose Color**: by clicking "Fill Color" or "Stroke Color" in the ShapeRenderer Widget, a basic color picker 
  is displayed.

