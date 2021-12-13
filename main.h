#include <stdio.h>
#include <sched.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <dirent.h>

// Process struct
typedef struct processStruct
{
    char Name[100]; // Process name
    int TA; // Arrival time
    int TE; // Burst time
    int PR; // Priority
} processStruct;


// A linked list node
typedef struct Node
{
    processStruct process;
    struct Node *next;
} Node;


// This function prints contents of process linked list
void printList(Node *n)
{
    while (n != NULL)
    {
        printf(" %s %d %d %d ", n->process.Name, n->process.TA, n->process.TE, n->process.PR);
        n = n->next;
    }
}

// This function return the length of process linked list
int length(Node *list)
{
    int length = 0;
    Node *current;
    for (current = list; current != NULL; current = current->next)
    {
        length++;
    }
    return length;
}


// This function sort process linked list using arrival time
void sortTA(Node *list)
{
    int i, j, k;
    processStruct tempData;
    Node *current;
    Node *next;
    int size = length(list);
    k = size;
    for (i = 0; i < size - 1; i++, k--)
    {
        current = list;
        next = list->next;
        for (j = 1; j < k; j++)
        {
            if (current->process.TA > next->process.TA)
            {
                // Permut processes
                tempData = current->process;
                current->process = next->process;
                next->process = tempData;
            }
            current = current->next;
            next = next->next;
        }
    }
}

// This function add an item at the end of process linked list
void addLast(Node **head, processStruct val)
{
    // Create a new node
    Node* newNode = malloc(sizeof(Node));
    newNode->process = val;
    newNode->next   = NULL;
    
    if(*head == NULL)
        // If head is NULL, use the new node as head
         *head = newNode;
    else
    {
        // Insert at the end of the list
        Node *lastNode = *head;
        //find the last node
        while(lastNode->next != NULL)
        {
            lastNode = lastNode->next;
        }
        // Add the newNode at the end of the linked list
        lastNode->next = newNode;
    }
}

// All processes in the config file will be saved in this list 
Node *processList = NULL;

// Process list length
int processListLength = -1;

// This function saves all processes in the config file in process linked list
void getProcessListFromFile(char *fileName)
{
    // Read the config file
    FILE *file = fopen(fileName, "r");
    char line[256];
    processStruct proc;
    if (file == NULL)
    {
        //Alert the user if the file doesn't exist
        printf("The file: %s doesn't exist \n", fileName);
    }
    else
    {
        // File exist
        while (fgets(line, sizeof(line), file))
        {
            // First character of the line
            char firstChar = line[0];

            // Check if line is empty or is a comment
            if ((firstChar != '/') && (strlen(line) > 2))
            {
                // Separator
                char d[] = ";";

                // Save process details in "proc"
                strcpy(proc.Name, strtok(line, d));
                proc.TA = atoi(strtok(NULL, d));
                proc.TE = atoi(strtok(NULL, d));
                proc.PR = atoi(strtok(NULL, d));

                // Add the process to our linked list "processList"
                processListLength = processListLength + 1;
                addLast(&processList, proc);
            }
        }
        processListLength = processListLength + 1;
    }
}

// This function print the process list
void ProcessListPrint(Node* processList, int processListLength)
{
    Node* processListCopy=processList;
    printf("\n");
    printf("******************  Table of processes  ********************\n");
    printf("\n");
    printf("+-----------------------------------------------------------+\n");
    printf("|  Processes  |  Arrival time  |  Brust time  |  Priority   | \n");
    printf("+-------------+----------------+--------------+-------------+\n");
    for (int i = 0; i < processListLength; i++)
    {

        printf("|   %s        |   %d            |   %d          |   %d         | \n", processListCopy->process.Name, processListCopy->process.TA, processListCopy->process.TE, processListCopy->process.PR);
        printf("+-------------+----------------+--------------+-------------+\n");
        processListCopy=processListCopy->next;
    }
    printf("\n");
}

/////////////////////////////   ALGORITHMS   ////////////////////////////////////////////////

// A linked list Algorithm
typedef struct Algorithm
{
    char *algoName; // Algorithm name
    struct Algorithm *next;
} Algorithm;

