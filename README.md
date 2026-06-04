# Bare Metal STM32 Programs

A collection of bare-metal programs for STM32F401CCU6 microcontroller, demonstrating low-level hardware control without using HAL (Hardware Abstraction Layer).

## Repository Overview

This repository contains bare-metal implementations for the STM32F401CCU6 ARM Cortex-M4 microcontroller. All programs are written in C and Assembly with direct hardware register access.

### Language Composition
- **Assembly**: 46.4% - Startup code and low-level initialization
- **C**: 25.1% - Core application logic
- **Makefile**: 16.1% - Build configuration
- **Linker Script**: 12.4% - Memory layout and section definitions

## Projects Included

### 1. **LED Blink** (`ledblink/`)
A simple LED blinking program that toggles PC13 (built-in LED on most STM32 boards) at regular intervals.

**Features:**
- Direct register manipulation without HAL
- Custom delay function
- Simple and educational

**Key Files:**
- `Src/main.c` - Main program implementation
- `Startup/startup_stm32f401ccux.s` - Assembly startup code
- `STM32F401CCUX_FLASH.ld` - Linker script

**How It Works:**
1. Enable GPIOC clock via RCC_AHB1ENR
2. Configure PC13 as GPIO output (GPIO Mode = 01)
3. Toggle PC13 with software delay

### 2. **GPIO Toggler** (`GPIOToggler/`)
A modular GPIO driver implementation providing abstraction over GPIO operations while maintaining bare-metal access.

**Features:**
- Reusable GPIO driver library
- GPIO peripheral clock control
- Pin initialization with configurable parameters
- Output toggle and read operations
- Support for multiple GPIO ports (A, B, C, D, E, H)

**Directory Structure:**
```
GPIOToggler/
├── Src/
│   ├── main.c          - Application entry point
│   ├── syscalls.c      - System call implementations
│   └── sysmem.c        - Memory management
├── driver/
│   ├── Inc/
│   │   ├── stm32_driver.h   - GPIO driver API
│   │   └── stm32f401.h      - Register definitions
│   └── src/
│       └── stm32_toggler.c  - GPIO driver implementation
├── Startup/
│   └── startup_stm32f401ccux.s - Assembly startup
└── STM32F401CCUX_FLASH.ld      - Linker script
```

## Hardware Details

**Microcontroller**: STM32F401CCU6
- **Architecture**: ARM Cortex-M4
- **Clock**: Up to 84 MHz
- **Flash**: 256 KB
- **RAM**: 64 KB
- **GPIO Ports**: A, B, C, D, E, H

**Memory Layout:**
- Flash Memory: 0x08000000
- SRAM: 0x20000000
- ROM: 0x1FFF0000

## GPIO Driver API

### Structure Definitions

```c
typedef struct{
    uint32_t GPIO_PinNumber;
    uint32_t GPIO_PinMode;
    uint32_t GPIO_PinSpeed;
    uint32_t GPIO_PinPuPdControl;
    uint32_t GPIO_PinOPtype;
    uint32_t GPIO_PinAltFun;
} GPIO_pinconfig_t;

typedef struct{
    GPIO_regdef_t *pGPIOx;
    GPIO_pinconfig_t GPIO_PinConfig;
} GPIO_Handle_t;
```

### Available Functions

- `GPIO_PeriClockControl()` - Enable/Disable GPIO peripheral clock
- `GPIO_Inti()` - Initialize GPIO pin with configuration
- `GPIO_DeInit()` - De-initialize GPIO port
- `GPIO_ReadFromInputPin()` - Read single pin value
- `GPIO_ReadFromInputPort()` - Read entire port
- `GPIO_WriteToOutputPin()` - Write to single pin
- `GPIO_WriteToOutputPort()` - Write to entire port
- `GPIO_ToggleOutputPin()` - Toggle pin state

### GPIO Pin Modes

```c
#define GPIO_MODE_IN        0    // Input
#define GPIO_MODE_OUT       1    // Output
#define GPIO_MODE_ALTFN     2    // Alternate Function
#define GPIO_MODE_ANALOG    3    // Analog
#define GPIO_MODE_IT_FT     4    // Interrupt - Falling Trigger
#define GPIO_MODE_IT_RT     5    // Interrupt - Rising Trigger
#define GPIO_MODE_IT_RFT    6    // Interrupt - Rising/Falling Trigger
```

## Building

### Prerequisites
- ARM GCC Toolchain (arm-none-eabi-gcc)
- GNU Make
- OpenOCD (for debugging)
- STM32CubeIDE or similar IDE (optional)

### Compilation

Each project includes a Makefile for compilation:

```bash
cd ledblink
make clean
make
```

### Flashing

Using OpenOCD:
```bash
openocd -f stm32f4discovery.cfg -c "program build/ledblink.elf verify reset exit"
```

Using STM32CubeIDE:
1. Import the project
2. Build (Ctrl+B)
3. Debug/Run (F11/Ctrl+F11)

## Project Files Explained

### Startup Code (`startup_stm32f401ccux.s`)
- Initializes the stack pointer
- Sets up exception vectors
- Calls C runtime initialization (libc)
- Jumps to main()

### Linker Script (`STM32F401CCUX_FLASH.ld`)
- Defines flash and RAM memory regions
- Maps sections (.text, .data, .bss)
- Sets up heap and stack
- Defines entry point

### System Calls (`syscalls.c`)
- Provides syscall interface for libc functions
- Implements file I/O redirection
- Used by printf for serial output

### Memory Management (`sysmem.c`)
- Implements malloc/free for heap management
- Defines heap boundaries
- Critical for dynamic memory allocation

## Code Quality Notes

### Typos Found and Fixed
- `GPIO_Inti()` → Should be `GPIO_Init()` (typo in function name)
- `GPIO_PinOPtype` → Should be `GPIO_PinOPType` (inconsistent naming)
- `GPIO_DeInti()` → Should be `GPIO_DeInit()` (typo in function declaration)
- `GPIO_PinAltFun` → Should be `GPIO_PinAltFunMode` (typo in driver implementation)

### Improvements Recommended

1. **Add Error Checking**
   - Validate pin numbers (0-15)
   - Check GPIO port validity

2. **Add Comments**
   - Document register operations
   - Add parameter descriptions

3. **Complete API Implementation**
   - Implement missing write and toggle functions
   - Add interrupt configuration functions

4. **Add Examples**
   - Button input reading
   - PWM configuration
   - UART communication

## Testing

The projects have been designed to work on STM32F401 discovery boards. Verify:
- LED blinks at PC13
- GPIO driver correctly toggles pins
- No compilation warnings

## License

This project demonstrates bare-metal STM32 programming concepts. Some code is auto-generated by STM32CubeIDE and retains original STMicroelectronics copyright notices.

## References

- [STM32F401xx Datasheet](https://www.st.com/resource/en/datasheet/stm32f401ce.pdf)
- [STM32F401xx Reference Manual](https://www.st.com/resource/en/reference_manual/dm00096844-stm32f401xde-stm32f401xce-stm32f401xcc-stm32f401xbd-stm32f401xbc-advanced-arm-based-32-bit-mcus-stmicroelectronics.pdf)
- [ARM Cortex-M4 Devices Generic User Guide](https://developer.arm.com/documentation/100166/0001)

## Contributing

This is an educational repository. Feel free to fork, modify, and improve the implementations.

## Author

**Chitransh** - Bare Metal STM32 Programming

---

*Last Updated: June 2026*
