#include "state.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "snake_utils.h"

/* Helper function definitions */
static void set_board_at(game_state_t *state, unsigned int row, unsigned int col, char ch);
static bool is_tail(char c);
static bool is_head(char c);
static bool is_snake(char c);
static char body_to_tail(char c);
static char head_to_body(char c);
static unsigned int get_next_row(unsigned int cur_row, char c);
static unsigned int get_next_col(unsigned int cur_col, char c);
static void find_head(game_state_t *state, unsigned int snum);
static char next_square(game_state_t *state, unsigned int snum);
static void update_tail(game_state_t *state, unsigned int snum);
static void update_head(game_state_t *state, unsigned int snum);

/* Task 1 */
game_state_t *create_default_state() {
    // TODO: Implement this function.
    // Initialize the board
    game_state_t *game = malloc(sizeof(game_state_t));
    game->num_rows = 18;
    int num_cols = 20;

    char **board = malloc(game->num_rows * sizeof(char *));
    board[0] = malloc((num_cols + 1) * sizeof(char));
    strcpy(board[0], "####################\n");
    for (int i = 1; i < game->num_rows - 1; i++) {
        board[i] = malloc((num_cols + 1) * sizeof(char));
        strcpy(board[i], "#                  #\n");
    }
    board[game->num_rows - 1] = malloc((num_cols + 1) * sizeof(char));
    strcpy(board[game->num_rows - 1], "####################\n");

    // Add the food and snake
    //! the snake is hardcodeed, should be modified later
    board[2][9] = '*';
    board[2][2] = 'd';
    board[2][3] = '>';
    board[2][4] = 'D';
    game->board = board;

    // Generate snake
    game->num_snakes = 1;
    snake_t *snake = malloc(game->num_snakes * sizeof(snake_t));
    snake[0].tail_row = snake->tail_col = 2;
    snake[0].head_row = 2;
    snake[0].head_col = 4;
    snake[0].live = true;
    game->snakes = snake;
    return game;
}

/* Task 2 */
void free_state(game_state_t *state) {
    // TODO: Implement this function.
    // Free the board
    char **board = state->board;
    for (int i = 0; i < state->num_rows; i++) {
        free(*(board + i));
    }
    free(board);
    // Free the snakes
    free(state->snakes);
    // Free the game state
    free(state);
    return;
}

/* Task 3 */
void print_board(game_state_t *state, FILE *fp) {
    // TODO: Implement this function.
    for (int i = 0; i < state->num_rows; i++) {
        fprintf(fp, "%s", state->board[i]);
    }

    return;
}

/*
  Saves the current state into filename. Does not modify the state object.
  (already implemented for you).
*/
void save_board(game_state_t *state, char *filename) {
    FILE *f = fopen(filename, "w");
    print_board(state, f);
    fclose(f);
}

/* Task 4.1 */

/*
  Helper function to get a character from the board
  (already implemented for you).
*/
char get_board_at(game_state_t *state, unsigned int row, unsigned int col) { return state->board[row][col]; }

/*
  Helper function to set a character on the board
  (already implemented for you).
*/
static void set_board_at(game_state_t *state, unsigned int row, unsigned int col, char ch) {
    state->board[row][col] = ch;
}

/*
  Returns true if c is part of the snake's tail.
  The snake consists of these characters: "wasd"
  Returns false otherwise.
*/
static bool is_tail(char c) {
    // TODO: Implement this function.
    return (c == 'w' || c == 's' || c == 'a' || c == 'd');
}

/*
  Returns true if c is part of the snake's head.
  The snake consists of these characters: "WASDx"
  Returns false otherwise.
*/
static bool is_head(char c) {
    // TODO: Implement this function.
    return (c == 'W' || c == 'S' || c == 'A' || c == 'D' || c == 'x');
}

/*
  Returns true if c is part of the snake.
  The snake consists of these characters: "wasd^<v>WASDx"
*/
static bool is_snake(char c) {
    // TODO: Implement this function.
    char snake[] = "wasd^<v>WASDx";
    return (strchr(snake, c) != NULL);
}

