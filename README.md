# Lagrangian Fluid Simulator

A simple 2D Lagrangian fluid simulation using **C++**, **SFML**, and **Verlet integration**.

- Uniform grid partitioning (no k-d trees)
- No multithreading
- ~10,000 particles at ~45–50 FPS

<br/>

## 📸 Screenshots

![Fluids (hopefully) 17_06_2025 15_12_05](https://github.com/user-attachments/assets/3e9fafba-29e7-4345-983a-68bce95b1951)

<br/>

## 🛠️ Build Instructions

This project uses **CMake** and fetches **SFML** automatically via `FetchContent`.
Ninja is required in order to build.

```bash
git clone https://github.com/N0zye/LagrangianFluidSim_simple.git
cd LagrangianFluidSim_simple
cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build
./build/bin/Fluids.exe
```
