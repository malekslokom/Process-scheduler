#include "../../main.h"

void RR(Node* processList,int n)
{
    int i, finishedProcess = 0, Q, len = 0;
    int* burstTime=malloc(n * sizeof(int));
    
    // Front: the head of the pending processes table
    // Rear:  the end of the pending processes table
    int count = 0, front = 0, rear = -1, dec = 0, ganttCounter = -1; 

    GanttList* gantt=NULL;
    GanttProcess GanttProccess;
    Node* processListCopy=processList;
    Node* processListCopyIndex=NULL;

    printf("\n Enter time Quantum:\n");
    scanf("%d", &Q);

    // Save the processes burst time in a dynamic table
    // Save the sum of burst times
    for (i = 0; i < n; i++)
    {
        len += processListCopy->process.TE;
        burstTime[i] = processListCopy->process.TE;
        processListCopy=processListCopy->next;
    }

    // Table of processes waiting to execute (pending processes)
    int* ready=malloc(len * sizeof(int));
    
    printf("\n Process Scheduling: RR- Round Robin \n");
    while (finishedProcess < n)
    {
        //prevfinishedProcess = finishedProcess;
        int found = 0;
        if (front > rear)
        {
            processListCopy=processList;
            for (i = 0; i < n; i++){
                if (processListCopy->process.TA == count)
                {
                    // Save the Arrived processes in the pending processes table
                    ready[++rear] = i;
                    found = 1;
                }

                processListCopy=processListCopy->next;
            }

            if (found == 0)
            {
                //CPU Idle
                if (dec == 0)
                {
                    //CPU Idle
                    // Save the CPU Idle time detail in "GanttProccess"
                    GanttProccess.Start = count;
                    GanttProccess.Name =  "  ";

                    // Add the CPU Idle time to Gantt linked list
                    addLastGantt(&gantt,GanttProccess);
                    ganttCounter++ ;
                    dec = 1;
                }
                // Update the CPU execution time
                count++;
            }
        }
        else
        {
            int k, index = ready[front++];
            dec = 0;

            // Find the process struct in the process linked list
            processListCopyIndex = processList;
            for (int j = 0; j < index; j++)
                processListCopyIndex = processListCopyIndex->next;

            // Save executed process details in "GanttProccess"
            ganttCounter = ganttCounter + 1;
            GanttProccess.Start = count;
            GanttProccess.Name = processListCopyIndex->process.Name;

            
            if (burstTime[index] <= Q)
            {
                // Finish the remaining burst time if it's less than the quantum
                for (k = 0; k < burstTime[index]; k++)
                {
                    processListCopy=processList;
                    count++;
                    for (i = 0; i < n; i++)
                    {
                        if (processListCopy->process.TA == count)
                            ready[++rear] = i;
                        processListCopy=processListCopy->next;
                    }
                }
                //Process finished
                burstTime[index] = 0;
                GanttProccess.End = count;
                GanttProccess.Finished = 1;

                finishedProcess++;
            }
            else{
                // Execute quantum if the burst time is higher than the quantum
                for (k = 0; k < Q; k++)
                {
                    count++;
                    processListCopy=processList;
                    for (i = 0; i < n; i++)
                    {
                        // Save the Arrived processes in the pending processes table
                        if (processListCopy->process.TA == count)
                            ready[++rear] = i;

                        processListCopy=processListCopy->next;
                    }
                }

                // Reduce remaining burst time
                burstTime[index] -= Q;
                ready[++rear] = index;

                GanttProccess.End = count;
                GanttProccess.Finished = 0;
            }
      
            // Add the executed process to Gantt linked list
            addLastGantt(&gantt,GanttProccess);
        }

    }
            //addLastGantt(&gantt,GanttProccess);
            ganttCounter++;

    // Print the gantt chart
    GanttDisplay(gantt,ganttCounter);
    ganttCounter++;
}
int main(int argc, char *argv[])
{
    getProcessListFromFile(argv[1]);
    RR(processList, processListLength);
    char path[] = "./main ";
    strcat(path, argv[1]);
    system(path);
    return 0;
}