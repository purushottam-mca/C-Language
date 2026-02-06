#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define REFRESH_RATE 40000
#define RANDOM_NESS 5 // The higer value indicates less random
void clear_screen() {
   system("@cls||clear");
}
void display_random_leaf() {
   char type_of_leaves[5] = { '.', '*', '+', 'o', 'O' };
   int temp = rand() % RANDOM_NESS;
   if (temp == 1)
      printf("%c ", type_of_leaves[rand() % 5]);
   else
      printf("%c ", type_of_leaves[1]);
}
void tree_triangle(int f, int n, int toth) {
   int i, j, k = 2 * toth - 2;
   for (i = 0; i < f - 1; i++)
      k--;
   for (i = f - 1; i < n; i++) 
   {
      for (j = 0; j < k; j++)
        printf(" ");
      k = k - 1;
      for (j = 0; j <= i; j++)
         display_random_leaf();
      printf("
");
   }
}
void display_tree(int h) {
   int start = 1, end = 0, diff = 3;
   while (end < h + 1) {
      end = start + diff;
      tree_triangle(start, end, h);
      diff++;
      start = end - 2;
   }
}
void display_log(int n) {
   int i, j, k = 2 * n - 4;
   for (i = 1; i <= 6; i++) {
      for (j = 0; j < k; j++)
         printf(" ");
      for (j = 1; j <= 6; j++)
         printf("#");
      printf("
");
   }
}
main() {
   srand(time(NULL));
   int ht = 15;
   while (1) {
      clear_screen();
      display_tree(ht);
      display_log(ht);
      usleep(40000);
   }
}
