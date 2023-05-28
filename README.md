# mpi-studies
Parallel Programming using MPI and C

#### Requirements
```bash
# Dependencies
sudo apt install openmpi-bin libopenmpi-dev
```

#### Compiling

```bash
mpicc hello_world.c -o hello_world.x
```

```bash
# -np represents the number of processes. If you only have 1 CPU, that is the number you should use
mpicc hello_world -np 1 ./hello_world.x
```
