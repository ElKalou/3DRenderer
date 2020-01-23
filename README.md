# Minimal3DRenderer
​This is an elementary renderer written in OpenGl and C++.

It supports the basic functionnality to display a 3D model and apply a diffuse texture to it. This project allowed me to get deeply into the render pipeline, the interaction between the CPU and the GPU and the writting of shaders.

External librairies used : glfw, glew, glm, imgui, a .obj loader (https://github.com/Bly7/OBJ-Loader). 
External model: https://sketchfab.com/3d-models/mech-drone-8d06874aac5246c59edb4adbe3606e0e

I wish to add new functionnalities in the future such as batch rendering or more interesting shader effects (vertex lighting, shadow casting, global illumination...). 

About the OpenGL/src/ files:
- APIOpenGl contains class that wrap function defined in glew for an easier usage.
- test are closed and independent sandboxes that can be loaded from Application.cpp, and use to test new features.
- vendor contains the external source code librairies






