# WebAssemblyBase

This repository is for the testing WebAssembly. I want to achieve the following goals:
1. Pass number from JavaScript to C++ - **DONE**
2. Pass number from C++ to JavaScript - **DONE**
3. Pass string from JavaScript to C++ - **DONE**
4. Pass string from C++ to JavaScript - **DONE**
5. Invoke Javascript callback - **DONE**
6. Use thread for run looping function - **Problems**

There are four pages:
1. General - test some interaction wothout threads.
2. Threads - none - Thread test code without threads.
3. Threads - Posix - Thread test code using Posix Threads.
4. Threads - Worker - Thread test code using Wasm Worker.

All three thread test WASMs are generated from the same C++ source using __EMSCRIPTEN_PTHREADS__ and __EMSCRIPTEN_WASM_WORKERS__ macros.

The index page tests the https://github.com/gzuidhof/coi-serviceworker , but thread test pages are in PHP and has following code:
```
header("Cross-Origin-Embedder-Policy: require-corp");
header("Cross-Origin-Opener-Policy: same-origin");
```

# Project online link

This project is under the link, but PHP pages does not work due to GitHub limitations.

https://andrzejlisek.github.io/WebAssemblyBase/

