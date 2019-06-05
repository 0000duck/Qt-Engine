# Qt-Engine
This is a 3D mini engine that lets you create GameObjects with different shapes (Cubes, Spheres, Planes...) and load models (.obj) to visualize them and modify their "visual appearance" with shading techinques.

![](https://github.com/Jordior97/Qt-Engine/blob/OpenGL-Andrew/QtScreenshots/MainWindow3D.png)

## Authors:
- Andreu Rojas
- Jodi Oña

## USER GUIDE:

### Camera Controls:

**- Right CLik + WASD:** move camera.

**- Mouse Movement:** orientate camera.

**- Mouse Wheel (scroll):** zoom in/out.

**- F:** center the camera to the selected GameObject.

### 1) Loading Models
The user has 2 ways to add elements on the scene:

**1. Add Entity:** on the bottom of the Hierarchy Dock Window he can press the "Add Entity" button to generate a basic  cube primitive.

**2. Create:** on the top left corner they can see a dropdown menu with different specific elements to create.
  
![](https://github.com/Jordior97/Qt-Engine/blob/OpenGL-Andrew/QtScreenshots/CreateObject.png)
  
**3. Drag & Drop:** he can also drag models (.obj) from anywhere to the engine. It will be automatically loaded on the scene and saved in the "Models" Folder.
  
![](https://github.com/Jordior97/Qt-Engine/blob/OpenGL-Andrew/QtScreenshots/Drag%26Drop.gif)

### 2) Model Settings
We can see its properties on the left side, in the Inspector Window. Each Model in the scene has 2 components:

**1. Transform:** to move, rotate and scale it.

**2. Mesh Renderer:** to change the mesh and apply a texture on each submesh of the model. It contains a series of comboboxes that display all the available models and textures loaded in the engine. These resources can be found inside the folders "Models" and "Textures" (feel free to add more resources!). 

![](https://github.com/Jordior97/Qt-Engine/blob/OpenGL-Andrew/QtScreenshots/MeshRender.gif)

### 3) Render Settings

![](https://github.com/Jordior97/Qt-Engine/blob/OpenGL-Andrew/QtScreenshots/RenderSettings.png)

In order to apply the deferred shading technique, we store in different textures all the specific data about the scene. Throught the dropdown menu "View" we can navigate through these different textures:

**- Albedo:** shows the colors/textures of the models

**- Normals:** to display the normals of each vertex

**- Position:** to display the position of each vertex respecto to the worldspace view

**- Deferred:** the final render, combining all the previous views and adding some lights.

![](https://github.com/Jordior97/Qt-Engine/blob/OpenGL-Andrew/QtScreenshots/RenderView.gif)


### 3) Post Processing Techniques
We decided to implement the Multi-pass bloom technnique. In order to achieve this effect, we had to implement the blur technique. These are the different renders we can observe through the "Visual Effect" dropdown menu:

**Blur**

![](https://github.com/Jordior97/Qt-Engine/blob/OpenGL-Andrew/QtScreenshots/Blur.png)


**Total Bloom**

![](https://github.com/Jordior97/Qt-Engine/blob/OpenGL-Andrew/QtScreenshots/Glow.png)

**Bloom (with Brightness Filter):** bloom only applied to the most bright parts of the models.

![](https://github.com/Jordior97/Qt-Engine/blob/OpenGL-Andrew/QtScreenshots/GlowBrightness.png)




  
  
