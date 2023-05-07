![Go Figure screenshot](https://user-images.githubusercontent.com/61359702/236653859-7db4a605-4400-4228-b7e0-30dec8a82594.png)

# About Project

Go Figure is a simple game written in x86 assembly. It challenges players to quickly identify and click on the correct figures before the timer runs out. Players can choose to play by color or shape. The game could be useful in teaching children shapes and colors, and improving their reaction time and hand-eye coordination.

## What I learned

- Assembly language programming
- Game development basics
- Input handling
- Mouse input handling
- Performance optimization
- Debugging and testing
- Instruction set architecture
- Memory management
- Interrupt handling
- x86 Architecture
- User Interface design

---

## How to play

1. Download [DOSBox](https://www.dosbox.com/download.php?main=1).
   > If DOSBox is too small you can set windowresolution=1600x900 and output=overlay in DOSBox options.
2. Download [/build/GAME.EXE](./build/GAME.EXE).
3. Launch DOSBox.
4. Mount the directory where you downloaded GAME.EXE.  
   for example C:\Users\username\Downloads\GAME.EXE
   ```powershell
    mount D: C:\Users\username\Downloads\
   ```
5. Navigate to the newly mounted directory D by typing 'D:'.
   ```powershell
   D:
   ```
6. Launch the game by typing 'GAME.EXE'.
   ```powershell
   GAME.EXE
   ```
7. Enjoy!

### Gameplay

1. Start by entering your name.
2. Use the arrow buttons to navigate and select 'Play Go Figure!!' and hit Enter.
3. Select the desired game mode.
4. Select the speed of the timer.
5. Read the instructions and click with mouse when ready.
6. Click on the correct figure before the timer runs out.
   ![Go Figure screenshot](https://user-images.githubusercontent.com/61359702/236654015-5edd0830-e00c-4d25-81fd-ddc71aad9120.png)

---

## Build Go Figure from source

1. Download [DOSBox](https://www.dosbox.com/download.php?main=1).
   > If DOSBox is too small you can set windowresolution=1600x900 and output=overlay in DOSBox options.
2. Clone the repository by running the following command in your terminal or command prompt:
   ```shell
   git clone https://github.com/ziadabdo98/Go-Figure.git GoFigure
   ```
3. Launch DOSBox.
4. Mount the directory where you cloned GoFigure.  
   for example C:\Users\username\Downloads\GoFigure
   ```powershell
    mount D: C:\Users\username\Downloads\GoFigure
   ```
5. Navigate to the newly mounted directory D by typing 'D:'.
   ```powershell
   D:
   ```
6. Assemble game.asm file using TASM assembler in /tools/ and press enter for all the prompts.
   ```powershell
   tools\tasm.exe game.asm build\game.obj
   ```
   This will generate build\game.obj object file.
7. Link the object file generated from the previous steup using linker /tools/link.exe
   ```powershell
   tools\link.exe build\game.obj , build\game.exe
   ```
   This will generate an executable build\game.exe ready to be run.
