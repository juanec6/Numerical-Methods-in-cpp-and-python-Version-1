## Purpose of the Repository

The goal of this repository is to demonstrate how **numerical methods** can be implemented in **C++** to perform iterative or analytical computations, and how **Python** can be used to visualize and analyze those results.  

This integration between the two languages provides both **computational efficiency** (from C++) and **clarity in visualization** (from Python), making it a great resource for learning, experimentation, and teaching numerical analysis concepts.

---

### Methods Covered

- **Root Finding Methods**: Bisection, Newton–Raphson, and Hybrid techniques  
- **Linear Systems of Algebraic Equations**: Direct (e.g. Gaussian elimination) and Iterative methods (e.g. Jacobi, Gauss–Seidel)  
- **Interpolation, Extrapolation, and Approximation**  
- **Numerical Differentiation and Integration**  
- **Ordinary Differential Equations (ODEs)**  
- **Partial Differential Equations (PDEs)**  

---

### Implementation Characteristics

- Each method includes **two files**:
  - A **C++ file**, responsible for performing numerical computations and iterative processes with high performance and precision.  
  - A **Python file**, which reads the generated data, processes it, and produces **plots or analyses** that illustrate the behavior of the method.

- Both files must be in the **same folder** for the workflow to function correctly.  
- The **C++ executable (.exe)** automatically calls the corresponding Python script for visualization.  

⚠️ Important Notes

This version is currently compatible only with Windows OS, due to a specific C++ library used in the implementation.

Future updates aim to improve cross-platform support (Linux/macOS).

⚖️ Legal Notice

Copyright © 2025 Juan David Escobar Cruz

All rights reserved.
This repository and its contents are the intellectual property of the author.
No part of this code or documentation may be copied, modified, distributed, or used for commercial, educational, or research purposes without explicit written permission.

For collaboration or redistribution requests, please contact the author directly.

```cpp

