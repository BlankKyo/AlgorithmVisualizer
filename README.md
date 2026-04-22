# Algorithm Visualizer

An interactive desktop application built in **C++ with Qt 6** that visualizes fundamental algorithms step by step in real time.

---

## Features

- Real-time step-by-step visualization
- Start, Pause, and Reset controls
- Adjustable speed slider
- Live status bar (Ready / Running / Paused / Done)
- Clean architecture — algorithm engine is pure C++ with zero Qt dependency
- Logger utility for debug output

---

## Algorithms

### Sorting
| Algorithm | Status |
|-----------|--------|
| Bubble Sort | ✅ v1.0 |
| Quick Sort | 🔜 v2.0 |
| Merge Sort | 🔜 v2.0 |
| Heap Sort | 🔜 v4.0 |
| Insertion Sort | 🔜 v4.0 |
| Selection Sort | 🔜 v4.0 |

### Pathfinding
| Algorithm | Status |
|-----------|--------|
| BFS | 🔜 v1.0 |
| Dijkstra | 🔜 v2.0 |
| A* | 🔜 v4.0 |
| DFS | 🔜 v4.0 |

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
│   │   ├── MainWindow.h
│   │   └── SortingWidget.h
│   └── utils/
│       └── Logger.h
└── src/
    ├── main.cpp
    ├── engine/
    │   ├── AlgorithmEngine.cpp
    │   └── BubbleSortEngine.cpp
    ├── ui/
    │   ├── MainWindow.cpp
    │   └── SortingWidget.cpp
    └── utils/
        └── Logger.cpp
```

---

### Data flow

```
QTimer::timeout
  → MainWindow::onTimerTick()
      → AlgorithmEngine::step()
          → BubbleSortEngine::doStep()
              → fireEvent(StepEvent)
                  → MainWindow::applyStep()
                      → SortingWidget::repaint()
                          → paintEvent() reads engine->getData()
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
| **v1.0** | Bubble Sort, BFS, basic controls, clean architecture | ✅ Done |
| v2.0 | QuickSort, MergeSort, Dijkstra, wall drawing, stats overlay | 🔜 Next |
| v3.0 | Smooth animations, pseudocode panel, step forward/back, themes | 🔜 |
| v4.0 | Heap Sort, A*, DFS, side-by-side comparison, complexity panel | 🔜 |
| v5.0 | Custom input, export to GIF, benchmarking, plugin API | 🔜 |
| v6.0 | Unit tests, CI/CD, cross-platform packaging, accessibility | 🔜 |

---

## License

MIT
