#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>

int* plusOne(int* digits, int digitsSize, int* returnSize) 
{
    int carry_on = 1; // On commence avec une retenue de 1
    for (int i = digitsSize - 1; i >= 0; i--) 
    {
        if (digits[i] == 9) 
        {
            digits[i] = 0;
        } 
        else 
        {
            digits[i] += 1;
            carry_on = 0; // Pas de retenue nécessaire
            break;
        }
    }

    if (carry_on == 1) 
    {
        // Cas où tous les chiffres étaient 9 (ex: 999 -> 1000)
        *returnSize = digitsSize + 1;
        int *newDigits = malloc((*returnSize) * sizeof(int));
        if (!newDigits) return NULL; // Vérification allocation mémoire
        newDigits[0] = 1; // Le premier chiffre est 1
        memset(newDigits + 1, 0, digitsSize * sizeof(int)); // Remplir le reste avec des zéros
        return newDigits;
    }

    *returnSize = digitsSize;
    int *newDigits = malloc((*returnSize) * sizeof(int));
    if (!newDigits) return NULL; // Vérification allocation mémoire
    memcpy(newDigits, digits, digitsSize * sizeof(int)); // Copier le tableau
    return newDigits;
}


int main()
{
    int arr[] = {9,9,9};
    int returnSize = sizeof(arr)/sizeof(arr[0]);
    int *plus = plusOne(arr,returnSize,&returnSize);
    for(int i = 0;i < returnSize;i++)
    {
        printf("%d\n",plus[i]);
    } 
}
