#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define WIDTH 80
#define HEIGHT 25

void starting_screen();
void ending_screen();
int **create_field();
void input(int **prev_buffer);
void print_field(int **buffer);
int count_neighbours(int **prev_buffer, int i, int j);
void determine_state(int **prev_buffer, int **new_buffer, int i, int j,
                     int nearest_neighbours, int *state_life);
void change_speed(int *flag, int *m);
void game_of_life(int **prev_buffer, int **new_buffer);

int main() {
  nodelay(initscr(), 1);
  raw();
  noecho();
  char init_char;
  int **prev_field = create_field();
  int **new_field = create_field();
  starting_screen();
  refresh();
  input(prev_field);
  if (freopen("/dev/tty", "r", stdin) == NULL) {
    printf("Failed to redirect stdin from file!");
  } else {
    scanf("%c", &init_char);
    if (init_char != 'q' && init_char != 'Q') {
      game_of_life(prev_field, new_field);
      refresh();
    }
  }
  free(prev_field);
  free(new_field);
  endwin();
  ending_screen();
  return 0;
}

void starting_screen() {
  printw("*********************************************************************"
         "**********\n"
         "*                                                                    "
         "         *\n"

         "*         0000000   000000  00000  00000 000000     0000000  0000000 "
         "         *\n"
         "*        000       000  000 000 0000 000 000       000   000 000     "
         "         *\n"
         "*        000 00000 00000000 000  00  000 000000    000   000 000000  "
         "         *\n"
         "*        000   000 000  000 000      000 000       000   000 000     "
         "         *\n"
         "*         0000000  000  000 000      000 000000      000000  000     "
         "         *\n"
         "*                                                                    "
         "         *\n"
         "*                        000    000 0000000 000000                   "
         "         *\n"
         "*                        000    000 000     000                      "
         "         *\n"
         "*                        000    000 000000  000000                   "
         "         *\n"
         "*                        000    000 000     000                      "
         "         *\n"
         "*                        000000 000 000     000000                   "
         "         *\n"
         "*                                                                    "
         "         *\n"
         "*              * * * * * * * * * * * * * * * * * * * * * * * * * *   "
         "         *\n"
         "*              *              PRESS ANY KEY TO START             *   "
         "         *\n"
         "*              *      PRESS G TO SPEED UP AND H TO SLOW DOWN     *   "
         "         *\n"
         "*              *                  PRESS Q TO EXIT                *   "
         "         *\n"
         "*              *               GAME MADE BY TEAM 57              *   "
         "         *\n"
         "*              * * * * * * * * * * * * * * * * * * * * * * * * * *   "
         "         *\n"
         "*                                                                    "
         "         *\n"
         "*                                                                    "
         "         *\n"
         "*                                                                    "
         "         *\n"
         "*********************************************************************"
         "**********\n");
}

void ending_screen() {
  printf(
      "*********************************************************************"
      "***********\n"
      "*                                                                     "
      "         *\n"
      "*                                                                     "
      "         *\n"
      "*                                                                     "
      "         *\n"
      "*                                                                     "
      "         *\n"
      "*                   0000000    000000     000000   00000000           "
      "         *\n"
      "*                  000       000    000 000    000 000    000         "
      "         *\n"
      "*                  000 00000 000    000 000    000 000     000        "
      "         *\n"
      "*                  000   000 000    000 000    000 000    000         "
      "         *\n"
      "*                   0000000    000000     000000   00000000           "
      "         *\n"
      "*                                                                     "
      "         *\n"
      "*                     0000000   000000  00000  00000 000000           "
      "         *\n"
      "*                    000       000  000 000 0000 000 000              "
      "         *\n"
      "*                    000 00000 00000000 000  00  000 000000           "
      "         *\n"
      "*                    000   000 000  000 000      000 000              "
      "         *\n"
      "*                     0000000  000  000 000      000 000000           "
      "         *\n"
      "*                                                                     "
      "         *\n"
      "*                                                                     "
      "         *\n"
      "*                                                                     "
      "         *\n"
      "*                                                                     "
      "         *\n"
      "*                                                                     "
      "         *\n"
      "*                              GAME MADE BY TEAM 57                   "
      "         *\n"
      "*                                                                     "
      "         *\n"
      "*                                                                     "
      "         *\n"
      "**********************************************************************"
      "**********\n");
}

