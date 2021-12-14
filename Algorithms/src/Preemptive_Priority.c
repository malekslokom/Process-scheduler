#include "../../main.h"

void Preemptive_Priority(Node* processList,int n)
{
    int i, finishedProcess=0,done=1,ganttCounter=0;
    int count = 0, prev = -1, dec = 0;
    GanttList* gantt=NULL;
    GanttProcess GanttProccess;
    Node* processListCopy=processList;
    Node* processListCopyIndex=NULL;

    // Save the processes priority in a dynamic table
    int* PriorityTable =  malloc(n * sizeof(int));
    // Save the processes burst in a dynamic table
    int* burstTime =  malloc(n * sizeof(int));
    for (i = 0; i < n; i++)
    {
        PriorityTable[i] = processListCopy->process.PR;
        burstTime[i] = processListCopy->process.TE;
        processListCopy=processListCopy->next;
    }
    

    printf("\n Process Scheduling: Preemptive Priority \n");

    while (finishedProcess < n)
    {
        int max = -10, index = -1;
        processListCopy=processList;

        for (i = 0; i < n; i++)
        {
            // Find the process with the shortest arrival time and the highest priority
            // And save his index
            if (PriorityTable[i] == max && burstTime[i] > 0)
            {
                if (processListCopy->process.TA < processListCopyIndex->process.TA)
                    index = i;
            }

            else if (PriorityTable[i] > max && burstTime[i] > 0)
            {
                if (processListCopy->process.TA <= count)
                {
                    max = PriorityTable[i];
                    index = i;
                }
            }

            // Find the process struct in the process linked list
            processListCopyIndex=processList;
            for(int j=0;j<index;j++)
                processListCopyIndex=processListCopyIndex->next;

            processListCopy=processListCopy->next;
        }
    
        if (index != -1)
        {
            burstTime[index] -= 1;
            if (index != prev){
                if (done==0){
                    // In case of interruption mark the process as not finished
                    GanttProccess.Finished=0;

                    // Add the executed process to Gantt linked list
                    addLastGantt(&gantt,GanttProccess);
                    ganttCounter++;
                }
                // Save executed process details in "GanttProccess"
                GanttProccess.Start=count;
                GanttProccess.Name=processListCopyIndex->process.Name;
                done=0;
            }
        }
        else
        {
            if (dec == 0){
                //CPU Idle
                // Save the CPU Idle time detail in "GanttProccess"
                GanttProccess.Start=count;
                GanttProccess.Name= "  ";
                GanttProccess.Finished=0;
                // Add the CPU Idle time to Gantt linked list
                addLastGantt(&gantt,GanttProccess);
                ganttCounter++;
            }
            dec = 1;
        }
        // Update the CPU execution time
        count++;

        if (burstTime[index] == 0 && index != -1)
        {
            finishedProcess++;
            dec = 0;
            // In case the process is finished
            done=1;
            // Save executed process details in "GanttProccess"
            GanttProccess.End=count;
            GanttProccess.Finished=1;
            // Add the executed process to Gantt linked list
            addLastGantt(&gantt,GanttProccess);
            ganttCounter++;
        }
        prev = index;
        
    }
    // Print the gantt chart
    GanttDisplay(gantt,ganttCounter);
}

int main(int argc, char *argv[])
{
    getProcessListFromFile(argv[1]);
    Preemptive_Priority(processList, processListLength);
    char path[] = "./main ";
    strcat(path, argv[1]);
    system(path);
    return 0;
}