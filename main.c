//
//  main.c
//  SudokuDifficulty
//
//  Created by Axel Zuchovicki on 10/29/16.
//  Copyright © 2016 Axel Zuchovicki. All rights reserved.
//


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

bool checkPossible(int sudoku[9][9], int value, int row, int column);
void printSudoku(int sudoku[9][9]);
int checkIfSolution2 (int sudoku[9][9]);
void eraseNotNeeded (int sudoku[9][9]);
int possibilities(int sudoku[9][9], int row, int column);
int firstRule(int sudoku[9][9]);
int secondRule(int sudoku[9][9]);
void checkPossibilities(int sudoku[9][9], int *(apuntador[9][9]));
int placeIfOne(int sudoku[9][9], int *(apuntador[9][9]));
int thirdRuleRow(int sudoku[9][9], int *(apuntador[9][9]));
int thirdRuleColumn(int sudoku[9][9], int *(apuntador[9][9]));
int placeIfOnly(int sudoku[9][9], int *(apuntador[9][9]));
int fourthRuleCorrectedRows(int sudoku[9][9], int*(apuntador[9][9]));
int fourthRuleCorrectedColumns(int sudoku[9][9], int*(apuntador[9][9]));
int nakedDoubleColumn(int sudoku[9][9], int*(apuntador[9][9]));
int nakedDoubleRow(int sudoku[9][9], int*(apuntador[9][9]));
int nakedDoubleCell(int sudoku[9][9], int*(apuntador[9][9]));
int nakedTripleColumn(int sudoku[9][9], int*(apuntador[9][9]));
int nakedTripleRow(int sudoku[9][9], int*(apuntador[9][9]));
int nakedTripleCell(int sudoku[9][9], int*(apuntador[9][9]));
int nakedQuadrupleColumn(int sudoku[9][9], int*(apuntador[9][9]));
int nakedQuadrupleRow(int sudoku[9][9], int*(apuntador[9][9]));
int nakedQuadrupleCell(int sudoku[9][9], int*(apuntador[9][9]));
int checkDifficulty(int sudoku[9][9]);
bool checkPossible2(int sudoku[9][9], int value, int row, int column);
/* En la función para checar la dificultad, dentro de las reglas se utiliza un arreglo de apuntadores donde se señalan
 los posibles valores para cada posición del sudoku.
 */


int main() {
    int userDifficulty;
    int creatingSudoku[9][9];
    int checkingSudoku[9][9];
    printf("Please select the wished sudoku's difficulty\n 1: Easy\n 2: Medium\n 3: Difficult\n");
    scanf("%d", &userDifficulty);
    time_t  t;
    srand((unsigned) time (&t));
    newLabel:
    for (int i = 0; i<9; i++){
        for (int z = 0; z<9; z++){
            creatingSudoku[i][z] = 0;
            checkingSudoku[i][z] = 0;
        }
    }
    int adding = 0;
    int row = 0;
    int column = 0;
    int difficulty = 0;
    int check;
    do{
        label:
        do{
            do{
                row = rand()%9;
                column = rand()%9;
            }while(creatingSudoku[row][column] != 0);
            adding = rand()%9 + 1;
        }while(!checkPossible2(creatingSudoku, adding, row, column));
        creatingSudoku[row][column] = adding;
        check = checkIfSolution2(creatingSudoku);
        if (check != 1 && check != 2){
            creatingSudoku[row][column] = 0;
            goto label;
        }
    }while(check != 1 && check != 0);


    eraseNotNeeded(creatingSudoku);
    for (int i = 0; i<9; i++){
        for (int z = 0; z<9; z++){
            checkingSudoku[i][z] = creatingSudoku[i][z];
        }
    }

    difficulty = checkDifficulty(checkingSudoku);
    if (difficulty!= (userDifficulty-1)){
        goto newLabel;
    }
    printSudoku(creatingSudoku);
}

int checkDifficulty(int sudoku[9][9]){
    int *apuntador[9][9];
    int count = 0;
    int count2 = 0;
    int difficulty = 0;
    thelabel:
    while (firstRule(sudoku) != 0){
        count +=1;
    }
    count2 = secondRule(sudoku);
    if (count2 != 0){
        goto thelabel;
    }
    checkPossibilities(sudoku, apuntador);
    thirdRuleColumn(sudoku, apuntador);
    thirdRuleRow(sudoku, apuntador);
    if (placeIfOnly(sudoku, apuntador) == 1){
        for (int r = 0; r<9; r++){
            for (int s = 0; s<9; s++){
                free(apuntador[r][s]);
            }
        }
        if (difficulty < 1)
            difficulty = 1;
        goto thelabel;
    }
    if (placeIfOne(sudoku, apuntador) == 1){
        for (int r = 0; r<9; r++){
            for (int s = 0; s<9; s++){
                free(apuntador[r][s]);
            }
        }
        if (difficulty < 1)
            difficulty = 1;
        goto thelabel;
    }
    fourthRuleCorrectedRows(sudoku, apuntador);
    fourthRuleCorrectedColumns(sudoku, apuntador);
    if (placeIfOnly(sudoku, apuntador) == 1){
        for (int r = 0; r<9; r++){
            for (int s = 0; s<9; s++){
                free(apuntador[r][s]);
            }
        }
        if (difficulty < 1)
            difficulty = 1;
        goto thelabel;
    }
    if (placeIfOne(sudoku, apuntador) == 1){
        for (int r = 0; r<9; r++){
            for (int s = 0; s<9; s++){
                free(apuntador[r][s]);
            }
        }
        if (difficulty < 1)
            difficulty = 1;
        goto thelabel;
    }
    thislabel:
    nakedDoubleColumn(sudoku, apuntador);
    if (nakedDoubleRow(sudoku, apuntador) != 0)
        goto thislabel;
    if (nakedDoubleCell(sudoku, apuntador) != 0)
        goto thislabel;
    if (nakedTripleRow(sudoku, apuntador) != 0)
        goto thislabel;
    if (nakedTripleColumn(sudoku, apuntador) != 0)
        goto thislabel;
    if (nakedTripleCell(sudoku, apuntador)!= 0)
        goto thislabel;
    if (nakedQuadrupleCell(sudoku, apuntador) != 0)
        goto thislabel;
    if (placeIfOnly(sudoku, apuntador) == 1){
        for (int r = 0; r<9; r++){
            for (int s = 0; s<9; s++){
                free(apuntador[r][s]);
            }
        }
        difficulty = 1;
        goto thelabel;
    }
    if (placeIfOne(sudoku, apuntador) == 1){
        for (int r = 0; r<9; r++){
            for (int s = 0; s<9; s++){
                free(apuntador[r][s]);
            }
        }
        difficulty = 1;
        goto thelabel;
    }
    for (int i = 0; i<9; i++){
        for (int z = 0; z<9; z++){
            if (sudoku[i][z] == 0){
                return 2;
            }
        }
    }
    return difficulty;
}

