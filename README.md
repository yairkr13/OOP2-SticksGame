# 🎮 Pick Up Sticks – C++ OOP Game

An interactive desktop game built in modern C++ using SFML.  
Inspired by the classic "Pick Up Sticks" logic game, with a twist of algorithmic depth and object-oriented architecture.

## 🚀 Features

- 🧠 **Object-Oriented Design**: Built with clean separation of responsibilities between game logic, UI, and stick objects.
- 🧱 **Smart Architecture**: Uses STL containers, smart pointers, and efficient collision detection between rotated sticks.
- 🖱️ **Interactive Gameplay**: Click to pick up sticks – but only if they’re not covered by others.
- ⏳ **Real-time Constraints**: Includes countdown timer, scoring system, and a helper button to highlight available moves.
- 💾 **Save & Load Game State**: Includes exception handling for invalid or corrupted save files.

## 🛠️ Technologies & Concepts

- **C++17**
- **SFML (Simple and Fast Multimedia Library)**
- **STL (vectors, algorithms, iterators)**
- **Geometry & Collision Detection**
- **Smart Pointers & Resource Management**
- **Basic Serialization / File I/O**

## 🧠 What I Learned

This project strengthened my understanding of:
- Clean OOP design and class interactions
- Building a graphical game engine loop from scratch
- Collision logic and geometric reasoning
- Designing extensible, testable C++ code

## 📁 Project Structure

- `GameManager` – main loop and scene transitions
- `Stick` – represents a single stick with geometry and dependencies
- `StatsManager` – handles score, timer, and available moves
- `Button` – reusable button logic (menu/help)
- `SaveSystem` – serialization and deserialization

---

### 👨‍💻 Built by [Yair Krothamer](https://github.com/YairKrothamer)  
B.Sc. Computer Science | Passionate about clean code and game logic
