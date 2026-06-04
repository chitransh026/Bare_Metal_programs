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

### Memory Layout

```
┌─────────────────────────────────┐
│   FLASH Memory                  │
│  0x08000000 - 0x08040000       │
│      (256 KB)                   │
│  ┌─────────────────────────┐   │
│  │ .text (Code)            │   │
│  ├─────────────────────────┤   │
│  │ .rodata (Const Data)    │   │
│  ├─────────────────────────┤   │
│  │ .data (Init Data)       │   │
│  └─────────────────────────┘   │
└─────────────────────────────────┘
         (1)           (2)
┌─────────────────────────────────┐
│   SRAM                          │
│  0x20000000 - 0x20010000       │
│      (64 KB)                    │
│  ┌─────────────────────────┐   │
│  │ .data (Copied)          │   │
│  ├─────────────────────────┤   │
│  │ .bss (Zeroed)           │   │
│  ├─────────────────────────┤   │
│  │ Heap (malloc)           │   │
│  ├─────────────────────────┤   │
│  │ Stack (grows down)      │   │
│  └─────────────────────────┘   │
└─────────────────────────────────┘

(1) Linker copies initialized data from flash to SRAM
(2) Startup code zeros BSS and initializes heap/stack
```

### System Architecture

```
┌─────────────────────────────────────────────────────────┐
│                   STM32F401CCU6                        │
│              (ARM Cortex-M4 @ 84MHz)                   │
├─────────────────────────────────────────────────────────┤
│                                                         │
│  ┌──────────────┐      ┌──────────────┐               │
│  │     Core     │      │   Memory     │               │
│  │  (Cortex-M4) │      │   Controller │               │
│  └──────┬───────┘      └──────┬───────┘               │
│         │                      │                       │
│  ┌──────────────────────────────────┐                 │
│  │    Advanced Peripheral Bus       │                 │
│  ├──────────────────────────────────┤                 │
│  │  RCC │ GPIO │ UART │ SPI │ I2C  │                 │
│  └──────────────────────────────────┘                 │
│                                                         │
└─────────────────────────────────────────────────────────┘

Where:
  RCC   = Reset and Clock Control
  GPIO  = General Purpose Input/Output
  UART  = Universal Asynchronous Receiver/Transmitter
  SPI   = Serial Peripheral Interface
  I2C   = Inter-Integrated Circuit
```

## Boot Sequence Diagram

```
┌─────────────────────────────────────────────────┐
│         Power On or Reset                       │
└────────────────┬────────────────────────────────┘
                 │
                 ▼
┌─────────────────────────────────────────────────┐
│  1. ROM Bootloader Executes                    │
│     - Sets up stack pointer (SP)               │
│     - Jumps to Reset Handler                   │
└────────────────┬────────────────────────────────┘
                 │
                 ▼
┌─────────────────────────────────────────────────┐
│  2. startup_stm32f401ccux.s (Assembly)          │
│     - Initialize stack pointer                 │
│     - Initialize static data (.data)           │
│     - Zero out .bss section                    │
│     - Call system initialization               │
└────────────────┬────────────────────────────────┘
                 │
                 ▼
┌─────────────────────────────────────────────────┐
│  3. libc Initialization                         │
│     - Initialize heap, malloc/free             │
│     - Setup file descriptors                   │
└────────────────┬────────────────────────────────┘
                 │
                 ▼
┌─────────────────────────────────────────────────┐
│  4. main() - User Application Starts           │
│     - GPIO configuration                       │
│     - Main loop execution                      │
└────────────────┬────────────────────────────────┘
                 │
                 ▼
┌─────────────────────────────────────────────────┐
│  5. Application Running                         │
│     - Blink LED / GPIO operations              │
│     - Handle peripherals                       │
└─────────────────────────────────────────────────┘
```

## LED Blink Flow Diagram

