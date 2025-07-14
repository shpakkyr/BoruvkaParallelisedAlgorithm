# 🌲 Parallel Borůvka's Algorithm

This project implements Borůvka’s algorithm to find the Minimum Spanning Tree (MST) of a graph, providing both single-threaded and multi-threaded versions for performance comparison.

---

## 🎯 Project Objectives

- Implement Borůvka’s algorithm in a serial (single-threaded) version.
- Develop a parallel version using multi-threading to accelerate computation.
- Compare execution times between both implementations.
- Ensure correct input processing, precise memory management, and program portability.

---

## ⚙️ Application Features

### 🧵 Single-threaded Implementation

- Iteratively searches for the cheapest edge for each component.
- Uses disjoint sets to merge components efficiently.

### ⚡ Multi-threaded Implementation

- Divides edges into segments processed in parallel by multiple threads.
- Each thread finds the cheapest edges within its segment.
- At the end of each iteration, results are merged into the global state.

---

## 🧪 Performance Measurement

Execution times were measured on a Ryzen 7 7800X3D 8-core CPU at 4.2 GHz.  
Testing was performed on a virtual machine limited to 4 cores.

---

## 📥 Input Format

The input file must be structured as follows:

- **First line:** number of vertices `V` and edges `E`.
- **Subsequent lines:** edges in the format `U V W`, where:
  - `U` and `V` are vertex indices.
  - `W` is the edge weight.

**Example Input:**
5 7
0 1 10
0 2 6
0 3 5
1 3 15
2 3 4
1 4 7
3 4 2


---

## 🚀 Usage Examples

**Run single-threaded version:**
```bash
./SemestralWork -f data/input.txt -a serial
```

---

**Run multi-threaded version with 4 threads:**
```bash
./SemestralWork -f input.txt -a parallel -t 4
```

**Vertices Edges: serial_time - parallel_time**
```bash
5 7: 0 ms - 0 ms
100 300: 0 ms - 0 ms
10k 30k: 1 ms - 2 ms
10M 10M: 648 ms - 911 ms
10M 11M: 1585 ms - 1538 ms
11M 11.5M: 1359 ms - 1660 ms

With a larger difference between vertices and edges:

1M 5M: 479 ms - 284 ms
1M 10M: 811 ms - 411 ms
1M 15M: 1287 ms - 635 ms
1M 20M: 1757 ms - 691 ms
1M 30M: 2518 ms - 1014 ms
2M 10M: 1163 ms - 725 ms
4M 20M: 3185 ms - 1890 ms
4M 30M: 4648 ms - 2139 ms
100k 20M: 812 ms - 355 ms
100k 30M: 1226 ms - 517 ms
```

📈 Interpretation

When the number of vertices and edges are similar, the single-threaded implementation often performs faster or comparably.
As the graph grows larger and the ratio of edges to vertices increases, the parallel implementation demonstrates significant speed improvements.
