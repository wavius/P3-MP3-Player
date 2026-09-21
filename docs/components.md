# P3 MP3 Player — Components

| Block | Part | Status |
|---|---|---|
| MCU | STM32C552RET6 (LQFP64, 512KB flash, 128KB RAM) | ✓ |
| Battery | 702050 LiPo, ~650mAh, JST-PH 2.0 | ✓ |
| Charger | BQ24040 (ISET2=500mA, ~300mA) | ✓ |
| Buck-boost | TPS63050 @ 3.45V | ✓ |
| LDO (analog 3.3V) | LP5907-3.3 | ✓ |
| LDO (digital 3.3V) | LP5907-3.3 | ✓ |
| Ferrite bead | BLM18AG601SN1D (0603, 600Ω@100MHz) | ✓ |
| USB ESD | USBLC6-2 | ✓ |
| DAC + headphone amp | TAD5112 (VQFN-24, DAC + HP driver, I2C/SPI) | ✓ |
| Storage | microSD socket (10-pos push-push w/ CD, SPI + FatFs) | ✓ |
| Display | SSD1306B OLED (I2C) | ✓ |
| Audio clock | DSC6001JI2B-022.5792T (22.5792MHz MEMS XO, CMOS, OE tied high) | ✓ |
| Input | TBD (jog dial, buttons, hold) | ✗ |

✓ = chosen, ✗ = not yet selected

## Decisions

- **Audio clock / SYSCLK**: this MCU has no PLL (internal HSI is natively 144MHz; only dividers downstream). SYSCLK runs from HSI 144MHz. A 22.5792MHz MEMS oscillator (DSC6001, 512×44.1kHz) feeds the SPI1/I2S kernel clock via the AUDIOCLK input for audio-class accuracy, native 44.1kHz family (48kHz family not exact). OE tied high = always enabled; the OE option can't power down the core, and the standby variant (DSC6011) is not stocked at this frequency. No LSE (no RTC).
- **Power tree (three rails)**:
  - 3.45V digital (TPS63050 buck-boost): MCU, microSD, OLED VBAT
  - 3.3V analog (LP5907 #1 + ferrite): TAD5112 AVDD — clean rail for audio
  - 3.3V digital (LP5907 #2, DGND-referenced): SSD1306 VDD, TAD5112 IOVDD, I2C pull-ups
  - The 3.45V rail is kept because the LP5907 needs ~150mV dropout headroom to regulate 3.3V; digital loads run directly off it for efficiency (no LDO loss), and only loads that cannot take 3.45V (SSD1306 3.3V max, TAD5112 IOVDD 1.2/1.8/3.3V) use the LDOs.
- **DAC**: TAD5112 is a single chip that integrates the DAC, headphone driver (62.5mW @ 16Ω) and digital volume control. Configured over I2C2 (registers); I2S1 target (BCLK/FSYNC/DIN) with its own PLL and auto sample-rate detection. No separate headphone amp or attenuator required. AVDD on analog rail, IOVDD on digital 3.3V rail. Display is on I2C1 (separate bus, not shared).
- **Volume**: TAD5112 built-in digital volume via I2C register (no firmware sample scaling).
- **Display power**: SSD1306 VDD on the 3.3V digital rail (LP5907 #2, DGND-referenced); VBAT (charge pump) on 3.45V buck-boost; display GND to DGND (keeps charge-pump return off AGND); I2C1 SCL/SDA pulled up to 3.3V digital rail (no level shifter).
- **Storage**: microSD powered from 3.45V digital rail (2.7-3.6V range); CS/MOSI/MISO pulled up to 3.45V; card-detect (CD) switch to a GPIO (mechanical, works in SPI mode); 100nF decoupling at card VDD. SPI2 mode (card enters via CMD0 with CS low).
- **Charger status**: PG/CHG are open-drain, pulled up to the 3.45V digital rail (NOT VBAT, which reaches ~4.2V and would exceed MCU input abs-max). MCU senses at the PG/CHG pin, not the LED anode (~2V when conducting = ambiguous logic).
- **Bus/pin assignment** (source of truth: `st/P3-MP3-Player.ioc2`): I2C1 = SSD1306 (`DISP_I2C1_SCL/SDA`) + `DISP_NRES`; I2C2 = TAD5112 (`DAC_I2C2_SCL/SDA`); SPI2 = microSD (`SD_SPI2_SCLK/SDI/SDO`, `SD_CS`, `SD_CD`); SPI1 = I2S1 to TAD5112, MCU-perspective (`DAC_I2S1_FSYNC`/`DAC_I2S1_BCLK` MCU outputs, `DAC_I2S1_SDO` = MCU→DAC DIN, `DAC_I2S1_SDI` = DAC DOUT→MCU); `CLK_22_5792M` → AUDIOCLK (SPI1 kernel clock); `CHGR_NPG`/`CHGR_NCHG`; USB D+/D-.