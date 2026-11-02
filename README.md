# C++ Notes

My personal notes, C++ implementations, and solutions while learning **Data Structures, Algorithms, and C++**.

This repository may also contain miscellaneous C++ topics and experiments that I find useful during my learning, such as smart pointers, STL, memory management, debugging, and other programming concepts.

The implementations are not necessarily copied directly from the sources I learn from. Sometimes I rewrite the code in a different way because it is easier for me to understand.

This repository also contains solutions to programming problems from platforms such as:

* Codeforces
* LeetCode
* GeeksforGeeks
* Other programming platforms

## Repository Structure

```text
dsa-and-algo-notes/
│
├── algorithms/
│   ├── binary-search/
│   ├── bfs/
│   ├── dfs/
│   ├── dijkstra/
│   ├── dynamic-programming/
│   ├── greedy/
│   ├── max-flow/
│   └── ...
│
├── data-structures/
│   ├── disjoint-set/
│   ├── segment-tree/
│   ├── fenwick-tree/
│   └── ...
│
├── problems/
│   ├── codeforces/
│   ├── leetcode/
│   └── gfg/
│
├── cpp/
│   ├── smart-pointers/
│   ├── stl/
│   ├── memory/
│   └── ...
│
└── templates/
    └── cp.cpp
```

## Running C++ Code

Most examples are standalone C++ programs.

### Compile

From the directory containing `main.cpp`:

```bash
g++ main.cpp -o main
```

### Run

```bash
./main
```

### Example

```bash
cd algorithms/max-flow/Dinic

g++ main.cpp -o main
./main
```

If the program uses an `input.txt` file:

```bash
./main < input.txt
```

If you want to save the output to `output.txt`:

```bash
./main < input.txt > output.txt
```

## Notes

Some directories may contain additional files for testing or experimentation.

Generated files such as compiled executables, output files, and Valgrind logs are ignored by `.gitignore` and should not be committed.
