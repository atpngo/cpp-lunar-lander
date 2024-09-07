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
- Start Up:
    - Grafana
    - Telegraf
    - Python Server
    - OPTIONAL: Jupyter Lab

- ./remake.sh


## Acknowledgements
- big thanks to https://github.com/JodyAndrews/SDL2_Basic_Setup for helping me set up this project :)

## Features
- PID CONTROL IN THE Y-AXIS YAY


## TODOS
- font atlases for optimal text rendering (currently just printing everything in terminal)
- visualize force vectors
- reconstruct a flight from a log
- procedural terrain/obstacle generation
- autonomous controls 
    - convert "rotation" into a fixed gimbal -> thrust vectoring
    - need to compute x distance angle and adjust 
- better physics (working on this)
    - learn what the ideal rocket equation is
    - currently lander doesn't account for mass of itself and its fuel
    - air resistance/drag
    - wind


## Controllers
- on/off (lol)
- pid 
    - control variable duty cycle (discrete engine on/off state)