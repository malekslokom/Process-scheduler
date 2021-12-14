#include "../../main.h"

void Non_Preemptive_Priority(Node* processList,int n)
{
    int i, finishedProcess = 0, count = 0, dec = 0,ganttCounter=0;
    GanttList* gantt=NULL;
    GanttProcess GanttProccess;
    Node* processListCopy=processList;
    Node* processListCopyIndex=NULL;

    int* PriorityTable =  malloc(n * sizeof(int));

    // Save the processes priority in a dynamic table
    for (i = 0; i < n; i++){
        PriorityTable[i] = processListCopy->process.PR;
        processListCopy=processListCopy->next;
    }

    printf("\n");
    printf("Process Scheduling: Non Preemptive Priority \n");
    
    while (finishedProcess < n)
    {
        int max = -1, index = -1;
        processListCopy=processList;
        // Find the process with the shortest arrival time and the highest priority
        // And save his index
        for (i = 0; i < n; i++)
        {
            if (PriorityTable[i] == max)
            {
                if (processListCopy->process.TA < processListCopyIndex->process.TA){
                    index = i;
                }
            }
            else if (PriorityTable[i] > max)
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
            // Save executed process details in "GanttProccess"
            GanttProccess.Start=count;
            GanttProccess.End=count+processListCopyIndex->process.TE;
            GanttProccess.Name=processListCopyIndex->process.Name;
            GanttProccess.Finished=1;

            // Add the executed process to Gantt linked list
            addLastGantt(&gantt,GanttProccess);
            ganttCounter++;
            
            // Update the CPU execution time
            count += processListCopyIndex->process.TE;
            
            finishedProcess++;

            // Set the executed process priotrity to -2
            PriorityTable[index] = -2;
            dec = 0;
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
            // Update the CPU execution time
            count++;
            dec = 1;
        }
        
    }
    // Print the gantt chart
    GanttDisplay(gantt,ganttCounter);
}

int main(int argc, char *argv[])
{
    getProcessListFromFile(argv[1]);
    Non_Preemptive_Priority(processList, processListLength);
    char path[] = "./main ";
    strcat(path, argv[1]);
    system(path);
    return 0;
}