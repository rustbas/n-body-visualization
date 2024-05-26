#include <raylib.h>
#ifndef MATH_H
#define MATH_H
#include <math.h>
#endif

#define SOLVER_RUNGE_KUTTA_IMPLEMENTATION
#include "c-numerical-methods/solvers/runge-kutta.h"

#define SOLVER_EULER_IMPLEMENTATION
#include "c-numerical-methods/solvers/simple.h"

// CONSTS
#define WIDTH 800
#define HEIGHT 600

#define SHIFTX (WIDTH / 2)
#define SHIFTY (HEIGHT / 2)

#define RADIUS 5.0f
#define FPS 60

#define NBODY_IMPLEMENTATION
#include "initial_conditions.h"

float **normalize(float **X, unsigned COLS, unsigned ROWS) {
  int i, j;
  float max = 0.0f;

  for (i = 0; i < ROWS; i++) {
    for (j = 0; j < COLS; j += 4) {
      float norm = powf(X[i][j], 2) + powf(X[i][j + 2], 2);
      if (max < norm) {
        max = norm;
      }
    }
  }

  for (i = 0; i < ROWS; i++) {
    for (j = 0; j < COLS; j += 2) {
      X[i][j] /= sqrtf(max);
    }
  }
  return X;
};

Color colors[] = {RED, BLUE, GREEN, GOLD};

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
#if 1
  InitWindow(WIDTH, HEIGHT, "Main Windows");

  SetTargetFPS(FPS);

  int j, k;

  char line[1024];
  while (!WindowShouldClose() && !IsKeyPressed(KEY_Q) && i < N) {
    BeginDrawing();
    ClearBackground(BLACK);
    // DrawCircle((i+=4)%WIDTH,HEIGHT/2,10,RED);

    for (j = 0; j < Nbodies * 4; j += 4) {
      for (k = 0; k < i; k++) {
        int cx = (movement[k][j] * SHIFTX) + SHIFTX;
        int cy = (movement[k][j + 2] * SHIFTY) + SHIFTY;
        DrawPixel(cx, cy, colors[j / 4]);
      }
      int cx = (movement[i][j] * SHIFTX) + SHIFTX;
      int cy = (movement[i][j + 2] * SHIFTY) + SHIFTY;
      DrawCircle(cx, cy, RADIUS, colors[j / 4]);
    }

    i += 1;
    EndDrawing();
  }

  CloseWindow(); // Close window and OpenGL context
#endif
  for (i = 0; i < N; i += 4) {
    free(movement[i]);
    movement[i] = NULL;
  }
  free(movement);
  free(t);
}
