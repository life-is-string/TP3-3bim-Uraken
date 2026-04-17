LINGUAGENS E TÉCNICAS DE PROGRAMAÇÃO - INFO2
-------------------------------------------------------------------------------------------
Grupo 8: 
- Mel Raposeiras Ricaldoni 
- Núbia Torres de Oliveira
- Sarah dos Santos Oliveira

# Uraken - Platformer game with physics!
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
[![Windows](https://img.shields.io/badge/platform-Windows-blue)]()

Um jogo platformer desenvolvido em C++ com SFML e Box2D como projeto de conclusão de curso do ensino médio técnico.

## Dependencies

- **Windows 7/8/10/11** (64-bit) 
- **SFML 2.5.1 GCC 7.3.0 MinGW (SEH) - 64-bit** [Download](https://www.sfml-dev.org/download/sfml/2.5.1/)
- **Box2D 2.4.0** [Download](https://github.com/erincatto/box2d/releases/tag/v2.4.0)
- **MinGW-w64 7.3.0** - [Download](https://sourceforge.net/projects/mingw-w64/) -> add the bin folder to your PATH variables
- **CMake 3.20+** - [Download](https://cmake.org/download/)

## 🚀 Building

### 1. Clone
```bash
git clone https://github.com/seu-usuario/Uraken.git
cd Uraken
```
### 2. Dependencies download
**SFML**
```powershell
cd Uraken/libs
Invoke-WebRequest -Uri "https://www.sfml-dev.org/files/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit.zip" -OutFile "SFML.zip"
Expand-Archive -Path SFML.zip -DestinationPath .
Rename-Item -Path "SFML-2.5.1" -NewName "SFML"
Remove-Item SFML.zip
cd ..
```
**Box2D + lib build**
```powershell
cd Uraken/libs
git clone https://github.com/erincatto/box2d.git
cd box2d
git checkout v2.4.0
mkdir build && cd build
cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
mingw32-make box2d
cd ../../..
```
### 3. Set the environment
```powershell
$env:Path = "C:\mingw64\bin;$env:Path"
gcc --version #(deve retornar mingw 7.3.0)
```
### 4. Compile and run the project running the build.bat
