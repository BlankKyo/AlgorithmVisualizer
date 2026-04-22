# Algorithm Visualizer

An interactive desktop application built in **C++ with Qt 6** that visualizes fundamental algorithms step by step in real time.

---

## Features

- 🏠 **Home Page** — Browse and select from multiple algorithm categories
- Real-time step-by-step visualization
- Start, Pause, Reset, and Back controls
- Adjustable speed slider
- Multiple algorithm categories (Sorting, Searching, Graph Algorithms, Dynamic Programming)
- Clean architecture — algorithm engine is pure C++ with zero Qt dependency
- Logger utility for debug output
- Extensible widget system for adding new algorithm visualizations

---

## Algorithms

### Sorting
| Algorithm | Status |
|-----------|--------|
| Bubble Sort | ✅ v1.1 |
| Quick Sort | 🔜 v2.0 |
| Merge Sort | 🔜 v2.0 |
| Heap Sort | 🔜 v4.0 |
| Insertion Sort | 🔜 v4.0 |
| Selection Sort | 🔜 v4.0 |

### Searching
| Algorithm | Status |
|-----------|--------|
| Linear Search | 🔜 v2.0 |
| Binary Search | 🔜 v2.0 |

### Graph Algorithms
| Algorithm | Status |
|-----------|--------|
| BFS | 🔜 v2.0 |
| DFS | 🔜 v2.0 |
| Dijkstra | 🔜 v3.0 |
| A* | 🔜 v4.0 |

### Dynamic Programming
| Algorithm | Status |
|-----------|--------|
| Fibonacci Sequence | 🔜 v3.0 |
| Knapsack Problem | 🔜 v3.0 |
| Longest Common Subsequence | 🔜 v3.0 |

---

## Project Structure

```
AlgorithmVisualizer/
├── CMakeLists.txt
├── README.md
├── run.ps1
├── include/
│   ├── engine/
│   │   ├── AlgorithmEngine.h      # Abstract base + StepEvent
│   │   └── BubbleSortEngine.h
│   ├── ui/
│   │   ├── MainWindow.h           # Main window with navigation
│   │   ├── HomePage.h             # Algorithm selection page
│   │   ├── AlgorithmWidget.h      # Base class for algorithm visualizations
│   │   └── SortingWidget.h        # Sorting visualization widget
│   ├── utils/
│   │   ├── Logger.h
│   │   ├── MemoryUtils.h      
│   │   └── RandomGenerator.h
│   └── datastructure/
│       └── graphs/
│           └── Graph.h
└── src/
    ├── main.cpp
    ├── engine/
    │   └── BubbleSortEngine.cpp
    ├── ui/
    │   ├── MainWindow.cpp
    │   ├── HomePage.cpp           # Home page implementation
    │   ├── AlgorithmWidget.cpp    # Base algorithm widget
    │   └── SortingWidget.cpp
    ├── utils/
    │   ├── Logger.cpp
    │   ├── MemoryUtils.cpp      
    │   └── RandomGenerator.cpp
```

---

### UI Architecture

The application uses a stacked widget architecture:

```
MainWindow (QMainWindow)
  ├── HomePage
  │   ├── Category List (Sorting, Searching, Graph, DP)
  │   ├── Algorithm List (context-dependent)
  │   └── Description Panel
  │
  └── AlgorithmPage
      ├── Controls Bar (Back, Start, Pause, Reset, Speed)
      └── AlgorithmWidget (SortingWidget, GraphWidget, etc.)
```

### Data flow

```
HomePage::algorithmSelected()
  → MainWindow::onAlgorithmSelected()
      → MainWindow::setupEngine()
          → Creates appropriate engine (BubbleSortEngine, etc.)
          → Creates appropriate widget (SortingWidget, etc.)
QTimer::timeout
  → MainWindow::onTimerTick()
      → AlgorithmEngine::step()
          → Specific engine doStep()
              → fireEvent(StepEvent)
                  → MainWindow::applyStep()
                      → AlgorithmWidget::updateVisualization()
                          → paintEvent() reads engine data
```

### StepEvent types

| Type | Meaning | Widget color |
|------|---------|--------------|
| `Compare` | Two elements being examined | Amber |
| `Swap` | Two elements being exchanged | Red |
| `Visit` | Grid cell explored (pathfinding) | Blue |
| `PathFound` | Final path traced | Green |
| `Done` | Algorithm finished | — |

---

## Requirements

| Dependency | Version |
|------------|---------|
| Qt | 6.x |
| CMake | 3.20+ |
| C++ | 17 |
| Compiler | MSVC 2022 / GCC 11+ / Clang 13+ |

---

## Roadmap

| Version | Focus | Status |
|---------|-------|--------|
| **v1.0** | Bubble Sort, basic controls, clean architecture | ✅ Done |
| **v1.1** | Home page, multi-algorithm framework, extensible widgets | ✅ Done |
| v2.0 | Additional sorting (Quick, Merge), Searching algorithms | 🔜 Next |
| v3.0 | Graph algorithms (BFS, DFS), smooth animations | 🔜 |
| v4.0 | Dynamic programming, A*, side-by-side comparison | 🔜 |
| v5.0 | Custom input, export to GIF, benchmarking | 🔜 |
| v6.0 | Unit tests, CI/CD, cross-platform packaging | 🔜 |

---

## License

MIT
