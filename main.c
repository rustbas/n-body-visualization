#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// CONSTS
#define WIDTH 800
#define HEIGHT 600

#define SHIFTX (WIDTH / 2)
#define SHIFTY (HEIGHT / 2)

#define RADIUS 5.0f
#define FPS 60

const char *getfield(char *line, int num) {
  const char *tok;
  for (tok = strtok(line, ","); tok && *tok; tok = strtok(NULL, ",\n")) {
    if (!--num)
      return tok;
  }
  return NULL;
}

int main() {
  FILE *result = fopen("result.csv", "r");

  InitWindow(WIDTH, HEIGHT, "Main Windows");

  SetTargetFPS(FPS);

  int i = 1;

  char line[1024];
  while (!WindowShouldClose() && fgets(line, 1024, result)) {
    // BeginDrawing();
    ClearBackground(BLACK);
    // while (fgets(line, 1024, result)) {
    // char* tmp = strdup(line);
    // printf("Field 3 would be %s\n", getfield(tmp, 1));
    //  NOTE strtok clobbers tmp
    // free(tmp);
    //}
    // printf("%s\n", line);
    char *tmp = strdup(line);
    float x1 = atof(getfield(tmp, 2));
    tmp = strdup(line);
    float y1 = atof(getfield(tmp, 4));
    tmp = strdup(line);
    float x2 = atof(getfield(tmp, 6));
    tmp = strdup(line);
    float y2 = atof(getfield(tmp, 8));
    // tmp = strdup(line);
    // float x3 = atof(getfield(tmp, 10));
    // tmp = strdup(line);
    // float y3 = atof(getfield(tmp, 12));
    // tmp = strdup(line);
    // float x4 = atof(getfield(tmp, 14));
    // tmp = strdup(line);
    // float y4 = atof(getfield(tmp, 16));

    // DrawCircle((i+=4)%WIDTH,HEIGHT/2,10,RED);
    DrawCircle((int)(SHIFTX * x1) + SHIFTX, (int)(SHIFTY * y1) + SHIFTY, RADIUS,
               GREEN);
    DrawCircle((int)(SHIFTX * x2) + SHIFTX, (int)(SHIFTY * y2) + SHIFTY, RADIUS,
               RED);
    // DrawCircle((int)(SHIFTX*x3)+SHIFTX, (int)(SHIFTY*y3)+SHIFTY, RADIUS,
    // BLUE); DrawCircle((int)(SHIFTX*x4)+SHIFTX, (int)(SHIFTY*y4)+SHIFTY,
    // RADIUS, YELLOW);

    EndDrawing();
  }

  fclose(result);

  CloseWindow(); // Close window and OpenGL context
}
