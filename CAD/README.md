# CAD — Piezobot mechanical design files

Mechanical CAD and 3D-printing files for the Piezobot robot.

All files in this folder are released under the
**Creative Commons Attribution-ShareAlike 4.0 International (CC BY-SA 4.0)** licence.
See the repository root [`LICENSE`](../LICENSE) for the full text.

---

## File inventory

```
CAD/
├── Piezobot_Assembly.f3z               Complete robot assembly (Fusion 360 archive)
├── Piezobot_Assembly.step              Complete robot assembly (neutral STEP)
├── CNC/
│   ├── aluminium_base.f3d              CNC-machined aluminium base (Fusion 360 part)
│   └── aluminium_base.step             CNC-machined aluminium base (neutral STEP)
└── STLs(3D Print)/
    ├── shell.stl                       3D-printed shell
    └── LCD_retaining_ring_0.99in.stl   3D-printed retaining ring for the 0.99-inch LCD
```

| File | Format | Description |
|---|---|---|
| `Piezobot_Assembly.f3z` | Fusion 360 archive | Complete robot assembly — every part is in its assembled position; open this file first if you use Autodesk Fusion 360 |
| `Piezobot_Assembly.step` | STEP assembly | The same complete assembly in neutral STEP format, for any other CAD software |
| `CNC/aluminium_base.f3d` | Fusion 360 part | CNC-machined aluminium base |
| `CNC/aluminium_base.step` | STEP part | The same part in neutral STEP format |
| `STLs(3D Print)/shell.stl` | STL part | 3D-printed shell |
| `STLs(3D Print)/LCD_retaining_ring_0.99in.stl` | STL part | Retaining ring for the 0.99-inch LCD |


## How to use these files

- `Piezobot_Assembly.f3z` and `CNC/aluminium_base.f3d` open directly in Autodesk Fusion 360; the `.step` files carry the same geometry in a neutral format that any CAD software can import.
- `Piezobot_Assembly` contains the whole robot; you can locate a part in the assembly to see its assembled state and position.
- The two `.stl` files can be sliced and 3D printed directly.
- The assembly steps of the mechanical parts are described step by step in the accompanying HardwareX article: including the base and the stick–slip mechanism, the fixing and wiring of the PZT board, and the assembly of the screen, retaining ring and shell.

## Fabrication

| File | Process |
|---|---|
| `CNC/aluminium_base.step` | CNC machining (6061 aluminium) |
| `STLs(3D Print)/shell.stl` | 3D printing (PLA material, 0.2 mm nozzle) |
| `STLs(3D Print)/LCD_retaining_ring_0.99in.stl` | 3D printing (same process as above) |

More detailed printing and machining parameters (material, layer height, infill, etc.) are given in the accompanying article.
