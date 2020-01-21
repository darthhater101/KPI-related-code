#ifndef __MEASUREMENT_H__
#define __MEASUREMENT_H__
#include <time.h>

#define measurements_number 28

extern clock_t Res[measurements_number];

int MeasurementProcessing();

int Time_Measurememt(void (*f)(int***), int);

int Time_Measurememt_Vec(void (*f)(int*), int);

#endif
