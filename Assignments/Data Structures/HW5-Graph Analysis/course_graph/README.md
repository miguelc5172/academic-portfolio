# Course Graph Analyzer (C)

## 📘 Overview
This project builds a **directed graph** from an input file representing course prerequisites and checks whether the prerequisite structure is valid.  
It was part of a **Data Structures** assignment focused on graph representation and cycle detection.

---

## 🚀 Features
- Reads an input file describing course prerequisites.  
- Builds a **directed adjacency list graph**.  
- Detects **cycles** in the graph (e.g., circular prerequisites).  
- Reports whether the course structure is valid.  

---

## 🛠️ Implementation
- **Language:** C  
- **Graph Representation:** adjacency lists (dynamic memory).  
- **Cycle Detection:** depth-first search (DFS) with recursion stack.  

---

## 📂 Usage
### Compile
```bash
gcc -o course_graph
```

### Run
```bash
./a.out input.txt
```

Where `input.txt` contains prerequisite pairs, e.g.:

```
CS101 CS102
CS102 CS201
CS201 CS301
```

If a cycle is present, the program will report an error.

---

## 🎯 Learning Outcomes
- Practiced **DFS** in C for cycle detection.  
- Applied **graph theory** to real-world problems (course prerequisite validation).  
- Strengthened skills in **dynamic memory management** and input parsing in C.  
