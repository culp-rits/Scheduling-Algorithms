#include<stdio.h>

struct process{
    int id, arrival_time, burst_time,completion_time, turnaround_time,waiting_time;
}p[10],temp;

int n;

void fcfs(){
    for(int i=0;i<n;i++)
        for(int j=i+1; j<n; j++)
            if(p[i].arrival_time > p[j].arrival_time){
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
    for (int i = 0; i < n; i++)
        if(i==0){
            p[i].completion_time = p[i].burst_time;
            p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
            p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
        }
        else{    
            p[i].completion_time = p[i-1].completion_time + p[i].burst_time;
            p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
            p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
        }
}

void times(){
    float time=0;
    for(int i=0; i<n; i++)
        time+=p[i].waiting_time;
    time=time/n;
    printf("\naverage waiting time : %f",time);
    time=0;
    for(int i=0; i<n; i++)
        time+=p[i].turnaround_time;
    time=time/n;
    printf("\naverage turnaround time : %f",time);
}

void gant(){
    printf("\ngant chart\n");
    for(int i=0; i<n; i++)
        printf("    P%d\t",i);
    printf("\n0");
    for(int i=0; i<n; i++)
        printf("\t%d",p[i].completion_time);
}

void table(){
    printf("\n");
    for(int i=0;i<n;i++)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",p[i].id,p[i].arrival_time,p[i].burst_time,p[i].completion_time,p[i].turnaround_time,p[i].waiting_time);
}

int main(){
    printf("enter the number of process : ");
    scanf("%d", &n);
    for(int i=0; i<n; i++){
        printf("process id : ");
        scanf("%d", &p[i].id);
        printf("arrival time : ");
        scanf("%d", &p[i].arrival_time);
        printf("burst time : ");
        scanf("%d", &p[i].burst_time);
    }
    fcfs();
    table();
    gant();
    times();
}
