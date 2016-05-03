import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from scipy.optimize import curve_fit


Zeit , Ort_x , Ort_y , Ort_z , V_x ,V_y , V_z = np.genfromtxt( 'Ergebnisse/Ergebnis_2_A.txt' , unpack=True)

plt.plot( Zeit , Ort_y ,'r-')
plt.grid()
plt.savefig("Plots/Plot_2_A.pdf")
plt.clf()
#plt.show()

Zeit , Ort_x , Ort_y , Ort_z , V_x ,V_y , V_z = np.genfromtxt( 'Ergebnisse/Ergebnis_2_B.txt' , unpack=True)

#fig = plt.figure()
#ax = fig.add_subplot(111,projection='3d')

plt.plot( Zeit , Ort_y  ,'r-')
plt.grid()
plt.savefig("Plots/Plot_2_B.pdf")
#plt.show()

Zeit , Ort_x , Ort_y , Ort_z , V_x ,V_y , V_z = np.genfromtxt( 'Ergebnisse/Ergebnis_4_A.txt' , unpack=True)
plt.clf()

plt.grid()
plt.plot( Ort_x , Ort_y  ,'r-')
plt.savefig("Plots/Plots_4_A.pdf")
plt.clf()
