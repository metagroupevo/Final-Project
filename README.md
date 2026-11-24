# Smart City Infrastructure System

A beginner-friendly standard C++ Data Structures project. It uses structures, fixed and dynamic arrays, pointers, manual traversal, shifting, searching, Merge Sort, and a two-dimensional matrix. Data is intentionally kept only during one program run.

## Requirement and lecture map

The referenced PDF and PowerPoint files were not present in the accessible workspace on November 24, 2026. The mapping therefore uses the lecture titles supplied in the request; slide numbers are marked unavailable rather than invented.

| Required feature | Data structure or method | Relevant lecture | Slide |
|---|---|---|---|
| Five record modules | Structures plus arrays and separate counts | Static Arrays & Traversal Operations | Not available |
| Road positional insertion | Right-shift loop | Static Arrays & Traversal Operations | Not available |
| Record deletion | Left-shift loop | Static Arrays & Traversal Operations | Not available |
| Utility records | Validated fixed-capacity `new[]` array | C++ Pointers & Memory Allocation | Not available |
| Address/dereference | `&`, `*`, `->`, and `pointer + index` | C++ Pointers & Memory Allocation | Not available |
| District links | Fixed `int[5][5]`, nested loops, row processing | Multi-Dimensional Arrays & Matrices | Not available |
| ID lookup | Manual sequential and iterative binary search | Searching Algorithms | Not available |
| ID/name/status ordering | Manual recursive Merge Sort | Advanced Sorting Algorithms | Not available |
| Validation/audit | Input-process-output functions, bounds, tests, Big-O | Linear Architecture & Peer Code Audit | Not available |

Linked lists, stacks, queues, priority queues, and trees are not included because the requested system is completely served by the required arrays, matrix, and algorithms.

## Folder structure

```text
include/  input.h, models.h, modules.h
src/      input.cpp, main.cpp, modules.cpp, search.cpp
docs/     architecture, technical manual, Big-O, testing, defense
```

## Compile and run

From `C:\Users\milton\Desktop\Final Project`:

### MinGW g++

```powershell
$env:PATH = "C:\msys64\ucrt64\bin;$env:PATH"
g++ -std=c++17 -Wall -Wextra -pedantic src\main.cpp src\input.cpp src\modules.cpp src\search.cpp -Iinclude -o smart_city.exe
.\smart_city.exe
```

For the detected MSYS2 installation, the provided build script performs the same setup and compilation:

```powershell
powershell -ExecutionPolicy Bypass -File .\build.ps1
$env:PATH = "C:\msys64\ucrt64\bin;$env:PATH"
.\smart_city.exe
```

The PATH line is required because `g++.exe` and its backend need DLL files stored in `C:\msys64\ucrt64\bin`.

### Visual Studio Developer Command Prompt

```bat
cl /std:c++17 /EHsc /W4 /Iinclude src\main.cpp src\input.cpp src\modules.cpp src\search.cpp /Fe:smart_city.exe
smart_city.exe
```

At startup, choose Utility Monitoring capacity from 1 to 100. This is intentionally not auto-resized: a `new[]` allocation has runtime-selected but still fixed capacity until a programmer explicitly reallocates it.

## Valid field values

- Traffic: Low, Medium, High
- Road condition: Good, Fair, Poor, Closed
- Facility status: Operational, Maintenance, Closed
- Emergency availability: Available, Unavailable
- Response status: Ready, Responding, Returning
- Utility status: Normal, Warning, Outage; usage 0–100
- Request priority: Low, Medium, High, Critical
- Request status: Pending, In Progress, Resolved
