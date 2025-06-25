# Hangman-Game
🎮 A classic Hangman word guessing game implemented in C++ with Trie-based word hints and a max-heap leaderboard system.
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
