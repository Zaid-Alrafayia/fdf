# *This project has been created as part of the 42 curriculum by zaalrafa.*

## Description
fdf is a 3D wireframe viewer (a "Fil de Fer" project) that reads a heightmap from a `.fdf` file and renders a 2D isometric projection of the 3D points using MiniLibX. The program supports scaling, height/zoom adjustments, basic rotations, and color gradients between vertices. The goal is to practice low-level C, pointers, linked lists, simple 2D/3D math, and the use of MiniLibX while following the 42 project rules (including Norminette).

Key features
- Parse `.fdf` maps into an internal matrix (linked lists of pixels).
- Project 3D coordinates to isometric 2D points.
- Draw anti-aliased-like lines using Bresenham + color gradient.
- Interactive controls: zoom, rotate, move, height-scale adjustments.
- Careful memory management, Valgrind-clean (no definite leaks).

## Instructions

Prerequisites
- A working C compiler (gcc/clang).
- make
- MiniLibX (Linux/X11 or macOS version). On Linux, libX11 and libxcb must be available.
- Standard 42 libc helpers (libft or equivalent functions used: ft_split, ft_strdup, ft_atoi, etc.).

Build
- Run:
```sh
make
```
This builds the `fdf` executable using the included `Makefile`. The `Makefile` sets compilation flags and links MiniLibX.

Run
- Example:
```sh
./fdf test_maps/t2.fdf
```
- Controls (default, may vary depending on implementation):
  - Mouse wheel / +/- : zoom in/out
  - Arrow keys : move the projection
  - Keys to rotate the model about x/y/z axes
  - Key to reset view or exit (see program key bindings printed in console)

Developer / debug run
- Use Valgrind to check memory:
```sh
valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all ./fdf test_maps/t2.fdf
```
- For address sanitizer build (if you adjust compile flags):
  - Add `-fsanitize=address -g` to CFLAGS and rebuild.

Notes about MiniLibX & platforms
- On Linux, ensure your MiniLibX installation is the X11 version and X11 development headers are installed.
- Some "still reachable" Valgrind entries from X11/MiniLibX are expected (library-internal caches). Focus on "definitely lost" entries — the code aims to produce none.

## Project structure (high level)
- main.c — initialization and top-level control
- init_matrix.c / parse routines — read .fdf files into linked-list matrix
- draw.c / line.c — projection and line rasterization
- rotate.c — rotate / project functions
- pixel_gen.c  — image buffer writing
- free.c — cleanup utilities
- Makefile — build rules

## Resources
- Harm Smits — 42 graphic projects documentation: https://harm-smits.github.io/42docs/ (Chapter VII)
- FDF walkthroughs:
  - https://medium.com/@amehri_tarik/fdf-42-a-detailed-walkthrough-7184cca317fc
  - https://medium.com/@ouaallaabdelali1/fdf-725b6255d053

## How AI was used
I used an AI assistant (ChatGPT / GitHub Copilot persona) to help with several development tasks. The assistant was used for:
- Refactoring large functions to match Norminette-style constraints (splitting functions so each has at most ~4 local variables and <25 lines). For example:
  - drawline was split into helper functions that compute absolute differences, step directions, update error and coordinates, etc.
  - compute_center_offsets was split into init_minmax, scan_matrix_minmax, and apply_center_offsets.
- Fixing a critical buffer overrun bug in `img_pixel_put` (incorrect loop bounds that wrote past end of pixel buffer). The fix changed loops to write exactly `bpp` bytes (indices 0..bpp-1).
- Debugging Valgrind `Conditional jump or move depends on uninitialised value(s)` issues by ensuring `t_fdf` is zero-initialized (using `calloc` or `memset`) and setting sensible defaults in `init_fdf`.

Important: All AI-proposed code was reviewed, adapted, and integrated by me (zaalrafa). The AI assisted as a tool for refactoring, bug identification, and producing code sketches / patches — but final code and decisions were made by the author.

- Use `valgrind --leak-check=full --show-leak-kinds=definite,possible` to focus on real leaks. Many small "still reachable" allocations from X11/MiniLibX are normal.

## Example compile & run (summary)
```sh
make
./fdf test_maps/t2.fdf
valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all ./fdf test_maps/t2.fdf
```

## Contact
Author: zaalrafa (42 login: zaalrafa)

---

If you want, I can:
- Produce a short CONTRIBUTING.md with coding style and the exact Norminette checks I used.
- Create a reproducible Valgrind script and a small unit test that exercises GNL EOF behavior to show the leak is fixed.
- Produce a minimal diff / PR for any of the refactors discussed.

