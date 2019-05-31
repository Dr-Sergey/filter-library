#ifndef IIR1_H
#define IIR1_H

class IIR1_LowPass
{
public:
	IIR1_LowPass(float decay);
	float Filter(float value);
	void Reset();

	void setTimeConstant(float value, float sample_time);
	
	float m_decay = 0;

protected:
	float yn1;
	
};


#endif 
