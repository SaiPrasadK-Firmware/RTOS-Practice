# RTOS-Practice
Hands-on FreeRTOS (CMSIS-RTOS v2 API) examples and mini-projects on STM32, exploring mutexes, semaphores, queues, timers, and task management.




💡 Practical RTOS concepts on STM32 using FreeRTOS with CMSIS-RTOS v2 API

This repo is a hands-on lab for learning real-time operating systems on embedded systems.
It contains mini-projects that demonstrate synchronization, communication, and scheduling features of FreeRTOS on STM32 microcontrollers.

Each project is built using:

STM32F401RE Nucleo Board (but portable to other STM32 boards)

STM32CubeIDE with FreeRTOS middleware enabled

CMSIS-RTOS v2 API for task creation, synchronization, and resource management

UART (115200 baud) for debugging and output

📂 What’s Inside

01_Mutex → Safe access to shared resources (counter, UART, I2C bus).

02_Semaphores → Task synchronization (binary + counting).

03_Queues → Producer-consumer and task communication.

04_Timers → Software timers and watchdog refresh.

05_TaskManagement → Task priorities, preemption, round robin.

🚀 Why This Repo?

This repo is not just “hello world” — each example is designed to:

Show the problem without RTOS sync (race conditions, corrupted data).

Show the solution using FreeRTOS features (mutex, semaphores, queues).

Provide clean, interview-ready explanations + code.

⚙️ How to Run

Clone this repo.

Open a project folder in STM32CubeIDE.

Build & flash to STM32 board.

Open a UART terminal at 115200 baud to view logs.
