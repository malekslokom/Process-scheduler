#include "main.h"

//This function gets algorithms names from files names 
void GetFilesName(Algorithm* *AlgorithmsList, int *algoNb)
{
    struct dirent *dir;
    // opendir() returns a pointer of type DIR.
    DIR *d = opendir("./Algorithms/src");
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            if ((dir->d_name[strlen(dir->d_name) - 1] == 'c') && (dir->d_name[strlen(dir->d_name) - 2] == '.') && (strcmp(dir->d_name, "main.c") != 0))
            {
                char *filename = malloc(strlen(dir->d_name));
                //Delete the file extension 
                strncpy(filename, dir->d_name, strlen(dir->d_name) - 2);
                //Add the algorithm name to algorithm linked list
                addLastAlgorithm(AlgorithmsList,filename);
                *algoNb = *algoNb + 1;
            }
        }
        closedir(d);
    }
}


int main(int argc, char *argv[])
{
    Algorithm* AlgorithmsList=NULL;
    Algorithm* AlgorithmsListCopy=NULL;
    int algoNb = 0;

    // Save all processes in the config file in process linked list
    getProcessListFromFile(argv[1]);

    
    if (processListLength != -1)
    {
        // Print process list
        ProcessListPrint(processList, processListLength);

        // Dynamic Menu
        int menuChoice;
        int algoNameCounter = 0;
        //Get algorithms names from files names 
        GetFilesName(&AlgorithmsList, &algoNb);

        // Print the dynamic menu
        do
        {
            printf("*********************      Menu       ***********************\n");
            printf("Select an option: \n");
            AlgorithmsListCopy=AlgorithmsList;

            // print algorithms names
            for (algoNameCounter = 0; algoNameCounter < algoNb; algoNameCounter++)
            {
                printf("  %d) %s \n", algoNameCounter + 1, AlgorithmsListCopy->algoName);
                AlgorithmsListCopy=AlgorithmsListCopy->next;
            }
            // Add "Quit" option
            printf("  %d) Quit \n", algoNameCounter + 1);
            // Read user choice
            scanf("%d", &menuChoice);
            if (menuChoice - 1 < algoNb)
            {
                // Find the chosen algorithm build path
                char path[] = "Algorithms/build/";
                AlgorithmsListCopy=AlgorithmsList;
                for(int i=0;i<menuChoice - 1;i++)
                    AlgorithmsListCopy=AlgorithmsListCopy->next;
                
                strcat(path, AlgorithmsListCopy->algoName);
                strcat(path, " ");
                strcat(path, argv[1]);

                // Execute the algorithm chosen by the user
                system(path);
            }
        } while ((menuChoice - 1 != algoNb));// Quit if user chose "Quit" menu option
    }
    else
    {
        // file empty
        printf("The file is empty \n");
    }
}