# 8x8x8 LED Cube: Complete Engineering Journey & Technical Breakdown

**Project Team:**
* Nguyen Duy Khoa (SE200494)
* Pham Vo Hoang Nhan (SE200778)
* Nguyen Cao Ky (SE201611)
* Ngo Tu Nha Quyen (SE201483)

---

## Introduction

An 8x8x8 LED Cube is a complex three-dimensional display matrix consisting of 512 individually addressable LEDs. By manipulating each LED in a synchronized sequence, we can render beautiful 3D animations, volumetric typography, fluid dynamics simulations, and complex geometric transformations.

This project may look very complex from the outside, but with the right method, correct measurements, and proper soldering steps, it becomes an enjoyable build. Instead of a standard step-by-step tutorial, this document serves as a comprehensive engineering log written from practical experience, covering both the physical build and the underlying software architecture.

---

## Components Required

* **512 × 5mm Diffused LEDs** (single color of our choice)
* **1 × Arduino Nano** (Arduino Uno also compatible)
* **Custom PCB** (or Zero PCB if making manually)
* **9 × 74HC595 Shift Registers** (as per circuit design)
* **9 × 16 Pin IC Base**
* **16 × NPN Transistors (2222A)** (for layer control)
* **Current Limiting Resistors - 220 OHM**
* **20-Gauge Copper Wire** & **Ribbon Cable**
* **Male & Female Header Pins**
* **Push Button Switch** & **Type-C Female Power Connector**
* **MDF / Acrylic Sheets** (for jig and enclosure)
* **Misc:** Heat-Shrink Tubes, Glue Stick / Hot Glue, 3V Coin Cell (for testing), Screws & Spacers.

---

## Part 1: How We Made It (The Engineering Process)

Building this voxel-based display required a rigorous approach. We divided the development lifecycle into three distinct phases.

### Phase 1: Structural Fabrication
The physical integrity of the cube dictates the visual quality of the animations. We began by individually testing all 512 diffused 5mm LEDs, as a single component failure post-assembly would be catastrophic.
* **The Jig Method:** We CNC-milled a precision wooden MDF jig. This ensured every LED leg was bent at an exact 90-degree angle and guaranteed uniform spacing.
* **The Matrix Assembly:** We stripped, straightened, and tensioned 20-gauge copper wire to serve as both structural scaffolding and the electrical bus. We soldered the cube layer by layer into 8 horizontal planes (common cathodes).
* **3D Integration:** Stacking the 8 layers vertically required meticulous measurement. We used 22mm spacers to solder the 64 vertical columns (common anodes), ensuring a geometrically flawless cube.

### Phase 2: Hardware Architecture
A standard microcontroller cannot drive 512 discrete channels simultaneously. We engineered a multiplexed control board to solve this IO bottleneck.
* **Shift Register Array:** We designed a circuit utilizing nine 74HC595 8-bit Shift Registers. Eight of these control the 64 vertical anode columns. The ninth acts as the sink for the 8 horizontal cathode layers, paired with a high-current array of PN2222A NPN Transistors.
* **Cable Routing:** We employed modular 10-pin ribbon cables to bridge the LED matrix to the PCB. They ensure signal integrity and allow the hardware to be easily disassembled for debugging.

### Phase 3: Firmware Architecture
The final phase involved writing the embedded C++ firmware to translate abstract 3D coordinates into physical electrical signals.
* **Coordinate Mapping:** We wrote drivers that mapped the physical X, Y, and Z axes to a multi-dimensional array in the microcontroller's memory.
* **Animation Engine:** We developed functions to draw geometric primitives (lines, boxes, spheres) and created state machines to handle complex frame-by-frame animations.

---

## Part 2: What We Learned (Technical Takeaways)

This project evolved far beyond a simple soldering task. It became an intensive masterclass in hardware and software engineering.

### 1. Advanced Low-Level C++
To render 3D animations smoothly, our code had to execute with extreme efficiency.
* We abandoned high-level API calls (like standard `digitalWrite`) because their overhead caused visible lag.
* We heavily utilized **C++ bitwise operations** (`&`, `|`, `^`, `<<`, `>>`) and direct **Port Register Manipulation** (e.g., writing directly to `PORTB`).
* **Memory Optimization:** We packed 8 boolean voxel states into a single 8-bit unsigned integer. This drastically reduced the SRAM footprint, leaving more memory available for complex animation algorithms.

### 2. Digital IC Design Principles
Working with daisy-chained 74HC595 shift registers was a practical lesson in digital logic.
* We carefully managed the Serial Data, Clock, and Latch pins, dealing with propagation delay and parasitic capacitance across PCB traces.
* We ensured our software bit-banging was synchronized perfectly to prevent flickering.

### 3. Data Structures & 3D Mapping
Mapping a physical 3D space into computer memory challenged our understanding of algorithms.
* **Double Buffering Algorithm:** We designed an efficient 3D byte-array mapping system and implemented Double Buffering to prevent the "screen tearing" effect. We draw the next frame to a hidden background buffer in memory; once calculated, we swap the pointer to the active display buffer for a seamless transition.

### 4. Hardware Timer Interrupts
Relying on a standard `loop()` with `delay()` functions was inadequate.
* We configured Hardware Timer Interrupts, setting up Timer1 to trigger an Interrupt Service Routine (ISR) at precise intervals.
* This decoupled the display refreshing logic from the animation calculation logic, ensuring the display updates flawlessly regardless of CPU load.

### 5. Persistence of Vision (POV)
Lighting all 512 LEDs at 20mA simultaneously would melt our control board.
* We solved this using **Persistence of Vision (POV)** and Multiplexing.
* Our ISR firmware rapidly scans through the Z-axis, turns on a single horizontal layer, pulses the data, and then moves to the next layer in microseconds. Refreshing all layers at >60Hz creates the illusion of a solid 3D object.

### 6. Power Distribution
On the analog side, we learned to calculate power budgets and manage instantaneous current spikes.
* We used Ohm’s Law to select the perfect current-limiting resistors and balanced brightness against the current limit of the PN2222A transistors.
* We strategically placed decoupling capacitors to filter high-frequency noise.

### 7. Algorithmic Generation
Instead of hardcoding frames, we generated animations dynamically.
* We utilized sine and cosine functions to create fluid wave patterns and implemented basic physics equations (gravity and velocity) to simulate realistic rain and bouncing objects.
* We learned how to translate continuous math into a discrete 8x8x8 voxel grid.

---

## Acknowledgements & References

We would like to acknowledge the following individuals and resources. Their work provided crucial foundational knowledge for our project:
* **How to Make an 8x8x8 LED Cube with Arduino at home:** Easiest DIY Method & Full Step-by-Step Tutorial.
* **Efficient design of 8×8×8 LED Cube with Low Power consumption using Arduino UNO:** N. Sri Sai, B. Naga Subrahmanyam, K. Yeshwanth Sai, A. Vara Durga Siva Sai, K. Pavan Kumar, S. Sai Harsha.
