#include <math.h>
#include <math_const.h>
#include "iir2.h"

IIR2::IIR2(IIRFilterType type, float frequency, float Q, float sampletime)
{
	m_type = type;
	m_frequency = frequency;
	m_Q = Q;
	m_sampletime = sampletime;
	Calc_Coefs();
}
//-------------------------------------------------------------------------------------------------
//Y[n] = A0*X[n] + A1*X[n-1] + A2*X[n-2] - B1*Y[n-1] - B2*Y[n-2]
float IIR2::Filter(float xn)
{
	float yn;
	
	switch(m_type)
	{
		//Y[n] = A0*(X[n] - X[n-2]) - B1*Y[n-1] - B2*Y[n-2]
		case FT_BANDPASS:
			yn = A0*(xn - xn2) - B1*yn1 - B2*yn2;
		break;
		
		//Y[n] = A0*(X[n] + X[n-2]) + A1*(X[n-1] - Y[n-1]) - B2*Y[n-2]
		case FT_BANDSTOP:
			yn = A0*(xn + xn2) + A1*(xn1 - yn1) - B2*yn2;
		break;
		
		//Y[n] = A0*(X[n] + X[n-2]) + A1*X[n-1] - B1*Y[n-1] - B2*Y[n-2]
		case FT_HIGHPASS:
			yn = A0*(xn + xn2) + A1*xn1 - B1*yn1 - B2*yn2;
		break;
		
		//Y[n] = A0*(X[n] + X[n-2]) + A1*X[n-1] - B1*Y[n-1] - B2*Y[n-2]
		case FT_LOWPASS:
			yn = A0*(xn + xn2) + A1*xn1 - B1*yn1 - B2*yn2;
		break;		
	}
	
	xn2 = xn1;
	xn1 = xn;
	yn2 = yn1;
	yn1 = yn;
	
	return yn;
}
//-------------------------------------------------------------------------------------------------
void IIR2::SetFrequency(float value){m_frequency = value; Calc_Coefs();}
void IIR2::SetType(IIRFilterType value) {m_type = value; Calc_Coefs();}
void IIR2::SetQ(float value) {m_Q = value; Calc_Coefs();}
void IIR2::SetSampletime(float value) {m_sampletime = value; Calc_Coefs();}
//-------------------------------------------------------------------------------------------------
void IIR2::Calc_Coefs(void)
{
	float m_a0, m_a1, m_a2, m_b0, m_b1, m_b2;
	
	float omega = 2.0*PI*m_frequency*m_sampletime;
	float SIN = sinf(omega);
	float COS = cosf(omega);
	float alpha = SIN/(2.0*m_Q);
	
	switch(m_type)
	{
		case FT_BANDPASS:
			m_b0 = alpha;
			m_b1 = 0;
			m_b2 = -alpha;
			m_a0 = 1 + alpha;
			m_a1 = -2*COS;
			m_a2 = 1 - alpha;
		break;
		
		case FT_BANDSTOP:
			m_b0 = 1;
			m_b1 = -2*COS;
			m_b2 = 1;
			m_a0 = 1 + alpha;
			m_a1 = -2*COS;
			m_a2 = 1 - alpha;
		break;
		
		case FT_HIGHPASS:
			m_b0 = (1 + COS)/2;
			m_b1 = -(1 + COS);
			m_b2 = (1 + COS)/2;
			m_a0 = 1 + alpha;
			m_a1 = -2*COS;
			m_a2 = 1 - alpha;
		break;
		
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
	
	A0 = m_b0/m_a0;
	A1 = m_b1/m_a0;
	A2 = m_b2/m_a0;
	B1 = m_a1/m_a0;
	B2 = m_a2/m_a0;
}
