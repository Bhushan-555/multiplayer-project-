#  Unreal Engine 5 Multiplayer Prototype (C++)

---

##  Overview

This is a **Unreal Engine 5 C++ multiplayer prototype** developed to practice and demonstrate **core gameplay systems with a server-authoritative architecture**.

The project focuses on implementing **clean, scalable gameplay systems** using Unreal Engine’s networking and replication features.

---

##  Features

###  Core Gameplay Systems

* Server-authoritative **Health, Damage, and Respawn system**
* **Collectable system** with:

  * PlayerState (individual score)
  * GameState (total score)
* **Pressure Plate & Gate system** requiring multiple players
* **Damage Volume and Heal Volume**
* Basic **HUD** displaying:

  * Health
  * Score
  * Lives

---

##  Multiplayer Architecture

* All gameplay logic runs on the **server**
* Proper use of:

  * **Replicated variables**
  * **PlayerState & GameState**
  * **Authority checks (`HasAuthority()`)**
* Clients receive updates via **replication**

---

##  Tech Stack

* Unreal Engine 5
* C++
* Blueprint (for UI and tuning)

---

##  How to Run

###  In Editor (Multiplayer Test)

1. Open the project in Unreal Engine
2. Click **Play Settings**
3. Set:

   * Number of Players = 2
   * Net Mode = Listen Server
4. Click **Play**

---

###  Mobile / LAN Testing

1. Build and install the game on two devices
2. Connect both devices to the same Wi-Fi network
3. On Device 1 → **Start as Host**
4. On Device 2 → Enter Host IP → **Join**

---

##  Controls

* Move → WASD / Touch
* Jump → Space
* Collectables → Overlap-based pickup

---

## Gameplay Video :- https://youtu.be/rkJURUN9i8A