```
┌──────────────────────┐
│   Program Start      │
│   (Reset Handler)    │
└──────────┬───────────┘
           │
           ▼
┌──────────────────────────────────┐
│ Enable GPIOC Clock              │
│ RCC_AHB1ENR |= (1 << 2)         │
└──────────┬───────────────────────┘
           │
           ▼
┌──────────────────────────────────┐
│ Configure PC13 as Output        │
│ GPIOC_MODER &= ~(3 << 26)       │
│ GPIOC_MODER |= (1 << 26)        │
└──────────┬───────────────────────┘
           │
           ▼
┌──────────────────────────────────┐
│      Infinite Loop               │
│   ┌──────────────────────┐      │
│   │ Toggle PC13          │      │
│   │ GPIOC_ODR ^= (1<<13) │      │
│   ├──────────────────────┤      │
│   │ Delay (1M cycles)    │      │
│   ├──────────────────────┤      │
│   └──────────────────────┘      │
│            ▲                     │
│            │                     │
│            └─────────────────────┘
└──────────────────────────────────┘
```

## GPIO Driver Architecture

```
┌────────────────────────────────────────────────┐
│         Application Layer                      │
│      (main.c - User Code)                      │
└────────────────┬─────────────────────────────┘
                 │
        ┌────────▼────────┐
        │ API Functions   │
        ├─────────────────┤
        │ GPIO_Init()     │
        │ GPIO_DeInit()   │
        │ GPIO_PeriClock()│
        │ GPIO_Read()     │
        │ GPIO_Write()    │
        │ GPIO_Toggle()   │
        └────────┬────────┘
                 │
        ┌────────▼──────────────────┐
        │  Driver Layer             │
        │  stm32_toggler.c          │
        │  (Implementation)         │
        └────────┬──────────────────┘
                 │
        ┌────────▼──────────────────┐
        │  Hardware Abstraction     │
        │  Register Definitions     │
        │  stm32f401.h              │
        │  stm32_driver.h           │
        └────────┬──────────────────┘
                 │
        ┌────────▼──────────────────┐
        │  Microcontroller          │
        │  STM32F401CCU6            │
        │  - GPIO Ports (A-H)       │
        │  - Registers (MODER, ODR)│
        │  - RCC (Clock Control)    │
        └───────────────────────────┘
```

## GPIO Register Bit Mapping (PC13 Example)

```
GPIO Port Register Layout (for 32-bit registers):

MODER (Mode Register):
┌─────────────────────────────────┐
│ [27:26] PC13 Mode Selection     │
│   00 = Input (default)          │
│   01 = Output                   │
│   10 = Alternate Function       │
│   11 = Analog                   │
└─────────────────────────────────┘

ODR (Output Data Register):
┌─────────────────────────────────┐
│ [13] PC13 Output State          │
│   0 = Low (LED ON)              │
│   1 = High (LED OFF)            │
└─────────────────────────────────┘

IDR (Input Data Register - Read Only):
┌─────────────────────────────────┐
│ [13] PC13 Input State           │
│   0 = Pin is Low                │
│   1 = Pin is High               │
└─────────────────────────────────┘
```

## Data Flow: GPIO Toggle Operation

```
User Code:
┌─────────────────────────────────┐
│ GPIO_ToggleOutputPin(GPIOC, 13) │
└────────────────┬────────────────┘
                 │
                 ▼
Driver Function:
┌─────────────────────────────────┐
│ pGPIOx->ODR ^= (1 << PinNumber) │
└────────────────┬────────────────┘
                 │
                 ▼
Hardware Register:
┌─────────────────────────────────┐
│ Read Current ODR Value          │
│ XOR with (1 << 13) mask         │
│ Write Back to ODR               │
└────────────────┬────────────────┘
                 │
                 ▼
Physical GPIO Pin:
┌─────────────────────────────────┐
│ PC13 Toggles State              │
│ (High ↔ Low)                    │
│ LED toggles (ON ↔ OFF)          │
└─────────────────────────────────┘
```

## Compilation and Linking Process

