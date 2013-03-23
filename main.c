#include <string.h>
#include <stdio.h>
#include <stdlib.h>

const int stringSize = 30;

struct cars_t {
    char *number;
    struct cars_t *next;
    struct cars_t *prev;
};

struct parking_t {
    int size;
    int carsNum;
    int pendingNum;
    struct cars_t *car;
    struct cars_t *pending;
    struct parking_t *next;
};

void checkKeys(char **argv);
int inputNumericalData();
char *inputStringData();

int addParcking(struct parking_t *parking, int lastParking);
struct cars_t *createcarsList(int size);
struct parking_t *gotoParking(struct parking_t *parking, int parkingNum);
void moveCar(struct parking_t *parking, int lastParking);
void addCar(struct parking_t *parking, int parkingNum);
void addPending(struct parking_t *parking, char *number);
void removeCar(struct parking_t *parking, int parkingNum);
char *removePending(struct parking_t *parking);
void showAllParkings(struct parking_t *parking, int lastParking);
void freeAll(struct parking_t *parking, int lastParking);

int main(int argc, char **argv)
{
    checkKeys(argv);
    struct parking_t *parking;
    parking = (struct parking_t *) calloc(1, sizeof(struct parking_t));
    int lastParking = -1;
    char command[stringSize];
    while (1) {
        printf("\nEnter command:\n");
        printf("    1 - Add parking\n");
        printf("    2 - Move car\n");
        printf("    3 - Show all parkings\n");
        printf("    4 - Exit\n");
        fgets(command, stringSize, stdin);
        switch (command[0]) {
        case '1':
            lastParking = addParcking(parking, lastParking);
            break;
        case '2':
            moveCar(parking, lastParking);
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
    struct parking_t *temp;
    if (lastParking == -1) {
        temp = parking;
    } else {
        temp = (struct parking_t *) calloc(1 ,sizeof(struct parking_t));
        parking = gotoParking(parking, lastParking);
        parking->next = temp;
    }
    lastParking++;
    printf("Enter the maximum number of cars in the parking: ");
    temp->size = inputNumericalData();
    temp->carsNum = 0;
    temp->car = createcarsList(temp->size);
    printf("Parking #%d created.\n", lastParking + 1);
    return lastParking;
}

struct parking_t *gotoParking(struct parking_t *parking, int parkingNum)
{
    int i;
    for (i = 0; i < parkingNum; i++){
        parking = parking->next;
    }
    return parking;
}

struct cars_t *createcarsList(int size)
{
    int i;
    struct cars_t *car, *temp, *startPoint;
    car = (struct cars_t *) calloc(1, sizeof(struct cars_t));
    startPoint = car;
    for (i = 1; i < size; i++) {
        temp = (struct cars_t *) calloc(1, sizeof(struct cars_t));
        car->next = temp;
        temp->prev = car;
        car = temp;
    }
    car->next = startPoint;
    startPoint->prev = car;
    return startPoint;
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
    parking = gotoParking(parking, parkingNum);
    do {
        printf("+ to add car, - to remove car: ");
        fgets(command, stringSize, stdin);
        switch (command[0]) {
        case '+':
            addCar(parking, parkingNum);
            return;
        case '-':
            removeCar(parking, parkingNum);
            return;
        default:
            break;
        }
    } while (1);
}

void addCar(struct parking_t *parking, int parkingNum)
{
    char *temp;
    printf("Enter car number: ");
    temp = inputStringData();
    if (parking->carsNum == parking->size) {
        printf("Parking #%d is full.\n", parkingNum  + 1);
        addPending(parking, temp);
        return;
    }
    parking->car = parking->car->next;
    parking->car->number = temp;
    parking->carsNum++;
    printf("Car '%s' added to parking #%d\n", parking->car->number, parkingNum + 1);
}

void addPending(struct parking_t *parking, char *number)
{
    struct cars_t *temp;
    temp = (struct cars_t *) malloc(sizeof(struct cars_t));
    if (!parking->pendingNum) {
        parking->pending = temp;
    }
    else {
        parking->pending->next = temp;
        temp->prev = parking->pending;
        parking->pending = temp;
    }
    parking->pending->number = number;
    parking->pendingNum++;
    printf("Car '%s' will wait for parking place.\n", parking->pending->number);
}

void removeCar(struct parking_t *parking, int parkingNum)
{
    if (parking->carsNum == 0) {
        printf("There are no cars in this parking.\n");
        return;
    }
    printf("Car '%s' removed from parking #%d.\n", parking->car->number, parkingNum + 1);
    if (parking->pendingNum) {
        free(parking->car->number);
        parking->car->number = removePending(parking);
        printf("Car '%s' added from the pending queue.\n", parking->car->number);
    }
    else {
        free(parking->car->number);
        parking->car = parking->car->prev;
        parking->carsNum--;
    }
}

char *removePending(struct parking_t *parking)
{
    int i;
    char *temp;
    struct cars_t *first;
    first = parking->pending;
    for (i = 1; i < parking->pendingNum; i++) {
        first = first->prev;
    }
    temp = first->number;
    free(first);
    parking->pendingNum--;
    return temp;
}

void showAllParkings(struct parking_t *parking, int lastParking)
{
    return;
}

void freeAll(struct parking_t *parking, int lastParking)
{
    int i, j;
    struct parking_t *tempParking;
    struct cars_t *tempCar;
    for (i = 0; i <= lastParking; i++) {
        for (j = 0; j < parking->carsNum; j++) {
            printf("%s\n", parking->car->number);
            free(parking->car->number);
            tempCar = parking->car;
            parking->car = parking->car->next;
            free(tempCar);
        }
        for (; j < parking->size; j++) {
            tempCar = parking->car;
            parking->car = parking->car->next;
            free(tempCar);
        }
        for (j = 0; j < parking->pendingNum; j++) {
            free(parking->pending->number);
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

char *inputStringData()
{
    char *buffer;
    buffer = (char *) malloc(stringSize * sizeof(char));
    do {
        fgets(buffer, stringSize, stdin);
        if (buffer[0] == ' ') {
            printf("The number can not start with a space. Try again: ");
            continue;
        }
        if (buffer[0] == '\n') {
            printf("You did not enter a number. Try again: ");
            continue;
        }
        break;
    } while (1);
    buffer[strlen(buffer) - 1] = '\0';
    return buffer;
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
