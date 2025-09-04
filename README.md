# RTOS-Practice
Hands-on FreeRTOS (CMSIS-RTOS v2 API) examples and mini-projects on STM32, exploring mutexes, semaphores, queues, timers, and task management.






Hands-on repo for exploring **FreeRTOS concepts** with STM32.  
Each folder contains a **mini-project** demonstrating a real-time OS concept with code + explanation.

---

## 📂 Folder Layout
- `01_Mutex` → Protecting shared resources (counter, UART, I2C bus).
- `02_Semaphores` → Task synchronization with binary & counting semaphores.
- `03_Queues` → Safe data transfer (producer-consumer, task communication).
- `04_Timers` → Software timers for periodic tasks and watchdog handling.
- `05_TaskManagement` → Task priorities, preemption, and scheduling.

---

## ⚙️ Requirements
- STM32F401RE (Nucleo Board)  
- STM32CubeIDE + FreeRTOS middleware  
- UART (via ST-Link or USB-TTL) for debugging  

---

## 🚀 How to Run
1. Clone this repo.
2. Open any project folder in **STM32CubeIDE**.
3. Flash to STM32 board.
4. Monitor UART output at **115200 baud**.

---

## 🔥 Current Progress
- ✅ `01_Mutex/Counter` → Global counter with and without mutex.  
- 🚧 Next: `01_Mutex/UART_Logger`.  

---

## 📜 License
MIT License
