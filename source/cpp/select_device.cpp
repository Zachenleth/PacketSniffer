#include "libreria.h"

int select_device()
{
    int choice;
    printf("Selecciona interfaz: ");
    scanf("%d", &choice);
    return choice;
}