# FLAME TROUBLE

A 2D pixel-art game made in C++ with SFML. You play as a small flame that has to dodge enemies, burn/collect leaves scattered around each level, and reach the goal zone to advance. The game has 10 levels, a level selector, checkpoints, a settings menu, and persistent save data (best times, death records, settings).

## 📥 Download & Play

**[Download the latest installer here!](https://github.com/Patrick-Jambo/psio-project/releases/tag/v.1.0.0)**

1. Go to the link above.
2. Download the `FlameTrouble_Setup.exe` file.
3. Run the installer and enjoy the game!

## Controls

- `W A S D` – move
- `P` or `ESC` – pause the game
- `R` – reset the current level
- Mouse – navigate menus / settings / level selector

## Features

- 10 handcrafted levels with different enemy patterns (ping-pong, path-following, circular movement)
- Collectibles (leaves) that must all be picked up before the goal area opens
- Checkpoints that update the respawn point mid-level
- Main menu, level selector, settings (music/sound toggle, volume, god mode, hitbox debug view)
- Level transition screens with custom text per level, loaded from a save file
- End screen showing total deaths/time, with global "best run" records
- Save/load system using `nlohmann::json` (best times, global records, settings) — see `assets/data/game_data.json`

## Project structure

- `main.cpp`, `Game.hpp/.cpp` – entry point and main game loop/state machine (menu, rules, transition, playing, paused, end screen)
- `core/` – engine-level systems:
  - `Config` – window/game constants
  - `ResourceManager` – caches textures, fonts, and sound buffers
  - `Animation` – simple sprite-sheet frame animator
  - `TileMap` – loads/draws the level grid and handles wall collision
  - `LevelManager` – defines all 10 levels (tile grids, enemy/collectible/area placement, spawn points)
  - `SaveManager` – reads/writes `game_data.json` (records, settings, level intertitles)
  - `SoundManager` – plays one-shot sounds (death, collect, level clear, checkpoint)
  - `Utils` – small helper functions (e.g. centering UI elements)
- `objects/` – game entities:
  - `Entity` – base class for drawable, updatable objects with a hitbox
  - `Player` – movement, collision with walls, animation
  - `Enemy` – supports ping-pong, multi-point path, and circular movement patterns
  - `Collectible` – the leaves; has an idle/bounce state and a burning/collected animation
- `areas/` – trigger zones placed on the map:
  - `Area` – base class for rectangular trigger zones
  - `GoalArea` – ends the level once all collectibles are picked up
  - `CheckpointArea` – moves the respawn point and plays a campfire animation
- `ui/` – all menus and HUD elements:
  - `Button` – reusable clickable text button with hover states
  - `MainMenu`, `Settings`, `LevelSelector`, `GameRules`, `LevelTransition`, `LevelStatsDisplay`, `EndGameScreen`
  - 
## Assets

- Textures/sprites: generated with the help of AI image tools and touched up in Photopea
- Fonts: `Pixeled.ttf` and `Pixelzone.ttf`, free fonts from dafont.com
- Background music: based on an existing track, heavily pitch-shifted in Audacity
- Sound effects: free assets licensed for commercial use
