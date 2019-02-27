#ifndef CICDECIMATOR_H_
#define CICDECIMATOR_H_

#include <stdint.h>
#include <memory>

template<int M, // Decimation Factor
         int N,  // Order
         int R>	 // Delay scale of comb filter
class CIC_decimator
{
public:
	CIC_decimator()
	{
		output = 0;
		ind_delay = 0;
	}

	void reset()
	{
		output = 0;
		ind_delay = 0;

		std::memset(acc, 0, sizeof(acc[0])*N);
		std::memset(combs, 0, sizeof(combs[0][0])*(N+1)*(R+1));
	}

	void new_value(int32_t value)
	{
		// handle delay line
		cic_delay[ind_delay] = value;
		++ind_delay;
		if(ind_delay >= M)
		{
			ind_delay = 0;
			calc();
		}
	}

	int32_t output;

private:
	void calc()
	{
		int i = 0, k = 0, n = 0;

		// Downsample each element one by one
		for (i = 0; i < M; i++)
		{
			/*INTEGRATE*/
			acc[0] = acc[0] + cic_delay[i]; // 1st Stage
			for (n = 1; n < N; n++)
			{	// Remaining Stages
				// Output =  Last Output Value + Output of Previous Stage
				acc[n] = acc[n] + acc[n-1];
			}
		}

	   // Decimate block
	   // COMB
	   // First Value - Store in _Input_
	   combs[R][0] = acc[N-1];

	   // Next Values
	   for (n = 1; n <= N; n++)
	   {
		   combs[R][n] = combs[R][n-1] - combs[0][n-1];
	   }

	   // Copy back delays
	   for (n = 0; n <= N; n++)
	   {
		   for (k = 0; k < R; k++)
		   {
			   combs[k][n] = combs[k+1][n];
		   }
	   }

	   output = combs[R][N];
	}

	int32_t	 acc[N];              // Accumulators for COMB
	int32_t  combs[R + 1][N + 1]; // Values of comb, including previous

	int32_t cic_delay[M];
	int32_t ind_delay;
};

#endif /* CICDECIMATOR_H_ */