/*
  Converts a character in the snake's body ("^<v>")
  to the matching character representing the snake's
  tail ("wasd").
*/
static char body_to_tail(char c) {
    // TODO: Implement this function.
    switch (c) {
        case '^':
            return 'w';
            break;
        case '<':
            return 'a';
            break;
        case 'v':
            return 's';
            break;
        case '>':
            return 'd';
            break;
        default:
            break;
    }
    return '?';
}

/*
  Converts a character in the snake's head ("WASD")
  to the matching character representing the snake's
  body ("^<v>").
*/
static char head_to_body(char c) {
    // TODO: Implement this function.
    switch (c) {
        case 'W':
            return '^';
            break;
        case 'A':
            return '<';
            break;
        case 'S':
            return 'v';
            break;
        case 'D':
            return '>';
            break;
        default:
            break;
    }
    return '?';
}

/*
  Returns cur_row + 1 if c is 'v' or 's' or 'S'.
  Returns cur_row - 1 if c is '^' or 'w' or 'W'.
  Returns cur_row otherwise.
*/
static unsigned int get_next_row(unsigned int cur_row, char c) {
    // TODO: Implement this function.
    if (c == 'v' || c == 's' || c == 'S') {
        return cur_row + 1;
    } else if (c == '^' || c == 'w' || c == 'W') {
        return cur_row - 1;
    }
    return cur_row;
}

/*
  Returns cur_col + 1 if c is '>' or 'd' or 'D'.
  Returns cur_col - 1 if c is '<' or 'a' or 'A'.
  Returns cur_col otherwise.
*/
static unsigned int get_next_col(unsigned int cur_col, char c) {
    // TODO: Implement this function.
    if (c == '>' || c == 'd' || c == 'D') {
        return cur_col + 1;
    } else if (c == '<' || c == 'a' || c == 'A') {
        return cur_col - 1;
    }
    return cur_col;
}

/*
  Task 4.2

  Helper function for update_state. Return the character in the cell the snake is moving into.

  This function should not modify anything.
*/
static char next_square(game_state_t *state, unsigned int snum) {
    // TODO: Implement this function.
    snake_t cur_snake = state->snakes[snum];
    char snake_head = get_board_at(state, cur_snake.head_row, cur_snake.head_col);
    return get_board_at(
        state, 
        get_next_row(cur_snake.head_row, snake_head),
        get_next_col(cur_snake.head_col, snake_head)
    );
}

/*
  Task 4.3

  Helper function for update_state. Update the head...

  ...on the board: add a character where the snake is moving

  ...in the snake struct: update the row and col of the head

  Note that this function ignores food, walls, and snake bodies when moving the head.
*/
static void update_head(game_state_t *state, unsigned int snum) {
    // TODO: Implement this function.
    snake_t *cur_snake = &state->snakes[snum];
    // Change the char in previous head to body
    char pre_head = get_board_at(state, cur_snake->head_row, cur_snake->head_col);
    set_board_at(state, cur_snake->head_row, cur_snake->head_col, head_to_body(pre_head));
    // Update the row and col of the head
    cur_snake->head_row = get_next_row(cur_snake->head_row, pre_head);
    cur_snake->head_col = get_next_col(cur_snake->head_col, pre_head);
    // Set the head in the board
    set_board_at(state, cur_snake->head_row, cur_snake->head_col, pre_head);
    return;
}

/*
  Task 4.4

  Helper function for update_state. Update the tail...

  ...on the board: blank out the current tail, and change the new
  tail from a body character (^<v>) into a tail character (wasd)

  ...in the snake struct: update the row and col of the tail
*/
static void update_tail(game_state_t *state, unsigned int snum) {
    // TODO: Implement this function.
    snake_t *cur_snake = &state->snakes[snum];
    // Clear the tail, change body to tail
    char pre_tail = get_board_at(state, cur_snake->tail_row, cur_snake->tail_col);
    set_board_at(state, cur_snake->tail_row, cur_snake->tail_col, ' ');
    // Update the row and col of the tail
    cur_snake->tail_row = get_next_row(cur_snake->tail_row, pre_tail);
    cur_snake->tail_col = get_next_col(cur_snake->tail_col, pre_tail);
    // Set the tail in the board
    set_board_at(state, cur_snake->tail_row, cur_snake->tail_col,
                 body_to_tail(get_board_at(state, cur_snake->tail_row, cur_snake->tail_col)));
    return;
}

