#ifndef CIC_DECIMATOR_H
#define CIC_DECIMATOR_H

#include <assert.h>
#include <stdlib.h>
#include <stdint.h>

#define CIC_MAX_N	 	(3)
#define CIC_MAX_R 	 	(2)

typedef struct
{
    uint16_t M;                                     /* Decimation Factor */
    uint8_t  N;                                     /* Order */
    uint8_t	 R;                                     /* Delay scale of comb filter */
    int32_t	 accum[CIC_MAX_N];                      /* Accumulators for COMB */
    int32_t  combs[CIC_MAX_R + 1][CIC_MAX_N + 1];	/* Values of comb, including previous */
} CIC_t;

void CIC_Init(CIC_t* handle, uint16_t decimationFactor, uint8_t numberOfSections, uint8_t diferrencialDelay);

// reset internal state
void  CIC_Reset(CIC_t* handle);

// the actual filter function
// the parameter input shuld be M-dimensional vector(M continuous samples)
// the output is corresponding to the downsample value
int32_t CIC_filter(CIC_t *handle, int32_t *input);

#endif // CIC_DECIMATOR_H