bool checkPossible(int sudoku[9][9], int value, int row, int column)
{
    if(sudoku[row][column] != 0)
        return false;
    if (value == 0)
    {
        return false;
    }
    for (int i = 0; i<9; i++)
    {
        if (column == i)
            continue;
        if (sudoku[row][i] == value)
            return false;
    }
    for (int z= 0; z<9; z++)
    {
        if (row == z)
            continue;
        if (sudoku[z][column] == value)
            return false;
    }
    for (int i=row-(row%3); i<(row-(row%3)+3); i++){
        for (int z=column-(column%3); z<(column-(column%3)+3); z++){
            if (row == i && column == z)
                continue;
            if(sudoku[i][z] == value)
                return false;
        }
    }


    return true;
}
void printSudoku(int sudoku[9][9]){
    for (int row = 0; row<9; row++){
        for (int column = 0; column<9; column++){
            if (row%3 == 0 && column == 0 && row != (8 && 0)){
                for (int i = 0; i<21; i++){
                    printf("-");
                }
                printf("\n");
            }
            printf("%d ", sudoku[row][column]);
            if (column%3 == 2){
                if (column != 8)
                    printf("| ");
            }
        }
        printf("\n");
    }
}

int checkIfSolution(int sudoku[9][9]){
    int newSudoku[9][9] = {0};
    int solutionsNumber = 0;
    char fixed[9][9];
    for (int row = 0; row<9; row++){
        for (int column = 0; column<9; column++){
            if (sudoku[row][column] != 0){
                newSudoku[row][column] = sudoku[row][column];
                fixed[row][column] = 'a';
            }
            else{
                fixed[row][column] = 'c';
            }
        }
    }
    //The fixed matrix has the objective of identifying which numbers are provided by the puzzle and shouldn't be changed.
    int firstColumn = 0;
    int firstRow = 0;
    while (fixed[firstRow][firstColumn] == 'a'){
        firstColumn+=1;
        if (firstColumn == 9)
            firstRow+=1;
    }
    //This while loop has the sole purpose of identifying which number is the first number that isn't provided by the puzzle. This 'a' variable will be used to check if the puzzle has solution or not. This will be done by checking if in that position the value has exceeded 9.
    int lastColumn = 8;
    int lastRow = 8;
    while (fixed[8][lastRow] == 'a'){
        lastRow-=1;
        if (lastRow<0)
            lastColumn-=1;
    }
    for (int row = 0; row<9; row++)
    {
        for (int column = 0; column<9; column++)
        {
            if(fixed[row][column] == 'a')
            {
                continue;
            }

            else
            {
                while (!checkPossible2(newSudoku, newSudoku[row][column], row, column) || newSudoku[row][column] > 9)
                {
                    newSudoku[row][column]+=1;
                    if (newSudoku[firstRow][firstColumn]>9){
                        if (solutionsNumber == 0){
                            return 0;
                        }
                        else{
                            return 1;
                        }
                    }
                    //This if function runs when all the possibilities have been checked, if it has found a solution it prints it, if not it prints the message.
                    if (newSudoku[row][column]>9)
                    {
                        newSudoku[row][column] = 0;
                        do
                        {
                            if (column > 0)
                            {
                                column-=1;
                            }
                            else
                            {
                                row-=1;
                                column = 8;
                            }
                        } while(fixed[row][column] == 'a');

                        newSudoku[row][column]+=1;


                    }
                }

            }
            //This while loop is entered when the value cannot be entered in the sudoku, then if the value exceeds 9, the loop will manage to start checking the position before this value, and adding 1 to that value, to start checking again.


            if (row == lastRow && column == lastColumn){
                solutionsNumber+=1;
                newSudoku[lastRow][lastColumn]+=1;
                column=lastColumn-1;
                row=lastRow;
            }
            if (solutionsNumber>1){
                return 2;
            }
            //This if funciton checks if with the possibilities analyzed there has been more than one solution. If it is the case, then it prints the specified message.


        }

    }
    return 3;
}

void eraseNotNeeded (int sudoku[9][9]){
    int erasing;
    for (int row = 0; row<9; row++)
    {
        for (int column = 0; column<9; column++)
        {
            if (sudoku[row][column] == 0)
                continue;
            else{
                erasing = sudoku[row][column];
                sudoku[row][column] = 0;
                if (checkIfSolution(sudoku) == 1)
                    continue;
                else{
                    sudoku[row][column] = erasing;
                    continue;
                }
            }
        }
    }

}

int possibilities (int sudoku[9][9], int row, int column){
    int quantity = 0;
    int number = 0;
    for (int i=1; i<=9; i++){
        if (checkPossible(sudoku, i, row, column)){
            quantity+=1;
            number = i;
        }
    }
    if (quantity>1){
        return 0;
    }
    return number;
}

int firstRule (int sudoku[9][9]){
    int repeat = 0;
    int using;
    for (int row = 0; row<9; row++){
        for (int column = 0; column<9; column++){
            if (sudoku[row][column] != 0){
                continue;
            }
            using = possibilities(sudoku, row, column);
            if(using != 0){
                sudoku[row][column] = using;
                repeat+=1;
            }
        }
    }
    return repeat;

}

int secondRule (int sudoku[9][9]){
    int repeat = 0;
    for (int row = 0; row<9; row++){
        for (int column = 0; column<9; column++){
            if (sudoku[row][column] != 0){
                continue;
            }
            for (int value = 1; value<= 9; value++){
                if (checkPossible(sudoku, value, row, column)){
                    for (int i=row-(row%3); i<(row-(row%3)+3); i++){
                        for (int z=column-(column%3); z<(column-(column%3)+3); z++){
                            if (sudoku[i][z] != 0)
                                continue;
                            if (row == i && column == z)
                                continue;
                            if(checkPossible(sudoku, value, i, z)){
                                goto label;
                            }
                        }
                    }
                    sudoku[row][column] = value;
                    repeat+=1;
                    continue;
                    label:
                    for (int i = 0; i<9; i++){
                        if (sudoku[row][i] != 0)
                            continue;
                        if (column == i)
                            continue;
                        if(checkPossible(sudoku, value, row, i))
                            goto otherLabel;
                    }
                    sudoku[row][column] = value;
                    repeat+=1;
                    continue;
                    otherLabel:
                    for (int i = 0; i<9; i++){
                        if (sudoku[i][column] != 0)
                            continue;
                        if (row == i)
                            continue;
                        if(checkPossible(sudoku, value, i, column))
                            goto othernewLabel;
                    }
                    sudoku[row][column] = value;
                    repeat+=1;
                    othernewLabel:
                    continue;
                }


            }
        }
    }


    return repeat;

}

