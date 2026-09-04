# P3 MP3 Player - Components

## MCU

| Field | Value |
|---|---|
| Part | STM32C551CET6 |
| Manufacturer | STMicroelectronics |
| Source | DigiKey CA |
| Price | ~$4.00 CAD |
| Package | LQFP48 (hand-solderable) |
| Operating temp | -40 to 85 C (T6) |
| Supply | 2.7-3.6V |

### Specs
- Arm Cortex-M33 @ 144MHz with FPU, DSP instructions, MPU
- 512KB flash (ECC, 8KB ART instruction cache, 0-wait-state at max speed)
- 128KB SRAM (64KB with ECC)
- 3x SPI, one per full-duplex I2S (audio-class accuracy via external clock)
- USB 2.0 full-speed host + device
- 2x 12-bit ADC (2.25 MSPS), 1x 12-bit DAC, 1x comparator
- 2x I2C (FM+), 1x I3C, 3x USART, 2x UART, 1x LPUART
- 2x watchdogs (IWDG/WWDG), RTC with calendar/alarms
- 2x LPDMA, 12 channels
- Low-power modes: Sleep, Stop, Standby
- 38 high-current I/Os in LQFP48

### Why this part
- Cheapest of all candidates considered ($4 vs $10 for F401)
- 128KB RAM + 144MHz M33 puts it 2-3x over the comfortable minimum for Helix MP3 decode
- Unlocks FLAC decode as a future option
- I2S and SD-card SPI on separate peripherals (no conflict)
- New C5 value line: smaller process node, aggressive pricing

### Open checks before committing
- [ ] CubeMX/CubeIDE support via STM32CubeC5 pack
- [ ] Confirm USB clocking requirement (external crystal? 24/25MHz?)
- [ ] Confirm I2S external MCLK footprint need (24.576MHz for exact 44.1/48kHz)

## Battery

| Field | Value |
|---|---|
| Cell | 702050 LiPo (size code: 7 x 20 x 50mm) |
| Chemistry | 1S LiPo, 3.7V nominal, 3.0-4.2V |
| Capacity | ~650mAh (verify against actual listing) |
| Connector | JST-PH 2.0, 2-pin (verify pigtail) |
| Protection | Built-in protection PCB (verify; add external if absent) |

### Design parameters
- Body target: ~110 x 24 x 20mm (grown from NW-S203F's 96.5 x 15 x 15mm, same stick silhouette)
- Battery envelope on PCB/case: 20 x 50 x 7mm; design zone to accept up to 8-9mm thickness
- Runtime: ~5.5h at ~120mA playback draw
- Firmware cutoff: shut down at ~3.2V (cell protection cuts at 3.0V as last resort)
- Polarity: note Adafruit vs other-vendor JST-PH convention on silkscreen

### Sourcing
- Search "702050" on Amazon.ca / AliExpress / hobby shops
- Buy first, measure actual dimensions + verify capacity before committing PCB layout
- Verify: JST-PH 2.0 connector, built-in protection, polarity

## Power Management

### Charger: Microchip MCP73832T-2ACI/OT (SOT-23-5)
- CC/CV linear charger, 4.2V, industrial temp
- Charge current: I(mA) ~= 1000 / R_PROG(kOhm), max 500mA
  - 650mAh cell at ~0.5C -> ~300mA -> R_PROG ~= 3.3kOhm
- STAT pin: open-drain, active-low, charge/done status -> MCU GPIO (pull-up to 3.3V)
- No power path / no load-sharing: system sits on BAT node (battery + system share one node)
- Hookup: VDD <- VBUS 5V (1uF), VBAT -> battery node (1uF) + buck-boost input, PROG -> R to VSS, VSS -> GND
- Verify SOT-23-5 pin numbering against datasheet before footprint
- No-battery bench mode: charger sources ~4.2V at set current to the BAT node; system runs but keep load <= ~300mA set current

### Buck-boost: TI TPS63050 @ 3.45V (QFN-HR RMW)
- Input: BAT node (2.5-5.5V), accepts ~4.2V (charger, no battery) or battery voltage (2.6-4.2V)
- Output: 3.45V digital rail (C551 range 2.7-3.6V; 150mV margin below max)
- 2.5MHz switching, >90% eff, PFM/PWM selectable (force PWM for audio predictability)
- Feedback divider tolerance keeps 3.45V + ripple < ~3.55V (1% resistors)
- Note: with system on BAT node, charge current is shared with system draw; charge slower while playing, termination fuzzy (acceptable: charge with device idle)

### Analog rail: TI LP5907-3.3 LDO + ferrite bead(s)
- 3.45V rail -> LP5907 -> 3.3V audio rail (dropout at ~30mA is ~40-60mV, 3.45V gives headroom)
- 3.3V -> 10uF + 100nF -> ferrite bead -> DAC/amp supplies (100nF at each pin)
- Ferrite: 0603, 600Ohm@100MHz, ~0.5A (e.g. Murata BLM18AG601SN1D), DCR ~0.3-0.5Ohm
- Optional: one bead per load (DAC and amp separately) for better isolation
- I2S logic at 3.45V into 3.3V DAC is within abs max (3.6V); 22-33Ohm series resistors on I2S lines recommended

### Power flow
```
USB 5V --> MCP73832 --> BAT node --> 702050 cell (3.0-4.2V)
                             |
                             +--> TPS63050 (3.45V) --> 3V45 rail (MCU, SD, USB)
                                              |
                                              +-- LP5907 (3.3V) --> ferrite bead(s) --> DAC/amp
```

### Monitoring
- Charge status: MCP73832 STAT pin (charging/done) -> MCU GPIO
- USB present: VBUS resistor divider -> MCU ADC/GPIO (do NOT rely on charger status when no battery)
- Battery level: VBAT divider (1:2, ~100k) -> MCU ADC, calibrated with VREFINT, mapped via discharge curve lookup table (voltage-based, rough +/-10-20%)