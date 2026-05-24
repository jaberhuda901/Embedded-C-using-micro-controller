# SYSC 3310 Labs Portfolio

This repository contains my submissions for the **SYSC 3310** (Microprocessor Systems) practical labs. Throughout these labs, I worked with the MSP432/ARM Cortex-M4 microcontroller environments, advancing from basic bare-metal C programming to implementing elements of a Real-Time Operating System (RTOS). 

The progression of these projects provided hands-on experience with hardware-software interfacing, interrupt-driven programming, hardware timers, and task scheduling.

## 🚀 Projects Overview

Here is a summary of what I learned and accomplished in each lab submission:

### [Lab 4] GPIO configuration, Polling & Debouncing
- **Concept:** Basics of General Purpose Input/Output (GPIO) control.
- **Learnings:** 
  - Configured hardware pins as inputs for switches (with pull-up resistors) and outputs for LEDs (Red and RGB).
  - Implemented continuous polling to read switch states.
  - Mitigated switch bouncing using software delay loops for proper signal debouncing.

### [Lab 5] Interrupt-Driven I/O & NVIC
- **Concept:** Transition from CPU-intensive polling to interrupt-driven architectures.
- **Learnings:** 
  - Configured the Nested Vectored Interrupt Controller (NVIC) to manage hardware interrupts.
  - Implemented `PORT1_IRQHandler` to trigger code execution strictly upon hardware button presses.
  - Improved overall system efficiency by allowing the CPU to remain idle when no events occur.

### [Lab 6] Hardware Timers (Timer A)
- **Concept:** Accurate event timing without blocking the CPU.
- **Learnings:** 
  - Introduced to hardware timers utilizing the 32.768kHz ACLK (Auxiliary Clock).
  - Configured Timer A0 in Up-Mode to trigger periodic interrupts (e.g., triggering exactly every 1 second).
  - Managed timer interrupts via the `TA0_N_IRQHandler` to periodically toggle LEDs while continuing to service GPIO button interrupts concurrently.

### [Lab 7] Advanced Timer Modes & Complex Interrupts
- **Concept:** Multiple timers and Up/Down counting modes.
- **Learnings:** 
  - Managed multiple hardware timers (Timer A0 and Timer A1) running concurrently.
  - Configured complex Up/Down count modes and pre-scaled clock dividers to achieve different timing resolutions.
  - Captured multiple interrupt channels (`TA1_0_IRQHandler` and `TA1_N_IRQHandler`) to sequence advanced lighting state machines (multi-color RGB rotations).

### [Lab 8] Task Scheduling & RTOS Fundamentals
- **Concept:** Designing a custom multi-tasking scheduler.
- **Learnings:** 
  - Moved beyond monolithic `while(1)` loops by utilizing an introductory Real-Time Operating System kernel (`fate.c` / `fate.h`).
  - Added deterministic, periodic execution via `Task_add()` and `Task_schedule()`.
  - Implemented completely decoupled routines (`Task_1`, `Task_2`, `Task_3`) that are concurrently scheduled with specific periods, execution limits, and priorities without interfering with one another.

---

### Technologies & Hardware Used:
- **Language:** Embedded C
- **Hardware:** ARM Cortex-M4 Microcontroller (MSP432)
- **Key Subsystems:** GPIO, NVIC (Interrupts), Timer_A modules, Custom RTOS Scheduler.
