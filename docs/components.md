# P3 MP3 Player — Components

| Block | Part | Status |
|---|---|---|
| MCU | STM32C552RET6 (LQFP64, 512KB flash, 128KB RAM); STM32C562 alternative | ✓ |
| Battery | 702050 LiPo, ~650mAh, JST-PH 2.0 | ✓ |
| Charger | BQ24040 (ISET2=500mA, ~300mA) | ✓ |
| Buck-boost | TPS63050 @ 3.3V | ✓ |
| LDO (analog 3.0V) | TPS7A2030PDQNR (3.0V, 300mA, 4-pin X2SON) | ✓ |
| USB ESD | USBLC6-2 | ✓ |
| DAC + headphone amp | MAX9850 (28-pin TQFN, integrated DirectDrive HP amp, I2S + I2C) | ✓ |
| Storage | microSD socket (10-pos push-push w/ CD, SPI + FatFs) | ✓ |
| Display | SSD1306B OLED (I2C) | ✓ |
| Audio clock | DSC6001JI2B-022.5792T (22.5792MHz MEMS XO, CMOS, OE tied high) | ✓ |
| Input | Six switches: vol+, vol-, play, home, clockwise, counterclockwise; plus one three-way switch (part numbers TBD) | ✗ |

✓ = chosen, ✗ = not yet selected

## Decisions

- **MCU alternative**: STM32C562 is an alternative to the selected STM32C552RET6. Exact C562 ordering code, package/pin compatibility, and firmware configuration remain to be confirmed; it is not yet verified as a drop-in replacement. Manufacturer reference: [STM32C562 datasheet](https://www.st.com/resource/en/datasheet/stm32c562ce.pdf).

- **Inputs**: six switches provide vol+, vol-, play, home, clockwise, and counterclockwise; the last two are the rotary control actions. An additional three-way switch mimics the original dial. Position functions, switch parts/contact arrangement, and MCU GPIO assignments are not yet specified.

- **Audio clock / SYSCLK**: this MCU has no PLL (internal HSI is natively 144MHz; only dividers downstream). SYSCLK runs from HSI 144MHz. A 22.5792MHz MEMS oscillator (DSC6001, 512×44.1kHz) feeds both the MAX9850 MCLK input and the MCU SPI1/I2S kernel clock via AUDIOCLK for audio-class accuracy, native 44.1kHz family (48kHz family not exact). OE tied high = always enabled; the OE option can't power down the core, and the standby variant (DSC6011) is not stocked at this frequency. No LSE (no RTC).
- **Power tree (two rails)**:
  - 3.3V digital directly from TPS63050: MCU, microSD, SSD1306 VDD/VBAT, MAX9850 DVDD, I2C and PG/CHG pull-ups.
  - 3.0V analog from TPS7A2030PDQNR: MAX9850 AVDD/PVDD.
  - Digital LDO removed. Analog regulator is TPS7A2030PDQNR, as specified. Nominal headroom is 0.3V; load/dropout and thermal margin require schematic confirmation.
- **Audio**: MAX9850 replaces the prior DAC/headphone driver block and integrates both functions. I2S1 supplies BCLK/LRCLK/SDIN; I2C1 controls configuration, headphone volume, and mute. AVDD/PVDD use 3.0V analog; DVDD uses 3.3V digital. The manufacturer specifies 1.8–3.6V for both supply domains and requires AVDD = PVDD.
- **Volume**: MAX9850 I2C headphone volume/mute control; no firmware sample scaling assumed.
- **Display power**: SSD1306 VDD and VBAT on the 3.3V buck-boost rail; GND to DGND; I2C2 pull-ups to 3.3V digital.
- **Storage**: microSD powered from 3.3V digital rail (2.7-3.6V range); CS/MOSI/MISO pulled up to 3.3V; card-detect (CD) switch to a GPIO (mechanical, works in SPI mode); 100nF decoupling at card VDD. SPI2 mode (card enters via CMD0 with CS low).
- **Charger status**: PG/CHG are open-drain, pulled up to the 3.3V digital rail (NOT VBAT, which reaches ~4.2V and would exceed MCU input abs-max). MCU senses at the PG/CHG pin, not the LED anode (~2V when conducting = ambiguous logic).
- **Bus/pin assignment**: bus assignments are I2C1 = MAX9850 control, I2C2 = SSD1306 (separate buses), SPI2 = microSD, SPI1/I2S1 = MAX9850 audio input. The existing `st/P3-MP3-Player.ioc2` may retain TAD5112-era DAC signal names and GPIO assignments; The 22.5792MHz DSC6001 drives both MCU AUDIOCLK and MAX9850 MCLK; remaining MAX9850 pin mapping and register setup require confirmation. No schematic or firmware changes are included here.
- **Datasheets checked for this change**: [MAX9850](https://www.analog.com/media/en/technical-documentation/data-sheets/max9850.pdf), [TPS7A20](https://www.ti.com/lit/ds/symlink/tps7a20.pdf), [TPS63050](https://www.ti.com/lit/ds/symlink/tps63050.pdf). MAX9850 package is 28-pin TQFN (5×5mm), not BGA. Pricing and DigiKey CA stock were not checked; these are user-selected architecture changes, not a new procurement recommendation.
