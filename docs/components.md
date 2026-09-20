# P3 MP3 Player — Components

| Block | Part | Status |
|---|---|---|
| MCU | STM32C551CET6 (LQFP48) | ✓ |
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

- **Audio clock / SYSCLK**: this MCU has no PLL (internal HSI is natively 144MHz; only dividers downstream). SYSCLK runs from HSI 144MHz. A 22.5792MHz MEMS oscillator (DSC6001, 512×44.1kHz) feeds the I2S external clock for audio-class accuracy, native 44.1kHz family (48kHz family not exact). OE tied high = always enabled; the OE option can't power down the core, and the standby variant (DSC6011) is not stocked at this frequency. No LSE (no RTC).
- **Power tree (three rails)**:
  - 3.45V digital (TPS63050 buck-boost): MCU, microSD, OLED VBAT
  - 3.3V analog (LP5907 #1 + ferrite): TAD5112 AVDD — clean rail for audio
  - 3.3V digital (LP5907 #2, DGND-referenced): SSD1306 VDD, TAD5112 IOVDD, I2C pull-ups
  - The 3.45V rail is kept because the LP5907 needs ~150mV dropout headroom to regulate 3.3V; digital loads run directly off it for efficiency (no LDO loss), and only loads that cannot take 3.45V (SSD1306 3.3V max, TAD5112 IOVDD 1.2/1.8/3.3V) use the LDOs.
- **DAC**: TAD5112 is a single chip that integrates the DAC, headphone driver (62.5mW @ 16Ω) and digital volume control. Configured over I2C (registers); I2S slave (BCK/LRCK/DATA) with its own PLL and auto sample-rate detection. No separate headphone amp or attenuator required. AVDD on analog rail, IOVDD on digital 3.3V rail. I2C bus shared with the display.
- **Volume**: TAD5112 built-in digital volume via I2C register (no firmware sample scaling).
- **Display power**: SSD1306 VDD on the 3.3V digital rail (LP5907 #2, DGND-referenced); VBAT (charge pump) on 3.45V buck-boost; display GND to DGND (keeps charge-pump return off AGND); I2C SCL/SDA pulled up to 3.3V digital rail (no level shifter).
- **Storage**: microSD powered from 3.45V digital rail (2.7-3.6V range); CS/MOSI/MISO pulled up to 3.45V; card-detect (CD) switch to a GPIO (mechanical, works in SPI mode); 100nF decoupling at card VDD. SPI mode (card enters via CMD0 with CS low).
- **Charger status**: PG/CHG are open-drain, pulled up to the 3.45V digital rail (NOT VBAT, which reaches ~4.2V and would exceed MCU input abs-max). MCU senses at the PG/CHG pin, not the LED anode (~2V when conducting = ambiguous logic).