# P3 MP3 Player — Architecture

## Outline
Battery-powered MP3 player modeled on the Sony Walkman NW-S203F (grown body ~110×24×20mm). USB-C charging, microSD storage, 3.5mm headphone out, OLED display, jog dial + buttons.

## Blocks
- MCU — decode, I2S, USB, UI
- Charger — USB 5V → LiPo
- Battery — LiPo
- Buck-boost — 3.45V digital rail
- LDO + ferrite — 3.3V analog rail
- LDO (2nd) — 3.3V digital rail
- USB — USB-C + ESD
- DAC + headphone amp — TAD5112 (I2C/SPI, integrated HP driver)
- Storage — microSD (SPI + FatFs)
- Display — SSD1306 OLED (I2C)
- Audio clock — 11.2896MHz crystal (I2S external clock)
- Input — TBD (jog dial, buttons)

Part list: `docs/components.md`

## Data
microSD → MCU (SPI + FatFs, Helix decode) → I2S (3-wire: BCK/LRCK/DATA) + I2C control → TAD5112 → 3.5mm jack → headphones

## Power
USB 5V → Charger → LiPo → Buck-boost (3.45V) → LDO (3.3V) → ferrite → audio

Three-rail power tree:
- **3.45V digital** (TPS63050 buck-boost): MCU, microSD, OLED VBAT, PG/CHG pull-ups
- **3.3V analog** (LP5907 #1 + ferrite): TAD5112 AVDD
- **3.3V digital** (LP5907 #2, DGND-referenced): SSD1306 VDD, TAD5112 IOVDD, I2C pull-ups

The buck-boost stays at 3.45V because the LP5907 needs ~150mV dropout headroom to regulate 3.3V. Digital loads run directly off 3.45V (efficient, no LDO loss); LDOs serve only loads that cannot take 3.45V (SSD1306 3.3V max, TAD5112 IOVDD 3.3V).

## Clocking
- SYSCLK: HSI 144MHz (part has no PLL; only dividers downstream)
- I2S: 11.2896MHz fundamental crystal feeds the external clock input, native 44.1kHz
- TAD5112: on-chip PLL + auto sample-rate detection, I2S slave

## Boundaries
- PGND → DGND at buck-boost, DGND → AGND at LDO
- Display GND → DGND (keeps SSD1306 charge-pump return current off AGND)

