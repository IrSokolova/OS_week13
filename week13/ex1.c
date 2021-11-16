#include <stdio.h>

typedef struct process{
    int allocation[3];
    int request[3];
    int complete;
} process;

int main(){
    FILE *fp;
    const int PROCESSES = 5;
    const int RESOURCES = 3;

    int existing[RESOURCES];
    int available[RESOURCES];

    process processes[PROCESSES];

    if ((fp = fopen("input.txt", "r")) == NULL)
    {
        printf("The error in the file opening\n");
        return 0;
    } else {

        int check = 0;

        for (int i = 0; i < RESOURCES; i++) {
            fscanf(fp, "%d", &existing[i]);
        }

        for (int i = 0; i < RESOURCES; i++) {
            fscanf(fp, "%d", &available[i]);
        }

        for (int i = 0; i < PROCESSES; ++i) {
            for (int j = 0; j < RESOURCES; ++j) {
                fscanf(fp, "%d", &processes[i].allocation[j]);
                processes[i].complete = 0;
            }
        }

        for (int i = 0; i < PROCESSES; ++i) {
            for (int j = 0; j < RESOURCES; ++j) {
                fscanf(fp, "%d", &processes[i].request[j]);
            }
        }

        fclose(fp);

        for (int i = 0; i < PROCESSES; ++i){
            for (int j = 0; j < PROCESSES; ++j){
                if (processes[j].complete!=1) {
                    for (int k = 0; k < RESOURCES; ++k) {
                        if (processes[j].request[k] <= available[k]) {
                            check++;
                        }
                    }
                    if (check == RESOURCES) {
                        for (int k = 0; k < RESOURCES; ++k) {
                            available[k]+=processes[j].allocation[k];
                            processes[j].complete = 1;
                        }
                    }
                }
                check = 0;
            }
        }

        for (int i = 0; i < PROCESSES; ++i) {
            if (processes[i].complete==1){
                check++;
            }
        }

        if (check==PROCESSES){
            printf("No deadlock occur\n");
        } else printf("There is a deadlock\n");

    }
    return 0;
}