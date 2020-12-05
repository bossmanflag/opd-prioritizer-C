#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "queues.c"

int main()
{
    srand(time(0));
    int opd_counter = 0;
    int emergency_counter = 0;

    patient_t *opd_queue = malloc(sizeof(patient_t));
    opd_queue->id = rand() % 50;
    patient_t *emergency_queue = malloc(sizeof(patient_t));
    emergency_queue->id = rand() % 50;

    int interval = 0;
    printf("This is a ER simulation of an hospital. It consists of a 2 queues, opd(out patient department) and emergency queues. \nIn an real world scenario, emergencies and opds patients should be balanced. \nThis simulation shows how a computer program can help in such a condition.");

    char inp = getchar();

    int r = rand() % 50;

    for (int i = 0; i < (rand() % 10) + 1; i++)
    {

        pushPatient(emergency_queue, r);
        r = rand() % 50;
    }

    for (int i = 0; i < (rand() % 10) + 1; i++)
    {
        pushPatient(opd_queue, r);
        r = rand() % 50;
    }

    printf("Assuming Queues before the simulation starts \n");
    printLists(emergency_queue, opd_queue);
    printf("\n \n");
    r = rand() % 50;

    while ((inp == '\n' || inp == 'q' || inp == 'd') && interval <= SIMTIME)
    {
        printf("Time : %d \n", interval + 1);
        if (inp == 'q')
        {
            break;
        }

        else
        {

            if (emergency_queue != NULL && opd_queue == NULL)
            {
                int emergency_patient = popPatient(&emergency_queue->next);
                printf("Doctor attending emergency. ID: %d \n", emergency_patient);
                emergency_counter++;
                printList(emergency_queue);
                if (count(emergency_queue) < 10)
                {

                    for (int i = 0; i < rand() % 3; i++)
                    {
                        r = rand() % 50;
                        while (checkPatient(emergency_queue, r) == 1)
                        {
                            r = rand() % 50;
                        }
                        pushPatient(emergency_queue, r);
                    }
                }
                if (count(opd_queue) < 10)
                {

                    for (int i = 0; i < rand() % 3; i++)
                    {
                        r = rand() % 50;
                        while (checkPatient(opd_queue, r) == 1)
                        {
                            r = rand() % 50;
                        }
                        pushPatient(opd_queue, r);
                    }
                }
            }

            if (opd_queue != NULL && emergency_queue == NULL)
            {
                int opd_patient = popPatient(&opd_queue->next);
                printf("Doctor attending OPD. ID: %i \n", opd_patient);
                opd_counter++;
                printList(opd_queue);
                if (count(emergency_queue) < 10)
                {

                    for (int i = 0; i < rand() % 3; i++)
                    {
                        r = rand() % 50;
                        while (checkPatient(emergency_queue, r) == 1)
                        {
                            r = rand() % 50;
                        }
                        pushPatient(emergency_queue, r);
                    }
                }
                if (count(opd_queue) < 10)
                {

                    for (int i = 0; i < rand() % 3; i++)
                    {
                        r = rand() % 50;
                        while (checkPatient(opd_queue, r) == 1)
                        {
                            r = rand() % 50;
                        }
                        pushPatient(opd_queue, r);
                    }
                }
            }

            if (emergency_queue != NULL && opd_queue != NULL)
            {
                float score_emergency = (float)0.5 * count(emergency_queue);
                float score_opd = (float)0.5 * count(opd_queue);
                int selection = 0;
                if (score_emergency < score_opd)
                {
                    selection = 1;
                }
                if (selection == 0)
                {
                    int emergency_patient = popPatient(&emergency_queue->next);
                    printf("Doctor attending emergency. ID: %d \n", emergency_patient);
                    emergency_counter++;
                }
                else if (selection == 1)
                {
                    int opd_patient = popPatient(&opd_queue->next);
                    printf("Doctor attending opd. ID: %d \n", opd_patient);
                    opd_counter++;
                }
                if (count(emergency_queue) < 10)
                {
                    for (int i = 0; i < rand() % 3; i++)
                    {
                        r = rand() % 50;
                        while (checkPatient(emergency_queue, r) == 1)
                        {
                            r = rand() % 50;
                        }
                        pushPatient(emergency_queue, r);
                    }
                }
                if (count(opd_queue) < 10)
                {

                    for (int i = 0; i < rand() % 3; i++)
                    {
                        r = rand() % 50;
                        while (checkPatient(opd_queue, r) == 1)
                        {
                            r = rand() % 50;
                        }
                        pushPatient(opd_queue, r);
                    }
                }
            }
            printf("Report \n");
            printf("Number of patients in emergency : %d \n", count(emergency_queue));
            printf("Number of patients in opd : %d \n", count(opd_queue));
            printLists(emergency_queue, opd_queue);
            inp = getchar();
            interval++;
        }
    }
    printf("\n \n");
    if (interval - 1 == SIMTIME)
    {
        printf("The simulation has reached maximum allocated time of the simulation.\n This can be changed in the Queues.c file.\nNow, halting. \n");
    }
    else
    {
        printf("The simulation has been interrupted by user. Now, halting.");
    }
    printf("Report \n");
    printLists(emergency_queue, opd_queue);
    printf("Number of patients in emergency : %d \n", count(emergency_queue));
    printf("Number of patients in opd : %d \n", count(opd_queue));
    printf("Total Time simulation ran for : %d \n ", interval - 1);
}
