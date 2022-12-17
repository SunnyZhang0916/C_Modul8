#include <stdio.h>

//
char cDisplayBoard[20][20];
//
void InitializeDisplay()
{
    for (int iRow = 0; iRow < 20; iRow++)
        for (int iCol = 0; iCol < 20; iCol++)
           cDisplayBoard[iRow][iCol] = '.';
}

void Display() {
    for (int iRow = 0; iRow < 20; iRow++)
    {
    for (int iCol = 0; iCol < 20; iCol++)
        printf("%c", cDisplayBoard[iRow][iCol]);
    printf("\n");
    }

}
int main()
{
    printf("Sunny Zhang - Conway's Game of Life\n\n");
    InitializeDisplay();
    Display();
}
