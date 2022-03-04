#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Le stack va de la plus haute adresse vers la plus basse (penser à sub esp <value>. On retire à esp pour stocker quelque chose)
 * Ici, j'ai défini ESP qui recoit le malloc de la mémoire, hors ca devrait être le contraire.. EBP EST LA BASE DONC l'ADDRESSE LA PLUS HAUTE.
 * Ce que je devrait faire ca serrait malloc EBP, Dire que EBP = EBP + le max, et dire ESP = EBP - max, ce qui echange les deux
 * Enfin pour savoir si le stack est plein je doit retirer des valeurs pour compar" au lieux d'augmenter !
 * 
 */
typedef struct stack
{
    char data[10];
    struct stack *next_stack;
}stack_t;


short push(char *data, stack_t**ESP, stack_t *EBP);
short secureInput(char* str, int size_str);

int main()
{
    stack_t *EBP = NULL;
    stack_t *ESP = NULL;
    char data[10];

    printf("Allocating memory for the stack...\n");

    EBP = (stack_t*)malloc(sizeof(stack_t)*10);
    if (EBP == NULL)
    {
        printf("Error trying to alloc memory for the stack !\n");
        return -1;
    }
    EBP = EBP + 9;
    ESP = EBP;

    while (1)
    {
        printf("EBP : 0x%X\n", EBP);
        printf("ESP : 0x%X\n", ESP);
        printf("Enter data : ");
        secureInput(data, sizeof(data));
        push(data, &ESP, EBP);


    }


}

short push(char *data, stack_t**ESP, stack_t *EBP)
{
    stack_t *pstack = *(ESP)-1;
    if (pstack != EBP -20)
    {
         if (pstack != NULL)
        {
            strcpy(pstack->data, data);
            pstack->next_stack = *ESP;
            *ESP = pstack;
        }
        else
        {
            printf("Stack corrupted !\n");
            return -1;
        }
    }
    else
    {
        printf("Stack is full !\n");
        return -2;
    }

}
short secureInput(char* str, int size_str)
{
    int c, i = 0;

    while (((c = getchar()) != '\n') && c != EOF)
    {
        if (i < size_str-1)
            *str++ = c;
        i++;
    }
    *str = '\0';

    if (i == 0)
        return 0;
    else
        return 1;
}