void checkPossibilities(int sudoku[9][9], int *apuntador[9][9]){
    int end = -1;
    int size = 1;
    for (int row = 0; row<9; row++){
        for (int column = 0; column<9; column++){
            (apuntador[row][column]) = malloc(sizeof(int));
            *(apuntador[row][column]) = end;
            if(sudoku[row][column]!=0){
                continue;
            }
            for (int value= 1; value<10; value++){
                if(checkPossible(sudoku, value, row, column)){
                    int *assignArray = malloc(size*sizeof(int));
                    for (int i = 0; i<size-1; i++){
                        assignArray[i] = *(apuntador[row][column] + i);
                    }
                    free(apuntador[row][column]);
                    size += 1;
                    apuntador[row][column] = calloc(size, sizeof(int));

                    for (int i = 0; i<size-2; i++){
                        *(apuntador[row][column] + i) = assignArray[i];
                    }
                    free(assignArray);
                    *(apuntador[row][column] + size-2) = value;
                    *(apuntador[row][column] + size-1) = end;

                }
            }
            size = 1;
        }
    }
}
int placeIfOne(int sudoku[9][9], int *(apuntador[9][9])){
    int value = 0;
    int conteo = 0;
    int check = 0;
    int adding = 0;
    for (int row = 0; row<9; row ++){
        for (int column= 0; column<9; column ++){
            if (sudoku[row][column] != 0)
                continue;
            while(value != -1){
                value = *(apuntador[row][column] + conteo);
                conteo+=1;
                if (value != 0 && value != -1){
                    check+=1;
                    adding = value;
                }
            }
            if (check == 1){
                sudoku[row][column] = adding;
                return 1;
            }
            value = 0;
            conteo = 0;
            check = 0;
        }
    }
    return 0;
}

int thirdRuleRow(int sudoku[9][9], int *(apuntador[9][9])){
    int returnValue = 0;
    int end = 0;
    int conteo = 0;
    int check = 0;
    int rowToCheck = 0;
    int columnToStay = 0;
    for (int row = 0; row <9; row+=3){
        for (int column = 0; column<9; column+=3)
        {
            for (int value = 1; value<10; value++)
            {
                for (int i=row; i<row+3; i++)
                {
                    for (int z=column; z<column+3; z++)
                    {
                        if (sudoku[i][z] != 0){
                            continue;
                        }
                        if (check == 2){
                            end = 0;
                            conteo = 0;
                            check = 0;
                            break;
                        }
                        while(end != -1){
                            end = *(apuntador[i][z] + conteo);
                            conteo+=1;
                            if (value == end){
                                rowToCheck = i;
                                columnToStay = column;
                                check+=1;
                                goto thislabel;
                            }
                        }
                        conteo = 0;
                        end = 0;
                    }
                    thislabel:
                    conteo = 0;
                    end = 0;
                }
                if(check == 1){
                    for (int z = 0; z<9; z++){
                        if (z == columnToStay || z == columnToStay+1 || z == columnToStay+2){
                            continue;
                        }
                        if(sudoku[rowToCheck][z]!= 0)
                            continue;
                        while(end != -1){
                            end = *(apuntador[rowToCheck][z] + conteo);
                            if (end == value){
                                *(apuntador[rowToCheck][z] + conteo) = 0;
                                returnValue += 1;
                                break;
                            }
                            conteo+=1;
                        }
                        conteo = 0;
                        end = 0;

                    }
                }
                end = 0;
                conteo = 0;
                check = 0;
            }

        }
    }
    return returnValue;
}

int thirdRuleColumn(int sudoku[9][9], int *(apuntador[9][9])){
    int returnValue = 0;
    int end = 0;
    int conteo = 0;
    int check = 0;
    int columnToCheck = 0;
    int rowToStay = 0;
    for (int row = 0; row <9; row+=3){
        for (int column = 0; column<9; column+=3)
        {
            for (int value = 1; value<10; value++)
            {
                for (int i=column; i<column+3; i++)
                {
                    for (int z=row; z<row+3; z++)
                    {
                        if (sudoku[z][i] != 0){
                            continue;
                        }
                        if (check == 2){
                            end = 0;
                            conteo = 0;
                            check = 0;
                            break;
                        }
                        while(end != -1){
                            end = *(apuntador[z][i] + conteo);
                            conteo+=1;
                            if (value == end){
                                columnToCheck = i;
                                rowToStay = row;
                                check+=1;
                                goto thislabel;
                            }
                        }
                        conteo = 0;
                        end = 0;
                    }
                    thislabel:
                    conteo = 0;
                    end = 0;
                }
                if(check == 1){
                    for (int z = 0; z<9; z++){
                        if (z == rowToStay || z == rowToStay+1 || z == rowToStay+2){
                            continue;
                        }
                        if(sudoku[z][columnToCheck]!= 0)
                            continue;
                        while(end != -1){
                            end = *(apuntador[z][columnToCheck] + conteo);
                            if (end == value){
                                returnValue += 1;
                                *(apuntador[z][columnToCheck] + conteo) = 0;
                                break;
                            }
                            conteo+=1;

                        }
                        conteo = 0;
                        end = 0;

                    }
                }
                end = 0;
                conteo = 0;
                check = 0;
            }

        }
    }
    return returnValue;
}

