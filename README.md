# Lunar Lander Simulation in C++


## MacOS Installation Instructions

Xcode Command Line Tools ( if not already installed )

- xcode-select --install

SDL2 Installs

- brew install sdl2
- brew install sdl2_image
- brew install sdl2_mixer
- brew install sdl2_ttf


## Command Line Build

- ./remake.sh


## Acknowledgements
- big thanks to https://github.com/JodyAndrews/SDL2_Basic_Setup for helping me set up this project :)


## TODOS
- font atlases for optimal text rendering (currently just printing everything in terminal)
- visualize force vectors
- reconstruct a flight from a log
- procedural terrain/obstacle generation
- autonomous controls 
- better physics
    - currently lander doesn't account for mass of itself and its fuel
    - air resistance/drag
    - thrust vectoring
- autonomously move to mouse


## Controllers
- on/off (lol)
- pid 
    - control variable duty cycle (discrete engine on/off state)