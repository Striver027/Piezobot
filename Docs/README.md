# Documentation — Piezobot

Supporting documentation for building, operating and reproducing the Piezobot robot.

Everything in this folder is released under the
**Creative Commons Attribution-ShareAlike 4.0 International (CC BY-SA 4.0)** licence.
See the repository root [`LICENSE`](../LICENSE) for the full text.

---

## Bill of materials

The electronics are itemised board by board — one editable spreadsheet per board:

| File | Board |
|---|---|
| `BOM_PZT_board.xlsx` | PZT board |
| `BOM_power_board.xlsx` | power board |
| `BOM_controller_board.xlsx` | controller board |
| `BOM_function_board.xlsx` | function board |
| `BOM_LCD_board.xlsx` | LCD board |
| `BOM_DAP_board.xlsx` | DAP board |
| `BOM_BAT_board.xlsx` | BAT board |

Every file uses exactly the same columns as the *Bill of materials summary* in the
article:

```
Designator, Component, Number of units, Cost per unit - CNY,
Total cost - CNY, Source of materials, Material type
```

The first row of each file is the bare-board fabrication cost (JLCPCB, 21.6 CNY per
board). The `Source of materials` cells are hyperlinks to *Taobao* or *LCSC*. The total
of each file is the cost of that board.

The parts other than the PCBs, together with the board-level totals, are listed in the
*Bill of materials summary* of the article.
