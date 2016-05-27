import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
from scipy.optimize import curve_fit

###############################################################################################################

X_1 , Y_1 , X_2 , Y_2 , X_3 , Y_3 , X_4 , Y_4 , X_5 , Y_5 , X_6 , Y_6 , X_7 , Y_7 , X_8 , Y_8 , X_9 , Y_9 , X_10 , Y_10 , X_11 , Y_11 , X_12 , Y_12 , X_13 , Y_13 , X_14 , Y_14 , X_15 , Y_15 , X_16 , Y_16 = np.genfromtxt( 'Ergebnisse/Ergebnis_0_Orte.txt' , unpack=True)

plt.xlabel(r'$x/\sigma$')
plt.ylabel(r'$y/\sigma$')

plt.plot( X_1 , Y_1 , 'x')
plt.plot( X_2 , Y_2 , 'x')
plt.plot( X_3 , Y_3 , 'x')
plt.plot( X_4 , Y_4 , 'x')
plt.plot( X_5 , Y_5 , 'x')
plt.plot( X_6 , Y_6 , 'x')
plt.plot( X_7 , Y_7 , 'x')
plt.plot( X_8 , Y_8 , '.')
plt.plot( X_9 , Y_9 , '.')
plt.plot( X_10 , Y_10 , '.')
plt.plot( X_11 , Y_11 , '.')
plt.plot( X_12 , Y_12 , '.')
plt.plot( X_13 , Y_13 , '.')
plt.plot( X_14 , Y_14 , '.')
plt.plot( X_15 , Y_15 , 'o')
plt.plot( X_16 , Y_16 , 'o')

plt.grid()
plt.savefig("Plots/Plot_0_Orte.png")
plt.clf()

Zeit , Energie_kin , Energie_pot , Energie_ges , Temperatur , V_S_X , V_S_Y = np.genfromtxt( 'Ergebnisse/Ergebnis_0_Energie.txt' , unpack=True)
plt.plot( Zeit, Energie_ges , 'k-' , label=r'$E_{ges}$')
plt.plot( Zeit, Energie_pot , 'b-' , label=r'$E_{pot}$')
plt.plot( Zeit, Energie_kin , 'r-' , label=r'$E_{kin}$')
plt.xlabel(r'$t/s$')
plt.ylabel(r'$E/\epsilon$')
plt.legend(loc='best')
plt.grid()
plt.savefig("Plots/Plot_0_Energie.pdf")
plt.clf()

plt.xlabel(r'$t/s$')
plt.ylabel(r'$T/\epsilon$')
plt.plot( Zeit, Temperatur , 'b-' )
plt.grid()
plt.savefig("Plots/Plot_0_Temperatur.pdf")
plt.clf()

plt.plot( Zeit, V_S_Y*1e14 , 'b-' , label=r'$V_x$')
plt.plot( Zeit , V_S_X*1e14 , 'r-' , label=r'$V_y$')
plt.xlabel(r'$t/s$')
plt.ylabel(r'$v/\sigma/s\cdot10^{14} $')
plt.legend(loc='best')
plt.grid()
plt.savefig("Plots/Plot_0_schwer.pdf")
plt.clf()

Zeit , Energie_kin , Energie_pot , Temperatur = np.genfromtxt( 'Ergebnisse/Ergebnis_0_OBS.txt' , unpack=True)
plt.plot( Zeit , Energie_kin , label=r'$\langle E_{kin}\rangle$')
plt.plot( Zeit , Energie_pot , label=r'$\langle E_{pot}\rangle$')
plt.grid()
plt.xlabel(r'$t/s$')
plt.legend(loc='best')
plt.ylabel(r'$\langle E\rangle /\epsilon$')
plt.savefig("Plots/Plot_0_E_OBS.pdf")
plt.clf()

plt.grid()
plt.xlabel(r'$t/s$')
plt.ylabel(r'$\langle T\rangle /\epsilon$')
plt.plot( Zeit , Temperatur)
plt.savefig("Plots/Plot_0_Temperatur_OBS.pdf")
plt.clf()

Abstand , g_ = np.genfromtxt( 'Ergebnisse/Ergebnis_0_Paar.txt' , unpack=True)
plt.plot( Abstand , g_ , ".")
plt.grid()
plt.xlabel(r'$r/\sigma$')
plt.ylabel(r'$g(r)$')
plt.savefig("Plots/Plot_0_Paar.pdf")
plt.clf()

###############################################################################################################

Zeit , Energie_kin , Energie_pot , Energie_ges , Temperatur , V_S_X , V_S_Y = np.genfromtxt( 'Ergebnisse/Ergebnis_1_Energie.txt' , unpack=True)
plt.plot( Zeit, Energie_ges , 'k-' , label=r'$E_{ges}$')
plt.plot( Zeit, Energie_pot , 'b-' , label=r'$E_{pot}$')
plt.plot( Zeit, Energie_kin , 'r-' , label=r'$E_{kin}$')
plt.xlabel(r'$t/s$')
plt.ylabel(r'$E/\epsilon$')
plt.legend(loc='best')
plt.grid()
plt.savefig("Plots/Plot_1_Energie.pdf")
plt.clf()

