#ifndef _types_h_
#define _types_h_

/*
 * Namens-Konventionen f�r Variablen:
 * Objekte                o
 * global                 g
 * globale Objekte        go
 * super global           sg
 * super globale Objekte  sgo
 */

#define PI 3.14159265358979323846

#define length(x) (sizeof(x) / sizeof(*x))

#define FOV 60.0f

#define FOG_START 20.0f
#define FOG_END   30.0f

#define MATRIX_SIZE 4

typedef float Matrix[MATRIX_SIZE][MATRIX_SIZE];

#endif
