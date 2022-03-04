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


short push(char *data, stack_t**ESP, stack_t *EBP, int stacksize);
void pop(stack_t **ESP, stack_t *EBP);
short secureInput(char* str, int size_str);

int main()
{
    stack_t *EBP = NULL;
    stack_t *ESP = NULL;
    char data[10];
    char choice [5];
    printf("Allocating memory for the stack...\n");

    EBP = (stack_t*)malloc(sizeof(stack_t)*2);
    if (EBP == NULL)
    {
        printf("Error trying to alloc memory for the stack !\n");
        return -1;
    }
    EBP = EBP + 1;
    ESP = EBP;

    while (1)
    {
        printf("Push or Pop ? : ");
        secureInput(choice, sizeof(choice));
        if (strcmp(choice, "push") == 0 || strcmp(choice, "PUSH") == 0)
        {
            printf("Enter data : ");
            secureInput(data, sizeof(data));
            if (*data != '\0')
                if(push(data, &ESP, EBP, 3) == -1)
                    return -1;
        }
        else if (strcmp(choice, "pop") == 0 || strcmp(choice, "POP") == 0)
        {
            pop(&ESP, EBP);
        }
        
        printf("EBP : 0x%X\n", EBP);
        printf("ESP : 0x%X\n", ESP);   
    }


}

short push(char *data, stack_t**ESP, stack_t *EBP, int stack_size)
{
    stack_t *pstack = (*ESP)-1;
    if (pstack != EBP - stack_size)
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

void pop(stack_t **ESP, stack_t *EBP)
{
    stack_t *pstack = *ESP;
    if (pstack != EBP)
    {
        *ESP = (*ESP)->next_stack;
    }
}