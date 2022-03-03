#include <stdio.h>
#include <stdbool.h>

typedef int grid_t[9][9];

void print_sudoku(grid_t grid) {
  for (int y = 0; y < 9; y++) {
    for (int x = 0; x < 9; x++) {
      printf("%d ", grid[y][x]);
      if (x % 3 == 2) {
        printf("| ");
      }
    }
    printf("\n");
    if (y % 3 == 2) {
      printf("----------------------\n");
    }
  }
}

bool not_on_line(grid_t grid, int value, int y) {
  for (int i = 0; i < 9; i++) {
    if (grid[y][i] == value) {
      return false;
    }
  }
  return true;
}

bool not_on_column(grid_t grid, int value, int x) {
  for (int i = 0; i < 9; i++) {
    if (grid[i][x] == value) {
        return false;
    }
  }
  return true;
}

bool not_on_square(grid_t grid, int value, int x, int y) {
  int _x = x - (x % 3);
  int _y = y - (y % 3);
  for (int i = _y; i < _y + 3; i++) {
    for (int j = _x; j < _x + 3; j++) {
      if (grid[i][j] == value) {
        return false;
      }
    }
  }
  return true;
}

bool is_valid(grid_t grid, int position) {
  if (position == 9*9)
    return true;

  int y = position / 9;
  int x = position % 9;

  if (grid[y][x] != 0)
    return is_valid(grid, position + 1);

  for (int i = 1; i <= 9; i++) {
    if (not_on_line(grid, i, y) && not_on_column(grid, i, x) && not_on_square(grid, i, x, y)) {
      grid[y][x] = i;
      if (is_valid(grid, position + 1))
        return true;
    }
  }
  grid[y][x] = 0;

  return false;
}

int main(int argc, char** argv) {

  int sudoku[9][9] = {
     {9, 0, 0, 1, 0, 0, 0, 0, 5},
     {0, 0, 5, 0, 9, 0, 2, 0, 1},
     {8, 0, 0, 0, 4, 0, 0, 0, 0},
     {0, 0, 0, 0, 8, 0, 0, 0, 0},
     {0, 0, 0, 7, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 2, 6, 0, 0, 9},
     {2, 0, 0, 3, 0, 0, 0, 0, 6},
     {0, 0, 0, 2, 0, 0, 9, 0, 0},
     {0, 0, 1, 9, 0, 4, 5, 7, 0}
  };

  print_sudoku(sudoku);
  is_valid(sudoku, 0);
  printf("\n\n");
  print_sudoku(sudoku);
  return 0;
}
