#include <stdio.h>


void frame_drow();
int mv_Ball();
#define rocket_x_1 2
#define rocket_x_2 79
int rocket_p1 = 10;
int rocket_p2 = 10;
int ball_x = 40;
int ball_y = 12;
int score1 =0;
int score2 = 0;
int x_vector =1;
int y_vector = 1;
int height = 26;
int width = 81;
void clearScreen();
int main() {
    
    char v;
    char temp;
    
     while (1) {
        if (score1 == 21) {
      clearScreen();
      printf("Player 1 WIN!\n");
      break;
        }
    if (score2 == 21) {
      clearScreen();
      printf("layer 2 WIN!\n");
      break;
        }
clearScreen();
        frame_drow();
      //  getchar("%c\n",&v);
     switch (getchar()) {
        case 32 : rocket_p1;break;
        case 'a' : ((rocket_p1) -1 == 1) ?  rocket_p1:((rocket_p1 -=1));printf("\n");break;
        case 'z' : ((rocket_p1) +1 == height -1) ?  rocket_p1:(rocket_p1 +=1);printf("\n");break;
        case 'k' : ((rocket_p2) -1 == 1) ?  rocket_p2:(rocket_p2 -=1);printf("\n");break;
        case 'm' : ((rocket_p2) +1 == height -1) ?  rocket_p2:(rocket_p2 +=1);printf("\n");break;
     }
     
     
        mv_Ball();
        
  
         
    }

}



void frame_drow() {
  char gran = '*';
  char space =' ';
  for (int y = 0; y <= height; y++) {
    for (int x = 0; x <= width; x++) {
      if (x == 0 || y == 0 || y == height) {
        printf("*");
      }
      if (x != 0 && y != 0 && y != height && x != width + 1) {
        if ((x == rocket_x_1 && y == rocket_p1) ||
            (x == rocket_x_1 && y == rocket_p1 - 1) ||
            (x == rocket_x_1 && y == rocket_p1 + 1) ||
            (x == rocket_x_2 && y == rocket_p2) ||
            (x == rocket_x_2 && y == rocket_p2 - 1) ||
            (x == rocket_x_2 && y == rocket_p2 + 1)) {
          printf("|");
        } else if (x == ball_x && y == ball_y)
          printf("%c", gran);
        else
          printf("%c", space);
      }
      if (x == width) printf("%c\n", gran);
    }
  }
    for (int y = 0; y <= 6 ; y++) {
        for (int x =0; x <= width; x++) {
            if (x == 0 ) 
                printf("*");
                    else if (y == 6)
                    printf("*");
                     else if (x == 20 && y == 3)
                        printf("%d",score1);
                        else
                        if (x == 60 && y == 3)
                            printf("%d",score2);
                                     else printf(" ");
            if (x == width)
            printf("*\n");
            
    }
}
}
int mv_Ball(){
    // Check GOLL 1!
    if(ball_x == 0 && x_vector == - 1){
        ball_x = 41;
        ball_y = 12;
        y_vector = 1;
        x_vector = 1;
        score2 +=1;
        
    }
    // Check GOLL 2!
    if(ball_x == 80 && x_vector)
    {
        ball_x = 41;
        ball_y = 12;
        y_vector = 1;
        x_vector = -1;
        score1 +=1;
    }
    // Check wall
  if (ball_y == 1 && y_vector == -1) y_vector *= -1;
  if (ball_y == 26 - 1 && y_vector == 1) y_vector *= -1;
  // Check Slab 1
  if ((ball_x == rocket_x_1 + 1) &&
      (ball_y == rocket_p1 || ball_y == rocket_p1 + 1 ||
       ball_y == rocket_p1 - 1) &&
      x_vector == -1)
    x_vector *= -1;
  // Check Slab 2
  if ((ball_x == rocket_x_2 - 1) &&
      (ball_y == rocket_p2 || ball_y == rocket_p1 - 1 ||
       ball_y == rocket_p1 + 1) &&
      x_vector == 1)
    x_vector *= -1;
  ball_x += x_vector;
  ball_y += y_vector;
  return -1;
}



void clearScreen(void) {
    printf("\33[0d\33[2J");
}
