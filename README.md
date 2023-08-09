# philosophers
Dining philosophers simulator with multithreading and multiprocessing.

[wikipedia: Dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)

![App screenshot](https://github.com/akinori-s/philosophers/blob/main/docs/philo.png?raw=true)

## How to Run

1. Clone the repository and compile the program.
```bash
git clone https://github.com/akinori-s/philosophers.git
cd philosophers/philo
make
```

2. Execute the program in the format below. Times are in milliseconds. The last argument is optional.

`./philo [no. of philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [no. of times to eat]`
```bash
./philo 4 410 200 200  2
```

## Visualization

How it looks when visualised with nfukada's [visualizer.](https://github.com/nafuka11/philosophers-visualizer)

```bash
./philo 4 410 200 200  2`
```

![App screenshot](https://github.com/akinori-s/philosophers/blob/main/docs/philo_visualisation.png?raw=true)
