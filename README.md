## Description

OpenCGE is a 3D game engine using component-based design with event-based messaging. It is programmed in C++17.

## Current State

Currently the core framework is functional and a basic proof of concept has been completed for multiple modules. Please see the examples for current usage. This project is still in early development stages and as such is not yet recommended for serious game development. Features may be added/removed at any time and backwards compatibility will not be guaranteed prior to the future 1.0 release. I will try to keep this README updated as I go.

## Dependencies

OpenCGE is modular by design and you will need different dependencies installed depending on which module(s) you wish to use. The core framework is provided by opencge-system and is required by all the modules. 

### Core Framework

**opencge-system**

* nlohmann/json

### Modules

**opencge-graphics-opengl-legacy**

* GLFW
* Assimp
* GLM

**opencge-physics**

* GLM

