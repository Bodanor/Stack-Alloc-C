#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    ESP = (stack_t*)malloc(sizeof(stack_t)*10);
    if (ESP == NULL)
    {
        printf("Error trying to alloc memory for the stack !\n");
        return -1;
    }
    EBP = ESP + 10;

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
    stack_t *pstack = *(ESP)+1;
    if (pstack != EBP)
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

