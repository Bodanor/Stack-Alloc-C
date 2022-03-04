#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stack{
    int data;
    struct stack *next_stack;

}stack_t;

void push(int data, stack_t **stack);
void pop(stack_t **stack);
short secureInput(char* str, int size_str);


void pop(stack_t **stack)
{
    stack_t *pstack = *stack;
    if (pstack != NULL)
        *stack = pstack->next_stack;
    free(pstack);   // Meme si *stack = pstack->next_stack, pstack pointe vers l'ancien top de la stack. Il pointe l'ancienne adresse
    /* Peut-on directement écrire : *stack = *stack->next_stack ? */
    /* Edit : Peut-être que on ne doit pas faire cela, car sinon aucun autre moyen de free, donc fuites mémoires */

}

void push(int data, stack_t **stack)
{
    stack_t *pstack = (stack_t*)malloc(sizeof(stack_t));
    if (pstack != NULL)
    {
        pstack->data = data;
        pstack->next_stack = *stack;
        *stack = pstack;
    }
    else
    {
        printf("Malloc error !\n");
    }

}
int main()
{
    stack_t *esp = NULL;
    stack_t *ebp = esp;

    char data[5];
    int data_int;
    char choice[5]= {0};
    int i;
    while (1)
    {
        printf("POP or PUSH ? : ");
        secureInput(choice, sizeof(choice));
        if (strcmp(choice, "push") == 0 || strcmp(choice, "PUSH") == 0)
        {
            printf("Enter data : ");
            secureInput(data, sizeof(data));
            data_int = atoi(data);
            push(data_int, &esp);
        }
        else
            pop(&esp);
        printf("EBP : 0x%X\n", ebp);
        printf("ESP: 0x%X\n", esp);
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