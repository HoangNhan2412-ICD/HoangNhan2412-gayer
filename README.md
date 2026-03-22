# 8x8x8 LED Cube Build Guide

**Project Team:**
* Nguyen Duy Khoa (SE200494)
* Pham Vo Hoang Nhan (SE200778)
* Nguyen Cao Ky (SE201611)
* Ngo Tu Nha Quyen (SE201483)

---

## Introduction
An 8x8x8 LED Cube is a three-dimensional structure made using 512 LEDs arranged in the form of a perfect cube. Each LED can be controlled individually using an Arduino, allowing us to create beautiful 3D animations, flowing patterns, waves, rain effects, and text-like movements.

This project may look very complex from the outside, but if we follow the right method, correct measurements, and proper soldering steps, it becomes much easier and enjoyable. This tutorial is written from practical experience, not only with theory.

We will complete this project in only two main stages:
1. Building the LED cube structure with perfect size and alignment.
2. Building the circuit board and making all electronic connections.

We will go step by step, without skipping anything, so let's start with the most important part—the cube itself.

---

## Components Required
- **512 × 5mm Diffused LEDs** (single color of our choice)
- **Arduino Nano** (Arduino Uno also compatible)
- **Custom PCB** (or Zero PCB if making manually)
- **9 × 74HC595 Shift Registers** (as per circuit design)
- **9 × 16 Pin IC Base**
- **16 × NPN Transistors (2222A)** (for layer control)
- **Current Limiting Resistors - 220 OHM**
- **20-Gauge Copper Wire**
- **Ribbon Cable**
- **Male & Female Header Pins**
- **Push Button Switch**
- **Type-C Female Power Connector**
- **USB Cable** (Type-B or Type-C as used)
- **MDF / Acrylic Sheets** (for jig and enclosure)
- **Heat-Shrink Tubes**
- **Glue Stick / Hot Glue**
- **3V Coin Cell** (for LED testing)
- **Screws & Spacers**

---
# 8x8x8 LED Cube: 
## Complete Engineering Journey & Technical Breakdown

---

## Introduction

An 8x8x8 LED Cube is a complex three-dimensional display matrix.

It consists of 512 individually addressable LEDs.

By manipulating each LED in a synchronized sequence, we can render:
* 3D animations
* Volumetric typography
* Fluid dynamics simulations
* Complex geometric transformations

Instead of a standard step-by-step tutorial, this document serves as a comprehensive engineering log.

It outlines our methodology:
**How We Made It**

And provides an in-depth technical analysis:
**What We Learned**

---

## Part 1: How We Made It 
*(The Engineering Process)*

Building this voxel-based display required a rigorous approach.

We divided the development lifecycle into three distinct phases.

### Phase 1: Structural Fabrication
The physical integrity of the cube dictates the visual quality of the animations.

We began by individually testing all 512 diffused 5mm LEDs. 

A single component failure post-assembly would be catastrophic for the matrix.

**The Jig Method:**
* We CNC-milled a precision wooden MDF jig.
* This ensured every LED leg was bent at an exact 90-degree angle.
* It also guaranteed uniform spacing.

**The Matrix Assembly:**
* We stripped, straightened, and tensioned 20-gauge copper wire.
* This wire serves as both structural scaffolding and the electrical bus.
* We soldered the cube layer by layer into 8 horizontal planes (common cathodes).

**3D Integration:**
* Stacking the 8 layers vertically required meticulous measurement.
* We used 22mm spacers to solder the 64 vertical columns (common anodes).
* This ensured the final structure was a geometrically flawless cube.

### Phase 2: Hardware Architecture
A standard microcontroller cannot drive 512 discrete channels simultaneously. 

We engineered a multiplexed control board to solve this IO bottleneck.

**Shift Register Array:**
* We designed a circuit utilizing nine 74HC595 8-bit Shift Registers.
* Eight of these control the 64 vertical anode columns.
* The ninth acts as the sink for the 8 horizontal cathode layers.
* This ninth register is paired with a high-current array of PN2222A NPN Transistors.

