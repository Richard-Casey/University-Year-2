
# Artificial Intelligence for Games – Predator/Prey Simulation in C++

**Module Grade: 54% – Lower Second Class (2:2)**  
**Report Grade: 55%**  
**Project Grade: 53%**

This project was developed as part of the second-year *Artificial Intelligence for Games* module at the University of Suffolk. The assessment was split into two parts: a written research report and a technical simulation demonstrating multiple AI behaviours in a game context.

Despite being one of my more challenging modules, it gave me a valuable foundation in AI systems and programming logic that I've since built upon in later projects.

---

## 🧠 Assessment Breakdown

### 📄 Report (2000 words)
- Overview of AI techniques used
- Reasoning behind system and structure choices
- Agent behaviour mapping (state machines, decision trees)
- References to academic and industry research

### 💻 Simulation Project
- A 2D predator/prey simulation built in **C++** with **SFML**
- Includes the following AI techniques:
  - ✅ Finite State Machines (FSM)
  - ✅ Steering Behaviours
  - ✅ A* Pathfinding
  - ✅ Behaviour Trees (BT)

---

## 👾 Agents Implemented

- **Hunter** – Pursues prey using steering, state switching, and behaviour tree conditions
- **Prey** – Avoids hunter, navigates using A* pathfinding and FSM logic

---

## 🧩 Key Components

- `State.h / State.cpp` – Manages agent states and transitions
- `AStarPathFinding.h / .cpp` – Grid-based pathfinding algorithm
- `Behaviour.h / .cpp` – Behaviour Tree node system
- `Hunter`, `Prey`, `BaseEntity` – Core AI actors
- `GridManager` – Manages navgrid and spatial layout

---

## 🛠 Tech Stack

- **Language**: C++
- **Graphics/Input**: SFML
- **Structure**: Visual Studio Solution
- **Build**: `.exe` demo included

---

## 🎮 How to Run

Navigate to the `/Build` directory and run `AIFramework.exe`.  
Assets are located in `/Build/Assets/` and loaded automatically at runtime.

---

## 🎓 Reflection

This module challenged my C++ problem-solving and understanding of AI logic structures. While I found it difficult at the time, it sparked a deeper interest in systems design, and I’ve since improved significantly in building logic-based systems in games.

The skills learned here laid a foundation I continued to develop in later projects like Tools Programming and gameplay systems in my dissertation work.

---

## 🙌 Final Thoughts

This project demonstrates:
- A working knowledge of core game AI systems
- Honest progress in an area I’ve worked hard to improve
- My ability to complete a complex technical brief, even when outside my comfort zone