int placeIfOnly(int sudoku[9][9], int *(apuntador[9][9])){
    int end = 0;
    int conteo = 0;
    int check = 0;
    int partialRow = 0;
    int partialColumn = 0;
    for (int value = 1; value<10; value ++){
        for (int row = 0; row<9; row++){
            for (int column = 0; column<9; column++){
                if (sudoku[row][column] != 0){
                    continue;
                }
                if (check>=2){
                    check = 0;
                    break;
                }
                while(end != -1){
                    end = *(apuntador[row][column] + conteo);
                    if (end == value){
                        check += 1;
                        partialRow=row;
                        partialColumn=column;
                    }
                    conteo+=1;
                }
                conteo = 0;
                end = 0;
            }
            if (check == 1){
                sudoku[partialRow][partialColumn] = value;
                return 1;
            }
            check = 0;
        }
    }
    for (int value = 1; value<10; value ++){
        for (int column = 0; column<9; column++){
            for (int row = 0; row<9; row++){
                if (sudoku[row][column] != 0){
                    continue;
                }
                if (check>=2){
                    check = 0;
                    break;
                }
                while(end != -1){
                    end = *(apuntador[row][column] + conteo);
                    if (end == value){
                        check += 1;
                        partialRow=row;
                        partialColumn=column;
                    }
                    conteo+=1;
                }
                conteo = 0;
                end = 0;
            }
            if (check == 1){
                sudoku[partialRow][partialColumn] = value;
                return 1;
            }
            check = 0;
        }
    }

    for (int row = 0; row <9; row+=3){
        for (int column = 0; column<9; column+=3)
        {
            for (int value = 1; value<10; value++)
            {
                for (int i=row; i<row+3; i++)
                {
                    for (int z=column; z<column+3; z++)
                    {
                        if (sudoku[i][z] != 0){
                            continue;
                        }
                        if (check == 2){
                            end = 0;
                            conteo = 0;
                            check = 0;
                            goto newlabel;
                        }
                        while(end != -1){
                            end = *(apuntador[i][z] + conteo);
                            conteo+=1;
                            if (value == end){
                                partialRow = i;
                                partialColumn = column;
                                check+=1;
                            }
                        }
                        conteo = 0;
                        end = 0;
                    }
                }
                if (check == 1){
                    sudoku[partialRow][partialColumn] = value;
                    return 1;
                }
                check = 0;
                newlabel:
                continue;
            }
        }
    }


    return 0;
}


int fourthRuleCorrectedRows(int sudoku[9][9], int*(apuntador[9][9])){
    int returnValue = 0;
    int columnToCheck = 0;
    int otherCheck = 0;
    int end = 0;
    int conteo = 0;
    int firstRow = -1;
    int secondRow = -1;
    int check = 0;
    int bigCheck = 0;
    int columnToStay1 = 0;
    int columnToStay2 = 0;
    for (int value = 1; value<10; value++){
        for (int row = 0; row<9; row+=3){
            for (int column = 0; column<9; column+=3){
                for (int otherRow = row; otherRow < row+3; otherRow++){
                    for (int otherColumn = column; otherColumn < column + 3; otherColumn++){
                        if (sudoku[otherRow][otherColumn] != 0 )
                            continue;
                        while(end != -1){
                            end = *(apuntador[otherRow][otherColumn] + conteo);
                            conteo+=1;
                            if (value == end){
                                check+=1;
                                if (firstRow == -1){
                                    firstRow = otherRow;
                                    goto label;
                                }
                                else if (secondRow == -1){
                                    secondRow = otherRow;
                                    columnToStay1 = column;
                                    goto label;
                                }
                                else if (check == 3){
                                    goto thislabel;
                                }
                                else if(otherRow == firstRow || otherRow == secondRow){
                                    otherCheck+=1;
                                    if (otherCheck == 1 || otherRow < (row+2))
                                        goto label;
                                }
                                if (otherCheck == 2 && check == 2){
                                    columnToStay2 = column;
                                    columnToCheck = 0;
                                    while(columnToCheck == columnToStay1 || columnToCheck == columnToStay2){
                                        columnToCheck+=3;
                                    }
                                    for (int i = firstRow; i<(firstRow+3); i++){
                                        if (i != firstRow && i != secondRow)
                                            continue;
                                        for (int z = columnToCheck; z<(columnToCheck+3); z++){
                                            if (sudoku[i][z] != 0){
                                                continue;
                                            }
                                            end = 0;
                                            conteo = 0;
                                            while(end != -1){
                                                end = *(apuntador[i][z] + conteo);
                                                if (end == value){
                                                    *(apuntador[i][z] + conteo) = 0;
                                                    break;
                                                }
                                                conteo+=1;

                                            }
                                            conteo = 0;
                                            end = 0;

                                        }
                                    }
                                }
                            }
                        }
                        end = 0;
                        conteo = 0;
                    }
                    bigCheck += 1;
                    label:
                    end = 0;
                    conteo = 0;
                    continue;
                }
                check = 0;
                otherCheck = 0;
                continue;
                thislabel:
                otherCheck = 0;
                end = 0;
                conteo = 0;
                check = 0;
                if (bigCheck == 0){
                    firstRow = -1;
                    secondRow = -1;
                }
                continue;
            }
            bigCheck = 0;
            firstRow = -1;
            secondRow = -1;
        }
    }
    return returnValue;
}

int fourthRuleCorrectedColumns(int sudoku[9][9], int*(apuntador[9][9])){
    int returnValue = 0;
    int rowToCheck = 0;
    int otherCheck = 0;
    int end = 0;
    int conteo = 0;
    int firstColumn = -1;
    int secondColumn = -1;
    int check = 0;
    int bigCheck = 0;
    int rowToStay1 = 0;
    int rowToStay2 = 0;
    for (int value = 1; value<10; value++){
        for (int column = 0; column<9; column+=3){
            for (int row = 0; row<9; row+=3){
                for (int otherColumn = column; otherColumn < column + 3; otherColumn++){
                    for (int otherRow = row; otherRow < row+3; otherRow++){
                        if (sudoku[otherRow][otherColumn] != 0 )
                            continue;
                        while(end != -1){
                            end = *(apuntador[otherRow][otherColumn] + conteo);
                            conteo+=1;
                            if (value == end){
                                check+=1;
                                if (firstColumn == -1){
                                    firstColumn = otherColumn;
                                    goto label;
                                }
                                else if (secondColumn == -1){
                                    secondColumn = otherColumn;
                                    rowToStay1 = row;
                                    goto label;
                                }
                                else if (check == 3){
                                    goto thislabel;
                                }
                                else if(otherColumn == firstColumn || otherColumn == secondColumn){
                                    otherCheck+=1;
                                    if (otherCheck == 1 || otherColumn < (column+2))
                                        goto label;
                                }
                                if (otherCheck == 2 && check == 2){
                                    rowToStay2 = row;
                                    rowToCheck = 0;
                                    while(rowToCheck == rowToStay1 || rowToCheck == rowToStay2){
                                        rowToCheck+=3;
                                    }
                                    for (int i = firstColumn; i<(firstColumn+3); i++){
                                        if (i != firstColumn && i != secondColumn)
                                            continue;
                                        for (int z = rowToCheck; z<(rowToCheck+3); z++){
                                            if (sudoku[z][i] != 0){
                                                continue;
                                            }
                                            end = 0;
                                            conteo = 0;
                                            while(end != -1){
                                                end = *(apuntador[z][i] + conteo);
                                                if (end == value){
                                                    *(apuntador[z][i] + conteo) = 0;
                                                    returnValue += 1;
                                                    break;
                                                }
                                                conteo+=1;

                                            }
                                            conteo = 0;
                                            end = 0;

                                        }
                                    }
                                }
                            }
                        }
                        end = 0;
                        conteo = 0;
                    }
                    bigCheck += 1;
                    label:
                    end = 0;
                    conteo = 0;
                    continue;
                }
                check = 0;
                otherCheck = 0;
                continue;
                thislabel:
                otherCheck = 0;
                end = 0;
                conteo = 0;
                check = 0;
                if (bigCheck == 0){
                    firstColumn = -1;
                    secondColumn = -1;
                }
                continue;
            }
            bigCheck = 0;
            firstColumn = -1;
            secondColumn = -1;
        }
    }
    return returnValue;

}