plt.xlabel(r'$t/s$')
plt.ylabel(r'$T/\epsilon$')
plt.plot( Zeit, Temperatur , 'b-' )
plt.grid()
plt.savefig("Plots/Plot_1_Temperatur.pdf")
plt.clf()

Zeit , Energie_kin , Energie_pot , Temperatur = np.genfromtxt( 'Ergebnisse/Ergebnis_1_OBS.txt' , unpack=True)
plt.plot( Zeit , Energie_kin , label=r'$\langle E_{kin}\rangle$')
plt.plot( Zeit , Energie_pot , label=r'$\langle E_{pot}\rangle$')
plt.grid()
plt.xlabel(r'$t/s$')
plt.legend(loc='best')
plt.ylabel(r'$\langle E\rangle /\epsilon$')
plt.savefig("Plots/Plot_1_E_OBS.pdf")
plt.clf()

plt.grid()
plt.xlabel(r'$t/s$')
plt.ylabel(r'$\langle T\rangle /\epsilon$')
plt.plot( Zeit , Temperatur)
plt.savefig("Plots/Plot_1_Temperatur_OBS.pdf")
plt.clf()

Abstand , g_ = np.genfromtxt( 'Ergebnisse/Ergebnis_1_Paar.txt' , unpack=True)
plt.plot( Abstand , g_ , ".")
plt.grid()
plt.xlabel(r'$r/\sigma$')
plt.ylabel(r'$g(r)$')
plt.savefig("Plots/Plot_1_Paar.pdf")
plt.clf()

###############################################################################################################

Zeit , Energie_kin , Energie_pot , Energie_ges , Temperatur , V_S_X , V_S_Y = np.genfromtxt( 'Ergebnisse/Ergebnis_2_Energie.txt' , unpack=True)
plt.plot( Zeit, Energie_ges , 'k-' , label=r'$E_{ges}$')
plt.plot( Zeit, Energie_pot , 'b-' , label=r'$E_{pot}$')
plt.plot( Zeit, Energie_kin , 'r-' , label=r'$E_{kin}$')
plt.xlabel(r'$t/s$')
plt.ylabel(r'$E/\epsilon$')
plt.legend(loc='best')
plt.grid()
plt.savefig("Plots/Plot_2_Energie.pdf")
plt.clf()

plt.xlabel(r'$t/s$')
plt.ylabel(r'$T/\epsilon$')
plt.plot( Zeit, Temperatur , 'b-' )
plt.grid()
plt.savefig("Plots/Plot_2_Temperatur.pdf")
plt.clf()

Zeit , Energie_kin , Energie_pot , Temperatur = np.genfromtxt( 'Ergebnisse/Ergebnis_2_OBS.txt' , unpack=True)
plt.plot( Zeit , Energie_kin , label=r'$\langle E_{kin}\rangle$')
plt.plot( Zeit , Energie_pot , label=r'$\langle E_{pot}\rangle$')
plt.grid()
plt.xlabel(r'$t/s$')
plt.legend(loc='best')
plt.ylabel(r'$\langle E\rangle /\epsilon$')
plt.savefig("Plots/Plot_2_E_OBS.pdf")
plt.clf()

plt.grid()
plt.xlabel(r'$t/s$')
plt.ylabel(r'$\langle T\rangle /\epsilon$')
plt.plot( Zeit , Temperatur)
plt.savefig("Plots/Plot_2_Temperatur_OBS.pdf")
plt.clf()

Abstand , g_ = np.genfromtxt( 'Ergebnisse/Ergebnis_2_Paar.txt' , unpack=True)
plt.plot( Abstand , g_ , ".")
plt.grid()
plt.xlabel(r'$r/\sigma$')
plt.ylabel(r'$g(r)$')
plt.savefig("Plots/Plot_2_Paar.pdf")
plt.clf()

###############################################################################################################

Zeit , Energie_kin , Energie_pot , Energie_ges , Temperatur , V_S_X , V_S_Y = np.genfromtxt( 'Ergebnisse/Ergebnis_3_Energie.txt' , unpack=True)
plt.plot( Zeit, Energie_ges , 'k-' , label=r'$E_{ges}$')
plt.plot( Zeit, Energie_pot , 'b-' , label=r'$E_{pot}$')
plt.plot( Zeit, Energie_kin , 'r-' , label=r'$E_{kin}$')
plt.xlabel(r'$t/s$')
plt.ylabel(r'$E/\epsilon$')
plt.legend(loc='best')
plt.grid()
plt.savefig("Plots/Plot_3_Energie.pdf")
plt.clf()

plt.xlabel(r'$t/s$')
plt.ylabel(r'$T/\epsilon$')
plt.plot( Zeit, Temperatur , 'b-' )
plt.grid()
plt.savefig("Plots/Plot_3_Temperatur.pdf")
plt.clf()

