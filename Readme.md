*This project has been created as part of the 42 curriculum by zaalrafa.*

# FDF

## Description

**FDF** is a 3D wireframe renderer written in C.  
The goal of this project is to parse a map file containing height values and display it as a 3D representation using a 2D graphics library.

The program reads a `.fdf` map file where each number represents the height (z-value) of a point on a grid. These points are then projected in 3D space (usually using isometric projection) and connected with lines to form a wireframe model.

This project introduces key concepts such as:
- 3D to 2D projections
- Linear algebra (vectors, scaling, rotation)
- Event handling (keyboard, window events)
- Basic graphics programming using **MiniLibX**

---

## Instructions

### Requirements

- **C compiler** (`cc`)
- **Make**
- **MiniLibX**
- Linux or macOS environment compatible with MiniLibX

### Compilation

Clone the repository and compile the project using:

```bash
make
