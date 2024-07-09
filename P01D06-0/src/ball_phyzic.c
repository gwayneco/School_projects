#include <stdio.h>

#define ball_vector_x_base_2st = 1
#define ball_vector_y_base_2st = 1
#define ball_vector_x_base_1st = -1
#define ball_vector_y_base_1st = -1
#define ball_y_start_1stpl = 40
#define ball_y_start_2stpl = 42

int height = 25, width = 80, ball_x, ball_y, ball_x_start, ball_y_start;
int ball_x_speed, ball_y_speed;
int main() {}

int start() {
  if (player_1 = 1) ball_y_start = ball_y_start_2stpl;
  ball_x_start = hidth / 2;
  ball_x_speed = ball_vector_x_base_2st;
  ball_y_speed = ball_vector_y_base_2st;

  if (player_2 = 1) ball_y_start = ball_y_start_1stpl;
  ball_x_start = hidth / 2;
  ball_x_speed = ball_vector_x_base_1st;
  ball_y_speed = ball_vector_y_base_1st;
}
int moving_x() {
  for (ball_x = ball_x_start; ball_x != 0 && ball_x != height;) {
    if (ball_x != 0 && ball_x != widht) {
      ball_x = ball_x_start + ball_x_speed;
    }
    if (ball_x == 0 || ball_x == width) {
      ball_x = ball_x + ball_x_speed;
    }
    if (ball_x == rocket_x_1 && ball_y == rocket_y_1 ||
        ball_x == rocket_x_2 &&
            ball_y == rocket_y_1 ||) {  // ввести соприкосновение с ракеткой
      ball_x_speed *= -1;
      ball_x = ball_x - ball_x_speed;
    }
  }
  return (ball_x);
}

int moving_y() {
  for (ball_y = ball_y_start;
       ball_y != 0 && ball_y != height;) {  // ввести соприкосновение с ракеткой
    if (ball_y != 0 && ball_y != height) {
      ball_y = ball_y_start + ball_y_speed;
    }
    if (ball_y != 0 && ball_y != height) {
      ball_y = ball_y_start + ball_y_speed;
    }
    if (ball_x == 0 || ball_x == height) {
      ball_y_speed *= -1;
      ball_y = ball_y_start + ball_y_speed;
    }
  }

  return (ball_y);
}

int win_count() {
  if (ball_y == 0) {
    player_2 = 1;
    player_2_count++;
  }
  if (ball_y == height) {
    player_1 = 1;
    player_1_count++;
  }
}