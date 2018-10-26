#include "iir1.h"

//----------------------------------------------------------------------------------------------------------
IIR1_t IIR1_Init()
{
    IIR1_t tmp;
    tmp.coefs.decay = 0.1f;
    tmp.yn1 = 0;

    return  tmp;
}
//----------------------------------------------------------------------------------------------------------
void IIR1_Reset(IIR1_t *handle)
{
    handle->yn1 = 0;
}
//----------------------------------------------------------------------------------------------------------
float IIR1_process(IIR1_t *handle, float value)
{
    float output = handle->coefs.decay*value + (1 - handle->coefs.decay)*handle->yn1;
    handle->yn1 = output;

    return output;
}
