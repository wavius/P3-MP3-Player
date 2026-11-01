# P3 MP3 Player — Architecture

## Outline
Battery-powered MP3 player modeled on the Sony Walkman NW-S203F (grown body ~110×24×20mm). USB-C charging, microSD storage, 3.5mm headphone out, OLED display, six switches + a three-way switch.

## Blocks
- MCU — STM32C552RET6 (decode, I2S, USB, UI); STM32C562 alternative (exact ordering code and compatibility to confirm)
- Charger — USB 5V → LiPo
- Battery — LiPo
- Buck-boost — 3.3V digital rail
- LDO — 3.0V analog rail
- USB — USB-C + ESD
- DAC + headphone amp — MAX9850 (I2S1 + I2C1, integrated HP driver)
- Storage — microSD (SPI2 + FatFs)
- Display — SSD1306 OLED (I2C2)
- Audio clock — 22.5792MHz MEMS oscillator, DSC6001 (shared MCU AUDIOCLK + MAX9850 MCLK)
- Input — six switches (vol+, vol-, play, home, clockwise, counterclockwise) plus one three-way switch to mimic the original dial

Part list: `docs/components.md`

## Data
microSD → MCU (SPI2 + FatFs, Helix decode) → I2S1 (3-wire: BCLK/FSYNC/DIN) + I2C1 control → MAX9850 → 3.5mm jack → headphones. Display uses I2C2; MAX9850 control uses I2C1 (separate buses).

## Power
USB 5V → Charger → LiPo → Buck-boost (3.3V digital) → LDO (3.0V) → audio analog supplies

Two-rail power tree:
- **3.3V digital** (TPS63050 buck-boost, directly): MCU, microSD, SSD1306 VDD/VBAT, MAX9850 DVDD, I2C and PG/CHG pull-ups
- **3.0V analog** (TPS7A2030PDQNR): MAX9850 AVDD and PVDD

The digital LDO is removed. The analog LDO has 0.3V nominal input/output headroom. The analog LDO is TPS7A2030PDQNR (3.0V, 300mA, DQN X2SON); load/dropout and thermal margin require schematic confirmation.

## Clocking
- SYSCLK: HSI 144MHz (part has no PLL; only dividers downstream)
- I2S: 22.5792MHz MEMS oscillator (DSC6001, OE tied high) feeds AUDIOCLK, selected as SPI1 kernel clock; native 44.1kHz family
- MAX9850: I2S slave with MCLK and internal digital PLL; MCLK is driven by the same 22.5792MHz DSC6001 oscillator that feeds MCU AUDIOCLK. Register configuration requires firmware confirmation.

## Boundaries
- PGND → DGND at buck-boost, DGND → AGND at LDO
- Display GND → DGND (keeps SSD1306 charge-pump return current off AGND)

## Audio replacement and verification
- MAX9850 integrates the stereo DAC, DirectDrive headphone amplifier, and I2C headphone volume/mute control. No separate DAC or headphone amplifier is required.
- Intended buses remain I2S1 (BCLK/LRCLK/SDIN) and I2C1. Existing MCU configuration may still contain TAD5112-era names/pins; this architecture update does not change firmware or schematics.
- Manufacturer datasheets checked: [MAX9850](https://www.analog.com/media/en/technical-documentation/data-sheets/max9850.pdf), [TPS7A20](https://www.ti.com/lit/ds/symlink/tps7a20.pdf), [TPS63050](https://www.ti.com/lit/ds/symlink/tps63050.pdf). MAX9850 AVDD/PVDD and DVDD support 1.8–3.6V; AVDD and PVDD must use the same voltage.

## Inputs
- Six switches: vol+, vol-, play, home, clockwise, and counterclockwise. Clockwise/counterclockwise are the two switch actions for the rotary control.
- One additional three-way switch mimics the original dial; position functions are not yet specified.
- Input signals connect to MCU GPIO; exact switch parts, contact arrangement, and GPIO assignments remain unselected.
