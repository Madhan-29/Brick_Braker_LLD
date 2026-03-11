# 🧱 Brick Breaker — Console Game (C++)

> A text-based Brick Breaker game built in **C++** as a **Low-Level Design (LLD)** exercise. Control a ball to destroy bricks on a grid-based board using directional commands.

---

## 🎮 How to Play

1. Choose the board size (creates an N×N grid)
2. Place bricks at specific positions on the board
3. Use commands to launch the ball and break bricks:

| Command | Action |
|---------|--------|
| `st`    | Straight hit — ball shoots up vertically |
| `lt`    | Left hit — ball moves diagonally up-left |
| `rt`    | Right hit — ball moves diagonally up-right |

- The ball starts at the **bottom center** of the board
- Each brick hit **reduces ball life by 1**
- After hitting a brick or wall, the ball **falls back down**
- Game ends when **ball life reaches 0**

---

## 🏗️ Board Legend

| Symbol | Meaning |
|--------|---------|
| `w`    | Wall (boundary) |
| `1`    | Brick |
| `o`    | Ball |
| `g`    | Ground |
| ` `    | Empty space |

---

## 📁 Project Structure

```
Brick_Breaker_CPP/
├── BrickBreaker.h     # Class declaration — game board, ball, brick management
├── BrickBreaker.cpp   # Game logic — movement, collision, brick destruction
├── Main.cpp           # Entry point — user input loop & game flow
└── .gitignore
```

---

## 🚀 Compile & Run

```bash
g++ -o BrickBreaker Main.cpp BrickBreaker.cpp
.\BrickBreaker.exe    # Windows
```

---

## 💡 Example Session

```
Enter size: 7
Enter number of bricks: 2
Enter brick positions (row col):
2 3
3 4

w w w w w w w
w         w
w     1     w
w       1   w
w           w
w           w
g g g o g g g
Ball count: 5

Enter command (st/lt/rt): st
```

---

## 🧩 Key Design

- **Grid-based board** using `vector<vector<string>>` for flexible sizing
- **Diagonal movement** — ball reflects horizontally on wall hits before falling
- **Collision detection** — brick life tracked via `map<int, int>` with exact-position encoding
- **Separation of concerns** — `BrickBreaker` handles all game logic; `Main.cpp` handles I/O

---

## 🛠️ Built With

- **Language:** C++
- **Platform:** Windows (uses `windows.h` for `Sleep`)
- **Data Structures:** `vector`, `map`

---

## 📄 License

This project is for educational and interview-preparation purposes.