int nakedDoubleColumn(int sudoku[9][9], int*(apuntador[9][9])){
    int returnValue = 0;
    int end = 0;
    int conteo = 0;
    int check = 0;
    int rowOne = 0;
    int rowTwo = 0;
    int checkedColumn = 0;
    for (int column = 0; column<9; column++){
        for (int firstValue = 1; firstValue<10; firstValue++){
            for (int secondValue = firstValue+1; secondValue<10; secondValue++){
                for (int row = 0; row<9; row++){
                    end = 0;
                    conteo = 0;
                    if (sudoku[row][column] != 0)
                        continue;
                    end = *(apuntador[row][column]);
                    while(end != -1){
                        if (end != firstValue && end != secondValue){
                            goto label;
                        }
                        conteo+=1;
                        end = *(apuntador[row][column] + conteo);
                    }
                    if (check == 0){
                        rowOne = row;
                        checkedColumn = column;
                    }
                    if (check == 1){
                        rowTwo = row;
                    }
                    check+=1;
                    if (check == 2){
                        for (int newRow = 0; newRow<9; newRow++){
                            if (sudoku[newRow][checkedColumn] != 0)
                                continue;
                            if (newRow == rowOne || newRow == rowTwo)
                                continue;
                            conteo = 0;
                            end = *(apuntador[newRow][checkedColumn]);
                            while(end != -1){
                                if (end == firstValue){
                                    *(apuntador[newRow][checkedColumn] + conteo) = 0;
                                    returnValue += 1;
                                }
                                if (end == secondValue){
                                    *(apuntador[newRow][checkedColumn] + conteo) = 0;
                                    returnValue += 1;
                                }
                                conteo+=1;
                                end = *(apuntador[newRow][checkedColumn] + conteo);
                            }

                        }


                    }
                    label:
                    conteo = 0;
                    end = 0;
                }
                check = 0;
            }
        }
    }
    return returnValue;
}

int nakedDoubleRow(int sudoku[9][9], int*(apuntador[9][9])){
    int returnValue = 0;
    int end = 0;
    int conteo = 0;
    int check = 0;
    int columnOne = 0;
    int columnTwo = 0;
    int checkedRow = 0;
    for (int row = 0; row<9; row++){
        for (int firstValue = 1; firstValue<10; firstValue++){
            for (int secondValue = firstValue+1; secondValue<10; secondValue++){
                for (int column = 0; column<9; column++){
                    end = 0;
                    conteo = 0;
                    if (sudoku[row][column] != 0)
                        continue;
                    end = *(apuntador[row][column]);
                    while(end != -1){
                        if (end != firstValue && end != secondValue){
                            goto label;
                        }
                        conteo+=1;
                        end = *(apuntador[row][column] + conteo);
                    }
                    if (check == 0){
                        columnOne = column;
                        checkedRow = row;
                    }
                    if (check == 1){
                        columnTwo = column;
                    }
                    check+=1;
                    if (check == 2){
                        for (int newColumn = 0; newColumn<9; newColumn++){
                            if (sudoku[checkedRow][newColumn] != 0)
                                continue;
                            if (newColumn == columnOne || newColumn == columnTwo)
                                continue;
                            conteo = 0;
                            end = *(apuntador[checkedRow][newColumn]);
                            while(end != -1){
                                if (end == firstValue){
                                    *(apuntador[checkedRow][newColumn] + conteo) = 0;
                                    returnValue += 1;
                                }
                                if (end == secondValue){
                                    returnValue += 1;
                                    *(apuntador[checkedRow][newColumn] + conteo) = 0;
                                }
                                conteo+=1;
                                end = *(apuntador[checkedRow][newColumn] + conteo);
                            }

                        }


                    }
                    label:
                    conteo = 0;
                    end = 0;
                }
                check = 0;
            }
        }
    }
    return returnValue;
}

int nakedDoubleCell(int sudoku[9][9], int*(apuntador[9][9])){
    int returnValue = 0;
    int columnOne = 0;
    int columnTwo = 0;
    int rowOne = 0;
    int rowTwo = 0;
    int check = 0;
    int end = 0;
    int conteo = 0;
    for (int firstValue = 1; firstValue<10; firstValue++){
        for (int secondValue = firstValue+1; secondValue<10; secondValue++){
            for (int row = 0; row <9; row+=3){
                for (int column = 0; column<9; column+=3) {
                    for (int i=row; i<row+3; i++) {
                        for (int z=column; z<column+3; z++){
                            end = 0;
                            conteo = 0;
                            if (sudoku[i][z] != 0)
                                continue;
                            end = *(apuntador[i][z]);
                            while(end != -1){
                                if (end != firstValue && end != secondValue){
                                    goto label;
                                }
                                conteo+=1;
                                end = *(apuntador[i][z] + conteo);
                            }
                            if (check == 0){
                                columnOne = z;
                                rowOne = i;
                            }
                            if (check == 1){
                                columnTwo = z;
                                rowTwo = i;
                            }
                            check +=1;
                            if (check == 2){
                                for (int a=row; a<row+3; a++) {
                                    for (int b=column; b<column+3; b++){
                                        if (sudoku[a][b] != 0)
                                            continue;
                                        if ((a == rowOne && b == columnOne) || (a == rowTwo && b == columnTwo))
                                            continue;
                                        conteo = 0;
                                        end = *(apuntador[a][b]);
                                        while(end != -1){
                                            if (end == firstValue){
                                                *(apuntador[a][b] + conteo) = 0;
                                                returnValue += 1;
                                            }
                                            if (end == secondValue){
                                                *(apuntador[a][b] + conteo) = 0;
                                                returnValue += 1;
                                            }
                                            conteo+=1;
                                            end = *(apuntador[a][b] + conteo);
                                        }

                                    }


                                }
                            }
                            label:
                            conteo = 0;
                            end = 0;
                        }
                    }
                    check = 0;
                }
            }
        }
    }
    return returnValue;
}

