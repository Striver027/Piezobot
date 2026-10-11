# Piezobot

**A desktop-scale, low-cost stick–slip piezoelectric robot for validating swarm
algorithms that require fine relative positioning.**

## Overview

Piezobot is a small mobile robot whose motion is produced by a **stick–slip
(friction–inertia) mechanism**: two piezoelectric stacks drive it across a flat
ferromagnetic surface, while N52 magnets simultaneously provide the preload force and the
friction surface. Driving the stacks with a sawtooth waveform generates a small net
displacement on every cycle, which accumulates into centimetre-scale travel. Turning is
obtained by **reducing (or switching off) the drive signal of one of the two channels**.


## Repository structure

```
Piezobot/
├── README.md                 This file
├── LICENSE                   CC BY-SA 4.0
├── Hardware/                 Editable PCB source projects, PDFs and Gerber files
│   └── README.md             File-by-file inventory of the hardware folder
├── CAD/                      Mechanical CAD: Fusion 360 sources and neutral STEP files
│   └── README.md             Description of the CAD files
├── Docs/                     Documentation and the editable bill of materials
│   ├── README.md             Index of the documentation
│   └── BOM_<board>.xlsx      Editable bill of materials, one file per board
└── firmware/                 STM32 firmware for the controller board
    ├── README.md             Directory structure, protocol and build notes
    └── Piezobot/             STM32CubeMX project + Keil MDK-ARM project
```


⚠️ **Safety:** the board generates up to 30 V and the magnets are strong N52 magnets —
take care with the boost converter output and avoid pinching fingers between the magnets
and the steel plate. Instant adhesive is used during assembly.


## Installation

**(a) Software and toolchain (build and flash the firmware)**

1. Install STM32CubeMX if you need to change the peripheral or clock configuration;
2. Install **Keil MDK-ARM** and the **STM32G4xx_DFP** device pack;
3. Open `firmware/Piezobot/MDK-ARM/Piezobot.uvprojx` and *Rebuild* (the first build is a
   full build);
4. Flash the firmware over SWD with a DAPLink probe.


**(b) Assembling the robot**

1. Four boards are stacked, from bottom to top: **PZT → power → controller → function**;
   they share a common power and signal interface;
2. The LCD board sits above the stack, at the very top of the robot: the display is taped
   onto it and its ribbon cable is soldered to it, and it connects to the controller board
   through an FPC;
3. The DAP and BAT boards are not part of the stack: the former is used to flash the
   firmware, the latter to adapt the battery that powers the robot;
4. The magnet orientation, the glue points and the contact-resistance check between the
   brass screw and the base are described in the build instructions of the article.

## Materials not included in this repository

This repository contains the design files only; the items below have to be obtained
separately (prices, suppliers and purchase links are given in the article and in
`Docs/BOM_<board>.xlsx`):

| Item | Detail |
|---|---|
| PCBs | Fabricate from the Gerber/drill archives in [`Hardware/`](Hardware); the electronic components are itemised board by board in `Docs/BOM_<board>.xlsx` |
| Drive parts | Piezoelectric stacks, NdFeB magnets |
| Structural parts | Aluminium base (CNC), shell, LCD retaining ring (3D printed), brass cap screws, brass ball plungers |
| Wiring and consumables | FPC, instant adhesive, magnetic pole indicator card |
| Power | Li-ion cell and charger |
| Tools and equipment | DAPLink probe, soldering station / hot air, multimeter, 3D printer, CNC machining service |
| Working surface | Flat ferromagnetic plate |
| Software | Altium Designer, Fusion 360, Keil MDK-ARM |

## Licence

All design files in this repository are released under the
**[Creative Commons Attribution-ShareAlike 4.0 International (CC BY-SA 4.0)](LICENSE)**
licence: you are free to use, modify and redistribute them, provided that you give
appropriate credit and license any derivative work under the same terms.
