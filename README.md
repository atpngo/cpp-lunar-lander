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
- visualize force vectors for debugging
- reconstruct a flight from a log
- procedural terrain/obstacle generation
- autonomous controls 
    - (1) touch down with no obstacles (y-axis only) [DONE]
    - (2) move to target position (x+y axis)
    - (3) obstacle avoidance via sensor simulation and potentially sensor fusion?
    
- better physics (working on this)
    - learn what the ideal rocket equation is
    - currently lander doesn't account for mass of itself and its fuel
    - air resistance/drag
    - wind

- create a utility to generate scenarios (make every constant value adjustable)


## Controllers
- on/off (lol)
- pid 
    - control variable duty cycle (discrete engine on/off state)