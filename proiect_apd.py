
import numpy as np
from scipy.signal import hilbert
from scipy.io import wavfile
import matplotlib.pyplot as plt

samplerate, data = wavfile.read('/content/52.wav')

wavFileInfo = open("wafeInfo.txt", "a")
wavFileInfo.write(str(samplerate)+'\n')
wavFileInfo.write(str(data.size)+'\n')
wavFileInfo.close()

v=[]
for row in range(len(data)):#extragere un canal
  for column in range(len(data[0])):
    v.append((data[row][0]))
analytic_signal=hilbert(v);
amplitude_envelope=np.abs(analytic_signal)#anvelopa pentru un singur canal

analytic_signal2=hilbert(data)
envelope2=np.abs(analytic_signal2)

a=np.diff(np.sign(np.diff(v))).nonzero()[0]+1 #local min si max
b=(np.diff(np.sign(np.diff(v)))>0).nonzero()[0]+1 #local min
c=(np.diff(np.sign(np.diff(v)))<0).nonzero()[0]+1 #local max
print(a)
print(b)
print(c)
x=np.arange(len(v))
plt.plot(np.array(v)[c], color='r')  # Afișează maximele locale
plt.show()

#print(samplerate)
#print(data.size)
#print (data)
#print(v)

np.savetxt("waveData.txt", data, fmt="%2.0f")
np.savetxt("envelope.txt",amplitude_envelope,fmt="%2.0f")
np.savetxt("canal1.txt",v,fmt="%2.0f")
np.savetxt("anvelopa.txt",envelope2,fmt="%2.0f")
np.savetxt("c.txt",c,fmt="%2.0f")





