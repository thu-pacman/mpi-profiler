/************************************************************
*           Main Profiling Interface for libmpit            *
* Modified by Jidong Zhai on July 18, 2012.                 *
************************************************************/

#include <stdlib.h>
#include <stdio.h>

#include "profile.h"
#include "timer.h"
#include "mpiname.h"

static mpi_perf mpi_profile[MPI_FUNCTIONS];
double used_time = 0.0, comm_time = 0.0, comp_time = 0.0, elapsed_time = 0.0;
int    proc_id = 0; 
int    profile_on = 1;
FILE*  profile_file;
int    threshold;

void sort_mpi(mpi_perf **_mpi_sort);

void PROFILE_INIT(int process_id){
	char profile_name[100];
	int i;

    for (i = 0; i < 64; ++ i) _timer_clear(i);
	_timer_start(0);
	
	for (i=0; i<MPI_FUNCTIONS; i++){
		mpi_profile[i].entry_time = 0.0;
		mpi_profile[i].total_time = 0.0;
		mpi_profile[i].count = 0;
		mpi_profile[i].flag = 0;
	}
	proc_id = process_id;
	
	sprintf(profile_name, "mpi_record.%d", proc_id);
	profile_file = fopen(profile_name, "w");
	if (profile_file == NULL){
		printf("Open profile file failed\n");
		exit(0);
	}

	// Hardcoding here. Print the elasped time for MPI functions.
	// This function is used to analyze the accuracy of MPI simulator
	#ifdef MPI_TIME
	mpi_profile[25].flag = 1;
	mpi_profile[26].flag = 1;
	threshold = 2000;
	#endif
	
}

void PROFILE_ON(){

	// Default is ON. 
	profile_on = 1;
}

void PROFILE_OFF(){

	profile_on = 0;
}

void PROFILE_START(int mpi_id){
	if (profile_on)
		mpi_profile[mpi_id].entry_time = current_time();

}

void PROFILE_STOP(int mpi_id){
	if (profile_on){
		used_time = current_time() - mpi_profile[mpi_id].entry_time;
		mpi_profile[mpi_id].total_time += used_time;
		(mpi_profile[mpi_id].count)++;
		if ((mpi_profile[mpi_id].flag == 1)&&(threshold>0)){
			fprintf(profile_file, "%d\t%.2f\n", mpi_id, used_time);
			threshold--;
		}
	}
}

void PROFILE_FINISH(){

	int i,j;
	_timer_stop(0);
	elapsed_time = _timer_read(0);
	mpi_perf * mpi_sort[MPI_FUNCTIONS];

	for(i=0; i<MPI_FUNCTIONS; i++)
		comm_time += mpi_profile[i].total_time;
	comp_time = elapsed_time - comm_time;

	fprintf(profile_file, "Rank: %d, Total time: %.2lf sec.\n", proc_id, elapsed_time);
	fprintf(profile_file, "MPI time: %.2lf (%4.2lf%%), CPU time: %.2lf (%4.2lf%%)\n", comm_time, 100.0*comm_time/elapsed_time, comp_time, 100.0*(1-comm_time/elapsed_time));
    fprintf(profile_file, "Caution: MPI_Init and MPI_Finalize are not included.\n");
	
	fprintf(profile_file, "%25s%12s%10s\n", "--------Function--------", "--Time(s)--", "--Count--");

	for(i=0; i<MPI_FUNCTIONS; i++)
		mpi_sort[i] = &mpi_profile[i];

	sort_mpi(mpi_sort);

	for(i=0; i<MPI_FUNCTIONS; i++){
		if (mpi_sort[i]->count != 0){
			j = mpi_sort[i] - &mpi_profile[0];
			fprintf(profile_file, "%25s%12.2lf%10lld\n", MPI_Functions[j], mpi_sort[i]->total_time, mpi_sort[i]->count);
		}
	}
	fclose(profile_file);
}

void sort_mpi(mpi_perf **_mpi_sort){
	int i, j;
	mpi_perf* temp;
	for(i=0; i<MPI_FUNCTIONS; i++){
		for(j=i; j<MPI_FUNCTIONS; j++){
			if (_mpi_sort[j]->total_time > _mpi_sort[i]->total_time){
				temp = _mpi_sort[i];
				_mpi_sort[i] = _mpi_sort[j];
				_mpi_sort[j] = temp;
			}
		}
	}
}

