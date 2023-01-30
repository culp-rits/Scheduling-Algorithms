#include<stdio.h>

struct process{
    int id, index, arrival_time, burst_time,completion_time, turnaround_time,waiting_time;
}p[10],q[10],temp;

int l=0,m=0,n,total_time=0,g[100];

void priority_queue(){
    for(int i=0;i<m;i++)
        for(int j=i+1; j<m; j++)
            if(q[i].burst_time > q[j].burst_time){
                temp = q[i];
                q[i] = q[j];
                q[j] = temp;
            }
}

void enq(){
    q[m] = temp;
    m++;
    priority_queue();
}

void deq(){
    for(int i=1; i<m; i++)
        q[i-1]=q[i];
    m--;
}

void sjfp(){
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
    int anchor = 0;
    for (int i = 0; i < total_time; i++){
        while(i==p[anchor].arrival_time){
            temp = p[anchor];
            enq();
            anchor++;
        }
        q[0].burst_time--;
        g[l] = q[0].id;
        l++;
        if(q[0].burst_time==0){
            p[q[0].index].completion_time = i+1;
            deq();
        }
    }
    for (int i = 0; i < n; i++){
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
    for(int i=0; i<total_time; i++)
        printf("    P%d\t",g[i]);
    printf("\n");
    for(int i=0; i<total_time+1; i++)
        printf("%d\t",i);
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
        p[i].index = i;
        total_time+=p[i].burst_time;
    }
    sjfp();
    table();
    gant();
    times();
}
