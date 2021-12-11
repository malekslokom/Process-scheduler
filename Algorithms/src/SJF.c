#include "../../main.h"

void SJF(Node* processList,int n)
{
    int i, finishedProcess = 0, ganttCounter = 0;
    int count = 0;
    GanttList* gantt=NULL;
    GanttProcess GanttProccess;
    Node* processListCopy=NULL;
    Node* processListCopyIndex=NULL;

    printf("\n Process Scheduling: SJF-Shortest Job First \n");

    while (finishedProcess < n)
    {
        int min = 10000, index = -1;
        processListCopy=processList;
        // Find the process with the shortest arrival time and shortest burst time
        // And save his index
        for (i = 0; i < n; i++)
        {
            if (processListCopy->process.TE == min)
            {
                if (processListCopy->process.TA < processListCopyIndex->process.TA)
                    index = i;
            }else if (processListCopy->process.TE < min)
            {
                if (processListCopy->process.TA <= count)
                {
                    min = processListCopy->process.TE;
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
            
            // Set the executed process burst time to 10001
            processListCopyIndex->process.TE = 10001;

            finishedProcess++;
            
        }
        else{
            // CPU Idle

            // Save the CPU Idle time detail in "GanttProccess"
            GanttProccess.Start=count;
            GanttProccess.Name="Idle";
            GanttProccess.Finished=0;
            // Update the CPU execution time
            count++;
            GanttProccess.End = count;

            // Add the CPU Idle time to Gantt linked list
            addLastGantt(&gantt,GanttProccess);
            ganttCounter++;
        }
    }
    // Print the gantt chart
    GanttDisplay(gantt, ganttCounter);
}


int main(int argc, char *argv[])
{
    getProcessListFromFile(argv[1]);
    SJF(processList, processListLength);
    char path[] = "./main ";
    strcat(path, argv[1]);
    system(path);
    return 0;
}