```
┌──────────────────────────────────────┐
│     Source Files                    │
│  ┌──────────────────────────────┐   │
│  │ main.c                       │   │
│  │ stm32_toggler.c              │   │
│  │ startup_stm32f401ccux.s      │   │
│  │ syscalls.c, sysmem.c         │   │
│  └──────────────────────────────┘   │
└────────────────┬─────────────────────┘
                 │
    ┌────────────┴────────────┐
    │                         │
    ▼                         ▼
┌──────────────┐         ┌──────────────┐
│ Compiler     │         │ Assembler    │
│ (arm-gcc)    │         │ (arm-as)     │
└──────┬───────┘         └──────┬───────┘
       │                        │
       ▼                        ▼
┌──────────────────────────────────────┐
│  Object Files (.o)                   │
│  ┌──────────────────────────────┐   │
│  │ main.o                       │   │
│  │ stm32_toggler.o              │   │
│  │ startup_stm32f401ccux.o      │   │
│  └──────────────────────────────┘   │
└────────────────┬─────────────────────┘
                 │
                 ▼
┌────────────────────────────────────┐
│  Linker                            │
│  (arm-ld)                          │
│  + STM32F401CCUX_FLASH.ld          │
└────────────────┬───────────────────┘
                 │
                 ▼
┌────────────────────────────────────┐
│  Executable ELF File               │
│  (ledblink.elf)                    │
│  ┌──────────────────────────────┐  │
│  │ .text (Code)                 │  │
│  │ .data (Initialized Data)     │  │
│  │ .bss (Uninitialized Data)    │  │
│  │ .symtab (Symbols)            │  │
│  │ Debug Info                   │  │
│  └──────────────────────────────┘  │
└────────────────┬───────────────────┘
                 │
                 ▼
┌────────────────────────────────────┐
│  Binary Conversion                 │
│  (objcopy)                         │
└────────────────┬───────────────────┘
                 │
                 ▼
┌────────────────────────────────────┐
│  Flash Image                       │
│  (ledblink.bin)                    │
│  Ready to program onto MCU         │
└────────────────────────────────────┘
```

## Project File Structure

```
Bare_Metal_programs/
│
├── README.md                          (This file)
│
├── ledblink/                          (Simple LED Blink Project)
│   ├── Src/
│   │   ├── main.c                     (Application code)
│   │   ├── syscalls.c                 (System calls)
│   │   └── sysmem.c                   (Memory management)
│   ├── Startup/
│   │   └── startup_stm32f401ccux.s    (Assembly startup)
│   ├── Debug/                         (Build artifacts)
│   ├── ledblink.launch                (Debug configuration)
│   └── STM32F401CCUX_FLASH.ld         (Linker script)
│
└── GPIOToggler/                       (GPIO Driver Project)
    ├── Src/
    │   ├── main.c                     (Application code)
    │   ├── syscalls.c                 (System calls)
    │   └── sysmem.c                   (Memory management)
    ├── driver/
    │   ├── Inc/
    │   │   ├── stm32_driver.h         (GPIO API)
    │   │   └── stm32f401.h            (Register definitions)
    │   └── src/
    │       └── stm32_toggler.c        (Driver implementation)
    ├── Startup/
    │   └── startup_stm32f401ccux.s    (Assembly startup)
    ├── Debug/                         (Build artifacts)
    └── STM32F401CCUX_FLASH.ld         (Linker script)
```

## GPIO Driver API

### Structure Definitions

```c
typedef struct{
    uint32_t GPIO_PinNumber;
    uint32_t GPIO_PinMode;
    uint32_t GPIO_PinSpeed;
    uint32_t GPIO_PinPuPdControl;
    uint32_t GPIO_PinOPType;
    uint32_t GPIO_PinAltFunMode;
} GPIO_pinconfig_t;

typedef struct{
    GPIO_regdef_t *pGPIOx;
    GPIO_pinconfig_t GPIO_PinConfig;
} GPIO_Handle_t;
```

### Available Functions

- `GPIO_PeriClockControl()` - Enable/Disable GPIO peripheral clock
- `GPIO_Init()` - Initialize GPIO pin with configuration
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
- `GPIO_Inti()` → Fixed to `GPIO_Init()` ✓
- `GPIO_PinOPtype` → Fixed to `GPIO_PinOPType` ✓
- `GPIO_DeInti()` → Fixed to `GPIO_DeInit()` ✓
- `GPIO_PinAltFun` → Fixed to `GPIO_PinAltFunMode` ✓

### Improvements Recommended

1. **Add Error Checking**
   - Validate pin numbers (0-15)
   - Check GPIO port validity

2. **Add Comments**
   - Document register operations
   - Add parameter descriptions

3. **Complete API Implementation**
   - Implement missing write and toggle functions ✓
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
