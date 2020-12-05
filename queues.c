#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIMTIME 10

typedef struct patient
{
    int id;
    struct patient *next;
} patient_t;

// -- Queues implemented List Defination --
int count(patient_t *head)
{
    int i = 0;
    patient_t *present = head->next;
    while (present->next != NULL)
    {
        i++;
        present = present->next;
    }
    return i;
}

void pushPatient(patient_t *head, int value)
{

    patient_t *current = head;

    while (current->next != NULL)
    {

        current = current->next;
    }

    current->next = malloc(sizeof(patient_t));
    current->next->id = value;
    current->next->next = NULL;
}

int popPatient(patient_t **head)
{

    patient_t *nextPatient = NULL;
    int currentID = -1;

    if (*head == NULL)
    {
        return -1;
    }

    nextPatient = (*head)->next;
    currentID = (*head)->id;
    free(*head);
    *head = nextPatient;

    return currentID;
}

void printLists(patient_t *list1, patient_t *list2)
{
    int count1 = count(list1);
    int count2 = count(list2);
    int max = count1 > count2 ? count1 : count2;
    patient_t *present1 = list1->next;
    patient_t *present2 = list2->next;
    printf("Emergency \t| OPD \n");

    for (int i = 0; i < max; i++)
    {
        if (present1->next == NULL)
        {
            printf("- \t \t| %d \n", present2->id);
            present2 = present2->next;
        }
        else if (present2->next == NULL)
        {
            printf("%d \t \t| - \n", present1->id);
            present1 = present1->next;
        }
        else
        {
            printf("%d \t \t| %d \n", present1->id, present2->id);
            present1 = present1->next;
            present2 = present2->next;
        }
    }
}
int checkPatient(patient_t *head, int id)
{
    patient_t *current = head;
    while (current->next != NULL)
    {
        if (current->id == id)
        {
            return 1;
        }
        current = current->next;
    }
    return 0;
}
// -- End of queues defination --