int nakedTripleColumn(int sudoku[9][9], int*(apuntador[9][9])){
    int returnValue = 0;
    int end = 0;
    int conteo = 0;
    int check = 0;
    int rowOne = 0;
    int rowTwo = 0;
    int rowThree = 0;
    int checkedColumn = 0;
    for (int column = 0; column<9; column++){
        for (int firstValue = 1; firstValue<10; firstValue++){
            for (int secondValue = firstValue+1; secondValue<10; secondValue++){
                for (int thirdValue = secondValue+1; thirdValue<10; thirdValue++){
                    for (int row = 0; row<9; row++){
                        end = 0;
                        conteo = 0;
                        if (sudoku[row][column] != 0)
                            continue;
                        end = *(apuntador[row][column]);
                        while(end != -1){
                            if (end != firstValue && end != secondValue && end != thirdValue){
                                goto label;
                            }
                            conteo+=1;
                            end = *(apuntador[row][column] + conteo);
                        }
                        if (check == 0){
                            rowOne = row;
                            checkedColumn = column;
                        }
                        if (check == 1){
                            rowTwo = row;
                        }
                        if (check == 2){
                            rowThree = row;
                        }
                        check+=1;
                        if (check == 3){
                            for (int newRow = 0; newRow<9; newRow++){
                                if (sudoku[newRow][checkedColumn] != 0)
                                    continue;
                                if (newRow == rowOne || newRow == rowTwo || newRow == rowThree)
                                    continue;
                                conteo = 0;
                                end = *(apuntador[newRow][checkedColumn]);
                                while(end != -1){
                                    if (end == firstValue){
                                        *(apuntador[newRow][checkedColumn] + conteo) = 0;
                                        returnValue += 1;
                                    }
                                    if (end == secondValue){
                                        *(apuntador[newRow][checkedColumn] + conteo) = 0;
                                        returnValue += 1;
                                    }
                                    if (end == thirdValue){
                                        *(apuntador[newRow][checkedColumn] + conteo) = 0;
                                        returnValue += 1;
                                    }
                                    conteo+=1;
                                    end = *(apuntador[newRow][checkedColumn] + conteo);
                                }

                            }


                        }
                        label:
                        conteo = 0;
                        end = 0;
                    }
                    check = 0;
                }
            }
        }
    }
    return returnValue;
}

int nakedTripleRow(int sudoku[9][9], int*(apuntador[9][9])){
    int returnValue = 0;
    int end = 0;
    int conteo = 0;
    int check = 0;
    int columnOne = 0;
    int columnTwo = 0;
    int columnThree = 0;
    int checkedRow = 0;
    for (int row = 0; row<9; row++){
        for (int firstValue = 1; firstValue<10; firstValue++){
            for (int secondValue = firstValue+1; secondValue<10; secondValue++){
                for (int thirdValue = secondValue+1; thirdValue<10; thirdValue++){
                    for (int column = 0; column<9; column++){
                        end = 0;
                        conteo = 0;
                        if (sudoku[row][column] != 0)
                            continue;
                        end = *(apuntador[row][column]);
                        while(end != -1){
                            if (end != firstValue && end != secondValue && end !=thirdValue){
                                goto label;
                            }
                            conteo+=1;
                            end = *(apuntador[row][column] + conteo);
                        }
                        if (check == 0){
                            columnOne = column;
                            checkedRow = row;
                        }
                        if (check == 1){
                            columnTwo = column;
                        }
                        if (check == 2){
                            columnThree = column;
                        }
                        check+=1;
                        if (check == 3){
                            for (int newColumn = 0; newColumn<9; newColumn++){
                                if (sudoku[checkedRow][newColumn] != 0)
                                    continue;
                                if (newColumn == columnOne || newColumn == columnTwo || newColumn == columnThree)
                                    continue;
                                conteo = 0;
                                end = *(apuntador[checkedRow][newColumn]);
                                while(end != -1){
                                    if (end == firstValue){
                                        *(apuntador[checkedRow][newColumn] + conteo) = 0;
                                        returnValue += 1;
                                    }
                                    if (end == secondValue){
                                        *(apuntador[checkedRow][newColumn] + conteo) = 0;
                                        returnValue += 1;
                                    }
                                    if (end == thirdValue){
                                        *(apuntador[checkedRow][newColumn] + conteo) = 0;
                                        returnValue += 1;
                                    }
                                    conteo+=1;
                                    end = *(apuntador[checkedRow][newColumn] + conteo);
                                }

                            }


                        }
                        label:
                        conteo = 0;
                        end = 0;
                    }
                    check = 0;
                }
            }
        }
    }
    return returnValue;
}

int nakedTripleCell(int sudoku[9][9], int*(apuntador[9][9])){
    int returnValue = 0;
    int columnOne = 0;
    int columnTwo = 0;
    int rowOne = 0;
    int rowTwo = 0;
    int check = 0;
    int end = 0;
    int conteo = 0;
    int rowThree = 0;
    int columnThree = 0;
    for (int firstValue = 1; firstValue<10; firstValue++){
        for (int secondValue = firstValue+1; secondValue<10; secondValue++){
            for (int thirdValue = secondValue+1; thirdValue<10; thirdValue++){
                for (int row = 0; row <9; row+=3){
                    for (int column = 0; column<9; column+=3) {
                        for (int i=row; i<row+3; i++) {
                            for (int z=column; z<column+3; z++){
                                end = 0;
                                conteo = 0;
                                if (sudoku[i][z] != 0)
                                    continue;
                                end = *(apuntador[i][z]);
                                while(end != -1){
                                    if (end != firstValue && end != secondValue && end != thirdValue){
                                        goto label;
                                    }
                                    conteo+=1;
                                    end = *(apuntador[i][z] + conteo);
                                }
                                if (check == 0){
                                    columnOne = z;
                                    rowOne = i;
                                }
                                if (check == 1){
                                    columnTwo = z;
                                    rowTwo = i;
                                }
                                if (check == 2){
                                    columnThree = z;
                                    rowThree = i;
                                }
                                check +=1;
                                if (check == 3){
                                    for (int a=row; a<row+3; a++) {
                                        for (int b=column; b<column+3; b++){
                                            if (sudoku[a][b] != 0)
                                                continue;
                                            if ((a == rowOne && b == columnOne) || (a == rowTwo && b == columnTwo) || (a == rowThree && b == columnThree))
                                                continue;
                                            conteo = 0;
                                            end = *(apuntador[a][b]);
                                            while(end != -1){
                                                if (end == firstValue){
                                                    *(apuntador[a][b] + conteo) = 0;
                                                    returnValue += 1;
                                                }
                                                if (end == secondValue){
                                                    *(apuntador[a][b] + conteo) = 0;
                                                    returnValue += 1;
                                                }
                                                if (end == thirdValue){
                                                    *(apuntador[a][b] + conteo) = 0;
                                                    returnValue += 1;
                                                }
                                                conteo+=1;
                                                end = *(apuntador[a][b] + conteo);
                                            }

                                        }


                                    }
                                }
                                label:
                                conteo = 0;
                                end = 0;
                            }
                        }
                        check = 0;
                    }
                }
            }
        }
    }
    return returnValue;
}

