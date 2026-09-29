# 🤖 Maze-Solving Robot V1.0

![Robot In Action](https://via.placeholder.com/800x400.png?text=Robot+Operation+GIF) <!-- REPLACE WITH YOUR GIF: ![Demo](docs/images/robot-demo.gif) -->

Welcome to the **Maze-Solving Robot V1.0** repository. This project covers the design, development, and implementation of an autonomous mobile robot engineered to solve mazes using a two-phase navigation approach and an efficient path-optimization algorithm.

---

## 📸 Visual Gallery & Designs

### 📐 2D Design (Schematics / Layout)
![2D Design](https://via.placeholder.com/600x350.png?text=2D+Design+Image) <!-- REPLACE: ![2D Design](docs/images/design-2d.png) -->

*Schematic circuit diagram and dimensional architecture layout.*

### 🧊 3D Model (CAD)
![3D Model](https://via.placeholder.com/600x350.png?text=3D+Design+Image) <!-- REPLACE: ![3D Design](docs/images/design-3d.png) -->

*3D CAD model detailing the chassis structure, sensor placement, and component packaging.*

### 🛠️ Final Assembly
![Final Result](https://via.placeholder.com/600x350.png?text=Final+Robot+Result) <!-- REPLACE: ![Final Result](docs/images/final-result.jpg) -->

*Physical build of the fully assembled robot ready for autonomous navigation.*

---

## 🧠 Navigation Algorithm & Path Optimization

The core control system implements a two-phase navigation strategy combining the **Wall Follower (Hand Rule)** method with an automated **Path Reduction/Optimization** algorithm.

### 1. Exploration Phase (Initial Mapping)
During the first run, the robot explores the unknown maze environment. It systematically navigates intersections using the **Left-Hand Rule** (or Right-Hand Rule depending on configuration). At every decision point (turn or dead-end), the system logs the selected action into memory as a character token:
* `L` – Turn Left
* `R` – Turn Right
* `S` – Go Straight
* `B` – Back (U-turn at a dead-end)

### 2. Path Reduction Algorithm
Dead-ends introduce unnecessary U-turn maneuvers (`B`). The algorithm processes sequences containing `B` tokens and iteratively replaces them with their optimal equivalent action using String Replacement Algebra.

The reduction rules applied are:

* `L` + `B` + `L` $\rightarrow$ **`S`**
* `L` + `B` + `S` $\rightarrow$ **`R`**
* `R` + `B` + `L` $\rightarrow$ **`B`**
* `S` + `B` + `L` $\rightarrow$ **`R`**
* `S` + `B` + `S` $\rightarrow$ **`B`**
* `L` + `B` + `R` $\rightarrow$ **`B`**

### 3. Fast Run Phase
Once the robot reaches the destination, the recorded decision array is completely streamlined into the **shortest possible path**. On the second run, the robot executes this optimized sequence directly, eliminating unnecessary sensor polling and wrong turns to complete the maze in minimal time.

---

## ⚙️ Technical Specifications & Hardware

* **Main Controller:** [Insert Microcontroller, e.g., Arduino Nano / ESP32 / STM32]
* **Distance Sensors:** [Insert Sensors, e.g., Ultrasonic HC-SR04 / Sharp IR GP2Y0A21YK0F]
* **Motor Driver:** [Insert Driver, e.g., L298N / TB6612FNG]
* **Actuators:** DC Gear Motors (N20) with quadrature encoders (if applicable).
* **Power Supply:** LiPo Battery (2S/3S).

---

## 📂 Repository Structure

```text
Maze-Solving-Robot-V1.0/
├── docs/                  # Documentation and media assets
│   └── images/            # 2D/3D designs, photo gallery, and GIFs
├── firmware/              # Source code (C/C++ / Arduino)
├── hardware/              # Schematics, PCB designs, and 3D CAD/STL files
└── README.md              # Project documentation
