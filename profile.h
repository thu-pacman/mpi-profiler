#ifndef PROFILE_H
#define PROFILE_H

#define MPI_FUNCTIONS 127 


void PROFILE_INIT(int);
void PROFILE_START(int);
void PROFILE_STOP(int);
void PROFILE_FINISH();

typedef struct{
	double entry_time;
	double total_time;
	long int count;
	int flag; // Flag for printing elapsed time. Default = 0
}mpi_perf;


#endif /*PROFILE_H*/

