#include <stdio.h>
#include "sudoku.h"

int verifica_cella(sudoku_t);


int sudoku_verify(sudoku_t s){
	int ris, i, j, k, l;

	ris=1;

	for (i=0; i<SIZE && ris; i++)
		for (j=0; j<SIZE && ris; j++)
			if (s[i][j])
				for (k=0; k<j && ris; k++)
					if (to_cell_value(s[i][k])==to_cell_value(s[i][j]))
						ris=0;
	
	for (i=0; i<SIZE && ris; i++)
		for (j=0; j<SIZE && ris; j++)
			if (s[j][i])
				for (k=0; k<j && ris; k++)
					if (to_cell_value(s[k][i])==to_cell_value(s[j][i]))
						ris=0;

	for (i=0; i<SMALL_SIZE && ris; i++){
		for (j=0; j<SMALL_SIZE && ris; j++){
			printf("s[%d][%d]=%d\n", i, j, s[i*SMALL_SIZE][j*SMALL_SIZE]);
			ris=verifica_cella(&s[i*SMALL_SIZE][j*SMALL_SIZE]);
		}
	}
	return ris;
}

int verifica_cella(sudoku_t s){
	int i, j, ris;

	ris=1;
	for (i=0; i<SIZE && ris; i++){
		if (s[i/SMALL_SIZE][i%SMALL_SIZE]){

			for(j=0; j<i && ris; j++){
				if (to_cell_value(s[j/SMALL_SIZE][j%SMALL_SIZE])==to_cell_value(s[i/SMALL_SIZE][i%SMALL_SIZE]))
					ris=0;
			}
		}
	}
	return ris;
}

int sudoku_check_sol(sudoku_t sol, sudoku_t sud){
	int i, j;
	int ris;

	ris=1;

	for (i=0; i<SIZE && ris; i++){
		for (j=0; j<SIZE && ris; j++){
			if (sud[i][j]!=0 && !is_user_value(sud[i][j]))
				if (sol[i][j]!=to_cell_value(sol[i][j]))
					ris=0;
		}
	}
	return ris;
}