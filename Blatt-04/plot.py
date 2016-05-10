import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit


Zeit , theta_1 , theta_2 , theta_V_1 , theta_V_2 = np.genfromtxt( 'Ergebnisse/Ergebnis_1_C_1.txt' , unpack=True)
plt.plot( np.sin(theta_1) , -np.cos(theta_1) , 'r-' )
plt.plot( np.sin(theta_1) + np.sin(theta_2), -np.cos(theta_1)-np.cos(theta_2) , 'b-')
#plt.show()
plt.clf()

Zeit , theta_1 , theta_2 , theta_V_1 , theta_V_2 = np.genfromtxt( 'Ergebnisse/Ergebnis_1_C_1.txt' , unpack=True)
#plt.plot( np.sin(theta_1) , -np.cos(theta_1) , 'r-' )
plt.plot(theta_1 , theta_V_1, 'b-')
plt.show()