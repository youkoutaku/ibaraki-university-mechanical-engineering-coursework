# Manipulator-Simulation-by-OpenGL

3D Robot Manipulator Simulation using OpenGL and GLUT

Made by YANG (2023/01/31)

## Overview

This project implements a 3D robot manipulator simulation with inverse kinematics using OpenGL and GLUT. The simulation includes multiple versions with different degrees of freedom and provides real-time visualization of robot arm movements.

## Features

- **3D Visualization**: Real-time OpenGL rendering of robot manipulator
- **Inverse Kinematics**: Automatic calculation of joint angles for target positions
- **Interactive Controls**: Camera movement and angle adjustment
- **Multiple Versions**: Different degrees of freedom implementations
- **Trajectory Display**: Visual representation of arm movement paths

## Project Structure

```
code/
├── 3.0/           # Final version (4+1 DOF manipulator)
├── 20t1126n(YANG GUANGZE)/
│   ├── 1_0/       # 3 DOF manipulator
│   └── 2_0/       # 4 DOF manipulator
├── sample/        # Sample programs
├── test/          # Test programs
└── makefile/      # Build configuration

setup/             # GLUT setup files
OpenGL_study/      # OpenGL learning materials
```

## Versions

- **Version 1.0**: 3次元3自由度ロボットマニピュレータ (3D 3-DOF Robot Manipulator)
- **Version 2.0**: 3次元4自由度ロボットマニピュレータ (3D 4-DOF Robot Manipulator)
- **Version 3.0**: 最終版 (Final version with 4+1 DOF)

## Controls

| Key | Function |
|-----|----------|
| `F1` | 実行 (Execute/Run simulation) |
| `W` `S` `A` `D` `Q` `E` | カメラ移動 (Camera movement) |
| `↑` `↓` `←` `→` | カメラ角度 (Camera angle) |
| `0` | 原点復帰 (Return to origin) |

## Requirements

- **Compiler**: Borland C++ Compiler (BCC32)
- **Graphics**: OpenGL and GLUT libraries
- **OS**: Windows (tested on Windows NT/95/XP and later)

## Setup

1. **Install GLUT**: Run setup scripts in `setup/` directory
   ```batch
   cd setup
   glut-setup.bat
   bcc-setup.bat
   ```

2. **Set Environment**: Configure Borland compiler paths
   ```batch
   cd code/makefile
   setpath.bat
   ```

## Building

```batch
cd code/3.0
make
```

## Running

```batch
invK3d.exe
```

## Technical Details

- **Inverse Kinematics**: Jacobian matrix-based calculation
- **Sampling Time**: 0.005 seconds
- **Simulation Time**: 15.0 seconds
- **Control Gain**: KP = 20.0
- **Target Position**: Configurable in source code

## Files

- `invK3d.c`: Main simulation program
- `invK3d_l.c`: Inverse kinematics library
- `glwindow.c`: OpenGL window management
- `glshapes.c`: 3D shape rendering
- `armIK.dat`: Arm parameters
- `angles.dat`: Joint angle output

## Documentation

- [工夫点.pdf](工夫点.pdf): Technical improvements and features (Japanese)
- `OpenGL_study/doc/`: OpenGL learning materials

## License

MIT License - see [LICENSE](LICENSE) file for details.

## Encoding

UTF-8
