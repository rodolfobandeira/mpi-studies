# mpi-studies
Parallel Programming using MPI and C

---

#### Requirements

##### Linux
```bash
# Dependencies
sudo apt install openmpi-bin libopenmpi-dev
```

##### Windows
* https://www.microsoft.com/en-us/download/confirmation.aspx?id=57467
* Configuring MingW64 with Microsoft Studio Code: https://code.visualstudio.com/docs/cpp/config-mingw
* Configuring MSI with Microsoft Studio Code: https://www.youtube.com/watch?v=bkfCrj-rBjU
  * For this step, I had to replace the path MSMPI_INC and MSMPI_LIB64 to the real path otherwise it wouldn't work

---

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

To compile on Windows, use `Terminal` `->` `Run Build Task` on Microsoft Studio Code. After that, in the terminal: `mpiexec -n 4 send_recv`

# Reference
* MPI Basics from Tom Nurkkala: https://www.youtube.com/watch?v=c0C9mQaxsD4
* MPI Advanced from Tom Nurkkala: https://www.youtube.com/watch?v=q9OfXis50Rg
