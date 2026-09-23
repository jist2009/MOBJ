# Object-Oriented Modeling for Circuit Design

This project implements a C++ graphical interface based on Qt 4 to visualize Netlist objects (cells, instances, symbols, and connections). It also supports reading and writing these models in XML format. 

## Main features
- **CellViewer**: Main application window (based on QMainWindow).
- **CellWidget**: Drawing space handling coordinate system conversions (Netlist vs Screen) to draw wires, connectors, and instances. 
- **File Management**: Dialog boxes to open (OpenCellDialog) and save (SaveCellDialog) cells.
- Data Models (Qt MVC):
    -  InstancesWidget / InstancesModel: List of instances present in the loaded model.
    - CellsLib / CellsModel: List of all cells currently loaded in memory.
- Symbols and Icons: Graphical representation of components using polymorphism (BoxShape, LineShape, TermShape, etc.) and a Factory design pattern.
- Synchronization: Uses Qt's Signal/Slot mechanism (e.g., updating libraries when a new cell is loaded).

## Prerequisites

To compile this project, the following dependencies are required:
- C++ Compiler
- CMake
- Qt 4 
- libxml2 
