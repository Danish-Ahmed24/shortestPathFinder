# separation/

This folder contains a split-out, namespaced implementation of the classes found in the top-level `main.cpp`.

Files created:

- `City.h` / `City.cpp` — City data class
- `Route.h` / `Route.cpp` — Route (edge) representation with traffic and blocking state
- `MinHeap.h` / `MinHeap.cpp` — small custom min-heap used by Dijkstra
- `Graph.h` / `Graph.cpp` — Graph class containing adjacency lists, Dijkstra implementation, save/load
- `test.cpp` — small test harness to show these pieces compile and run

Notes:

- I did not modify `main.cpp` (per your request). The separated classes are inside namespace `separation` so they won't clash with existing symbols in `main.cpp`.
- To build the test program using g++ on Windows or Linux, from the repository root do:

```sh
# compile all separation files into a single executable
g++ -std=c++17 separation/*.cpp -o separation_test
```

## Windows (one-step)

If you use Windows (cmd.exe) there's a convenience script in this folder which will build and run the test for you. From inside the `separation/` directory run:

```
build_and_run_test.bat
```

This compiles the `.cpp` files in the directory and runs `separation_test.exe`.

- Or compile only the files explicitly:

```sh
g++ -std=c++17 separation/City.cpp separation/Route.cpp separation/MinHeap.cpp separation/Graph.cpp separation/test.cpp -o separation_test
```

If you'd like, next I can:

- Add a proper CMakeLists.txt for separation/ so the code can be built as a library,
- Update `main.cpp` to use these headers instead of its inline versions, or
- Add unit tests / examples that show saving/loading and query operations.
