#include <cmath>
#include "iir1.h"

#define M_E 2.71828182845904523536f

//------------------------------------------------------------------------------------------------
IIR1_LowPass::IIR1_LowPass(float decay): m_decay(decay), yn1(0)
{ }
//------------------------------------------------------------------------------------------------
float IIR1_LowPass::Filter(float value)
{
	float output = m_decay*value + (1 - m_decay)*yn1;
	yn1 = output;
	
	return output;
}
//------------------------------------------------------------------------------------------------
void IIR1_LowPass::Reset()
{
	yn1 = 0;
}
//------------------------------------------------------------------------------------------------
void IIR1_LowPass::setTimeConstant(float value, float sample_time)
{
	m_decay = 1 - pow(M_E, -sample_time/value);
}

