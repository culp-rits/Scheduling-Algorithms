#include<stdio.h>
//header file

struct process{
    int id, index, priority, arrival_time, burst_time,completion_time, turnaround_time,waiting_time;
}p[10],q[10],temp;
//defining the structure of process

int l=0,m=0,n,total_time=0,g[100];
//declaring number of processes, iterators, etc.

void priority_queue(){
    for(int i=0;i<m;i++)
        for(int j=i+1; j<m; j++)
            if(q[i].priority > q[j].priority){
                temp = q[i];
                q[i] = q[j];
                q[j] = temp;
            }
}
//sorting the ready queue based on the priority of processes

void enq(){
    q[m] = temp;
    m++;
    priority_queue();
}
//enqueue new process

void deq(){
    for(int i=1; i<m; i++)
        q[i-1]=q[i];
    m--;
}
//dequeue the finished process

void pp(){
    for(int i=0;i<n;i++)
        for(int j=i+1; j<n; j++)
            if(p[i].arrival_time > p[j].arrival_time){
                int x,y;
                x = p[i].index;
                y = p[j].index;
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
                p[i].index = x;
                p[j].index = y;
            }
    //marking the index values
    
    int anchor = 0;
    for (int i = 0; i < total_time; i++){
        while(i==p[anchor].arrival_time){
            temp = p[anchor];
            enq();
            anchor++;
        }
        //checking if any process arrives
        
        q[0].burst_time--;
        g[l] = q[0].id;
        l++;
        //updating gant chart and process taking place
        
        if(q[0].burst_time==0){
            p[q[0].index].completion_time = i+1;
            deq();
        }
        //checking if any process has been completed
        
    }
    for (int i = 0; i < n; i++){
        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
        p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
    }
    //computing turnaround and waiting time
}

void times(){
    float time=0;
    for(int i=0; i<n; i++)
        time+=p[i].waiting_time;
    time=time/n;
    printf("\naverage waiting time : %f",time);
    //computing average waiting time
    
    time=0;
    for(int i=0; i<n; i++)
        time+=p[i].turnaround_time;
    time=time/n;
    printf("\naverage turnaround time : %f",time);
    //computing average turnaround time
}

void gant(){
    printf("\ngant chart\n");
    for(int i=0; i<total_time; i++)
        printf("    P%d\t",g[i]);
    printf("\n");
    for(int i=0; i<total_time+1; i++)
        printf("%d\t",i);
    //printing gant chart  
}

void table(){
    printf("\n");
    for(int i=0;i<n;i++)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",p[i].id,p[i].arrival_time,p[i].burst_time,p[i].completion_time,p[i].turnaround_time,p[i].waiting_time);
    //printing the completed table
}

int main(){
    printf("enter the number of process : ");
    scanf("%d", &n);
    for(int i=0; i<n; i++){
        printf("process id : ");
        scanf("%d", &p[i].id);
        printf("priority : ");
        scanf("%d", &p[i].priority);
        printf("arrival time : ");
        scanf("%d", &p[i].arrival_time);
        printf("burst time : ");
        scanf("%d", &p[i].burst_time);
        p[i].index = i;
        total_time+=p[i].burst_time;
    }
    //input for all process
    
    pp();
    table();
    gant();
    times();
    //prints table, gant chart and metrics
}
