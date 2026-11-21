

# Philosophers

## What the program does

Philosophers is a concurrency and synchronization project written in C. It simulates the dining philosophers problem to demonstrate how multiple threads can execute concurrently while sharing limited resources.

Each philosopher alternates between eating, sleeping, and thinking. To eat, a philosopher must acquire two forks shared with neighboring philosophers. The program manages access to these resources while monitoring the simulation for deadlocks and philosopher starvation.

The project includes:

- **Multithreading:** Uses POSIX threads (`pthreads`) to run multiple philosophers concurrently.
- **Mutexes:** Synchronizes access to shared resources and prevents race conditions.
- **Resource management:** Controls access to forks to prevent multiple philosophers from using the same fork simultaneously.
- **Time management:** Tracks the time spent eating, sleeping, and thinking, as well as the time since each philosopher last ate.
- **Death detection:** Monitors philosophers and terminates the simulation if one exceeds the maximum allowed time without eating.
- **Simulation control:** Stops the simulation when a philosopher dies or when all philosophers have eaten the required number of times, if a meal limit is specified.
- **Thread synchronization:** Coordinates threads to ensure consistent access to shared simulation data.

## How to execute the project

Navigate to the project directory:

```bash
cd Philosophers
```

Compile the project using the Makefile:

```bash
make
```

Run the simulation with the following arguments:

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

Example:

```bash
./philo 5 800 200 200
```

This starts a simulation with:
- 5 philosophers
- 800 milliseconds until a philosopher dies without eating
- 200 milliseconds to eat
- 200 milliseconds to sleep

You can optionally specify how many times each philosopher must eat:

```bash
./philo 5 800 200 200 7
```

Additional Makefile commands:

```bash
make clean
make fclean
make re
```

