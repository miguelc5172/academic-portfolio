# Interactive Graph Tool (C)

## 📘 Overview
The **Interactive Graph Tool** is a command-line application that allows users to build and manipulate graphs dynamically.  
It was developed as part of a **Data Structures** assignment to reinforce graph construction and traversal.

---

## 🚀 Features
- Create a graph of user-defined size.  
- Insert directed edges interactively.  
- Print the current graph structure.  
- Test connectivity or reachability between nodes.  
- Explore graph behavior through manual input.  

---

## 🛠️ Implementation
- **Language:** C  
- **Graph Representation:** adjacency matrix / adjacency list.  
- **Traversal:** basic DFS/BFS for reachability queries.  

---

## 📂 Usage
### Compile
```bash
gcc -o interactive_graph
```

### Run
```bash
./a.out
```

### Example Session
```
MENU:
0: Exit
1: Create new graph.
2: Add an edge.
3: Remove an edge.
4: Print neighbors of an edge.
5: Print graph.

Enter command (0-5): 1
Enter number of vertices and 1 for undirected graph: 2
1

MENU:
0: Exit
1: Create new graph.
2: Add an edge.
3: Remove an edge.
4: Print neighbors of an edge.
5: Print graph.

Enter command (0-5): 5

Vertex 0. Neighbors:
Vertex 1. Neighbors:


MENU:
0: Exit
1: Create new graph.
2: Add an edge.
3: Remove an edge.
4: Print neighbors of an edge.
5: Print graph.

Enter command (0-5): 2
Enter vertices: 0 1

MENU:
0: Exit
1: Create new graph.
2: Add an edge.
3: Remove an edge.
4: Print neighbors of an edge.
5: Print graph.

Enter command (0-5): 5

Vertex 0. Neighbors: 1 
Vertex 1. Neighbors: 0
```

---

## 🎯 Learning Outcomes
- Reinforced understanding of **graph fundamentals**.  
- Practiced **user input handling** and dynamic updates to graph structures.  
- Gained experience in **interactive CLI program design** in C.  
