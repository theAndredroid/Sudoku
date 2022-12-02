#define STR_FORMAT_SIZE 81
#define EMPTY_CELL_C '_'
#define OFFESET_DEFAULT 9
#define SIZE 9
#define SMALL_SIZE 3

#define TRUE 1
#define FALSE 0

#define NEW 1
#define ADD_VAL 2
#define REM_VAL 3
#define VERIFY 4
#define SET_SOL 5
#define RESTART 6

typedef int sudoku_t[SIZE][SIZE];

void sudoku_view(sudoku_t); // matt
int sudoku_from_str(sudoku_t, char format_str[], int game); // matt
int sudoku_verify(sudoku_t); /*FATTOOOOOOOO*/
int sudoku_add(sudoku_t, int row, int column, int value); // matt
int sudoku_remove(sudoku_t, int row, int column); // matt
int is_user_value(int val); // matt
int to_cell_value(int val); // matt
int sudoku_complete(sudoku_t); // matt
int sudoku_check_sol(sudoku_t sol, sudoku_t sud);
void sudoku_new_game(sudoku_t);
void set_sol(sudoku_t);
void menu();
void display_opts();
