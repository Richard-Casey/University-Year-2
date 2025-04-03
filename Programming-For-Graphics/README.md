
# Programming For Graphics – 3D Graphics Techniques in OpenGL

**Module Grade: 64% – Upper Second Class (2:1)**

This project was completed as part of the second-year *Programming for Graphics* module at the University of Suffolk. The task was to develop a 3D graphics application demonstrating core and advanced rendering techniques using OpenGL and GLSL shaders.

The work involved using raw graphics primitives, loading textured models, and implementing various lighting models with multiple shader types. The resulting program demonstrates both real-time interactivity and static scene rendering using programmable pipelines.

---

## 🎯 Objectives & Requirements

**Required Techniques:**
- ✅ Graphics Primitives
- ✅ Transformations
- ✅ Movable Camera
- ✅ Texture File Loading
- ✅ Textured Meshes
- ✅ Phong Lighting
- ✅ Shader Pipeline (Vertex + Fragment)
- ✅ 3D Model Loading (OBJ)
- ✅ Normal Mapping
- ✅ Specular Mapping

**Advanced Features Attempted:**
- Directional Lighting
- Multiple Lights
- Flat/Gouraud Lighting
- Shadow system (partially implemented)
- Multi-camera render target concept

---

## 🧱 Features Demonstrated

- 🌐 **GLM Math Library** for matrix transformations
- 🎥 **FPS-style camera control** using keyboard and mouse input
- 🧱 **Mesh system** supporting multiple models and texture files
- 🔆 **Phong shading model** with adjustable parameters
- 🧪 Shader-based **normal and specular mapping**
- 🖼️ Scene rendering with **multiple materials and UVs**
- 🧭 Custom object loader (OBJ) with error checking
- 🎮 Real-time interaction with keyboard/mouse navigation

---

## 🛠 Tech Stack

- **Language:** C++
- **Graphics API:** OpenGL (Modern pipeline)
- **Libraries Used:**
  - **GLFW** – Window/context and input
  - **GLAD** – OpenGL function loader
  - **GLM** – Math/transformations
  - **stb_image** – Texture loading
  - **Assimp** – 3D model import
- **Shaders:** GLSL (Vertex + Fragment)

---

## 📁 Project Structure

```
Programming-For-Graphics/
├── src/                        # Source code and rendering pipeline
├── shaders/                    # Vertex and fragment shaders
├── assets/                     # Textures and 3D models
├── glm/                        # GLM library and doxygen docs
├── includes/                   # External libraries
├── build/                      # Build targets and binaries
```

---

## 🎓 Assessment Reflection

This module gave me the opportunity to explore **real-time rendering fundamentals** and experiment with **advanced shading models** and OpenGL best practices. While some bonus features were partially completed, the implementation covered all core criteria and delivered a functional, shader-based 3D graphics application.

**Final Grade: 64% – Upper Second-Class**

---

## 🙌 Final Thoughts

This project reflects my ability to:
- Handle lower-level graphics programming
- Work directly with the OpenGL pipeline
- Design reusable rendering code and scene logic
- Experiment with shader effects and multi-pass techniques

It helped lay the groundwork for further technical modules like Tools Programming and AI for Games in the second half of the year.
