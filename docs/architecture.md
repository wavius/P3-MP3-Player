# P3 MP3 Player — Architecture

## Outline
Battery-powered MP3 player modeled on the Sony Walkman NW-S203F (grown body ~110×24×20mm). USB-C charging, microSD storage, 3.5mm headphone out, OLED display, jog dial + buttons.

## Blocks
- MCU — decode, I2S, USB, UI
- Charger — USB 5V → LiPo
- Battery — LiPo
- Buck-boost — 3.45V digital rail
- LDO + ferrite — 3.3V analog rail
- USB — USB-C + ESD
- DAC — TBD
- Headphone amp — TBD
- Storage — TBD (microSD, SPI)
- Display — TBD (OLED, I2C)
- Input — TBD (jog dial, buttons)

Part list: `docs/components.md`

## Data
Storage → MCU (decode) → I2S → DAC → amp → 3.5mm jack → headphones

## Power
USB 5V → Charger → LiPo → Buck-boost (3.45V) → LDO (3.3V) → ferrite → audio

## Boundaries
- PGND → DGND at buck-boost, DGND → AGND at LDO