/* Task 4.5 */
void update_state(game_state_t *state, int (*add_food)(game_state_t *state)) {
    // TODO: Implement this function.
    for (int n_snake = 0; n_snake < state->num_snakes; n_snake++) {
        char next_state = next_square(state, n_snake);
        // The snake died
        if (next_state == '#' || is_snake(next_state)) {
            snake_t *cur_snake = &state->snakes[n_snake];
            set_board_at(state, cur_snake->head_row, cur_snake->head_col, 'x');
            cur_snake->live = false;
        } else {
            update_head(state, n_snake);
            // if food is eaten, generate food and not update the tail
            if (next_state == '*') {
                add_food(state);
            } else {
                update_tail(state, n_snake);
            }
        }
    }
    return;
}

/* Task 5.1 */
char *read_line(FILE *fp) {
    // TODO: Implement this function.
    // Allocate memory for the line
    size_t cols = 260 * sizeof(char);
    char *line = malloc(cols);
    // Gets one line from the fp
    if (fgets(line, cols, fp) == NULL) {
        line = NULL;
        return line;
    } else {
        realloc(line, (strlen(line) + 1) * sizeof(char));
        return line;
    }
}

/* Task 5.2 */
game_state_t *load_board(FILE *fp) {
    // TODO: Implement this function.
    game_state_t *game = malloc(sizeof(game_state_t));
    // Set the number of snake as 0 and snake array as NULL
    game->num_snakes = 0;
    game->snakes = NULL;
    // Load the board from fp
    size_t rows = 256 * sizeof(char *);
    char **board = malloc(rows);

    int num_rows = 0;
    char *line;
    while ((line = read_line(fp)) != NULL) {
        board[num_rows++] = line;
    }

    game->num_rows = num_rows;
    board = realloc(board, num_rows * sizeof(char *));
    game->board = board;

    return game;
}

/*
  Task 6.1

  Helper function for initialize_snakes.
  Given a snake struct with the tail row and col filled in,
  trace through the board to find the head row and col, and
  fill in the head row and col in the struct.
*/
static void find_head(game_state_t *state, unsigned int snum) {
    // TODO: Implement this function.
    unsigned int cur_row = state->snakes[snum].tail_row;
    unsigned int cur_col = state->snakes[snum].tail_col;
    char cur_state;

    while (!is_head((cur_state = get_board_at(state, cur_row, cur_col)))) {
        cur_row = get_next_row(cur_row, cur_state);
        cur_col = get_next_col(cur_col, cur_state);
    }

    state->snakes[snum].head_row = cur_row;
    state->snakes[snum].head_col = cur_col;
    return;
}

/* Task 6.2 */
game_state_t *initialize_snakes(game_state_t *state) {
    // TODO: Implement this function.
    // Allocate space for snake array
    state->snakes = malloc(256 * sizeof(snake_t));
    // Find each snake in the board
    unsigned int num_snakes = 0;
    for (int row = 0; row < state->num_rows; row++) {
        int col = 0;
        for (char *line = state->board[row]; *line; line++, col++) {
            if (is_tail(*line)) {
                // Generate a new snake
                state->snakes[num_snakes].tail_row = row;
                state->snakes[num_snakes].tail_col = col;
                state->snakes[num_snakes].live = true;
                // Find the head
                find_head(state, num_snakes);
                num_snakes++;
            }
        }
    }
    // Reallocate space for snake array
    state->num_snakes = num_snakes;
    realloc(state->snakes, state->num_snakes * sizeof(snake_t));
    return state;
}
