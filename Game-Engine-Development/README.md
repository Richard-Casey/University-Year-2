
# Game Engine Development – Custom C++ Engine + Demo Game

**Module Grade: 71% – First Class Honours**

This project was developed as part of the second-year *Game Engine Development* module at the University of Suffolk. The goal was to build a custom game engine in **C++** from scratch, following modern C++11 standards, and to deliver a playable **demo game** to prove the engine's functionality.

I implemented core systems including a scene manager, resource loader, input handling, and rendering pipeline using SDL, with additional tooling for performance profiling and structured game object management.

---

## 🧠 Project Goals & Requirements

**Engine Specification:**
- Written entirely in **C++**
- Modular architecture using custom header/source files
- Minimum feature set:
  - ✅ Renderer
  - ✅ Input Manager
  - ✅ Resource Manager
  - ✅ Scene Management System
  - ✅ Profiler
  - ✅ API Documentation (via Doxygen)

**Proof of Concept Game:**
- ✅ Movable Player
- ✅ At least one Level
- ✅ One Enemy AI
- ✅ One Pickup Item
- ✅ A reasonable gameplay goal

---

## 🔧 Engine Features

### 📁 Core Systems
- `ResourceManager` – Loads and tracks textures and assets
- `TextureManager` – Handles low-level SDL texture operations
- `SceneManager` – Manages game states and transitions
- `Input` – Keyboard input handling using SDL events
- `ProfilerSystem` – Lightweight system performance profiling
- `Game` – Engine entry point with a modular game loop

### 🧙 Entity System
- `Creature`, `Hero`, `Monster` – Inheritance-based actor system
- `Pickup` – Collectible item logic with visual feedback
- `Game::AssetData` – Structured game asset definitions

### 📜 Documentation
- Full engine documentation built with **Doxygen**
- HTML and LaTeX output included under `/html/` and `/latex/`
- Inheritance graphs, class references, and function summaries

---

## 🎮 Proof of Concept Game

A simple playable demo showcases:
- A controllable player character (using keyboard input)
- One enemy AI that can interact with the player
- One pickup item with defined interaction logic
- Goal: Navigate the environment and reach the end state

The game runs within the custom engine loop and uses the systems above to demonstrate functionality and extendability.

---

## 🛠 Tech Stack

- **Language**: C++ (C++11)
- **Frameworks**: SDL2
- **Tooling**: Doxygen, Visual Studio
- **External Libraries**: `nlohmann/json` for configuration and structured data

---

## 📁 Project Structure

```
RCaseySDL/
├── src/
│   ├── Game.cpp / Game.h              # Main game logic
│   ├── Input.cpp / Input.h            # Input manager
│   ├── ResourceManager.cpp / .h       # Asset loading
│   ├── TextureManager.cpp / .h        # SDL texture handler
│   ├── SceneManager.cpp / .h          # Scene switching and logic
│   ├── Creature.cpp / Hero.cpp / Monster.cpp # Game entities
│   ├── Pickup.cpp / Pickup.h          # Collectible logic
│   └── Profiler.cpp / Profiler.h      # Performance tracking
├── html/                              # Doxygen documentation (HTML)
├── latex/                             # Doxygen documentation (LaTeX)
├── Release/ & Debug/                  # Build outputs
└── nlohmann/json.hpp                  # JSON parsing lib
```

---

## 🎓 Assessment Reflection

This project demonstrates:
- A strong grasp of **C++ systems programming**
- Ability to architect a **modular, reusable engine**
- Focus on **documentation, structure, and maintainability**
- The creation of a complete, working game built on top of a custom engine

This project earned a **First (71%)**, reflecting a solid understanding of both engine and gameplay architecture, and a well-executed delivery against the design specification.

---

## 🙌 Final Thoughts

This was one of the most technically demanding modules of the year, and also one of the most rewarding. It pushed me to:
- Think like an engine developer
- Solve low-level design problems
- Document and reflect on my systems from an API user’s point of view

It laid a strong foundation for future C++ projects, including tools, AI, and rendering systems developed in later modules.
