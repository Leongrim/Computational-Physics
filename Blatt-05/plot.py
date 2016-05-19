import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit


Zeit , Energie_kin , Energie_pot , Energie_ges , Temperatur , V_S_X , V_S_Y = np.genfromtxt( 'Ergebnisse/Ergebnis_1.txt' , unpack=True)
plt.plot( Zeit, Energie_ges , 'b-' )
#plt.plot( Zeit , Energie_kin , 'r-')
#plt.plot( Zeit , Energie_pot , 'g-')
plt.grid()
plt.savefig("Plots/Plot_1_Energie.pdf")
plt.clf()