#include "../../main.h"
 
 
void permut(processStruct *A, processStruct *B)
{
  processStruct tmp;
  tmp = *A;
  *A = *B;
  *B = tmp;
}
void SRT(Node* processList,int n)
{

  int i, j, id, gantt[100][3], c, Counter = 0, TimeCPU = 0, tmp;
  //  gantt matrice de la forme:
  //  Processus_Id     Temps_de_debut_d'execution    Terminer(0:Name /1:Oui)
  //  Processus_Id: si le nom de processus=P1 alors id=1, -1 si processus Idle
  int* Burst =  malloc(n * sizeof(int));
  Node* processListCopy=processList;
  Node* processListCopyFirst=processList;

  for (i = 0; i < n; i++)
  {
    Burst[i] = processListCopy->process.TE;
    processListCopy=processListCopy->next;
  }

  while (1)
  {
    processListCopy=processList->next;
    // deplacer le processus qui admet le TE et TA minimale à la 1ere case de tableau
    for (i = 1; i < n; i++)
    {

      if ((Burst[0] == 0 || TimeCPU < processListCopyFirst->process.TA ? 1 : Burst[i] < Burst[0] || (Burst[i] == Burst[0] && processListCopy->process.TA < processListCopyFirst->process.TA)) && (TimeCPU >= processListCopy->process.TA) && (Burst[i] != 0))
      {
        permut(&processListCopyFirst->process, &processListCopy->process);
        tmp = Burst[0];
        Burst[0] = Burst[i];
        Burst[i] = tmp;
      }
      processListCopy=processListCopy->next;
    }

    if (Burst[0] == 0 || processListCopyFirst->process.TA > TimeCPU)
    {
      // CPU Idle
      if (Counter == 0 || gantt[Counter - 1][0] != -1)
      {

        gantt[Counter][0] = -1;
        gantt[Counter++][1] = TimeCPU;
      }
    }
    else if (Burst[0] != 0)
    {

      id = atoi(strtok(processListCopyFirst->process.Name, "P"));
      if (Counter == 0 || gantt[Counter - 1][0] != id)
      {
        gantt[Counter][0] = id;
        gantt[Counter][2] = 0;
        gantt[Counter++][1] = TimeCPU;
      }
      Burst[0] = Burst[0] - 1;

      if (Burst[0] == 0)
      {
        //terminer=1
        gantt[Counter - 1][2] = 1;
      }
    }

    TimeCPU++;
    c = 0;

    for (i = 0; i < n; i++)
    {
      if (Burst[i] != 0)
        c = 1;
    }

    if (c == 0)
      //Tous les processus sont finis
      break;
  }
  gantt[Counter][1] = TimeCPU;
  printf("Process Scheduling: SRT- Shortest Remaining Time \n");
  printf("\n");
  printf("Gantt Chart \n");
  
  //affichage de Gantt Chart
  for (i = 0; i < Counter; i++)
  {
    printf("+--");
    for (j = 0; j < gantt[i + 1][1] - gantt[i][1]; j++)
      printf("--");
  }
  printf("+\n");
  for (i = 0; i < Counter; i++)
  {
    printf("\033[0m");
    printf("|");
    if (gantt[i][2] == 1)
    {
      printf("\033[41;37m");
      if(gantt[i][0]!=-1)
        printf("P%d", gantt[i][0]);
      else
        printf("  ");
      printf("\033[0m");
    }
    else
    {
      printf("\033[0m");
      if(gantt[i][0]!=-1)
        printf("P%d", gantt[i][0]);
      else
        printf("  ");
    }
    for (j = 0; j < gantt[i + 1][1] - gantt[i][1]; j++)
    {
      if (gantt[i][2] == 1)
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
  }
  printf("| \n");
  for (i = 0; i < Counter; i++)
  {
    printf("+--");
    for (j = 0; j < gantt[i + 1][1] - gantt[i][1]; j++)
      printf("--");
  }
  printf("+\n");
  for (i = 0; i < Counter; i++)
  {
    if (gantt[i][1] < 10)
      printf("%d  ", gantt[i][1]);
    else
      printf("%d ", gantt[i][1]);
    for (j = 0; j < gantt[i + 1][1] - gantt[i][1]; j++)
      printf("  ");
  }
  printf("%d \n", gantt[Counter][1]);
}

int main(int argc, char *argv[])
{
  getProcessListFromFile(argv[1]);
  SRT(processList, processListLength);
  char path[] = "./main ";
  strcat(path, argv[1]);
  system(path);
  return 0;
}