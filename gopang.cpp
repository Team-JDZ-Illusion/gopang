#include <cstdio>
#include <cstdlib>
#include <ctype.h>
#include <stdlib.h>
#define PROGRAM_VERSION "v1.0.1"

char chessboard[13][13];

void title(void) {
  printf("  _______   ______   .______      ___      .__   __.   _______   __\n"
         " /  _____| /  __   \\ |   _   \\   /   \\     |  \\ |  |  /  _____| "
         "|  |\n"
         "|  |  __  |  |  |  | |  |_)  |  /  ^  \\    |   \\|  | |  |  __   "
         "|  |\n"
         "|  | |_ | |  |  |  | |   ___/  /  /_\\  \\   |  . `  | |  | |_ |  "
         "|  |\n"
         "|  |__| | |  `--'  | |  |     /  _____  \\  |  |\\   | |  |__| |  "
         "|__|\n"
         " \\______|  \\______/  |__|    /__/     \\__\\ |__| \\__|  \\______|"
         "  (__)"
         "\n");
  printf("               GOPANG - Simple Gobang game %s\n", PROGRAM_VERSION);
  printf("                   Have fun with GOPANG 🥰!\nP.S.\nInput "
         "format is like \"5 6\",\"1 "
         "2\"(enter q to quit)\n");
  printf(
      "Made with ❤️  by these programers:(\?)LZJ,(PANG GOD)WQY,(C_GH0S7)CJY\n");
}
/*initialize*/ void initialize(char chessboard[][13]) {
  for (int i = 0; i < 13; i++) {
    for (int j = 0; j < 13; j++) {
      chessboard[i][j] = '.';
    }
  }
  return;
}

/*print*/ void printX(char chessboard[][13]) {
  for (int i = 0; i < 13; i++) {
    for (int j = 0; j < 13; j++) {
      printf("%c", chessboard[i][j]);
    }
    printf("\n");
  }
  return;
}

/*O*/ int O(char chessboard[][13], int x, int y) {
  if (x < 0 || x > 13 || y < 0 || y > 13 || chessboard[x][y] != '.') {
    return 0;
  } else {
    chessboard[x][y] = 'O';
    return 1;
  }
}
/*X*/ int X(char chessboard[][13], int x, int y) {
  if (x < 0 || x > 13 || y < 0 || y > 13 || chessboard[x][y] != '.') {
    return 0;
  } else {
    chessboard[x][y] = 'X';
    return 1;
  }
}
int judge0(char chessboard[][13], const int x, const int y, int deltaX,
           int deltaY) {
  int count = 1;
  int cx = x, cy = y;
  char c = chessboard[x][y];
  while ((cx += deltaX) < 13 && cx >= 0 && (cy += deltaY) < 13 && cy >= 0)
    if (chessboard[cx][cy] == c)
      count++;
    else
      break;
  cx = x, cy = y;
  while ((cx -= deltaX) < 13 && cx >= 0 && (cy -= deltaY) < 13 && cy >= 0)
    if (chessboard[cx][cy] == c)
      count++;
    else
      break;
  return count >= 5;
}
/*judge*/ int judge(char chessboard[][13], int x, int y) {
  return judge0(chessboard, x, y, 1, 1) || judge0(chessboard, x, y, 0, 1) ||
         judge0(chessboard, x, y, 1, 0) || judge0(chessboard, x, y, -1, 1);
}

int main() {
  int x, y, os = 0, xs = 0;
  char k;
  char chessboard[13][13];
RESTART:
  title();
  initialize(chessboard);
  printX(chessboard);
  for (;;) {
  TO:
    printf("Please input the position of your chess:(Player O)\n");
    if (scanf("%d%d", &x, &y) == 2) {
      if (O(chessboard, x - 1, y - 1)) {
        printX(chessboard);
        if (judge(chessboard, x - 1, y - 1)) {
          printf("Player O wins !\n");
          os++;
          break;
        }
      }
    } else if (tolower((x = getchar())) == 'q' ||
               tolower((y = getchar())) == 'q') {
      printf("Quit successfully !\n");
      exit(0);
    } else {
      printf("WRONG FORMAT,PLEASE INPUT AGAIN\n");
      while (getchar() != '\n')
        continue;
      goto TO;
    }

  XO:
    printf("Please input the position of the chess:(Player X)\n");
    if (scanf("%d%d", &x, &y) == 2) {
      if (X(chessboard, x - 1, y - 1)) {
        printX(chessboard);
        if (judge(chessboard, x - 1, y - 1)) {
          printf("Player X wins !\n");
          xs++;
          break;
        }
      }
    } else if (tolower((x = getchar())) == 'q' ||
               tolower((y = getchar())) == 'q') {
      printf("QUIT SUCCESSFULLY !\n");
      exit(0);
    } else {
      printf("WRONG FORMAT,PLEASE INPUT AGAIN !\n");
      while (getchar() != '\n')
        continue;
      goto XO;
    }
  }
end:
  printf("TRY AGAIN?(enter y to again,enter n to end the game)\n");
  scanf(" %c", &k);
  if (tolower(k) == 'y')
    goto RESTART;
  else if (tolower(k) == 'n') {
    printf("score:Player O = %d, Player X = %d\n", os, xs);
    if (os > xs)
      printf("Player O wins !");
    else if (os < xs)
      printf("Player X wins !");
    else
      printf("BALANCED!!!");
    return 0;
  } else {
    printf("WRONG FORMAT,PLEASE ENTER AGAIN !");
    while (getchar() != '\n')
      continue;
    goto end;
  }
}
