# Maze-Solving Robot V1.0

<p align="center">
  <img src="images/robot.jpeg" alt="Maze-Solving Robot V1.0" width="700">
</p>

<p align="center">
  <b>An embedded systems project focused on bare-metal firmware, custom PCB design, hardware bring-up, and autonomous robot navigation.</b>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/MCU-STC89C52RC-blue">
  <img src="https://img.shields.io/badge/Firmware-Embedded%20C-orange">
  <img src="https://img.shields.io/badge/PCB-EasyEDA-green">
  <img src="https://img.shields.io/badge/PCB%20Assembly-JLCPCB-purple">
  <img src="https://img.shields.io/badge/Status-Working-success">
</p>

> **This project was sponsored by JLCPCB through PCB manufacturing and assembly support.**

---

## Overview

The **Maze-Solving Robot V1.0** is an academic embedded systems project developed to design and build a small autonomous robot capable of navigating a maze using ultrasonic distance measurements and a wall-following strategy.

The project was developed from the ground up, covering both **hardware and firmware**, from the initial system concept and embedded software development to custom PCB design, manufacturing, hardware bring-up, and final robot integration.

The project was also developed with support from **JLCPCB**, which provided PCB manufacturing and assembly services for the custom-designed board.

The main objective was not only to build a functional robot, but also to gain practical experience in **bare-metal embedded programming, low-level microcontroller peripherals, PCB design, hardware debugging, and hardware-software integration**.

---

## Project Demonstration

<p align="center">
  <img src="images/robot moving.gif" width="700">
</p>

**▶ [Watch the complete project video](YOUR_VIDEO_LINK_HERE)**

---

# JLCPCB Sponsorship & Manufacturing

This project was developed with support from **JLCPCB**, which sponsored the manufacturing and assembly of the custom PCB used in the robot.

The collaboration allowed the project to move from a prototype-level design to a **professionally manufactured and assembled PCB**.

The manufacturing process included:

* Custom PCB fabrication
* Component sourcing
* SMT assembly
* Automated component placement
* PCB assembly inspection
* Manufacturing of the final embedded hardware

<p align="center">
  <img src="images/unboxing.jpeg" width="700">
</p>

The complete manufacturing files are included in this repository to make the hardware design transparent and reproducible.

### Manufacturing Files

| File                  | Description              |
| --------------------- | ------------------------ |
| `Gerber_...zip`       | PCB manufacturing files  |
| `BOM_...csv`          | Bill of Materials        |
| `PickAndPlace_...csv` | Component placement data |
| `Schematic_...pdf`    | Electrical schematic     |
| `Schematic_...png`    | Schematic preview        |

The PCB was designed using **EasyEDA** and manufactured and assembled by **JLCPCB**.

---

## From Concept to Manufactured Hardware

One of the main purposes of this project was to experience the complete embedded systems development cycle rather than focusing exclusively on firmware.

The development process followed approximately this workflow:

```text
Initial Concept
      ↓
System Architecture
      ↓
Hardware & Firmware Development
      ↓
Prototype Testing
      ↓
Schematic Design
      ↓
PCB Layout
      ↓
Design Validation
      ↓
JLCPCB Manufacturing & Assembly
      ↓
Hardware Bring-Up
      ↓
Firmware Integration
      ↓
Robot Assembly
      ↓
System Testing
```
This process provided hands-on experience with the transition from an embedded systems concept to **real manufactured hardware**.

---

# Hardware

## Main Components

| Component                      | Description                          |
| ------------------------------ | ------------------------------------ |
| **STC89C52RC**                 | Main 8051-compatible microcontroller |
| **CH340C**                     | USB-to-UART interface                |
| **HC-SR04**                    | Ultrasonic distance sensor           |
| **SG90**                       | Servo motor for sensor positioning   |
| **BYJ48 ×2**                   | Stepper motors                       |
| **7805**                       | MCU voltage regulator                |
| **5 V high-current regulator** | Motor and servo power supply         |
| **USB-C**                      | Power and programming interface      |
| **16 MHz crystal**             | MCU clock source                     |
| **TVS protection**             | Transient voltage protection         |
| **Status LEDs**                | System and debugging indicators      |

<p align="center">
  <img src="images/components.jpeg" alt="Maze-Solving Robot V1.0" width="700">
</p>

---

# Custom PCB

The robot uses a **custom-designed and professionally assembled PCB** rather than a conventional development board.

The PCB integrates:

* STC89C52RC microcontroller
* CH340C USB-to-UART interface
* Power regulation
* Motor interfaces
* Servo interface
* Ultrasonic sensor interface
* Reset circuitry
* Programming interface
* Status LEDs
* Protection components
* Ground planes

<p align="center">
  <img src="Schematic_Maze-Solving-Robot_2026-09-14.png" width="700">
</p>

<p align="center">
  <img src="images/Design.png" width="700">
</p>

The custom PCB was designed specifically around the electrical and mechanical requirements of the robot, allowing the final system to be considerably more integrated than a breadboard prototype.

---

# Hardware Bring-Up

After receiving the assembled PCB from JLCPCB, the board was validated progressively before integrating the complete robot.

