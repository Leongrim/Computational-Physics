import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

theta_1 , theta_2 , theta_V_1 , theta_V_2 = np.genfromtxt( 'Ergebnisse/Ergebnis_2_C_Chaos.txt' , unpack=True)
plt.plot(theta_1 , theta_V_1 , 'r.')
plt.legend(loc='best')
plt.grid()
plt.show()
#plt.savefig("Plots/Plot_1_C_1_trajektorie.pdf")
plt.clf()
