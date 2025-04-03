
# Tools Programming – Custom Engine Editor Utilities

**Module Grade: 65% – Upper Second Class (2:1)**

This project is a direct continuation of the work completed in the *Game Engine Development* module. The task for this assessment was to build a set of tools and utilities to enhance usability and content creation within the custom `RCaseySDL` engine — effectively turning the foundation into a usable editor environment.

The tools were implemented in **C++**, and leverage **ImGui** for the GUI layer, providing intuitive control over object manipulation, asset importing, hierarchy management, and performance profiling.

---

## 🧰 Key Features Implemented

✅ **Scene Details Panel**  
- Interface to adjust properties and parameters for selected scene objects  
- Real-time updates using ImGui widgets and controls

✅ **Object Selection and Transformation**  
- Mouse-based selection of scene objects  
- Click-and-drag repositioning support  
- Coordinate system updates in real time

✅ **Asset Browser**  
- Lists all imported textures, sprites, and other assets  
- Supports drag-and-drop placement of assets into the scene

✅ **Scene Hierarchy Panel**  
- Displays all game objects currently in the scene  
- Supports reordering and **parenting objects** via a drag interface

✅ **Performance Monitoring**  
- Integrated **profiler and performance stats panel**  
- Displays real-time FPS and resource usage metrics

✅ **Save/Load Functionality**  
- Scene state persistence via JSON
- Allows full scene reload between engine sessions

---

## 🌟 Advanced Considerations

- Fully integrated **ImGui-based UI** to handle all editing functionality
- Layout and color themes designed for **readability and polish**
- Clean separation between engine logic and UI layer
- Consistent use of naming conventions and file structure
- Continued use of Doxygen for code documentation

---

## 🛠 Tech Stack

- **Language:** C++
- **Engine Base:** RCaseySDL (custom-built)
- **UI Framework:** ImGui
- **Libraries Used:**
  - SDL2
  - JSON for Modern C++
  - Doxygen (for code documentation)

---

## 📁 Directory Structure

```
RCaseySDL/
├── src/                      # Core engine and tool implementations
├── imgui/                   # GUI framework files
├── html/latex/              # Doxygen documentation outputs
├── Release/Debug/           # Build targets
├── nlohmann/json.hpp        # JSON parser for save/load system
├── profiler/                # System performance and debug overlays
```

---

## 🎓 Assessment Reflection

This project shows:
- A shift from engine building to **tool design**
- Consideration of **user experience** and editor workflow
- A clear understanding of **modularity** in C++ architecture
- Hands-on integration with modern UI libraries

Final mark: **65%** – meeting all core requirements and showing further development from the engine base project.

---

## 🙌 Final Thoughts

This project helped bridge the gap between engine functionality and game creation. It taught me the value of:
- Creating internal tools for designers or non-programmers
- Thinking in terms of user workflows, not just raw systems
- Maintaining modularity and extendability across large C++ codebases

Combined with my work on the core engine, this forms the backbone of my technical systems development during Year 2.
