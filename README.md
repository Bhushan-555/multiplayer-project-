Unreal Engine 5 Multiplayer Prototype (C++)
Overview

This is a personal Unreal Engine 5 C++ multiplayer prototype developed to practice and demonstrate core gameplay systems with a server-authoritative architecture.

The project focuses on implementing clean, scalable gameplay systems using Unreal Engine’s networking and replication features.

Features:-

Core Gameplay Systems
Server-authoritative Health, Damage, and Respawn system
Collectable system with PlayerState (individual score) and GameState (total score)
Pressure Plate & Gate system requiring multiple players
Damage Volume and Heal Volume
Basic HUD displaying Health, Score, and Lives

Multiplayer Architecture:-

All gameplay logic runs on the server
Proper use of:
Replicated variables
PlayerState & GameState
Authority checks (HasAuthority())
Clients receive updates via replication

Tech Stack:-

Unreal Engine 5
C++
Blueprint (for UI and tuning)

How to Run:-

In Editor (Multiplayer Test)
Open the project in Unreal Engine
Click Play Settings
Set:
Number of Players = 2
Net Mode = Listen Server
Click Play

Mobile / LAN Testing:-

Build and install the game on two devices
Connect both devices to the same Wi-Fi network
On Device 1 → Start as Host
On Device 2 → Enter Host IP and Join

Controls:-

Move: WASD / Touch
Jump: Space
Collectables: Overlap-based pickup

gameplay video :- https://youtu.be/rkJURUN9i8A
