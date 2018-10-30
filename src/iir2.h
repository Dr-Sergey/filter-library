#ifndef IIR2_H
#define IIR2_H

//Y[n] = A0*X[n] + A1*X[n-1] + A2*X[n-2] - B1*Y[n-1] - B2*Y[n-2]

typedef enum {/*FT_BANDPASS,*/ FT_BANDSTOP, /*FT_HIGHPASS,*/ FT_LOWPASS} IIRFilterType;

typedef struct
{
	IIRFilterType type;
	float frequency;
	float Q;

	float A0, A1, A2;
	float B1, B2;

	float xn1, xn2, yn1, yn2;
} iir2_t;

void iir2_calc_coefs(iir2_t* iir2);
float iir2_process(iir2_t* iir2, float xn);
	

#endif
