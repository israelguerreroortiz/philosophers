# Philosophers

## 🧠 Overview
The **Philosophers** project is part of the 42 curriculum.  
It explores **multithreading**, **synchronization**, and **concurrency control** using **pthread** in C.  
The goal is to simulate the *Dining Philosophers Problem* — a classic problem in computer science about resource sharing and deadlock prevention.

---

## 🧩 Problem
Several philosophers sit around a table with a fork between each of them.  
They must **eat**, **think**, and **sleep** without starving or causing a **deadlock**.  
Each philosopher needs **two forks** to eat.

---

## ⚙️ Rules
- If a philosopher doesn’t start eating within a certain `time_to_die`, they die.
- Philosophers alternate between **eating**, **sleeping**, and **thinking**.
- Each philosopher needs **two forks** to eat.
- The simulation stops if:
  - A philosopher dies.
  - All philosophers have eaten at least `number_of_times_each_philosopher_must_eat` (optional argument).

---

## 🛠️ Implementation Notes
- Written in **C**.
- Uses **pthread** for threads and **mutexes** for forks.
- Ensures:
  - No data races.
  - No deadlocks.
  - Accurate timing using `gettimeofday()`.
- The program handles concurrent actions safely through mutex protection on shared resources.
- Each philosopher’s state (eating, sleeping, thinking) is printed with a timestamp in milliseconds.

---

## 🧩 Key Concepts
- **Threads & Mutexes**: Manage concurrent execution and resource sharing.  
- **Synchronization**: Prevent simultaneous access to shared resources.  
- **Deadlock Avoidance**: Prevent all philosophers from waiting indefinitely.  
- **Timing Accuracy**: Maintain precise control over simulation timing.  
- **Data Consistency**: Ensure thread-safe updates and outputs.
  
---

## 🧵 Usage
### Compilation
```bash
make
```
### Execution
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```
### Example
```bash
./philo 5 800 200 200
```
### Example output
```bash
0 1 is thinking
50 1 has taken a fork
52 1 has taken a fork
55 1 is eating
255 1 is sleeping
455 1 is thinking
```




