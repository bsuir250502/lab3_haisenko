#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define stringSize 30

struct cars_t {
    char number[stringSize];
    struct cars_t *prev;
};

struct parking_t {
    int size;
    int carsNum;
    struct cars_t *car;
    struct cars_t *pending;     /*maybe begin and end and new structure? */
    struct parking_t *next;
};

void checkKeys(char **argv);
int inputNumericalData();
void inputStringData(char *string);

void addParcking(struct parking_t *parking, int *lastParking);
void moveCar(struct parking_t *parking, int lastParking);
void addCar(struct parking_t *parking);
void addPending(struct parking_t *parking, struct cars_t *tempCar);
void removeCar(struct parking_t *parking);
void removePending(struct parking_t *parking);
void showAllParkings(struct parking_t *parking, int lastParking);
void freeAll(struct parking_t *parking);

int main(int argc, char **argv)
{
    checkKeys(argv);
    int lastParking = -1;
    char command[stringSize];
    struct parking_t *parking;
    parking = (struct parking_t *) calloc(1, sizeof(struct parking_t));
    while (1) {
        printf("\nEnter command:\n");
        printf("    1 - Add parking\n");
        printf("    2 - Move car\n");
        printf("    3 - Show all parkings\n");
        printf("    4 - Exit\n");
        fgets(command, stringSize, stdin);
        switch (command[0]) {
        case '1':
            addParcking(parking, &lastParking);
            break;
        case '2':
            moveCar(parking, lastParking);
            break;
        case '3':
            showAllParkings(parking, lastParking);
            break;
        case '4':
            freeAll(parking);
            return 0;
        default:
            printf("Wrong command. Try again\n");
            break;
        }
    }
    return 0;
}

void addParcking(struct parking_t *parking, int *lastParking)
{
    if (*lastParking != -1) {
        while (parking->next) {
            parking = parking->next;
        }
        parking->next = (struct parking_t *) calloc(1, sizeof(struct parking_t));
        parking = parking->next;
    }
    (*lastParking)++;
    printf("Enter the maximum number of cars in the parking: ");
    parking->size = inputNumericalData();
    printf("Parking #%d created.\n", *lastParking + 1);
}

void moveCar(struct parking_t *parking, int lastParking)
{
    int parkingNum;
    char command[stringSize];
    if (lastParking == -1) {
        printf("You did not added any parking.\n");
        return;
    }
    printf("Enter parking number: ");
    do {
        parkingNum = inputNumericalData() - 1;
        if (parkingNum > lastParking) {
            printf("Last number of parking is %d. Try again: ", lastParking + 1);
            continue;
        }
        break;
    } while (1);
    while (parkingNum--) {
        parking = parking->next;
    }
    do {
        printf("+ to add car, - to remove car: ");
        fgets(command, stringSize, stdin);
        switch (command[0]) {
        case '+':
            addCar(parking);
            return;
        case '-':
            removeCar(parking);
            return;
        default:
            break;
        }
    } while (1);
}

void addCar(struct parking_t *parking)
{
    struct cars_t *tempCar;
    printf("Enter car number: ");
    tempCar = (struct cars_t *) calloc(1, sizeof(struct cars_t));
    inputStringData(tempCar->number);
    if (parking->carsNum == parking->size) {
        addPending(parking, tempCar);
        return;
    }
    tempCar->prev = parking->car;
    parking->car = tempCar;
    parking->carsNum++;
    printf("Car '%s' added to parking\n", parking->car->number);
}

void addPending(struct parking_t *parking, struct cars_t *tempCar)
{
    tempCar->prev = parking->pending;
    parking->pending = tempCar;
    printf("Parking is full.\n");
    printf("Car '%s' will wait for parking place.\n", parking->pending->number);
}

void removeCar(struct parking_t *parking)
{
    struct cars_t *temp;
    if (!parking->car) {
        printf("There are no cars in this parking.\n");
        return;
    }
    printf("Car '%s' removed from parking.\n", parking->car->number);
    temp = parking->car;
    parking->car = parking->car->prev;
    free(temp);
    if (parking->pending) {
        removePending(parking);
        printf("Car '%s' added from the pending queue.\n", parking->car->number);
    } else {
        parking->carsNum--;
    }
}

void removePending(struct parking_t *parking)
{
    struct cars_t *first, *preFirst;
    first = parking->pending;
    preFirst = first;
    if (!first->prev) {
        parking->pending = NULL;
    }
    while (first->prev) {
        preFirst = first;
        first = first->prev;
    }
    preFirst->prev = NULL;
    first->prev = parking->car;
    parking->car = first;
}

void showAllParkings(struct parking_t *parking, int lastParking)
{
    int i;
    struct cars_t *tempCar;
    if (lastParking == -1) {
        printf("Nothing is entered.\n");
        return;
    }
    printf("============================================================\n");
    for (i = 1;; i++) {
        printf("|| Parking #%d | ", i);
        printf("Cars: ");
        tempCar = parking->car;
        while (tempCar) {
            printf("%s ", tempCar->number);
            tempCar = tempCar->prev;
        }
        printf("\n");
        if (parking->size == parking->carsNum) {
            printf("||  (full)    | Pending cars: ");
        } else {
            printf("||            | Pending cars: ");
        }
        tempCar = parking->pending;
        while (tempCar) {
            printf("%s ", tempCar->number);
            tempCar = tempCar->prev;
        }
        printf("\n");
        parking = parking->next;
        if (parking) {
            printf("||-------------------------------------------------------\n");
        } else {
            printf("============================================================\n");
            break;
        }
    }
}

void freeAll(struct parking_t *parking)
{
    struct parking_t *tempParking;
    struct cars_t *tempCar;
    while (parking) {
        while (parking->car) {
            tempCar = parking->car;
            parking->car = parking->car->prev;
            free(tempCar);
        }
        while (parking->pending) {
            tempCar = parking->pending;
            parking->pending = parking->pending->prev;
            free(tempCar);
        }
        tempParking = parking;
        parking = parking->next;
        free(tempParking);
    }
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

void inputStringData(char *string)
{
    do {
        fgets(string, stringSize, stdin);
        if (string[0] == ' ') {
            printf("The number can not start with a space. Try again: ");
            continue;
        }
        if (string[0] == '\n') {
            printf("You did not enter a number. Try again: ");
            continue;
        }
        break;
    } while (1);
    string[strlen(string) - 1] = '\0';
}

void checkKeys(char **argv)
{
    if (!argv[1]) {
        return;
    }
    if (!strcmp(argv[1], "-h")) {
        printf("================================================================================\n");
        printf("                                     MANUAL:\n\n");
        printf("    Commands: 1 2 3 4\n\n");
        printf("1 - Add parking \n");
        printf("    Enter maximum number of cars. Command will created new parking.\n\n");
        printf("2 - Move cars\n");
        printf("    1) + to add new car:\n");
        printf("        Car with entered numer will added to parking.\n");
        printf("        Number should not be empty string or started with spaces.\n");
        printf("        If parking is full, car will added to pending queue.\n");
        printf("    2) - to remove last car:\n");
        printf("        Last entered car will be removed.\n");
        printf("        If there is a waiting queue, a car will added to parking out of it.\n\n");
        printf("3 - Output\n");
        printf("    Displays all parkings and cars.\n");
        printf("4 - Exit\n");
        printf("    Close the program.\n");
        printf("================================================================================\n");
        exit(0);
    }
}
