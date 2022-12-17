/*
 * Description:  A simple implementation of Conway's Game of Life.
 * Author:       Sunny Zhang
 * CS username:  dv21szg
 * Date:         2022.03.18
 * Input:        Choice of initial configuration and then instruction
 *               to step or exit.
 * Output:       Prints the game field in each step.
 * Limitations:  No validation of input.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Constants, representation of states */
#define ALIVE 'X'
#define DEAD '.'

/* Declaration of data structure */
typedef struct {
	char current;
	char next;
} cell;

/* Declaration of functions */
void init_field(const int rows, const int cols,
                cell field[rows][cols]);
void load_glider(const int rows, const int cols,
                 cell field[rows][cols]);
void load_semaphore(const int rows, const int cols,
                 cell field[rows][cols]);
void load_random(const int rows, const int cols,
                 cell field[rows][cols]);
void load_custom(const int rows, const int cols,
                 cell field[rows][cols]);
void print_field(const int rows, const int cols,
                 cell field[rows][cols]);
void game_rule(const int rows, const int cols,
               cell field[rows][cols], int r, int c);
int count_neighbors(const int rows, const int cols,
                    cell field[rows][cols], int r, int c);
int cell_states(const int rows, const int cols,
                cell field[rows][cols], int r, int c);
void update_field(const int rows, const int cols,
                  cell field[rows][cols]);
void print_menu(void);

/*
 * Description: Start and run games, interact with the user.
 * Input:       About what initial structure and whether to step or
 *              exit.
 * Output:      Prints information to the user, and the game field in
 *              each step.
 */
int main(void)
{
	int rows = 20;
	int cols = 20;

	srand(time(0));

	cell field[rows][cols];

	init_field(rows,cols,field);

	print_field(rows,cols,field);
	print_menu();	

	int ch = getchar();

	do{
		if(ch != '\n'){
			exit(0);
		}else{	
			for (int r = 0; r < rows; r++)
				for (int c = 0; c < cols; c++)
					game_rule(rows,cols,field,r,c);
			update_field(rows,cols,field);
			print_field(rows,cols,field);
			print_menu();
		}
	}while(getchar() == '\n');

	return 0;
}


void print_menu(void)
{
	printf("Select one of the following options:\n");
	printf("(enter) Step\n");
	printf("(any) Exit\n");
}


/*
 * Description: Initialize all the cells to dead, then asks the user
 *              about which structure to load, and finally load the
 *              structure.
 * Input:       The field array and its size.
 * Output:      The field array is updated.
 */
void init_field(const int rows, const int cols,
                cell field[rows][cols])
{
	for (int r = 0 ; r < rows ; r++) {
		for (int c = 0 ; c < cols ; c++) {
			field[r][c].current = DEAD;
		}
	}

	printf("Select field spec to load ");
	printf("([G]lider, [S]emaphore, ");
	printf("[R]andom or [C]ustom): ");

	int ch = getchar();

	/* Ignore following newline */
	if (ch != '\n') {
		getchar();
	}

	switch (ch) {
		case 'g':
		case 'G':
			load_glider(rows, cols, field);
			break;
		case 's':
		case 'S':
			load_semaphore(rows, cols, field);
			break;
		case 'r':
		case 'R':
			load_random(rows, cols, field);
			break;
		case 'c':
		case 'C':
		default:
			load_custom(rows, cols, field);
	}
}

/*
 * Description: Inserts a glider into the field.
 * Input:       The field array and its size.
 * Output:      The field array is updated.
 */
void load_glider(const int rows, const int cols,
                 cell field[rows][cols])
{
	field[0][1].current = ALIVE;
	field[1][2].current = ALIVE;
	field[2][0].current = ALIVE;
	field[2][1].current = ALIVE;
	field[2][2].current = ALIVE;
}

/*
 * Description: Inserts a semaphore into the field.
 * Input:       The field array and its size.
 * Output:      The field array is updated.
 */
void load_semaphore(const int rows, const int cols,
                    cell field[rows][cols])
{
	field[8][1].current = ALIVE;
	field[8][2].current = ALIVE;
	field[8][3].current = ALIVE;
}

/*
 * Description: Inserts a random structure into the field.
 * Input:       The field array and its size.
 * Output:      The field array is updated. There is a 50 % chance
 *              that a cell is alive.
 */
void load_random(const int rows, const int cols,
                 cell field[rows][cols])
{
	for(int r = 0; r < rows; r++){
		for(int c = 0; c < cols; c++){
			int status = rand() % 2;

			if(status == 0){
				field[r][c].current = DEAD;
			}else{
				field[r][c].current = ALIVE;
			}
		}
	}
}

/*
 * Description: Let the user specify a structure that then
 *              is inserted into the field.
 * Input:       The field array and its size.
 */
void load_custom(const int rows, const int cols,
                 cell field[rows][cols])
{
	printf("Give custom format string: ");
	do {
		int r, c;
		scanf("%d,%d", &r, &c);
		field[r][c].current = ALIVE;
	} while (getchar() != '\n');
}

/*
 * Description: To print out the current status of the world.
 * Input:       The field array and its size.
 */
void print_field(const int rows, const int cols,
                 cell field[rows][cols])
{
	for(int r = 0; r < rows; r++){
		for(int c = 0; c < cols; c++){
			putchar(field[r][c].current);
			if(c + 1 < cols){
				putchar(' ');
			}else{
				putchar('\n');
			}
		}
	}
}

/*
 * Description: To follow the game rules.
 * Input:       The field array and its size.
 */
void game_rule(const int rows, const int cols,
               cell field[rows][cols], int r, int c)
{
	int count = count_neighbors(rows,cols,field,r,c);

	if(field[r][c].current == ALIVE){
		if(count < 2 || count > 3){
			field[r][c].next = DEAD;
		}else{
			field[r][c].next = ALIVE;
		}
	}else{
		if(count == 3){
			field[r][c].next = ALIVE;
		}else{
			field[r][c].next = DEAD;
		}
	}
}

/*
 * Description: To count the neighbors who are alive.
 * Input:       The field array and its size.
 * Output:      The numbers of alive neighbors.
 */
int count_neighbors(const int rows, const int cols,
                    cell field[rows][cols], int r, int c)
{
	int count = 0;

 	for(int x = r - 1; x <= r + 1; x++){
		for(int y = c -1; y <= c + 1; y++){
			if(x != r || y != c){
				if(cell_states(rows,cols,field,x,y) == ALIVE){
					count++;
				}
			}
		}
	}
	return count;
}

/*
 * Description: To declare the status of the cell.
 * Input:       The field array and its size.
 * Output:      The status of the cell.
 */
int cell_states(const int rows, const int cols,
                cell field[rows][cols], int r, int c)
{
	if(r >= 0 && r < rows && c >= 0 && c < cols){
		return field[r][c].current;
	}else{
		return DEAD;
	/*
	The function now returns a valid state DEAD for invalid cells (indexes outside of the field).
	It would be better to return -1 or similar in the else{} and describe that in the function comment.
	*/
	}
}

/* Description: To update the field
 * Input:       The field array and its size.
 */
void update_field(const int rows, const int cols,
                  cell field[rows][cols])
{
	for(int r = 0; r < rows; r++){
		for(int c = 0; c < cols; c++){
			field[r][c].current = field[r][c].next;
		}
	}
}
