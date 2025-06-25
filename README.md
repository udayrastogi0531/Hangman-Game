# 🔤 Hangman Game in C++ ![C++](https://img.shields.io/badge/Language-C++-00599C?style=flat-square&logo=c%2B%2B&logoColor=white)

🎮 A terminal-based Hangman game implemented in **C++** featuring:
- 🔍 **Smart hints** using a Trie (prefix tree)
- 🏆 **Leaderboard** using a max-heap (priority queue)
- 💾 File-based word list and scoring system

---

## ✨ Features

- 🎯 **Random Word Selection** from `WordList.txt`
- 🧠 **Trie-Based Word Hint Suggestions**
- 📈 **Score Tracking System**
  - ✅ Correct guess: +1 point
  - ❌ Wrong guess: -1 point
  - 🎁 Bonus for guessing entire word (+2/+3)
- 🏆 **Leaderboard using Max-Heap** (Top scores displayed)
- 📁 **File I/O** for reading words and writing scores
- 🖥️ **Terminal-Friendly UI** with ASCII Hangman art

---

## 📁 Folder Structure

```
Hangman/
├── Hangman.cpp         # Main game code (C++)
├── WordList.txt        # Input word list
├── scores.txt          # Output score log
└── .vscode/            # (Optional) VS Code build/run configs
```

---

## ⚙️ How to Compile & Run

### 🔧 Compile (using g++):
```bash
g++ Hangman.cpp -o Hangman
```

### ▶️ Run the game:
```bash
./Hangman       # or Hangman.exe on Windows
```

### 📚 Requirements:
- C++ Compiler (`g++`, `clang++`, etc.)
- Terminal (Command Prompt, Bash, or VS Code)

---

## 🧠 Concepts Used

- 📚 **Trie (Prefix Tree)** – for fast auto-suggestions
- 📊 **Priority Queue (Max-Heap)** – for leaderboard ranking
- 🎨 **ASCII Art** – for visual hangman representation
- 💾 **File Input/Output** – reading word list and saving scores
- 🧮 **Score Calculation** – based on guess accuracy

---

## 🚀 Sample Gameplay

```text
_ _ _ _ _ _ _ _
Enter a letter to guess: a
_ _ a _ _ _ _ _

Wrong letter!

Hint! Words starting with 'a': airplane alluring ...
```

---

## 🔐 License

This project is licensed under the **MIT License**.  
Feel free to use, modify, and share.

---

## 🤝 Contributing

Pull requests and forks are welcome!

> 💡 Want to add new features (like difficulty levels or multiplayer)? Go for it!

---

## 🙌 Author

Developed by **[Uday Rastogi]**

Connect on [GitHub](https://github.com/udayrastogi0531) or [LinkedIn](https://www.linkedin.com/in/uday-prakash-rastogi-33b55a2a2/)
