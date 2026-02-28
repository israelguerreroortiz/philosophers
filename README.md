# Philosophers

*This project was created as part of the 42 curriculum by <isrguerr>.*

---

## 📖 Description
The **Philosophers** project explores fundamental concepts of **multithreading**, **synchronization**, and **concurrency control** using **pthread** in C. It simulates the classic *Dining Philosophers Problem*, where multiple philosophers must share limited resources (forks) while eating, thinking, and sleeping, avoiding starvation and deadlocks.

---

## 🧩 Project Objective
Implement a safe and efficient solution that:
- Prevents **deadlocks** and **data races**
- Synchronizes access to shared resources with mutexes
- Maintains precision in execution timings
- Ensures philosophers do not starve to death

---

## 📋 Instructions

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

### Expected Output
```bash
0 1 is thinking
50 1 has taken a fork
52 1 has taken a fork
55 1 is eating
255 1 is sleeping
455 1 is thinking
```

---

## 🔗 Resources

- [POSIX Threads Documentation](https://man7.org/linux/man-pages/man7/pthreads.7.html)
- [The Dining Philosophers Problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [Mutex and Synchronization Guide](https://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_mutex_lock.html)
- [Concurrency in C](https://www.geeksforgeeks.org/multithreading-in-c/)

### AI Usage
AI assistance was used for: [specify here: syntax review, algorithm optimization, documentation, etc.]

