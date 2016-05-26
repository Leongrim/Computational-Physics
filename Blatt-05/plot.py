import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
from scipy.optimize import curve_fit


Zeit , Energie_kin , Energie_pot , Energie_ges , Temperatur , V_S_X , V_S_Y = np.genfromtxt( 'Ergebnisse/Ergebnis_1.txt' , unpack=True)
plt.plot( Zeit, Energie_ges , 'k-' )
plt.plot( Zeit, Energie_pot , 'b-' )
plt.plot( Zeit, Energie_kin , 'r-' )

plt.grid()
plt.savefig("Plots/Plot_1_Energie.pdf")
plt.clf()
plt.plot( Zeit, Temperatur , 'b-' )
plt.grid()
plt.savefig("Plots/Plot_1_Temperatur.pdf")
plt.clf()
plt.plot( Zeit, V_S_Y , 'b-' )
plt.plot( Zeit , V_S_X , 'r-')
plt.grid()
plt.savefig("Plots/Plot_1_schwer.pdf")
plt.clf()

Zeit , Energie_kin , Energie_pot , Temperatur = np.genfromtxt( 'Ergebnisse/Ergebnis_1_OBS.txt' , unpack=True)
plt.plot( Zeit , Energie_kin)
plt.plot( Zeit , Energie_pot)
plt.grid()
plt.savefig("Plots/Plot_1_Energie_OBS.pdf")
plt.clf()
plt.grid()
plt.plot( Zeit , Temperatur)
plt.savefig("Plots/Plot_1_Temperatur_OBS.pdf")
plt.clf()

Abstand , g_ = np.genfromtxt( 'Ergebnisse/Ergebnis_1_PAAR.txt' , unpack=True)
plt.plot( Abstand , g_ , ".")
plt.savefig("Plots/Plot_1_Paar.pdf")
plt.clf()

##########################################

Zeit , Energie_kin , Energie_pot , Energie_ges , Temperatur , V_S_X , V_S_Y = np.genfromtxt( 'Ergebnisse/Ergebnis_2.txt' , unpack=True)
plt.plot( Zeit, Energie_ges , 'k-' )
plt.plot( Zeit, Energie_pot , 'b-' )
plt.plot( Zeit, Energie_kin , 'r-' )

plt.grid()
plt.savefig("Plots/Plot_2_Energie.pdf")
plt.clf()
plt.plot( Zeit, Temperatur , 'b-' )
plt.grid()
plt.savefig("Plots/Plot_2_Temperatur.pdf")
plt.clf()
plt.plot( Zeit, V_S_Y , 'b-' )
plt.plot( Zeit , V_S_X , 'r-')
plt.grid()
plt.savefig("Plots/Plot_2_schwer.pdf")
plt.clf()

Zeit , Energie_kin , Energie_pot , Temperatur = np.genfromtxt( 'Ergebnisse/Ergebnis_2_OBS.txt' , unpack=True)
plt.plot( Zeit , Energie_kin)
plt.plot( Zeit , Energie_pot)
plt.grid()
plt.savefig("Plots/Plot_2_Energie_OBS.pdf")
plt.clf()
plt.grid()
plt.plot( Zeit , Temperatur)
plt.savefig("Plots/Plot_1_Temperatur_OBS.pdf")
plt.clf()

Abstand , g_ = np.genfromtxt( 'Ergebnisse/Ergebnis_2_PAAR.txt' , unpack=True)
plt.plot( Abstand , g_ , ".")
plt.savefig("Plots/Plot_2_Paar.pdf")
plt.clf()

##################################

Zeit , Energie_kin , Energie_pot , Energie_ges , Temperatur , V_S_X , V_S_Y = np.genfromtxt( 'Ergebnisse/Ergebnis_3.txt' , unpack=True)
plt.plot( Zeit, Energie_ges , 'k-' )
plt.plot( Zeit, Energie_pot , 'b-' )
plt.plot( Zeit, Energie_kin , 'r-' )

