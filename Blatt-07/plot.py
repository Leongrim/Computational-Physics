import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

def  GAUSS( x ):
	return 1/np.sqrt(2*np.pi)*np.exp(-(x)**2/2)
	pass


Bin , Bincontent  = np.genfromtxt( 'Ergebnisse/Ergebnis_1_1_B.txt' , unpack=True)
plt.xlabel("Bin")
plt.ylabel("Bininhalt")
plt.plot( Bin , Bincontent , linestyle="steps")
plt.savefig("Plots/Plot_1_1_B.pdf")
plt.clf()

Zufall1 , Zufall2  = np.genfromtxt( 'Ergebnisse/Ergebnis_1_1_C.txt' , unpack=True)
plt.xlabel(r"$r_1$")
plt.ylabel(r"$r_2$")
plt.plot( Zufall1 , Zufall2 , ".")
plt.savefig("Plots/Plot_1_1_C.pdf")
plt.clf()

######################################################################################################################

Bin , Bincontent  = np.genfromtxt( 'Ergebnisse/Ergebnis_1_2_B.txt' , unpack=True)
plt.xlabel("Bin")
plt.ylabel("Bininhalt")
plt.plot( Bin , Bincontent , linestyle="steps")
plt.savefig("Plots/Plot_1_2_B.pdf")
plt.clf()

Zufall1 , Zufall2  = np.genfromtxt( 'Ergebnisse/Ergebnis_1_2_C.txt' , unpack=True)
plt.xlabel(r"$r_1$")
plt.ylabel(r"$r_2$")
plt.plot( Zufall1 , Zufall2 , ".")
plt.savefig("Plots/Plot_1_2_C.pdf")
plt.clf()

######################################################################################################################

Bin , Bincontent  = np.genfromtxt( 'Ergebnisse/Ergebnis_1_3_B.txt' , unpack=True)
plt.xlabel("Bin")
plt.ylabel("Bininhalt")
plt.plot( Bin , Bincontent , linestyle="steps")
plt.savefig("Plots/Plot_1_3_B.pdf")
plt.clf()

Zufall1 , Zufall2  = np.genfromtxt( 'Ergebnisse/Ergebnis_1_3_C.txt' , unpack=True)
plt.xlabel(r"$r_1$")
plt.ylabel(r"$r_2$")
plt.plot( Zufall1 , Zufall2 , ".")
plt.savefig("Plots/Plot_1_3_C.png")
plt.clf()

######################################################################################################################

Bin , Bincontent  = np.genfromtxt( 'Ergebnisse/Ergebnis_1_4_B.txt' , unpack=True)
plt.xlabel("Bin")
plt.ylabel("Bininhalt")
plt.plot( Bin , Bincontent , linestyle="steps")
plt.savefig("Plots/Plot_1_4_B.pdf")
plt.clf()

Zufall1 , Zufall2  = np.genfromtxt( 'Ergebnisse/Ergebnis_1_4_C.txt' , unpack=True)
plt.xlabel(r"$r_1$")
plt.ylabel(r"$r_2$")
plt.plot( Zufall1 , Zufall2 , ".")
plt.savefig("Plots/Plot_1_4_C.png")
plt.clf()
#######################################################################################################################

x = np.arange(-6 , 6 , 0.01)

Bin , Bincontent , Nomiert = np.genfromtxt( 'Ergebnisse/Ergebnis_2_b.txt' , unpack=True)
plt.xlabel("Bin")
plt.ylabel("Bininhalt")
plt.plot( x , GAUSS(x))
plt.plot( Bin , Nomiert , linestyle="steps")
plt.grid()
plt.savefig("Plots/Plot_2_b.pdf")
plt.clf()

x = np.arange( 0 , np.pi , 0.01)

Bin , Bincontent , Nomiert = np.genfromtxt( 'Ergebnisse/Ergebnis_2_c.txt' , unpack=True)
plt.xlabel("Bin")
plt.ylabel("Bininhalt")
plt.plot( x , 0.5*np.sin(x))
plt.plot( Bin , Nomiert , linestyle="steps")
plt.grid()
plt.savefig("Plots/Plot_2_c.pdf")
plt.clf()


x = np.arange( 0 , 1 , 0.01)

Bin , Bincontent , Nomiert = np.genfromtxt( 'Ergebnisse/Ergebnis_2_d.txt' , unpack=True)
plt.xlabel("Bin")
plt.ylabel("Bininhalt")
plt.plot( x , 3*x**2)
plt.plot( x , Nomiert , linestyle="steps")
plt.grid()
plt.savefig("Plots/Plot_2_d.pdf")
plt.clf()

