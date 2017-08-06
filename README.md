# mpi-profiler

## Sample Output
  Rank: 0, Total time: 0.30 sec.
  MPI time: 0.03 (9.83%), CPU time: 0.27 (90.17%)
  Caution: MPI\_Init and MPI\_Finalize are not included.
   --------Function-------- --Time(s)-- --Count--
                   MPI_Wait        0.02      1680
                   MPI_Send        0.01      1680
                  MPI_Irecv        0.00      1680
                 MPI_Reduce        0.00         1
                MPI_Barrier        0.00         1
              MPI_Comm_size        0.00         1
              MPI_Comm_rank        0.00         1

## Build
Type `make`
**If you are not using Intel MPI, then there will be some errors about type declaration**

## Link and Use
This tool is a static library `libmpit.a`, link this library to your MPI programs with `-L/PATH/TO/LIB -lmpit`.
A output file (shown as sample output above) will be generated for each process.
