#include <math.h>
#include "iir1.hpp"

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


