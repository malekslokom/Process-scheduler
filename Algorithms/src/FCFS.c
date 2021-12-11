#include "../../main.h"

void FCFS(Node* processList,int n)
{
    
    int i,Count_CPU=0,ganttCounter=0;
    GanttList* gantt=NULL;
    GanttProcess GanttProccess;
    Node* l=processList;

    // Sort process linked list using arrival time
    sortTA(processList);

    printf("\n");
    printf("Process Scheduling: FCFS- First Come First Serve \n");
    

    for (i=0;i<n;i++)
    {
        if (l->process.TA<= Count_CPU){
            // Update the CPU execution time
            Count_CPU=Count_CPU+l->process.TE;

            // Save executed process details in "GanttProccess"
            GanttProccess.Start=Count_CPU-l->process.TE;
            GanttProccess.End=Count_CPU;
            GanttProccess.Name=l->process.Name;
            GanttProccess.Finished=1;

            // Add the executed process to Gantt linked list
            addLastGantt(&gantt,GanttProccess);
            ganttCounter++;
        }else{
            //CPU Idle

            // Save the CPU Idle time detail in "GanttProccess"
            GanttProccess.Start=Count_CPU;
            GanttProccess.End=l->process.TA;
            GanttProccess.Name="Idle";
            GanttProccess.Finished=0;

            // Add the CPU Idle time to Gantt linked list
            addLastGantt(&gantt,GanttProccess);
            ganttCounter++;

            // Update the CPU execution time
            Count_CPU=l->process.TA+l->process.TE;
        }
        l=l->next;
    }
    // Print the gantt chart
   GanttDisplay(gantt,ganttCounter);
}

int main(int argc, char *argv[]){
    getProcessListFromFile(argv[1]);
    FCFS(processList,processListLength);
    char path[] = "./main ";
    strcat(path, argv[1]);
    system(path);
    return 0;
}