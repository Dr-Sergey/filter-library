import iir1
import numpy as np
import scipy as sp
from scipy import signal
import matplotlib.pyplot as plt
from matplotlib.widgets import Cursor
from timeit import default_timer as timer

samplerate = 2000
decay      = 0.01

# Time series parameters
A          = 100
freq       = 10  #Hz
time       = 0.2 #seconds

# Frequency responce parameters
Fmin       = 0.1
Fmax       = 30
Fdelta     = 0.1
NumPeriods = 20

t = np.linspace( 0, time, int(time*samplerate) )

# create and init filter
flt = iir1.iir1_lab()
print( flt.description() )
flt.setDecay(decay)
flt.setNumPeriods(NumPeriods)

datain_sin = A*sp.sin( 2*np.pi*freq*t )
datain_m   = A*signal.square( 2*np.pi*freq*t )

# filtering
dataout_sin = flt.process( list(datain_sin) )
dataout_m   = flt.process( list(datain_m) )

# plot transient for sinusoidal signal
fig1 = plt.figure(1)
ax1 = fig1.add_subplot(1, 1, 1)
ax1.plot( t, datain_sin )
ax1.plot( t, dataout_sin )
cursor1 = Cursor(ax1, useblit=True, color='r', linewidth=1)
plt.show( block=False )

# plot transient for meander
fig2 = plt.figure(2)
ax2 = fig2.add_subplot(1, 1, 1)
ax2.plot( t, datain_m )
ax2.plot( t, dataout_m )
cursor2 = Cursor(ax2, useblit=True, color='r', linewidth=1)
plt.show( block=False )

# build frequency response
start = timer()
f = np.arange(Fmin, Fmax, Fdelta)
fres = flt.fresponce( list(f), samplerate )
end = timer()
print( "Elapsed time for frequency response: ", end - start )

# plot frequency response
fig3 = plt.figure(3)
ax3 = fig3.add_subplot(1, 1, 1)
ax3.plot(f, fres)
cursor3 = Cursor(ax3, useblit=True, color='r', linewidth=1)
plt.show()