The bring-up process included:

* Power rail verification
* MCU supply verification
* Reset circuit testing
* Clock frequency verification
* USB-to-UART communication testing
* MCU programming
* LED testing
* Peripheral validation
* Motor and servo testing
* Firmware integration

> **Oscilloscope measurement of the MCU clock**
<p align="center">
  <img src="images/oscilador.jpeg" width="700">
</p>

> **Electrical measurements during bring-up**
<p align="center">
  <img src="images/voltaje.jpeg" width="700">
</p>

---

# Maze-Solving Algorithm

The robot uses a **left-hand wall-following strategy** based on continuous ultrasonic distance measurements.

The ultrasonic sensor is positioned to measure the distance to three directions:

* **L** — Left
* **F** — Front
* **R** — Right

The navigation algorithm continuously evaluates these three measurements and determines the next movement according to a defined priority.

<p align="center">
  <img src="images/flowchart.jpg" alt="Maze-solving algorithm flowchart" width="850">
</p>

### Navigation Logic

**1. Sensor Measurement**

The robot continuously measures the distance to the left, front, and right sides:

* `L` → Left
* `F` → Front
* `R` → Right

**2. Left-Side Priority**

If the left side is free:

`L = No`

the robot gives priority to turning left.

**3. Front and Right Evaluation**

If the left side is blocked:

`L = Yes`

the robot evaluates the front and then the right side.

* If the front is free:

  `F = No`

  → **Go Ahead**

* If the front is blocked:

  `F = Yes`

  but the right side is free:

  `R = No`

  → **Turn Right**

* If all three directions are blocked:

  `L = Yes, F = Yes, R = Yes`

  → **Turn 180°**

**4. Movement and Stop**

After selecting the appropriate direction, the robot proceeds through the **Go Ahead** stage.

The motors are then stopped for a programmed time interval by the microcontroller before the next sensor measurement cycle.

The algorithm does not maintain a complete map of the maze. Instead, it continuously reacts to the current sensor measurements, making it a relatively simple approach for demonstrating autonomous navigation using an embedded microcontroller.


# Firmware

The firmware was written in **Embedded C** for the STC89C52RC.

The project intentionally uses a low-level approach to develop a deeper understanding of the microcontroller architecture and its peripherals.

The firmware includes modules for:

* GPIO
* Timers
* Interrupts
* UART communication
* Servo control
* Ultrasonic distance measurement
* Stepper motor control
* Maze-solving logic

The code is organized into independent modules so that individual hardware components can be developed and tested before system-level integration.

---

# Engineering Skills Demonstrated

This project demonstrates practical experience across several areas relevant to embedded systems engineering.

### Embedded Firmware

* Bare-metal Embedded C
* 8051 architecture
* Register-level programming
* GPIO
* Timers
* Interrupts
* UART
* Timing-sensitive firmware
* Sensor interfacing
* Actuator control
* Modular firmware architecture

### Embedded Hardware

* Digital electronics
* Power regulation
* Power distribution
* USB-to-UART interfaces
* Sensor interfaces
* Motor interfaces
* Hardware bring-up
* Oscilloscope-based debugging
* Electrical validation

### PCB Design & Manufacturing

* Schematic capture
* PCB layout
* Component placement
* Routing
* Ground planes
* Design for manufacturing
* Gerber generation
* BOM preparation
* Pick-and-Place data
* PCB manufacturing
* SMT assembly

### Engineering Workflow

* Requirements definition
* Hardware/firmware co-design
* Prototype validation
* Hardware debugging
* Manufacturing
* System integration
* Functional testing
* Technical documentation

---

# About the Sponsorship

The PCB manufacturing and assembly for this project was supported by **JLCPCB**.

Their support made it possible to transition the project from a prototype developed during the academic design stage to a professionally manufactured PCB.

**JLCPCB** is a PCB manufacturing and PCBA service provider offering PCB fabrication, component sourcing, and assembly services.

<p align="center">
  <img src="images/sponsor.jpeg" width="700">
</p>

**Learn more about JLCPCB:**
https://jlcpcb.com

---

# Project Status

**Status: Functional Prototype**

The custom PCB has been manufactured and assembled, the main hardware interfaces have been validated, and the embedded firmware has been integrated with the robot.

Future iterations may focus on improving motion control, navigation reliability, sensor processing, and firmware architecture.

---

# Author

**Luis Pinto**
Electronics Engineering Student
Universidad Santiago de Cali — Colombia

**Focus:** Embedded Systems · Hardware · Firmware · PCB Design

---

## Project Resources

* **Source Code:** This repository
* **Schematic:** `Schematic_Maze-Solving-Robot_2026-09-14.pdf`
* **PCB Manufacturing Files:** `Gerber_...zip`
* **Bill of Materials:** `BOM_...csv`
* **Pick-and-Place Data:** `PickAndPlace_...csv`

---

<p align="center">
  <i>Designed, programmed, manufactured, assembled, and tested as an embedded systems engineering project.</i>
</p>

<p align="center">
  <b>Sponsored by JLCPCB</b>
</p>