void input(int **prev_buffer) {
  char temp;
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      scanf("%c", &temp);
      if (temp != '\n') {
        prev_buffer[i][j] = (int)temp - 48;
      } else {
        j--;
      }
    }
  }
}

void game_of_life(int **prev_buffer, int **new_buffer) {
  int flag = 0;
  int m = 100000;
  int state_life = 1;

  while (state_life != 0 && flag != 1) {
    print_field(prev_buffer);
    change_speed(&flag, &m);
    state_life = 0;
    for (int i = 0; i < HEIGHT; i++) {
      for (int j = 0; j < WIDTH; j++) {
        int neighbours = count_neighbours(prev_buffer, i, j);
        determine_state(prev_buffer, new_buffer, i, j, neighbours, &state_life);
      }
    }
    for (int i = 0; i < HEIGHT; i++) {
      for (int j = 0; j < WIDTH; j++) {
        prev_buffer[i][j] = new_buffer[i][j];
      }
    }
    refresh();
    usleep(m);
  }
}

int **create_field() {
  int **field = malloc(WIDTH * HEIGHT * sizeof(int) + HEIGHT * sizeof(int *));
  if (field != NULL) {
    int *ptr = (int *)(field + HEIGHT);
    for (int i = 0; i < HEIGHT; i++) {
      field[i] = ptr + WIDTH * i;
    }
  } else {
    printf("MEMORY ALLOCATION ERROR!");
  }
  return field;
}

int count_neighbours(int **prev_buffer, int i, int j) {
  int nearest_neighbours = 0;
  nearest_neighbours +=
      prev_buffer[(i - 1 + HEIGHT) % HEIGHT][(j - 1 + WIDTH) % WIDTH];
  nearest_neighbours +=
      prev_buffer[(i + 1 + HEIGHT) % HEIGHT][(j + 1 + WIDTH) % WIDTH];
  nearest_neighbours +=
      prev_buffer[(i - 1 + HEIGHT) % HEIGHT][(j + 1 + WIDTH) % WIDTH];
  nearest_neighbours +=
      prev_buffer[(i + 1 + HEIGHT) % HEIGHT][(j - 1 + WIDTH) % WIDTH];
  nearest_neighbours += prev_buffer[i][(j - 1 + WIDTH) % WIDTH];
  nearest_neighbours += prev_buffer[i][(j + 1 + WIDTH) % WIDTH];
  nearest_neighbours += prev_buffer[(i - 1 + HEIGHT) % HEIGHT][j];
  nearest_neighbours += prev_buffer[(i + 1 + HEIGHT) % HEIGHT][j];
  return nearest_neighbours;
}

void determine_state(int **prev_buffer, int **new_buffer, int i, int j,
                     int nearest_neighbours, int *state_life) {
  if (prev_buffer[i][j] == 1 &&
      (nearest_neighbours == 2 || nearest_neighbours == 3)) {
    new_buffer[i][j] = 1;
    (*state_life)++;
  } else if (prev_buffer[i][j] == 0 && nearest_neighbours == 3) {
    new_buffer[i][j] = 1;
    (*state_life)++;
  } else if (prev_buffer[i][j] == 1 && nearest_neighbours != 2 &&
             nearest_neighbours != 3) {
    new_buffer[i][j] = 0;
    (*state_life)++;
  } else {
    new_buffer[i][j] = 0;
  }
}

void change_speed(int *flag, int *m) {
  noecho();
  system("stty raw");
  char ch = getch();
  system("stty -raw");
  switch (ch) {
  case 'h':
  case 'H':
    if (*m > 0) {
      *m -= 50000;
    }
    break;
  case 'g':
  case 'G':
    *m += 50000;
    break;
  case 'q':
  case 'Q':
    *flag = 1;
    break;
  default:
    break;
  }
}

void print_field(int **buffer) {
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      if (i == 0 || i == HEIGHT - 1) {
        printf("*");
      } else if (j == 0 || j == WIDTH - 1) {
        printf("*");
      } else if (buffer[i][j] == 1) {
        printf("#");
      } else {
        printf(" ");
      }
    }
    printf("\n");
  }
}
