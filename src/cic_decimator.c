#include "string.h"
#include "cic_decimator.h"

//----------------------------------------------------------------------------------------------------------
void CIC_Init(CIC_t* handle, uint16_t decimationFactor, uint8_t numberOfSections, uint8_t diferrencialDelay)
{
    handle->M = decimationFactor;
    handle->N = numberOfSections;
    handle->R  =diferrencialDelay;

    assert((handle != NULL) &&
           (handle->R <= CIC_MAX_R) &&
           (handle->N <= CIC_MAX_N) );

    // Clear Arrays, we can't just use sizeof as we have a pointer
    CIC_Reset(handle);
}
//----------------------------------------------------------------------------------------------------------
int32_t CIC_filter(CIC_t *handle, int32_t *input)
{
    int i = 0, k = 0, n = 0;
    uint16_t M = 	handle->M; 			/*Decimation Factor */
    uint8_t	 R = 	handle->R;			/*Differential delay scale in comb */
    uint8_t	 nStages = 	handle->N;		/*Number of stages */


    /* Downsample each element one by one */
    for (i = 0; i < M; i++)
    {
        /*INTEGRATE*/
        handle->accum[0] = handle->accum[0] + input[i]; /* 1st Stage */
        for (n = 1; n < nStages; n++)
        {	/* Remaining Stages */
            /* Output =  Last Output Value + Output of Previous Stage */
            handle->accum[n] = handle->accum[n] + handle->accum[n-1];
        }
    }

    /*Decimate block*/
   /* COMB */
   /* First Value - Store in _Input_ */
   handle->combs[R][0] = handle->accum[nStages-1];

   /* Next Values */
   for (n = 1; n <= nStages; n++)
   {
       handle->combs[R][n] = handle->combs[R][n-1] - handle->combs[0][n-1];
   }

   /* Copy back delays */
   for (n = 0; n <= nStages; n++)
   {
       for (k = 0; k < R; k++)
       {
           handle->combs[k][n] = handle->combs[k+1][n];
       }
   }

   return handle->combs[R][nStages];
}
//----------------------------------------------------------------------------------------------------------
void CIC_Reset(CIC_t *handle)
{
    memset(handle->accum, 0, sizeof handle->accum[0] * CIC_MAX_N);
    memset(handle->combs, 0, sizeof handle->combs[0][0] * (CIC_MAX_N+1) * (CIC_MAX_R+1));
}
