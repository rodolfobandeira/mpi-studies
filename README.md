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
# "-np" represents the number of processes. You can use as much
# "-np" as long it doesn't pass the number of CPU Cores available
# You can check how many CPU Cores with: 
#   lscpu | grep "Core.* socket"

mpicc hello_world -np 4 ./hello_world.x
```
