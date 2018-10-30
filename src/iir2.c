#include <math.h>
#include "iir2.h"
#include "../config.h"

//-------------------------------------------------------------------------------------------------
//Y[n] = A0*X[n] + A1*X[n-1] + A2*X[n-2] - B1*Y[n-1] - B2*Y[n-2]
float iir2_process(iir2_t* iir2, float xn)
{
	float yn;
	
	if(iir2->frequency == 0) return xn;// bypass for zero frequency

	switch(iir2->type)
	{
		//Y[n] = A0*(X[n] - X[n-2]) - B1*Y[n-1] - B2*Y[n-2]
	/*case FT_BANDPASS:
		yn = iir2->A0*(xn - iir2->xn2) - iir2->B1*iir2->yn1 - iir2->B2*iir2->yn2;
		break;*/
		
		//Y[n] = A0*(X[n] + X[n-2]) + A1*(X[n-1] - Y[n-1]) - B2*Y[n-2]
	case FT_BANDSTOP:
		yn = iir2->A0*(xn + iir2->xn2) + iir2->A1*(iir2->xn1 - iir2->yn1) - iir2->B2*iir2->yn2;
		break;
		
		//Y[n] = A0*(X[n] + X[n-2]) + A1*X[n-1] - B1*Y[n-1] - B2*Y[n-2]
	/*case FT_HIGHPASS:
		yn = iir2->A0*(xn + iir2->xn2) + iir2->A1*iir2->xn1 - iir2->B1*iir2->yn1 - iir2->B2*iir2->yn2;
		break;*/
		
		//Y[n] = A0*(X[n] + X[n-2]) + A1*X[n-1] - B1*Y[n-1] - B2*Y[n-2]
	case FT_LOWPASS:
		yn = iir2->A0*(xn + iir2->xn2) + iir2->A1*iir2->xn1 - iir2->B1*iir2->yn1 - iir2->B2*iir2->yn2;
		break;

	default :
		yn = 0;
	}
	
	iir2->xn2 = iir2->xn1;
	iir2->xn1 = xn;
	iir2->yn2 = iir2->yn1;
	iir2->yn1 = yn;
	
	return yn;
}
//-------------------------------------------------------------------------------------------------
void iir2_calc_coefs(iir2_t* iir2)
{
	float m_a0, m_a1, m_a2, m_b0, m_b1, m_b2;
	
	float omega = 2.0*M_PI*iir2->frequency*SAMPLE_PERIOD;
	float SIN = sinf(omega);
	float COS = cosf(omega);
	float alpha = SIN/(2.0*iir2->Q);
	
	switch(iir2->type)
	{
		/*case FT_BANDPASS:
			m_b0 = alpha;
			m_b1 = 0;
			m_b2 = -alpha;
			m_a0 = 1 + alpha;
			m_a1 = -2*COS;
			m_a2 = 1 - alpha;
		break;*/
		
		case FT_BANDSTOP:
			m_b0 = 1;
			m_b1 = -2*COS;
			m_b2 = 1;
			m_a0 = 1 + alpha;
			m_a1 = -2*COS;
			m_a2 = 1 - alpha;
		break;
		
		/*case FT_HIGHPASS:
			m_b0 = (1 + COS)/2;
			m_b1 = -(1 + COS);
			m_b2 = (1 + COS)/2;
			m_a0 = 1 + alpha;
			m_a1 = -2*COS;
			m_a2 = 1 - alpha;
		break;*/
		
		case FT_LOWPASS:
			m_b0 = (1 - COS)/2.0;
			m_b1 = 1 - COS;
			m_b2 = (1 - COS)/2.0;
			m_a0 = 1 + alpha;
			m_a1 = -2.0*COS;
			m_a2 = 1 - alpha;
		break;

		default:
			m_b0 = 1;
			m_b1 = 1;
			m_b2 = 1;
			m_a0 = 1;
			m_a1 = 1;
			m_a2 = 1;
		break;
	}	
	
	iir2->A0 = m_b0/m_a0;
	iir2->A1 = m_b1/m_a0;
	iir2->A2 = m_b2/m_a0;
	iir2->B1 = m_a1/m_a0;
	iir2->B2 = m_a2/m_a0;
}
