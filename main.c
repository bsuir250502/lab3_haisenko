#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define stringSize 30

//const int stringSize = 30;

struct cars_t {
    char number[stringSize];
    struct cars_t *next;
};

struct parking_t {
    int size;
    int carsNum;
    struct cars_t *cars;
    struct parking_t *next;
    /*list of cars */
};

void checkKeys(char **argv);
int inputNumericalData();

int addParcking(struct parking_t *parking, int lastParking);
struct cars_t *createCarsList(int size);
void moveCars(struct parking_t *parking, int lastParking);
void addCar(struct parking_t *parking, int parkingNum);
void removeCar(struct parking_t *parking, int parkingNum);
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
    } else {
        temp = (struct parking_t *) malloc(sizeof(struct parking_t));
        for (i = 0; i < lastParking; i++) {
            parking = parking->next;
        }
        parking->next = temp;
    }
    lastParking++;
    printf("Enter the maximum number of cars in the parking: ");
    temp->size = inputNumericalData();
    temp->carsNum = 0;
    temp->cars = createCarsList(temp->size);

    printf("Parking #%d created.\n", lastParking + 1);
    return lastParking;
}

struct cars_t *createCarsList(int size)
{
    int i;
    struct cars_t *cars, *temp, *startPoint;
    cars = (struct cars_t *) malloc(sizeof(struct cars_t));
    startPoint = cars;
    for (i = 0; i < size; i++) {
        temp = (struct cars_t *) malloc(sizeof(struct cars_t));
        cars->next = temp;
        cars = temp;
    }
    cars->next = startPoint;
    return startPoint;
}

void moveCars(struct parking_t *parking, int lastParking)
{
    int parkingNum, i;
    char command[stringSize];
    if (lastParking == -1) {
        printf("You did not added parking.\n");
        return;
    }
    printf("Enter parking number: ");
    do {  //нужна функция для объявления списка
        parkingNum = inputNumericalData() - 1;
        if (parkingNum > lastParking) {
            printf("Last number of parking is %d. Try again: ", lastParking + 1);
            continue;
        }
        break;
    } while (1);
    for (i = 0; i < parkingNum; i++) {
        parking = parking->next;
    }
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
    return;
}

void removeCar(struct parking_t *parking, int parkingNum)
{
    return;
}

void showAllParkings(struct parking_t *parking, int lastParking)
{
    return;
}

void freeAll(struct parking_t *parking, int lastParking)
{
    return;
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
