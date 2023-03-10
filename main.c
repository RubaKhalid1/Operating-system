/*
Ruba Alsulami    2110618
Arjwan Alharbi   2110826
Teif Saleh       2111370
*/


#include <stdio.h>
#include <stdlib.h>

struct Process{ //struct to store information of process
    int num; //name of process
    int cpu_burst; //burst time for process
    int waiting; //waiting time for each process
    int response; //response time for each process
    int turnaround; //turnaround time for each process
};

int main(){
    printf("    > Enter total number of processes: "); //Get total number of processes from the user
    int SIZE;
    scanf("%d", &SIZE); //input total number of processes
    while(SIZE<=0)
    {
       printf("    > Enter again: "); //Get total number of processes from the user
       scanf("%d", &SIZE); //input total number of processes
    }
    
    int* remaining_cpu = malloc(sizeof(int)*SIZE); //declare remaining burst time array
    struct Process** processes = malloc(sizeof(struct Process*)*SIZE); //processes array
    //Queue 1 using RR algorithm with 8 time quantum
    struct Process** Queue1 = malloc(sizeof(struct Process*)*SIZE);
    for(int i=0; i<SIZE; i++){ //loop to get information for all processes
        int temp; //store burst time for each process
        processes[i] = malloc(sizeof(struct Process)); //declare each process
        printf("    > Enter burst time %d: ", i + 1); //enter burst time for each process
        scanf("%d", &temp); //get burst time for each process
        while(temp<=0)
        {
           printf("    > Enter again: "); //enter burst time for each process
           scanf("%d", &temp); //get burst time for each process
        }
        processes[i]->num = i; //store name for each process
        processes[i]->cpu_burst = temp; //store cpu time for each process
        remaining_cpu[i] = processes[i]->cpu_burst; //store remaining time for each process
        Queue1[i] = processes[i]; //store each process in Queue 1
    }
    
    int arrival = 0; // initialize arrival time to zero
    int counter = 0; //initialize timer to zero
    int total_wait = 0; //initialize total wait time to zero
    int total_turnaround = 0; //initialize total turnaround time to zero
    int total_response = 0; //initialize total response time to zero
    int x = 0; //variable to store size of queue 1
    int y = 0; //variable to store size of queue 2
    int z = 0; //variable to store size of queue 3
    int i = 0; //variable to iterate queue 2
    int j = 0; //variable to iterate queue 3
    
    //Queue 2 with RR algorithm with 16ms time quantum
    struct Process** Queue2 = malloc(sizeof(struct Process*)*SIZE);
    //Queue 3 with FCFS scheduling
    struct Process** Queue3 = malloc(sizeof(struct Process*)*SIZE);
    
    int executed = 0; //total executed processes
    while (executed!=SIZE) { //while not all processes are executed
        if (x < SIZE){ //if queue 1 has processes
            Queue1[x]->response = counter; //response time for each process
            total_response += counter; //calculate response time
            if(remaining_cpu[Queue1[x]->num] <= 8){ //if remaining time is less than 8ms
                
                counter += remaining_cpu[Queue1[x]->num]; //increase timer to remaining time for process
                executed++; //increase number of executed processes by 1
                Queue1[x]->waiting = counter - Queue1[x]->cpu_burst;  //waiting time for each process
                Queue1[x]->turnaround = Queue1[x]->cpu_burst + Queue1[x]->waiting; //turnaround time for each process
                total_wait += counter - Queue1[x]->cpu_burst; //calculate total wait time
                total_turnaround += Queue1[x]->cpu_burst + Queue1[x]->waiting; //calculate total turnaround time
                remaining_cpu[Queue1[x++]->num] = 0; //set remaining time of process to zero
            }
            else{
                counter += 8; //set timer to quantum of queue 1
                Queue2[y++] = Queue1[x]; //move process to queue 2
                remaining_cpu[Queue1[x++]->num] -= 8; //set remaining time of process
            }
        }
        else if (i < y){  //if queue 2 has processes
            if(remaining_cpu[Queue2[i]->num] <= 16){ //if remaining time is less than 16ms
                
                counter += remaining_cpu[Queue2[i]->num]; //increase timer to remaining time for process
                Queue2[i]->waiting = counter - Queue2[i]->cpu_burst;  //waiting time for each process
                Queue2[i]->turnaround = Queue2[i]->cpu_burst + Queue2[i]->waiting; //turnaround time for each process
                total_wait += counter - Queue2[i]->cpu_burst; //calculate total wait time
                total_turnaround += Queue2[i]->cpu_burst + Queue2[i]->waiting; //calculate total turnaround time
                remaining_cpu[Queue2[i++]->num] = 0; //set remaining time of process to zero
                executed++; //increase number of executed processes by 1
            }
            else{
                counter += 16; //set timer to quantum of queue 2
                Queue3[z++] = Queue2[i]; //move process to queue 3
                remaining_cpu[Queue2[i++]->num] -= 16; //set remaining time of process
            }
        }
        else if(j < z){ //if queue 3 has processes
            
            counter += remaining_cpu[Queue3[j]->num]; //set timer to remaining time of process
            Queue3[j]->waiting = counter - Queue3[j]->cpu_burst;  //waiting time for each process
            Queue3[j]->turnaround = Queue3[j]->cpu_burst + Queue3[j]->waiting; //turnaround time for each process
            total_wait += counter - Queue3[j]->cpu_burst; //calculate total wait time
            total_turnaround += Queue3[j]->cpu_burst + Queue3[j]->waiting; //calculate total turnaround time
            remaining_cpu[Queue3[j++]->num] = 0; //set remaining time of process to zero
            executed++; //increase number of executed processes by 1
        }
    }
    printf("---------------------------------------------------\n\n");
    for(int i=0; i<SIZE; i++){
        printf("     ______________________________________\n");
        printf("    |\t       PCB-PROCESS %d               |\n",(i+1));
        printf("    |______________________________________|\n");
        printf("    |>> Burst time     [process %d] : %.2d    |\n", processes[i]->num +1, processes[i]->cpu_burst);
        printf("    |>> Waiting time   [process %d] : %.2d    |\n", processes[i]->num +1, processes[i]->waiting);
        printf("    |>> Trnaround time [process %d] : %.2d    |\n", processes[i]->num +1, processes[i]->turnaround);
        printf("    |>> Response time  [process %d] : %.2d    |\n", processes[i]->num +1, processes[i]->response);
        printf("    |______________________________________|\n");
        printf("\n");
    }
    
    //Print average waiting, turnaround and response time for all processes
    printf("---------------------------------------------------\n\n");
    printf("     ______________________________________\n");
    printf("    |                                      |\n");
    printf("    |(1) Average waiting time : %.2f      |\n", (float)total_wait / (float)SIZE);
    printf("    |______________________________________|\n");
    printf("\n");
    printf("     ______________________________________\n");
    printf("    |                                      |\n");
    printf("    |(2) Average turnaround time : %.2f   |\n", (float)total_turnaround / (float)SIZE);
    printf("    |______________________________________|\n");
    printf("\n");
    printf("     ______________________________________\n");
    printf("    |                                      |\n");
    printf("    |(3) Average response time : %.2f      |\n", (float)total_response / (float)SIZE);
    printf("    |______________________________________|\n");
    printf("\n");
    printf("     ______________________________________\n");
    printf("    |                                      |\n");
    printf("    |(4) Throughput : %.2f                 |\n", (float)SIZE / (float)counter);
    printf("    |______________________________________|\n");
    return 0;
}