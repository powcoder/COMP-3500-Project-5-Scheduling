https://powcoder.com
代写代考加微信 powcoder
Assignment Project Exam Help
Add WeChat powcoder
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_TIME_UNIT 1000
#define MAX_PROCESS_NUM 30
#define MAX_ALGORITHM_NUM 10

#define FCFS 0
#define SJF 1
#define PRIORITY 2
#define RR 3
#define LIF 4
#define LISC 5

#define TRUE 1
#define FALSE 0

#define TIME_QUANTUM 3

//process
typedef struct myProcess* processPointer;
typedef struct myProcess {
    int pid;
    int priority;
    int arrivalTime;
    int CPUburst;
    int IOburst;
    int CPUremainingTime;
    int IOremainingTime;
    int waitingTime;
    int turnaroundTime;
    int responseTime;

}myProcess;

int Computation_start = 0;
int Computation_end = 0;
int Computation_idle = 0;

typedef struct evaluation* evalPointer;
typedef struct evaluation {
	int alg;
	int preemptive;
	int startTime;
	int endTime;
	int avg_waitingTime;
	int avg_turnaroundTime;
	int avg_responseTime;
	double CPU_util;
	int completed;
}evaluation;

evalPointer evals[MAX_ALGORITHM_NUM];
int cur_eval_num = 0;

void init_evals(){
	cur_eval_num = 0;
	int i;
	for(i=0;i<MAX_ALGORITHM_NUM;i++)
		evals[i]=NULL;
}

void clear_evals() {
	
	int i;
	for(i=0;i<MAX_ALGORITHM_NUM;i++){
		free(evals[i]);
		evals[i]=NULL;
	}
	cur_eval_num = 0;
}

//Job Queue
processPointer jobQueue[MAX_PROCESS_NUM];
int cur_proc_num_JQ = 0;

void init_JQ () {
	cur_proc_num_JQ = 0;
    int i;
    for (i = 0; i < MAX_PROCESS_NUM; i++)
        jobQueue[i] = NULL;
}

void sort_JQ() { //유저가 pid를 무작위의 순서로 넣는 것을 대비해서 pid를 기준으로 오름차순으로 정렬해준다. 
	//같은 시간에 도착한 프로세스들이 pid순서로 정렬되는 효과가 있다. 
	
	//위키피디아의 insertion sort사용 -> 성능 고려 안함
    int i, j;
    processPointer remember;
    for ( i = 1; i < cur_proc_num_JQ; i++ )
    {
      remember = jobQueue[(j=i)];
      while ( --j >= 0 && remember->pid < jobQueue[j]->pid )
          jobQueue[j+1] = jobQueue[j];
      jobQueue[j+1] = remember; 
    }
}

int getProcByPid_JQ (int givenPid) { //readyQueue에서 해당 pid를 가지고 있는 process의 index를 리턴한다.
    int result = -1;
    int i;
    for(i = 0; i < cur_proc_num_JQ; i++) {
        int temp = jobQueue[i]->pid;
        if(temp == givenPid)
            return i;
    }
    return result;
}
