# Raspberry Pi Pico – 3 Stepper Motor Control with Emergency Stop

## Overview
This project controls **three stepper motors** (X, Y, Z) using a Raspberry Pi Pico (W).  
Each axis is controlled by push buttons for **positive** and **negative** movement.  
An **emergency stop button** immediately halts all movement.

## Features
- Individual control of 3 stepper motors via ULN2003 drivers
- **Push button** input for each motor direction
- **Emergency Stop** (hardware interrupt)
- Simple, expandable code structure

## Hardware Used
- Raspberry Pi Pico
- 3 × 28BYJ-48 stepper motors
- 3 × ULN2003 driver boards
- 8 × push buttons (Start, Stop, ±X, ±Y, ±Z)
- Breadboard + jumper wires

## Pinout
| Function       | Pico Pin |
|----------------|----------|
| X Motor        | GP19, GP18, GP17, GP16 |
| Y Motor        | GP20, GP21, GP22, GP26 |
| Z Motor        | GP12, GP13, GP14, GP15 |
| Buttons        | GP0–GP7 |

## How to Run
1. Clone this repository.
2. Compile with the Pico SDK.
3. Flash the `.uf2` to your Pico.
4. Connect hardware as shown in the pinout table.
5. Press the direction buttons to move the motors.
