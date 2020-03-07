# Reme Game Engine

## Requirements

### Windows

Visual Studio build tools for C/C++

### Linux

Required package: libx11-dev mesa-common-dev

- libx11: X11 lib needed for `GLFW3`

- mesa-common-dev: OpenGL lib for `glad`

Can be install using the command:
```
sudo apt-get install libx11-dev mesa-common-dev
```

## Generate project

### Windows

```
vendor\premake5.exe vs2019
```

Switch `2019` with your Visual Studio version

### Linux

```
vendor/premake5 gmake2
```

## Configuration

### Define flags

- _REME_DISABLE_ASSERT : disable `assert`

- _REME_DISABLE_LOG : disable logging

- _REME_DISABLE_LUA : disable lua scripting