int nakedQuadrupleColumn(int sudoku[9][9], int*(apuntador[9][9])){
    int returnValue = 0;
    int end = 0;
    int conteo = 0;
    int check = 0;
    int rowOne = 0;
    int rowTwo = 0;
    int rowThree = 0;
    int rowFour = 0;
    int checkedColumn = 0;
    for (int column = 0; column<9; column++){
        for (int firstValue = 1; firstValue<10; firstValue++){
            for (int secondValue = firstValue+1; secondValue<10; secondValue++){
                for (int thirdValue = secondValue+1; thirdValue<10; thirdValue++){
                    for (int fourthValue = thirdValue+1; fourthValue<10; fourthValue++){
                        for (int row = 0; row<9; row++){
                            end = 0;
                            conteo = 0;
                            if (sudoku[row][column] != 0)
                                continue;
                            end = *(apuntador[row][column]);
                            while(end != -1){
                                if (end != firstValue && end != secondValue && end != thirdValue && end != fourthValue){
                                    goto label;
                                }
                                conteo+=1;
                                end = *(apuntador[row][column] + conteo);
                            }
                            if (check == 0){
                                rowOne = row;
                                checkedColumn = column;
                            }
                            if (check == 1){
                                rowTwo = row;
                            }
                            if (check == 2){
                                rowThree = row;
                            }
                            if (check == 3){
                                rowFour = row;
                            }
                            check+=1;
                            if (check == 4){
                                for (int newRow = 0; newRow<9; newRow++){
                                    if (sudoku[newRow][checkedColumn] != 0)
                                        continue;
                                    if (newRow == rowOne || newRow == rowTwo || newRow == rowThree || newRow == rowFour)
                                        continue;
                                    conteo = 0;
                                    end = *(apuntador[newRow][checkedColumn]);
                                    while(end != -1){
                                        if (end == firstValue){
                                            *(apuntador[newRow][checkedColumn] + conteo) = 0;
                                            returnValue += 1;

                                        }
                                        if (end == secondValue){
                                            *(apuntador[newRow][checkedColumn] + conteo) = 0;
                                            returnValue += 1;

                                        }
                                        if (end == thirdValue){
                                            *(apuntador[newRow][checkedColumn] + conteo) = 0;
                                            returnValue += 1;
                                        }
                                        if (end == fourthValue){
                                            *(apuntador[newRow][checkedColumn] + conteo) = 0;
                                            returnValue += 1;
                                        }
                                        conteo+=1;
                                        end = *(apuntador[newRow][checkedColumn] + conteo);
                                    }

                                }


                            }
                            label:
                            conteo = 0;
                            end = 0;
                        }
                        check = 0;
                    }
                }
            }
        }
    }
    return returnValue;
}

int nakedQuadrupleRow(int sudoku[9][9], int*(apuntador[9][9])){
    int returnValue = 0;
    int end = 0;
    int conteo = 0;
    int check = 0;
    int columnOne = 0;
    int columnTwo = 0;
    int columnThree = 0;
    int columnFour = 0;
    int checkedRow = 0;
    for (int row = 0; row<9; row++){
        for (int firstValue = 1; firstValue<10; firstValue++){
            for (int secondValue = firstValue+1; secondValue<10; secondValue++){
                for (int thirdValue = secondValue+1; thirdValue<10; thirdValue++){
                    for (int fourthValue = thirdValue+1; fourthValue<10; fourthValue++){
                        for (int column = 0; column<9; column++){
                            end = 0;
                            conteo = 0;
                            if (sudoku[row][column] != 0)
                                continue;
                            end = *(apuntador[row][column]);
                            while(end != -1){
                                if (end != firstValue && end != secondValue && end !=thirdValue && end!=fourthValue){
                                    goto label;
                                }
                                conteo+=1;
                                end = *(apuntador[row][column] + conteo);
                            }
                            if (check == 0){
                                columnOne = column;
                                checkedRow = row;
                            }
                            if (check == 1){
                                columnTwo = column;
                            }
                            if (check == 2){
                                columnThree = column;
                            }
                            if (check == 3){
                                columnFour = column;
                            }
                            check+=1;
                            if (check == 4){
                                for (int newColumn = 0; newColumn<9; newColumn++){
                                    if (sudoku[checkedRow][newColumn] != 0)
                                        continue;
                                    if (newColumn == columnOne || newColumn == columnTwo || newColumn == columnThree || newColumn == columnFour)
                                        continue;
                                    conteo = 0;
                                    end = *(apuntador[checkedRow][newColumn]);
                                    while(end != -1){
                                        if (end == firstValue){
                                            *(apuntador[checkedRow][newColumn] + conteo) = 0;
                                            returnValue += 1;
                                        }
                                        if (end == secondValue){
                                            *(apuntador[checkedRow][newColumn] + conteo) = 0;
                                            returnValue += 1;
                                        }
                                        if (end == thirdValue){
                                            *(apuntador[checkedRow][newColumn] + conteo) = 0;
                                            returnValue += 1;
                                        }
                                        if (end == fourthValue){
                                            *(apuntador[checkedRow][newColumn] + conteo) = 0;
                                            returnValue += 1;
                                        }
                                        conteo+=1;
                                        end = *(apuntador[checkedRow][newColumn] + conteo);
                                    }

                                }


                            }
                            label:
                            conteo = 0;
                            end = 0;
                        }
                        check = 0;
                    }
                }
            }
        }
    }
    return returnValue;
}

