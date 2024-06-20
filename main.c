#include <raylib.h>
#ifndef MATH_H
#define MATH_H
#include <math.h>
#endif

#define SOLVER_EULER_IMPLEMENTATION
#include "c-numerical-methods/solvers/simple.h"

// CONSTS
#define WIDTH 1024
#define HEIGHT 720

#define SHIFTX (WIDTH / 2)
#define SHIFTY (HEIGHT / 2)

#define RADIUS 5.0f
#define FPS 60

#define NBODY_IMPLEMENTATION
#include "initial_conditions.h"

#include "ffmpeg.h"

float **normalize(float **X, unsigned cols, unsigned rows) {
  int i, j;
  float max = -10.0;

  for (i = 0; i < rows; i++) {
    for (j = 0; j < cols; j += 4) {
      float norm = powf(X[i][j], 2) + powf(X[i][j + 2], 2);
      if (max < norm) {
        max = norm;
      }
    }
  }

  for (i = 0; i < rows; i++) {
    for (j = 0; j < cols; j += 2) {
      X[i][j] /= sqrtf(max);
    }
  }
  return X;
};

Color colors[] = {RED, BLUE, GREEN, GOLD};

void drawTrace(int i, int j, float **movement) {
  for (size_t k = 1; k < i; k++) {

    int cx_begin = (movement[k - 1][j] * SHIFTX) + SHIFTX;
    int cy_begin = (movement[k - 1][j + 2] * SHIFTY) + SHIFTY;
    int cx_end = (movement[k][j] * SHIFTX) + SHIFTX;
    int cy_end = (movement[k][j + 2] * SHIFTY) + SHIFTY;
    DrawLine(cx_begin, cy_begin, cx_end, cy_end, colors[j / 4]);
    // DrawPixel(cx, cy, colors[j / 4]);
  }
}

void DrawBodies(int i, float **movement) {
  for (size_t j = 0; j < Nbodies * 4; j += 4) {
    drawTrace(i, j, movement);
    int cx = (movement[i][j] * SHIFTX) + SHIFTX;
    int cy = (movement[i][j + 2] * SHIFTY) + SHIFTY;
    DrawCircle(cx, cy, RADIUS, colors[j / 4]);
  }
}

int main() {
  float *t = malloc(sizeof(float) * N);
  float dt = (T1 - T0) / N;
  t[0] = T0;
  for (int i = 1; i < N; i++) {
    t[i] = t[i - 1] + dt;
  }

  float **movement = euler(Nbodies * 4, N, t, dxdt, X0);
  movement = normalize(movement, Nbodies * 4, N);

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < Nbodies * 4; j++) {
      printf("%6.4f\t", movement[i][j]);
    }
    printf("\n");
  }

  int i = 1;
  InitWindow(WIDTH, HEIGHT, "Main Windows");

  SetTargetFPS(FPS);

  int j, k;

  while (!WindowShouldClose() && !IsKeyPressed(KEY_Q) && i < N) {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawBodies(i++, movement);
    EndDrawing();
  }

  CloseWindow(); // Close window and OpenGL context

  for (i = 0; i < N; i += 4) {
    free(movement[i]);
    movement[i] = NULL;
  }
  free(movement);
  movement = NULL;
  free(t);
  t = NULL;
}
