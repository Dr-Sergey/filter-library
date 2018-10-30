#ifndef IIR2_H
#define IIR2_H

typedef enum {FT_BANDPASS, FT_BANDSTOP, FT_HIGHPASS, FT_LOWPASS} IIRFilterType;

//Y[n] = A0*X[n] + A1*X[n-1] + A2*X[n-2] - B1*Y[n-1] - B2*Y[n-2]
class IIR2
{
	public:
	IIR2(IIRFilterType type = FT_LOWPASS, float frequency = 1.0, float Q = 1.0, float sampletime = 1e-4);
	float Filter(float xn);
	void SetType(IIRFilterType value);
	void SetFrequency(float value);
	void SetQ(float value);
	void SetSampletime(float value);
	
	protected:
	void Calc_Coefs(void);
	
	IIRFilterType m_type;
	float m_frequency;
	float m_Q;
	float m_sampletime;
	
	float A0, A1, A2;
	float B1, B2;
	
	float xn1, xn2, yn1, yn2;
};

#endif
