#ifndef MAVERAGE_H_
#define MAVERAGE_H_

#include <stdint.h>
#include <memory>

template<int S> // size of delay line
class MAverage
{
public:
	MAverage()
	{
		output = 0;
		ind_delay = 0;
		k_mult = 1.0f/S;
	}

	void reset()
	{
		ind_delay = 0;
		for(int i = 0; i < S; ++i) acc_delay[i] = 0;
	}

	float filter(float value)
	{
		// handle delay line
		acc_delay[ind_delay] = value;
		++ind_delay;
		if(ind_delay >= S) ind_delay = 0;

		return calc();
	}

	int32_t output;

private:
	float calc()
	{
		float acc = 0;
		for(int i = 0; i < S; ++i) acc += acc_delay[i];
		return acc*k_mult;
	}

	float   acc_delay[S];
	int32_t ind_delay;
	float   k_mult;
};

#endif /* MAVERAGE_H_ */
