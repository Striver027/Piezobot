# Firmware

## Directory structure

```
Piezobot/                  STM32CubeMX project
├── Piezobot.ioc           peripheral / clock configuration (CubeMX)
├── .mxproject             CubeMX bookkeeping for re-generation
├── Core/
│   ├── Src/main.c         start-up, control loop
│   ├── Src/int.c          HAL interrupt callbacks (TIM7, USART1/3, DAC)
│   └── Inc/int.h
├── Hardwares/
│   ├── HC_12/             HC-12 (433 MHz) driver, AT-command helpers
│   └── LCD/               0.99-inch display driver
├── Software/
│   ├── Inc|Src/wave.c     sawtooth table, drive-buffer generation
│   ├── Inc|Src/comm.c     communication handling
│   └── Inc|Src/protocol.c frame parsing (robot commands)
└── MDK-ARM/               Keil MDK project + start-up file
```

## Serial link and protocol

| Port | Use | Setting |
|---|---|---|
| USART3 | HC-12 radio module | 9600 baud, 8N1 |
| USART1 | debug output | 115200 baud, 8N1 |

Frame layout (13-byte payload):

```
0xAA | LEN | DATA[LEN] | XOR | 0x55
```

| Field | Type | Note |
|---|---|---|
| ID | uint8 | robot address, 1…50 |
| speed | float32 | target speed, 0…1 |
| angle | float32 | target heading, −π/2…π/2 |
| voltage | float32 | not used yet |

## LCD

`Hardwares/LCD` is a third-party ST7735 driver (comments in Chinese, no licence
stated in the sources); the application only calls `LCD_Init()`, `LCD_Fill()` and
`LCD_ShowFloatNum1()`.

## Licence

The firmware is released together with the other Piezobot design files under
**CC BY-SA 4.0** (see the repository root README).
