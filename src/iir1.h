#ifndef IIR1_H
#define IIR1_H

#include <math.h>

typedef struct
{
    float decay;
} IIR1_coefs_t;

typedef struct
{
    IIR1_coefs_t coefs;
    float yn1;
} IIR1_t;

IIR1_t IIR1_Init(void);
void   IIR1_Reset(IIR1_t *handle);
float  IIR1_process(IIR1_t *handle, float value);

#endif // IIR1_H