**Cable Routing:**
* We employed modular 10-pin ribbon cables.
* These bridge the LED matrix to the PCB.
* They ensure signal integrity.
* They allow the hardware to be easily disassembled for debugging.

### Phase 3: Firmware Architecture
The final phase involved writing the embedded C++ firmware.

This translates abstract 3D coordinates into physical electrical signals.

**Coordinate Mapping:**
* We wrote drivers that mapped the physical X, Y, and Z axes.
* These map to a multi-dimensional array in the microcontroller's memory.

**Animation Engine:**
* We developed functions to draw geometric primitives (lines, boxes, spheres).
* We created state machines to handle complex frame-by-frame animations.

---

## Part 2: What We Learned 
*(Technical Takeaways)*

This project evolved far beyond a simple soldering task. 

It became an intensive masterclass in hardware and software engineering.

### 1. Advanced Low-Level C++ 
To render 3D animations smoothly, our code had to execute with extreme efficiency. 

* We abandoned high-level API calls (like standard `digitalWrite`).
* Their overhead caused visible lag.
* We heavily utilized C++ bitwise operations (`&`, `|`, `^`, `<<`, `>>`).
* We used direct Port Register Manipulation (e.g., writing directly to `PORTB`).

**Memory Optimization:**
* We packed 8 boolean voxel states into a single 8-bit unsigned integer.
* This drastically reduced the SRAM footprint.
* It left more memory available for complex animation algorithms.

### 2. Digital IC Design Principles
Working with daisy-chained 74HC595 shift registers was a practical lesson in digital logic. 

* We carefully managed the Serial Data, Clock, and Latch pins.
* We learned about propagation delay.
* We learned how parasitic capacitance across PCB traces limits clock frequency.
* We ensured our software bit-banging was synchronized perfectly to prevent flickering.

### 3. Data Structures & 3D Mapping
Mapping a physical 3D space into computer memory challenged our understanding of algorithms.

**Double Buffering Algorithm:**
* We designed an efficient 3D byte-array mapping system.
* We implemented Double Buffering to prevent the "screen tearing" effect.
* We draw the next frame to a hidden background buffer in memory.
* Once calculated, we swap the pointer to the active display buffer for a seamless transition.

### 4. Hardware Timer Interrupts
Relying on a standard `loop()` with `delay()` functions was inadequate.

* We configured Hardware Timer Interrupts.
* We set up Timer1 to trigger an Interrupt Service Routine (ISR) at precise intervals.
* This decoupled the display refreshing logic from the animation calculation logic.
* It ensures the display updates flawlessly regardless of CPU load.

### 5. Persistence of Vision (POV)
Lighting all 512 LEDs at 20mA simultaneously would melt our control board. 

We solved this using Persistence of Vision (POV) and Multiplexing.

* Our ISR firmware rapidly scans through the Z-axis.
* It turns on a single horizontal layer and pulses the data.
* It then turns off and moves to the next layer in microseconds.
* Refreshing all layers at >60Hz creates the illusion of a solid 3D object.

### 6. Power Distribution
On the analog side, we learned to calculate power budgets.

* We managed instantaneous current spikes.
* We used Ohm’s Law to select the perfect current-limiting resistors.
* We balanced brightness against the current limit of the PN2222A transistors.
* We strategically placed decoupling capacitors to filter high-frequency noise.

### 7. Algorithmic Generation
Instead of hardcoding frames, we generated animations dynamically.

* We utilized sine and cosine functions to create fluid wave patterns.
* We implemented basic physics equations (gravity and velocity).
* This allowed us to simulate realistic rain and bouncing objects.
* We learned how to translate continuous math into a discrete 8x8x8 voxel grid.
## Acknowledgements & References

We would like to acknowledge the following individuals and resources.

Their work provided crucial foundational knowledge for our project:

* **Easiest DIY Method & Full Step-by-Step Tutorial:** How to Make an 8x8x8 LED Cube with Arduino at home.
* **N. Sri Sai, B. Naga Subrahmanyam, K. Yeshwanth Sai, A. Vara Durga Siva Sai, K. Pavan Kumar, S. Sai Harsha:** Efficient design of 8×8×8 LED Cube with Low Power consumption using Arduino