// This function add an item at the end of gantt linked list
void addLastAlgorithm(Algorithm **head, char* val)
{
    //create a new node
    Algorithm* newNode = malloc(sizeof(Algorithm));
    newNode->algoName = val;
    newNode->next   = NULL;

    if(*head == NULL)
        //If head is NULL, use the new node as head
         *head = newNode;
    else
    {
        //Insert at the end of the list
        Algorithm *lastNode = *head;

        //find the last node
        while(lastNode->next != NULL)
        {
            lastNode = lastNode->next;
        }

        //Add the newNode at the end of the linked list
        lastNode->next = newNode;
    }

}



//////////////////////////////   GANTT   /////////////////////////////////////////////
typedef struct GanttProcess
{
    char *Name; // Process name
    int Start; // Execution start time
    int End;   // Execution end time
    int Finished; // Has burst time finished (0/1)
} GanttProcess;

// A linked list GanttList
typedef struct GanttList
{
    GanttProcess process;
    struct GanttList *next;
} GanttList;
// This function return the length of gantt linked list
int lengthGantt(GanttList *list)
{
    int length = 0;
    GanttList *current;
    for (current = list; current != NULL; current = current->next)
    {
        length++;
    }
    return length;
}
// This function prints contents of gantt linked list
void printListGantt(GanttList *n)
{
    while (n != NULL)
    {
        printf(" %s %d %d %d ", n->process.Name, n->process.Start, n->process.End, n->process.Finished);
        n = n->next;
    }
}

// This function add an item at the end of a linked list
void addLastGantt(GanttList* *head, GanttProcess val)
{
    //create a new node
    GanttList* newNode = malloc(sizeof(GanttList));
    newNode->process = val;
    newNode->next   = NULL;

    if(*head == NULL)
        //If head is NULL, use the new node as head
         *head = newNode;
    else
    {
        //Insert at the end of the list
        GanttList* lastNode = *head;

        //find the last node
        while(lastNode->next != NULL)
        {
            lastNode = lastNode->next;
        }

        //Add the newNode at the end of the linked list
        lastNode->next = newNode;
    }
}


// Display Gantt chart in console with colors
// red color if the process finished
void GanttDisplay(GanttList *ganttList, int ganttCounter)
{
    int i, j;
    GanttList *gantt = ganttList;
    printf("\n");
    printf("Gantt Chart \n");

    for (i = 0; i < ganttCounter; i++)
    {
        printf("+--");
        for (j = 0; j < gantt->process.End - gantt->process.Start; j++)
            printf("--");
        gantt = gantt->next;
    }
    printf("+\n");
    gantt = ganttList;
    for (i = 0; i < ganttCounter; i++)
    {
        printf("\033[0m");
        printf("|");
        if (gantt->process.Finished == 1)
        {
            // process finished
            printf("\033[41;37m");
            printf("%s", gantt->process.Name);
            printf("\033[0m");
        }
        else
        {
            // process not finished
            printf("\033[0m");
            printf("%s", gantt->process.Name);
        }
        for (j = 0; j < gantt->process.End - gantt->process.Start; j++)
        {
            if (gantt->process.Finished == 1)
            {
                printf("\033[41;37m");
                printf("  ");
                printf("\033[0m");
            }
            else
            {
                printf("\033[0m");
                printf("  ");
            }
        }
        gantt=gantt->next;
    }
    printf("| \n");
    gantt = ganttList;
    for (i = 0; i < ganttCounter; i++)
    {
        printf("+--");
        for (j = 0; j < gantt->process.End - gantt->process.Start; j++)
            printf("--");
        gantt=gantt->next;
    }
    printf("+\n");
    gantt = ganttList;
    for (i = 0; i < ganttCounter; i++)
    {
        if (gantt->process.Start < 10)
            printf("%d  ", gantt->process.Start);
        else
            printf("%d ", gantt->process.Start);
        for (j = 0; j < gantt->process.End - gantt->process.Start; j++)
            printf("  ");
        gantt=gantt->next;
    }
    gantt = ganttList;
    for(i=0;i<ganttCounter - 1;i++)
        gantt=gantt->next;
    printf("%d \n", gantt->process.End);
}

