/*Even not compiled yet*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define arraySize 30

/*const int arraySize = 30;*/
const int stringSize = 30;

struct list_t {
    int size;
    int carsNum;
    int cars[arraySize];
    struct list_t *next;
    /*list of cars*/
};

void addList(struct list_t *list, int lastList);

int main(int argc, char const *argv[])
{
    struct list_t *list;
    int lastList = 0;
    list = (struct list_t *)malloc (sizeof (struct list_t));
    list->next = (struct list_t *)malloc (sizeof (struct list_t));
    addList(list, lastList); 
    return 0;
}

void addList(struct list_t *list, int lastList)
{
    struct list_t *buffer;
    if (!list) {
        list = (struct list_t *)malloc (sizeof (struct list_t));
    }
    buffer = (struct list_t *)malloc (sizeof (struct list_t));
    list->next = buffer;
}