plt.grid()
plt.savefig("Plots/Plot_3_Energie.pdf")
plt.clf()
plt.plot( Zeit, Temperatur , 'b-' )
plt.grid()
plt.savefig("Plots/Plot_3_Temperatur.pdf")
plt.clf()
plt.plot( Zeit, V_S_Y , 'b-' )
plt.plot( Zeit , V_S_X , 'r-')
plt.grid()
plt.savefig("Plots/Plot_3_schwer.pdf")
plt.clf()

Zeit , Energie_kin , Energie_pot , Temperatur = np.genfromtxt( 'Ergebnisse/Ergebnis_3_OBS.txt' , unpack=True)
plt.plot( Zeit , Energie_kin)
plt.plot( Zeit , Energie_pot)
plt.grid()
plt.savefig("Plots/Plot_3_Energie_OBS.pdf")
plt.clf()
plt.plot( Zeit , Temperatur)
plt.grid()
plt.savefig("Plots/Plot_3_Temperatur_OBS.pdf")
plt.clf()

Abstand , g_ = np.genfromtxt( 'Ergebnisse/Ergebnis_3_PAAR.txt' , unpack=True)
plt.plot( Abstand , g_ , ".")
plt.savefig("Plots/Plot_3_Paar.pdf")
plt.clf()




"""
X_1 , Y_1 , X_2 , Y_2 , X_3 , Y_3 , X_4 , Y_4 , X_5 , Y_5 , X_6 , Y_6 , X_7 , Y_7 , X_8 , Y_8 , X_9 , Y_9 , X_10 , Y_10 , X_11 , Y_11 , X_12 , Y_12 , X_13 , Y_13 , X_14 , Y_14 , X_15 , Y_15 , X_16 , Y_16 = np.genfromtxt( 'Ergebnisse/Ergebnis_1_Orte.txt' , unpack=True)

plt.plot( X_1 , Y_1 , 'x')

plt.plot( X_2 , Y_2 , 'x')
plt.plot( X_3 , Y_3 , 'x')
plt.plot( X_4 , Y_4 , 'x')
plt.plot( X_5 , Y_5 , 'x')
plt.plot( X_6 , Y_6 , 'x')
plt.plot( X_7 , Y_7 , 'x')
plt.plot( X_8 , Y_8 , 'x')
plt.plot( X_9 , Y_9 , 'x')
plt.plot( X_10 , Y_10 , 'x')
plt.plot( X_11 , Y_11 , 'x')
plt.plot( X_12 , Y_12 , 'x')
plt.plot( X_13 , Y_13 , 'x')
plt.plot( X_14 , Y_14 , 'x')
plt.plot( X_15 , Y_15 , 'x')

plt.plot( X_16 , Y_16 , 'x')
plt.savefig("Plots/Plot_1_Orte.png")

plt.clf()
X_1 , Y_1 , X_2 , Y_2 , X_3 , Y_3 , X_4 , Y_4 , X_5 , Y_5 , X_6 , Y_6 , X_7 , Y_7 , X_8 , Y_8 , X_9 , Y_9 , X_10 , Y_10 , X_11 , Y_11 , X_12 , Y_12 , X_13 , Y_13 , X_14 , Y_14 , X_15 , Y_15 , X_16 , Y_16 = np.genfromtxt( 'Ergebnisse/Ergebnis_2_Orte.txt' , unpack=True)

plt.plot( X_1 , Y_1 , 'x')

plt.plot( X_2 , Y_2 , 'x')
plt.plot( X_3 , Y_3 , 'x')
plt.plot( X_4 , Y_4 , 'x')
plt.plot( X_5 , Y_5 , 'x')
plt.plot( X_6 , Y_6 , 'x')
plt.plot( X_7 , Y_7 , 'x')
plt.plot( X_8 , Y_8 , 'x')
plt.plot( X_9 , Y_9 , 'x')
plt.plot( X_10 , Y_10 , 'x')
plt.plot( X_11 , Y_11 , 'x')
plt.plot( X_12 , Y_12 , 'x')
plt.plot( X_13 , Y_13 , 'x')
plt.plot( X_14 , Y_14 , 'x')
plt.plot( X_15 , Y_15 , 'x')

plt.plot( X_16 , Y_16 , 'x')
plt.savefig("Plots/Plot_2_Orte.png")
plt.clf()

"""