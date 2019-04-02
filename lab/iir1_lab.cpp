#include <math.h>
#include <limits>
#include "types.h"

#include "../src/iir1.hpp"

class iir1_lab
{
    public:
        // get lab description
        std::string description()
        {
            return std::string("Simple first order infinite impulse response filter");
        }

        // process data with filter
        list process(list data)
        {
            std::vector<float> tmp;
            py2stl(data, tmp);     
            return stl2py( filter_data(tmp) );
        }

        // set Decay filter parameter
        void setDecay(float value)
        {
            filter.m_decay = value;
        }

        // set number periods to calculate frequency response
        void setNumPeriods(int value)
        {
            if(value > 0) m_periods = value;
        }

        // calculate frequency response
        list fresponce(list freqs, float samplerate)
        {
            std::vector<float> res;
            std::vector<float> freqs_tmp;
            py2stl(freqs, freqs_tmp);

            for(auto& v : freqs_tmp)
            {
                std::vector<float> sine_data = getSine( v, samplerate );
                std::vector<float> tmp = filter_data( sine_data );
                float m = *std::max_element( tmp.begin() + tmp.size()*0.5, tmp.end() );            
                res.push_back(m);
            }

            return stl2py( res );
        }

    private:
        IIR1_LowPass filter{0.1};
        int m_periods{100};

        std::vector<float> filter_data(std::vector<float> data)
        {
            for(auto& v : data) v = filter.Filter(v);
            return std::move( data );
        }

        std::vector<float> getSine(float frequency, float samplerate)
        {
            int size = (samplerate/frequency)*m_periods;
            std::vector<float> res;
            float dt = 1.0/samplerate;
            for(int i = 0; i < size; ++i) 
            {
                res.push_back( std::sin(M_PI*2*frequency*dt*i) ); 
            }

            return std::move(res);
        }
};

BOOST_PYTHON_MODULE(iir1)
{

    class_<iir1_lab>( "iir1_lab" )
        .def( "description",   &iir1_lab::description )
        .def( "process",       &iir1_lab::process )
        .def( "setDecay",      &iir1_lab::setDecay )
        .def( "fresponce",     &iir1_lab::fresponce )
        .def( "setNumPeriods", &iir1_lab::setNumPeriods )
    ;
}