int nakedQuadrupleCell(int sudoku[9][9], int*(apuntador[9][9])){
    int returnValue = 0;
    int columnOne = 0;
    int columnTwo = 0;
    int rowOne = 0;
    int rowTwo = 0;
    int check = 0;
    int end = 0;
    int conteo = 0;
    int rowThree = 0;
    int columnThree = 0;
    int rowFour = 0;
    int columnFour = 0;
    for (int firstValue = 1; firstValue<10; firstValue++){
        for (int secondValue = firstValue+1; secondValue<10; secondValue++){
            for (int thirdValue = secondValue+1; thirdValue<10; thirdValue++){
                for (int fourthValue = thirdValue+1; fourthValue<10; fourthValue++){
                    for (int row = 0; row <9; row+=3){
                        for (int column = 0; column<9; column+=3) {
                            for (int i=row; i<row+3; i++) {
                                for (int z=column; z<column+3; z++){
                                    end = 0;
                                    conteo = 0;
                                    if (sudoku[i][z] != 0)
                                        continue;
                                    end = *(apuntador[i][z]);
                                    while(end != -1){
                                        if (end != firstValue && end != secondValue && end != thirdValue && end != fourthValue){
                                            goto label;
                                        }
                                        conteo+=1;
                                        end = *(apuntador[i][z] + conteo);
                                    }
                                    if (check == 0){
                                        columnOne = z;
                                        rowOne = i;
                                    }
                                    if (check == 1){
                                        columnTwo = z;
                                        rowTwo = i;
                                    }
                                    if (check == 2){
                                        columnThree = z;
                                        rowThree = i;
                                    }
                                    if (check == 3){
                                        columnFour = z;
                                        rowFour = i;
                                    }
                                    check +=1;
                                    if (check == 4){
                                        for (int a=row; a<row+3; a++) {
                                            for (int b=column; b<column+3; b++){
                                                if (sudoku[a][b] != 0)
                                                    continue;
                                                if ((a == rowOne && b == columnOne) || (a == rowTwo && b == columnTwo) || (a == rowThree && b == columnThree) || (a == rowFour && b == columnFour))
                                                    continue;
                                                conteo = 0;
                                                end = *(apuntador[a][b]);
                                                while(end != -1){
                                                    if (end == firstValue){
                                                        *(apuntador[a][b] + conteo) = 0;
                                                        returnValue += 1;
                                                    }
                                                    if (end == secondValue){
                                                        *(apuntador[a][b] + conteo) = 0;
                                                        returnValue += 1;
                                                    }
                                                    if (end == thirdValue){
                                                        *(apuntador[a][b] + conteo) = 0;
                                                        returnValue += 1;
                                                    }
                                                    if (end == fourthValue){
                                                        *(apuntador[a][b] + conteo) = 0;
                                                        returnValue += 1;
                                                    }
                                                    conteo+=1;
                                                    end = *(apuntador[a][b] + conteo);
                                                }

                                            }


                                        }
                                    }
                                    label:
                                    conteo = 0;
                                    end = 0;
                                }
                            }
                            check = 0;
                        }
                    }
                }
            }
        }
    }
    return returnValue;
}

bool checkPossible2(int sudoku[9][9], int value, int row, int column)
{
    if (value == 0)
    {
        return false;
    }
    for (int i = 0; i<9; i++)
    {
        if (column == i)
            continue;
        if (sudoku[row][i] == value)
            return false;
    }
    for (int z= 0; z<9; z++)
    {
        if (row == z)
            continue;
        if (sudoku[z][column] == value)
            return false;
    }
    for (int i=row-(row%3); i<(row-(row%3)+3); i++){
        for (int z=column-(column%3); z<(column-(column%3)+3); z++){
            if (row == i && column == z)
                continue;
            if(sudoku[i][z] == value)
                return false;
        }
    }


    return true;
}


int checkIfSolution2(int sudoku[9][9]){
    int newSudoku[9][9] = {0};
    int solutionsNumber = 0;
    char fixed[9][9];
    for (int row = 0; row<9; row++){
        for (int column = 0; column<9; column++){
            if (sudoku[row][column] != 0){
                newSudoku[row][column] = sudoku[row][column];
                fixed[row][column] = 'a';
            }
            else{
                fixed[row][column] = 'c';
            }
        }
    }
    //The fixed matrix has the objective of identifying which numbers are provided by the puzzle and shouldn't be changed.
    int firstColumn = 0;
    int firstRow = 0;
    while (fixed[firstRow][firstColumn] == 'a'){
        firstColumn+=1;
        if (firstColumn == 9)
            firstRow+=1;
    }
    //This while loop has the sole purpose of identifying which number is the first number that isn't provided by the puzzle. This 'a' variable will be used to check if the puzzle has solution or not. This will be done by checking if in that position the value has exceeded 9.
    int lastColumn = 8;
    int lastRow = 8;
    while (fixed[8][lastRow] == 'a'){
        lastRow-=1;
        if (lastRow<0)
            lastColumn-=1;
    }
    for (int row = 0; row<9; row++)
    {
        for (int column = 0; column<9; column++)
        {
            if(fixed[row][column] == 'a')
            {
                continue;
            }

            else
            {
                while (!checkPossible2(newSudoku, newSudoku[row][column], row, column) || newSudoku[row][column] > 9)
                {
                    newSudoku[row][column]+=1;
                    if (newSudoku[firstRow][firstColumn]>9){
                        if (solutionsNumber == 0){
                            return 0;
                        }
                        else{
                            return 1;
                        }
                    }
                    //This if function runs when all the possibilities have been checked, if it has found a solution it prints it, if not it prints the message.
                    if (newSudoku[row][column]>9)
                    {
                        newSudoku[row][column] = 0;
                        do
                        {
                            if (column > 0)
                            {
                                column-=1;
                            }
                            else
                            {
                                row-=1;
                                column = 8;
                            }
                        } while(fixed[row][column] == 'a');

                        newSudoku[row][column]+=1;


                    }
                }

            }
            //This while loop is entered when the value cannot be entered in the sudoku, then if the value exceeds 9, the loop will manage to start checking the position before this value, and adding 1 to that value, to start checking again.


            if (row == lastRow && column == lastColumn){
                solutionsNumber+=1;
                newSudoku[lastRow][lastColumn]+=1;
                column=lastColumn-1;
                row=lastRow;
            }
            if (solutionsNumber>1){
                return 2;
            }
            //This if funciton checks if with the possibilities analyzed there has been more than one solution. If it is the case, then it prints the specified message.


        }

    }
    return 3;
}



