#include <string.h>
#include <stdio.h>
#include <stdlib.h>

const int stringSize = 30;

struct parking_t {
    int size;
    int carsNum;
    int *cars;
    struct parking_t *next;
    /*list of cars*/
};

void checkKeys(char **argv);
int inputNumericalData();

int addParcking(struct parking_t *parking, int lastParking);
void moveCars(struct parking_t *parking, int lastParking);
void showAllParkings(struct parking_t *parking, int lastParking);
void freeAll(struct parking_t *parking, int lastParking);

int main(int argc, char **argv)
{
    checkKeys(argv);
    struct parking_t *parking;
    parking = (struct parking_t *)malloc (sizeof(struct parking_t));
    int lastParking = -1;
    char command[stringSize];
    parking = NULL;
    while (1) {
        printf("Enter command:\n"); 
        printf("    1 - Add parking\n");
        printf("    2 - Move cars\n");
        printf("    3 - Show all parkings\n");
        printf("    4 - Exit\n");
        fgets(command, stringSize, stdin);
        switch (command[0]) {
        case '1':
            lastParking = addParcking(parking, lastParking);
            break;
        case '2':
            moveCars(parking, lastParking);
            break;
        case '3':
            showAllParkings(parking, lastParking);
            break;
        case '4':
            freeAll(parking, lastParking);
            return 0;
        default:
            printf("Wrong command. Try again\n");
            break;
        }
    }
    return 0;
}

int addParcking(struct parking_t *parking, int lastParking)
{
    int i;
    struct parking_t *temp;
    if (lastParking == -1) {
        temp = parking;
        printf("1\n");
    }
    else {
        temp = (struct parking_t *)malloc (sizeof(struct parking_t));
        for (i = 0; i < lastParking; i++) {
            parking = parking->next;
        }
        parking->next = temp;
        printf("2\n");
    }\
    lastParking++;
    printf("Enter the maximum number of cars in the parking: \n");
    temp->size = inputNumericalData() + 1;
    printf("3\n");
    temp->carsNum = 0;
    printf("4\n");
    temp->cars = (int *)malloc (temp->size * sizeof(int));
    printf("5\n");
    printf("Parking #%d created.\n", lastParking + 1);
    return lastParking;
}

void moveCars(struct parking_t *parking, int lastParking)
{
    int i;
}

void showAllParkings(struct parking_t *parking, int lastParking)
{
    int i;
}

void freeAll(struct parking_t *parking, int lastParking)
{
    int i;
}

int inputNumericalData()
{
    char buffer[stringSize];
    int num;
    do {
        fgets(buffer, stringSize, stdin);
        num = atoi(buffer);
        if (num <= 0) {
            printf("Incorrect value. Try again: ");
            continue;
        }
        break;
    } while (1);
    return num;
}

void checkKeys(char **argv)
{
    if (!argv[1]) {
        return;
    }
    if (!strcmp(argv[1], "-h")) {
        printf("================================================================================\n");
        printf("                                     MANUAL:\n\n");
        printf("================================================================================\n");
        exit(0);
    }
}