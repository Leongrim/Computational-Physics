import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from scipy.optimize import curve_fit


Zeit , Ort_x , Ort_y , Ort_z , V_x ,V_y , V_z = np.genfromtxt( 'Ergebnisse/Ergebnis_A.txt' , unpack=True)

plt.plot( Zeit , Ort_y ,'r-')
plt.show()

Zeit , Ort_x , Ort_y , Ort_z , V_x ,V_y , V_z = np.genfromtxt( 'Ergebnisse/Ergebnis_B.txt' , unpack=True)

#fig = plt.figure()
#ax = fig.add_subplot(111,projection='3d')

plt.plot( Ort_x , Ort_y  ,'r-')
plt.show()