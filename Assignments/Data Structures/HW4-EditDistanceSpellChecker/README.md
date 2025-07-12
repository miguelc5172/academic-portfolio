# 🧠 Edit Distance Spell Checker (C)

This program demonstrates the use of **edit distance (Levenshtein distance)** to compare words and perform basic spell-checking by matching user-provided words against a dictionary file.

Developed as part of a Data Structures course, it showcases dynamic memory usage, string manipulation, and algorithmic problem solving in C.

---

## 🚀 Features

There are two parts to this program:

**🔹 Part 1: Edit Distance Calculation**
- Calculates the edit distance between two user-input words
- Suggests the closest dictionary match for each word in an input file

**🔹 Part 2: Spell Checker with Manual Corrections**
- Reads from external dictionary and input files
- Lets the user type manual corrections 
- Outputs suggested corrections and edit distances

---

## 🔧 How to Compile

Ensure you're in the directory that contains `spell_checker.c`, `spell.c`, and `spell.h`.

```bash
gcc -g spell_checker.c spell.c 
```


---

## 🖥️ How to Run

```bash
./a.out
```

### 🗒️ You’ll be prompted to:

1. Enter two words to compare:
   ```
   apple apply
   ```
   It will print the edit distance.

2. To end comparison mode:
   ```
   -1 -1
   ```

3. Then enter a dictionary file and an input file to spell-check. For example:
   ```
   dmed.txt
   list1.txt
   ```

The program will output suggestions for misspelled words in the input file, showing the closest dictionary match and the edit distance.

---

## 📁 Folder Structure

```
.
├── spell_checker.c
├── spell.c
├── spell.h
├── dmed.txt              # Sample dictionary file
├── list1.txt             # Sample input file for spell checking
├── Example Outputs/
│   ├── run_list1_dmed.txt
│   └── run_dbig_list1.txt
└── README.md
```

---

## 📂 Example Outputs

The `Example Outputs/` folder contains sample outputs from previous runs using different dictionary and input files. These demonstrate the spell-checking and edit distance behavior in real use cases.

---

## 🧪 Memory Testing with Valgrind

Valgrind may be utilized and is encouraged in order to demonstrate that there are no memory  leaks. To verify that the program does not leak memory:

```bash
valgrind --leak-check=full  ./a.out
```

Interact as usual and confirm clean memory usage when the program exits.

---

## ✅ Dependencies

- Standard C compiler (e.g., `gcc`)
- Compatible with Linux-based systems (tested with Ubuntu)
- No external libraries required

---