Zeit , Energie_kin , Energie_pot , Temperatur = np.genfromtxt( 'Ergebnisse/Ergebnis_3_OBS.txt' , unpack=True)
plt.plot( Zeit , Energie_kin , label=r'$\langle E_{kin}\rangle$')
plt.plot( Zeit , Energie_pot , label=r'$\langle E_{pot}\rangle$')
plt.grid()
plt.xlabel(r'$t/s$')
plt.legend(loc='best')
plt.ylabel(r'$\langle E\rangle /\epsilon$')
plt.savefig("Plots/Plot_3_E_OBS.pdf")
plt.clf()

plt.grid()
plt.xlabel(r'$t/s$')
plt.ylabel(r'$\langle T\rangle /\epsilon$')
plt.plot( Zeit , Temperatur)
plt.savefig("Plots/Plot_3_Temperatur_OBS.pdf")
plt.clf()

Abstand , g_ = np.genfromtxt( 'Ergebnisse/Ergebnis_3_Paar.txt' , unpack=True)
plt.plot( Abstand , g_ , ".")
plt.grid()
plt.xlabel(r'$r/\sigma$')
plt.ylabel(r'$g(r)$')
plt.savefig("Plots/Plot_3_Paar.pdf")
plt.clf()

###############################################################################################################

Zeit , Energie_kin , Energie_pot , Energie_ges , Temperatur , V_S_X , V_S_Y = np.genfromtxt( 'Ergebnisse/Ergebnis_D_Energie.txt' , unpack=True)
plt.plot( Zeit[:-1000:], Energie_ges[:-1000:] , 'k-' , label=r'$E_{ges}$')
plt.plot( Zeit[:-1000:], Energie_pot[:-1000:] , 'b-' , label=r'$E_{pot}$')
plt.plot( Zeit[:-1000:], Energie_kin[:-1000:] , 'r-' , label=r'$E_{kin}$')
plt.xlabel(r'$t/s$')
plt.ylabel(r'$E/\epsilon$')
plt.legend(loc='best')
plt.grid()
plt.savefig("Plots/Plot_D_Energie.pdf")
plt.clf()

plt.xlabel(r'$t/s$')
plt.ylabel(r'$T/\epsilon$')
plt.plot( Zeit, Temperatur , 'b-' )
plt.grid()
plt.savefig("Plots/Plot_D_Temperatur.pdf")
plt.clf()

Zeit , Energie_kin , Energie_pot , Temperatur = np.genfromtxt( 'Ergebnisse/Ergebnis_D_OBS.txt' , unpack=True)
plt.plot( Zeit , Energie_kin , label=r'$\langle E_{kin}\rangle$')
plt.plot( Zeit , Energie_pot , label=r'$\langle E_{pot}\rangle$')
plt.grid()
plt.xlabel(r'$t/s$')
plt.legend(loc='best')
plt.ylabel(r'$\langle E\rangle /\epsilon$')
plt.savefig("Plots/Plot_D_E_OBS.pdf")
plt.clf()

plt.grid()
plt.xlabel(r'$t/s$')
plt.ylabel(r'$\langle T\rangle /\epsilon$')
plt.plot( Zeit , Temperatur)
plt.savefig("Plots/Plot_D_Temperatur_OBS.pdf")
plt.clf()

Abstand , g_ = np.genfromtxt( 'Ergebnisse/Ergebnis_D_Paar.txt' , unpack=True)
plt.plot( Abstand , g_ , "-r")
plt.grid()
plt.xlabel(r'$r/\sigma$')
plt.ylabel(r'$g(r)$')
plt.savefig("Plots/Plot_D_Paar.pdf")
plt.clf()

###############################################################################################################

X_1 , Y_1 , X_2 , Y_2 , X_3 , Y_3 , X_4 , Y_4 , X_5 , Y_5 , X_6 , Y_6 , X_7 , Y_7 , X_8 , Y_8 , X_9 , Y_9 , X_10 , Y_10 , X_11 , Y_11 , X_12 , Y_12 , X_13 , Y_13 , X_14 , Y_14 , X_15 , Y_15 , X_16 , Y_16 = np.genfromtxt( 'Ergebnisse/Ergebnis_D_Orte.txt' , unpack=True)

plt.xlabel(r'$x/\sigma$')
plt.ylabel(r'$y/\sigma$')
plt.ylim(0 , 8)
plt.xlim(0 , 8)

plt.plot( X_1 , Y_1 , 'x')

plt.plot( X_2 , Y_2 , 'x')

plt.plot( X_3 , Y_3 , 'x')

plt.plot( X_4 , Y_4 , 'x')
plt.plot( X_5 , Y_5 , 'x')
plt.plot( X_6 , Y_6 , 'x')
plt.plot( X_7 , Y_7 , 'x')
plt.plot( X_8 , Y_8 , '.')
plt.plot( X_9 , Y_9 , '.')
plt.plot( X_10 , Y_10 , '.')
plt.plot( X_11 , Y_11 , '.')
plt.plot( X_12 , Y_12 , '.')
plt.plot( X_13 , Y_13 , '.')
plt.plot( X_14 , Y_14 , '.')
plt.plot( X_15 , Y_15 , 'o')
plt.plot( X_16 , Y_16 , 'o')

plt.grid()
plt.savefig("Plots/Plot_D_Orte.png")
plt.clf()