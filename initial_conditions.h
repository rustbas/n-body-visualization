#ifndef STDLIB_H
#define STDLIB_H
#include <stdlib.h>
#endif

#ifndef MATH_H
#define MATH_H
#include <math.h>
#endif

#ifndef STDIO_H
#define STDIO_H
#include <stdio.h>
#endif

#define T0 0.0f
#define T1 1000.0f
#define N 500
#define Nbodies 2
// #define M (Nbodies * 4)

#define G 1.0f // 6.67e-11

#ifdef NBODY_IMPLEMENTATION
// Initial conditions
float m[] = {1.0, 1.0};
// float m[] = {6e24f, 7.34e22f};
//  float m[] = {7.34e22f};

float X0[] = {
    -15.0f, // x_1
    0.0f,   // Vx_1
    0.0f,   // y_1
    0.13f,  // Vy_1
    15.0f,  // x_2
    0.0f,   // Vx_2
    0.0f,   // y_2
    -0.13f  // Vy_2
};

float *dxdt(float *X, float t, unsigned M) {
  float *dx = (float *)malloc(sizeof(float) * Nbodies * 4);
  int i, j;

  for (i = 0; i < Nbodies * 4; i++) {
    if (i % 2 == 0) {
      dx[i] = X[i + 1];
    } else if (i % 4 == 1) {
      for (j = 1; j < Nbodies * 4; j += 4) {
        if (i != j) {
          dx[i] += G * m[j / 4] * (X[j - 1] - X[i - 1]) /
                   powf((powf((X[j - 1] - X[i - 1]), 2) +
                         powf((X[j + 1] - X[i + 1]), 2)),
                        3.0f / 2.0f);
        }
      }
    } else if (i % 4 == 3) {
      for (j = 3; j < Nbodies * 4; j += 4) {
        if (i != j) {
          dx[i] += G * m[j / 4] * (X[j - 1] - X[i - 1]) /
                   powf((powf((X[j - 3] - X[i - 3]), 2) +
                         powf((X[j - 1] - X[i - 1]), 2)),
                        3.0f / 2.0f);
        }
      }
    } else {
      printf("UNREACHABLE CODE\n");
      exit(1);
    }
  }

  return dx;
}
#endif
