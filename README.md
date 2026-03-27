
# UART Command Interface (STM32)

Simple embedded system for controlling LEDs and a 7-segment display using UART commands and a joystick.




## Description


Supports multiple modes:
- LED control
- 7-segment display (mask / stopwatch)
- Joystick control

Uses non-blocking logic and input debouncing.

---

## Features
- UART command menu (`menu`, `LedControl`, `7SegControl`, etc.)

- LED control (UART mode):
  - Single LED selection
  - Toggle / shift
  - Control using mask (e.g. `1256`)

- 7-segment display (UART mode):
  - Two modes:
    - Mask mode (direct value input, e.g. `1324`)
    - Stopwatch mode:
      - Real-time counting (1-second resolution)
      - Start / stop / reset

- Joystick mode:
  - Mode-based control:
    - LED mode → manual LED control
    - 7-segment mode → display / stopwatch control
    - Value editing using joystick

- Non-blocking timing (SysTick)

---

## Architecture
- Polling-based input handling
- Debouncing using system tick
- Simple state control (`page`, `joy_mode`)

---

## Tech
- STM32
- C
- Register-level programming (no HAL)

---

## How to run
1. Upload the program to STM32 using ST-Link
2. Open UART terminal (RealTerm)
3. Send commands:
   - `menu`
   - `LedControl`
   - `7SegControl`
   - `JoyControl`
4. Use joystick or UART commands to control the system
