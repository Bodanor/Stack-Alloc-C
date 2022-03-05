#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Le stack va de la plus haute adresse vers la plus basse (penser à sub esp <value>. On retire à esp pour stocker quelque chose)
 * Ici, j'ai défini ESP qui recoit le malloc de la mémoire, hors ca devrait être le contraire.. EBP EST LA BASE DONC l'ADDRESSE LA PLUS HAUTE.
 * Ce que je devrait faire ca serrait malloc EBP, Dire que EBP = EBP + le max, et dire ESP = EBP - max, ce qui echange les deux
 * Enfin pour savoir si le stack est plein je doit retirer des valeurs pour comparé au lieux d'augmenter !
 * 
 * EDIT : Ignorer ce commentaire, j'ai appliquer ce que j'avais dit que j'allais faire.
 * Quand on démarre un programme, EBP et ESP on tout deux la même valeur (mov esp, ebp en assembleur). Comme je l'ai dit lorsque l'on push quelque
 * Chose, ESP diminue en addresse :
 *Addresse :  0:------ -> ESP (top de la pile)adresse 0
 *            1:|    |
 *            2:|    |
 *            3:|    |   // EBP est toujours plus grand ou égal à ESP.
 *            4:|    |
 *            5:|    |
 *            6:|    |
 *            7:------   -> EBP (le plus bas de la pile)adresse 7
 * 
 *Addresse :  0:------
 *            1:|    |
 *            2:|    |
 *            3:|    |   // Admettons q'un int c'est 1 octets, SI on décide de push la valeur 5, 
 *            4:|    |   // Alors, on aura entre l'adresse 7 et 6 la valeur 5 et ESP 
 *            5:|    |   // vaudra 6.
 *            6:|    |
 *            7:------  -> EBP et ESP on la même valeurs au debut d'un programme
 */
typedef struct stack
{
    char data[10];
    struct stack *next_stack;
}stack_t;

short push(char *data, stack_t**ESP, stack_t *EBP, int stacksize);
void pop(stack_t **ESP, stack_t *EBP);
short secureInput(char* str, int size_str);
void free_stack(stack_t *EBP, int stack_size);

int main()
{

    stack_t *EBP = NULL;
    stack_t *ESP = NULL;
    char buffer[10];
    char choice [5];
    int running = 1;
    printf("Allocating memory for the stack...\n");

    EBP = (stack_t*)malloc(sizeof(stack_t)*2);
    if (EBP == NULL)
    {
        printf("Error trying to alloc memory for the stack !\n");
        return -1;
    }
    EBP = EBP + 2;
    ESP = EBP;

    while (running)
    {
        printf("Push or Pop ? : ");
        secureInput(choice, sizeof(choice));
        if (strcmp(choice, "push") == 0 || strcmp(choice, "PUSH") == 0)
        {
            printf("Enter data : ");
            secureInput(buffer, sizeof(buffer));
            if (*buffer != '\0')
                if(push(buffer, &ESP, EBP, 2) == -1)
                    return -1;
        }
        else if (strcmp(choice, "pop") == 0 || strcmp(choice, "POP") == 0)
        {
            pop(&ESP, EBP);
        }
        else if (strcmp(choice, "exit") == 0 || strcmp(choice, "EXIT") == 0)
        {
            free_stack(EBP, 2);
            running = 0;
        }
        printf("EBP : %p\n",(void*)EBP);
        printf("ESP : %p\n", (void*)ESP);   
    }



}

short push(char *data, stack_t**ESP, stack_t *EBP, int stack_size)
{
    stack_t *pstack = (*ESP)-1;
    if (pstack != EBP - (stack_size + 1))
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
    return 0;

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

void free_stack(stack_t *EBP, int stack_size)
{
    free(EBP - stack_size);
}