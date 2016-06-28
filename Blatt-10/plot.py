import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit


Bin , Bincontent , Nomiert  = np.genfromtxt( 'Ergebnisse/Ergebnis_1_A.txt' , unpack=True)
plt.bar( Bin , Nomiert , width  = np.pi/1000 )
plt.savefig("Plots/Plot_A.pdf")
plt.clf()

Bin , Bincontent , Nomiert  = np.genfromtxt( 'Ergebnisse/Ergebnis_1_B.txt' , unpack=True)
plt.bar( Bin , Nomiert , width  = 1.5/1000 )
plt.savefig("Plots/Plot_B.pdf")
plt.clf()