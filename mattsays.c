#include "sudoku.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int is_user_value(int val)
{
    return val >= 1 && val <= 9;
}

int to_cell_value(int val)
{
    if(val >= 10 && val <= 19)
    {
        return val - 10;
    }
    return val;
}

void print_horizzontal_border()
{
    int k;

    // (SIZE*3) + SIZE_PER_CHAR + BORDERS_CHARS
    for(k=0;k<(SIZE * 3) + 3 + 4;k++){
        if(k == 0 || k == 11 || k == 22 | k == 33) {
            printf("+");
        }
        else
        {
            printf("-");
        }
    }
    printf("\n");
}

void sudoku_view(sudoku_t tabella)
{
    int i,j, k,c;

    for(i=0;i<SIZE;i++){
        if(i % 3 == 0)
        {
            print_horizzontal_border();
        }
        
        for(j=0;j<SIZE;j++)
        {
            
            if(j % 3 == 0)
            {
                printf("| ");
            }

            c=tabella[i][j];

            if(c != 0)
            {
                printf("%d",to_cell_value(tabella[i][j]));
            }
            else
            {
                printf(" ");
            }
            

            if(is_user_value(c)){   
                printf("* ");
            }
            else { 
                printf("  ");

            }

            if(j == SIZE - 1)
            {
                printf("| ");
            }
        }
        printf("\n");
    }
    print_horizzontal_border();
}

int sudoku_from_str(sudoku_t sud, char format_str[], int is_game)
{
    if(strlen(format_str) != STR_FORMAT_SIZE)
    {
        return FALSE;
    }

    int i,j;
    char raw_c;

    for(i = 0; i < SIZE; i++) 
    {
        for(j = 0; j < SIZE; j++)
        {
            raw_c = format_str[(i* SIZE) + j];
            if(raw_c == EMPTY_CELL_C)
            {
                sud[i][j] = 0;
            }
            else
            {
                sud[i][j] = atoi(&raw_c) + (is_game * 10);
            }
        }
    }

    return TRUE;
}

int sudoku_remove(sudoku_t sud, int row, int column)
{
    // Check if coords are in range
    if(!(row >= 1 && row <= 9) || !(column >= 1 && column <= 9))
    {
        printf("errore: le coordinate della cella sono errate.\n");
        return FALSE;
    }

    row = row - 1;
    column = column - 1;

    if(sud[row][column] == 0)
    {
        printf("errore: la cella e gia vuota.\n");
        return FALSE;
    }

    if(!(is_user_value(sud[row][column])))
    {
        printf("errore: la cella non e modificabile.\n");
        return FALSE;
    }

    sud[row][column] = 0;
    return TRUE;
}

int sudoku_add(sudoku_t sud, int row, int column, int value)
{
    // Check if coords are in range
    if(!(row >= 1 && row <= 9) || !(column >= 1 && column <= 9))
    {
        printf("errore: le coordinate della cella sono errate.\n");
        return FALSE;
    }

    if(!is_user_value(value))
    {
        printf("errore: i valore inserito non e compreso tra 1 e 9.\n");
        return FALSE;
    }

    row = row - 1;
    column = column - 1;

    if(sud[row][column] != 0)
    {
        printf("errore: la cella non e vuota.\n");
        return FALSE;
    }

    sud[row][column] = value;
    return TRUE;
}

void display_opts()
{
    printf("1 - avvia una nuova partita\n 2 - inserisci valore\n 3 - cancella valore\n 4 - verifica la soluzione attuale\n 5 - carica una soluzione e verificala\n 6 - riavvia partita attuale\n 0 - esci\n");
}

int sudoku_complete(sudoku_t sud)
{
    int i, j;
    int ris;
    ris = 1;

    for(i = 0; i < SIZE && ris; i++)
    {
        for(j = 0; j < SIZE && ris; j++)
        {
            if(sud[i][j] == 0)
                ris = 0;
        }
    }

    return ris;
}

void  print_win()
{
    printf("Hai vinto!!!!!\n");
}

void menu() 
{
    int win;
    int opt;
    int status;
    sudoku_t sol;
    sudoku_t sud;

    int a, b, c;
    char format_str[STR_FORMAT_SIZE + 1];
    
    status = 0;
    opt = 1;

    while(opt)
    {
        switch(opt)
        {
            case NEW || RESTART:
                printf("Inserisci il formato del sudoku: ");
                scanf(" %[^\n]", format_str);
                sudoku_from_str(sud, format_str, TRUE);
                break;
            case ADD_VAL:
            {
                printf("Inserisci le coordinate e il valore: ");
                scanf("%d%d%d", &a, &b, &c);
                status = sudoku_add(sud, a, b, c);
                if(status && sudoku_complete(sud) && sudoku_verify(sud)) 
                {
                    print_win();
                }
            }
            break;
            case REM_VAL:
            {
                printf("Inserisci le coordinate: ");
                scanf("%d%d", &a, &b);
                sudoku_remove(sud, a, b);
            }
            break;
            case VERIFY:
                {
                    if(sudoku_complete(sud) && sudoku_verify(sud))
                    {
                        print_win();
                    }
                }
                break;
            case SET_SOL:
            {
                printf("Inserisci la soluzione: ");
                scanf(" %[^\n]", format_str);
                sudoku_from_str(sol, format_str, FALSE);
                if(sudoku_check_sol(sol, sud) && sudoku_verify(sol))
                {
                    print_win();
                }
            }
            break;
        }

        sudoku_view(sud);
        display_opts();
        printf("option: ");
        scanf("%d", &opt);
    }
    printf("quit.\n");
}