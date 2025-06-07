# Koraset El-Rasm (كراسة الرسم) 🎨

A comprehensive Windows-based computer graphics application implementing various drawing algorithms and techniques. The name "Koraset El-Rasm" means "Drawing Notebook/Canvas" in Egyptian Arabic, reflecting both the project's purpose and its cultural identity.

## About the Name 📖
"Koraset El-Rasm" (كراسة الرسم) is a nostalgic term in Egyptian culture that refers to the drawing notebooks used by students in art classes. We chose this name to give our graphics project a familiar, local touch while maintaining its professional capabilities.

## Features 💡

### Line Drawing Algorithms
- DDA (Digital Differential Analyzer)
- Bresenham's Line Algorithm
- Parametric Line Drawing

### Circle Drawing Algorithms
- Cartesian Method
- Polar Method (Direct & Iterative)
- Bresenham's Midpoint Circle Algorithm
- Circle DDA Algorithm

### Ellipse Drawing
- Direct Method
- Polar Method
- Midpoint Method

### Curve Generation
- Quadratic Curves
- Bezier Curves (Recursive & Midpoint)
- Cardinal Splines
- Hermite Curves

### Filling Algorithms
- Flood Fill (Recursive, Stack-based(DFS), Queue-based(BFS))
- Convex Polygon Fill
- Non-Convex Polygon Fill
- Quarter Circle Fill (Lines & Circles)
- Window Fill using Hermite/Bezier Curves

### Clipping Algorithms
- Point Clipping
- Line Clipping (Cohen-Sutherland algorithm)
- Polygon Clipping (Sutherland–Hodgman algorithm)

### Additional Features
- Save/Load Functionality
- Custom Color Selection
- Multiple Cursor Styles
- Background Color Customization

## Architecture 🏗️

The project follows the Strategy design pattern, organizing different algorithms into strategy classes:

- `DrawingStrategy`: Base class for all drawing algorithms
- `FillStrategy`: Base class for filling algorithms
- `ClippingStrategy`: Base class for clipping algorithms

### Key Components 🔑

- `Context`: Main class managing strategy selection and execution
- `Point`: Basic 2D point structure with operator overloading
- `Line`: Structure for line representation and storage
- `Util`: Common utility functions and structures

## Implementation Details 💻

### 🖌️ Drawing Implementation 
All drawing algorithms are implemented using the Windows GDI (Graphics Device Interface), utilizing the HDC (Handle to Device Context) for rendering.

### ⚡Performance Optimization 
- OpenMP parallelization for flood fill operations
- Efficient data structures for shape management
- Smart pointer usage for memory management

### 🖥️ User Interface 
- Menu-driven interface for algorithm selection
- Interactive drawing with mouse input
- Real-time visual feedback
- Informative help messages for each tool

## Building and Running 🚀

### ✅ Prerequisites 
- Windows Operating System
- C++ Compiler with OpenMP support
- Windows GDI libraries

### 🔨 Compilation 
The project can be compiled using any C++ IDE that supports Windows API programming.

## Usage Guide 📚

1. **Tool Selection**: Choose drawing/filling tool from menu
2. **Drawing**:
   - Lines: Click and drag
   - Circles/Ellipses: Click center and drag for radius
   - Curves: Click points sequentially, right-click to finish
   - Polygons: Click vertices, right-click to close
3. **Filling**:
   - Select fill color
   - Right-click inside shape to fill
4. **Clipping**:
   - Draw shapes
   - Select clipping tool
   - Define clipping window
   - View results

## Future Enhancements 🔮

- Enhanced UI/UX
- 3D shape support
- GPU acceleration


## Contributors 👥

- [Daniel Sameh](https://github.com/Daniel-Sameh)
- [Abanob Essam](https://github.com/AbanobEssam19) 
- [Youssef Ehab](https://github.com/YoussefEhab2)
- [Danial Raafat](https://github.com/DannyRaafat)
