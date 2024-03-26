# Dining Philosophers Problem Simulation

A [42 London](https://42london.com/) project

## Overview

This repository contains implementations of the Dining Philosophers Problem in both multi-threading and multi-processing. The Dining Philosophers Problem is a classic synchronization problem that illustrates the challenges of deadlock and data race.

## Problem Description

The Dining Philosophers Problem is a thought experiment in which a number of philosophers sit at a table with a bowl of spaghetti in front of each one. A fork is placed between each pair of adjacent philosophers. Each philosopher must alternately eat, sleep, and think. However, a philosopher can only eat if they have both forks. 

The challenge arises from the potential for deadlock if each philosopher picks up the fork to their left simultaneously, preventing any philosopher from eating. Thus, a solution must be devised to prevent deadlock and enable the philosophers to dine in harmony.

## Implementations

### Multi-threading

The `multi_threading` directory contains the implementation of the Dining Philosophers Problem using threads. Each philosopher is represented by a separate thread, and synchronization mechanisms such as mutexes or semaphores are used to prevent deadlock and ensure proper resource allocation.

To run the multi-threaded simulation, navigate to the `multi_threading` directory and execute the corresponding script.

### Multi-processing

The `multi_processing` directory contains the implementation of the Dining Philosophers Problem using processes. Each philosopher is represented by a separate process, and inter-process communication mechanisms such as pipes or queues are used for coordination.

To run the multi-processing simulation, navigate to the `multi_processing` directory and execute the corresponding script.

## Usage

Follow these steps to run the simulation:

1. Clone the repository:

    ```bash
    git clone https://github.com/theVeryPulse/philosophers.git
    ```

2. Navigate to the desired implementation directory (`multi_threading` or `multi_processing`). Run
    ```bash
    make
    ```

3. Run the program with command line arguments. Arguments must be given according to the following order:
    * Number of philosophers
    * Time to die in millisecond
    * Time to eat in millisecond
    * Time to sleep in millisecond
    * Number of times each philosopher must eat (optional)
    ```bash
    ./philo 5 800 200 200 6
    ```
