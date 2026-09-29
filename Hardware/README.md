# Hardware — Piezobot hardware design files

Editable PCB design files for the Piezobot robot

All files in this folder are released under the
**Creative Commons Attribution-ShareAlike 4.0 International (CC BY-SA 4.0)** licence.
See the repository root [`LICENSE`](../LICENSE) for the full text.

---

## File inventory

### Stack order (bottom → top)

| # | Board |
|---|---|
| 1 (bottom) | PZT board |
| 2 | Power board |
| 3 | Controller board |
| 4 (top) | Function board |

The **LCD board** sits above the stack and is the topmost part of the whole robot; its FPC
connects to the controller board.
The **DAP board** and the **BAT board** are not part of the stack and are used only for some
auxiliary functions. In the panels of the DAP board and the BAT board, the larger part is the
DAPLink-end adapter. The small board in the DAP board is an adapter for connecting to the
robot end, and the small board in the BAT board is the battery adapter that powers the robot.

### Project files (open these first)

| File | Format | Purpose |
|---|---|---|
| `Piezobot.PrjPcb` | Altium project | **Master project** — open it with Altium Designer to browse all the schematics and PCB layouts below |
| `Piezobot.OutJob` | Altium output job | Fabrication and documentation output settings for the project |

### PZT board (piezoelectric stack carrier and wiring)

Stack position: bottom (1st from the bottom).

| File | Format | Purpose |
|---|---|---|
| `PZT_board.SchDoc` | Altium schematic | Schematic |
| `PZT_board.PcbDoc` | Altium PCB | PCB layout |
| `PZT_board.pdf` | PDF | Schematic (for viewing without Altium) |
| `PZT_board.zip` | Gerber + drill | Ready for PCB fabrication |

### Power board (boost converter + power operational amplifier)

Stack position: 2nd from the bottom.

| File | Format | Purpose |
|---|---|---|
| `power_board.SchDoc` | Altium schematic | Schematic |
| `power_board.PcbDoc` | Altium PCB | PCB layout |
| `power_board.pdf` | PDF | Schematic (for viewing without Altium) |
| `power_board.zip` | Gerber + drill | Ready for PCB fabrication |

### Controller board (STM32G431 main controller)

Stack position: 3rd from the bottom; the FPC of the LCD board connects to this board.

| File | Format | Purpose |
|---|---|---|
| `controller_board.SchDoc` | Altium schematic | Schematic |
| `controller_board.PcbDoc` | Altium PCB | PCB layout |
| `controller_board.pdf` | PDF | Schematic (for viewing without Altium) |
| `controller_board.zip` | Gerber + drill | Ready for PCB fabrication |

### Function board (IMU + 433 MHz wireless module)

Stack position: top (4th from the bottom).

| File | Format | Purpose |
|---|---|---|
| `function_board.SchDoc` | Altium schematic | Schematic |
| `function_board.PcbDoc` | Altium PCB | PCB layout |
| `function_board.pdf` | PDF | Schematic (for viewing without Altium) |
| `function_board.zip` | Gerber + drill | Ready for PCB fabrication |

### LCD board (screen base board, topmost part of the whole robot)

The 0.99-inch LCD screen is taped onto this board, and the screen ribbon cable is soldered to
this board. This board serves as the base board of the screen and adapts the screen signal
cable to an FPC, which is connected to the controller board through the FPC. It sits above the
stack and is the topmost part of the whole robot.

| File | Format | Purpose |
|---|---|---|
| `LCD_board.SchDoc` | Altium schematic | Schematic |
| `LCD_board.PcbDoc` | Altium PCB | PCB layout |
| `LCD_board.pdf` | PDF | Schematic (for viewing without Altium) |
| `LCD_board.zip` | Gerber + drill | Ready for PCB fabrication |

### DAP board (DAPLink adapter, panelized)

A simple adapter board: different types of connectors are adapted through this circuit board.
The layout of this board is **panelized**: it can adapt the 2.54 mm interface of PowerLink to a
0.8 mm BTB interface. The large board is used to first convert 2.54 mm into 1.27 mm pin
headers, and the small board is used to convert the 1.27 mm pin headers into a 0.8 mm BTB
interface.

| File | Format | Purpose |
|---|---|---|
| `DAP_board.SchDoc` | Altium schematic | Schematic |
| `DAP_board.PcbDoc` | Altium PCB | Panelized layout |
| `DAP_board.pdf` | PDF | Schematic (for viewing without Altium) |
| `DAP_board.zip` | Gerber + drill | Gerber and drill files of the panelized version |

### BAT board (battery adapter, panelized)

Battery adapter board. It has exactly the same structure and layout as the DAP board, but the
lead connections inside the board have been thickened and copper-poured, so the **DAP board and
the BAT board are not interchangeable**: only their large boards are the same — the large board
in the BAT panel can still be connected to a DAPLink programmer, while the small board is used
to retrofit a lithium-battery connector to power the robot.

| File | Format | Purpose |
|---|---|---|
| `BAT_board.SchDoc` | Altium schematic | Schematic |
| `BAT_board.PcbDoc` | Altium PCB | Panelized layout |
| `BAT_board.pdf` | PDF | Schematic (for viewing without Altium) |
| `BAT_board.zip` | Gerber + drill | Gerber and drill files of the panelized version |

---

## PCB fabrication parameters

| Board | Layers | Board thickness |
|---|---|---|
| PZT board | 2 | 1.0 mm |
| Power board | 2 | 1.6 mm |
| Controller board | 4 | 1.6 mm |
| Function board | 2 | 1.2 mm |
| LCD board | 2 | 1.2 mm |
| DAP board | 2 | 1.6 mm |
| BAT board | 2 | 1.6 mm |

Except for the controller board, which is a four-layer board (laminate order from top to
bottom: top layer / mid-layer 1 / mid-layer 2 / bottom layer), all the other boards are
two-layer boards.

The copper weight follows the manufacturer's (JLCPCB) default process: **1 oz on the outer
layers and 0.5 oz on the inner layers** (the inner-layer value applies to the four-layer
controller board).

---

## How to open these files

- **To edit the electronics**: use **Altium Designer** (the `.PrjPcb` project opens all the
  schematics and layouts together). You can also view them in a browser with the free
  **Altium 365 Viewer**.
- **To view without Altium**: use the `.pdf` file of each board (schematic).
- **To fabricate**: send the contents of the corresponding `.zip` (Gerber + drill) to any PCB
  manufacturer.
