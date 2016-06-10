import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

def  GAUSS( x ):
	return 1/np.sqrt(2*np.pi)*np.exp(-(x)**2/2)
	pass

xLabel = "Zufallszahl"
yLabel = "Nomierter Bininhalt"

Xbin = np.arange(0 , 1.01 ,0.01)
einzehntel = np.ones(101)
Bin , Bincontent , Nomiert = np.genfromtxt( 'Ergebnisse/Ergebnis_1_1_B.txt' , unpack=True)
plt.xlabel(xLabel)
plt.ylabel(yLabel)
plt.bar( Bin , Nomiert , width  = 0.1 , label="Verteilung 1 gebinnte" )
plt.plot(Xbin , einzehntel , "-r" , label="Theorie")
#plt.ylim(0.09 , 0.11)
plt.legend(loc='lower right')
plt.savefig("Plots/Plot_1_1_B.pdf")
plt.clf()

Zufall1 , Zufall2  = np.genfromtxt( 'Ergebnisse/Ergebnis_1_1_C.txt' , unpack=True)
plt.xlabel(r"$r_1$")
plt.ylabel(r"$r_2$")
plt.plot( Zufall1 , Zufall2 , ".")
plt.savefig("Plots/Plot_1_1_C.pdf")
plt.clf()

######################################################################################################################

Bin , Bincontent , Nomiert  = np.genfromtxt( 'Ergebnisse/Ergebnis_1_2_B.txt' , unpack=True)
plt.xlabel(xLabel)
plt.ylabel(yLabel)
plt.bar( Bin , Nomiert , width  = 0.1 , label="Verteilung 2 gebinnte" )
plt.plot(Xbin , einzehntel , "-r" , label="Theorie")
plt.legend(loc='lower right')
plt.savefig("Plots/Plot_1_2_B.pdf")
plt.clf()

Zufall1 , Zufall2  = np.genfromtxt( 'Ergebnisse/Ergebnis_1_2_C.txt' , unpack=True)
plt.xlabel(r"$r_1$")
plt.ylabel(r"$r_2$")
plt.plot( Zufall1 , Zufall2 , ".")
plt.savefig("Plots/Plot_1_2_C.pdf")
plt.clf()

######################################################################################################################

Bin , Bincontent , Nomiert = np.genfromtxt( 'Ergebnisse/Ergebnis_1_3_B.txt' , unpack=True)
plt.xlabel(xLabel)
plt.ylabel(yLabel)
plt.bar( Bin , Nomiert , width  = 0.1 , label="Verteilung 3 gebinnte" )
plt.plot(Xbin , einzehntel , "-r" , label="Theorie")
plt.legend(loc='lower right')
plt.savefig("Plots/Plot_1_3_B.pdf")
plt.clf()

Zufall1 , Zufall2  = np.genfromtxt( 'Ergebnisse/Ergebnis_1_3_C.txt' , unpack=True)
plt.xlabel(r"$r_1$")
plt.ylabel(r"$r_2$")
plt.plot( Zufall1 , Zufall2 , ".")
plt.savefig("Plots/Plot_1_3_C.png")
plt.clf()

######################################################################################################################

Bin , Bincontent , Nomiert = np.genfromtxt( 'Ergebnisse/Ergebnis_1_4_B.txt' , unpack=True)
plt.xlabel(xLabel)
plt.ylabel(yLabel)
plt.bar( Bin , Nomiert , width  = 0.1 , label="Verteilung 4 gebinnte" )
plt.plot(Xbin , einzehntel , "-r" , label="Theorie")
plt.legend(loc='lower right')
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

Bin , Bincontent , Nomiert = np.genfromtxt( 'Ergebnisse/Ergebnis_2_a.txt' , unpack=True)
plt.xlabel("Bin")
plt.ylabel("normierter Bininhalt")
plt.bar( Bin , Nomiert , width  = 0.1 , label="Gebinnte Zufallszahlen")
plt.plot( x , GAUSS(x) , "-r" , label="Theorie")
plt.grid()
plt.legend(loc='best')
plt.savefig("Plots/Plot_2_a.pdf")
plt.clf()


x = np.arange(-6 , 6 , 0.01)

Bin_b , Bincontent_b , Nomiert_b = np.genfromtxt( 'Ergebnisse/Ergebnis_2_b.txt' , unpack=True)
plt.xlabel(xLabel)
plt.ylabel(yLabel)
#plt.bar( Bin , Nomiert_b - GAUSS( Bin ) , width  = 0.1 )
plt.bar( Bin , Nomiert - GAUSS( Bin ) , width  = 0.1 , label= "Numerik - Theorie" )
plt.grid()
plt.legend(loc='best')
plt.savefig("Plots/Plot_2_a_diff.pdf")
plt.clf()


x = np.arange(-6 , 6 , 0.01)

Bin , Bincontent , Nomiert = np.genfromtxt( 'Ergebnisse/Ergebnis_2_b.txt' , unpack=True)
plt.xlabel(xLabel)
plt.ylabel(yLabel)
plt.bar( Bin , Nomiert , width  = 0.1 , label="Gebinnte Zufallszahlen")
plt.plot( x , GAUSS(x) , "-r" , label="Theorie")
plt.grid()
plt.legend(loc='best')
plt.savefig("Plots/Plot_2_b.pdf")
plt.clf()

plt.xlabel(xLabel)
plt.ylabel(yLabel)
plt.bar( Bin , Nomiert - GAUSS(Bin), width  = 0.1 , label= "Numerik - Theorie"  )
plt.grid()
plt.legend(loc='best')
plt.savefig("Plots/Plot_2_b_diff.pdf")
plt.clf()

x = np.arange( 0 , np.pi , 0.01)

Bin , Bincontent , Nomiert = np.genfromtxt( 'Ergebnisse/Ergebnis_2_c.txt' , unpack=True)
plt.xlabel(xLabel)
plt.ylabel(yLabel)
plt.bar( Bin , Nomiert , width  = np.pi/100 , label = "Gebinnte Zufallszahlen")
plt.plot( x , 0.5*np.sin(x) , "-r" , label = "Theorie")
plt.grid()
plt.legend(loc='best')
plt.savefig("Plots/Plot_2_c.pdf")
plt.clf()

plt.xlabel(xLabel)
plt.ylabel(yLabel)
plt.bar( Bin , Nomiert - 0.5*np.sin( Bin ), width  = np.pi/100 , label= "Numerik - Theorie"  )
plt.grid()
plt.legend(loc='best')
plt.savefig("Plots/Plot_2_c_diff.pdf")
plt.clf()


x = np.arange( 0 , 1 , 0.01)

Bin , Bincontent , Nomiert = np.genfromtxt( 'Ergebnisse/Ergebnis_2_d.txt' , unpack=True)
plt.xlabel(xLabel)
plt.ylabel(yLabel)
plt.bar( Bin , Nomiert , width  = 0.01 , label = "Gebinnte Zufallszahlen")
plt.plot( x , 3*x**2 , "-r" , label = "Theorie")
plt.grid()
plt.legend(loc='best')
plt.savefig("Plots/Plot_2_d.pdf")
plt.clf()

plt.xlabel(xLabel)
plt.ylabel(yLabel)
plt.bar( Bin , Nomiert - 3*Bin**2, width  = 0.01 , label= "Numerik - Theorie"  )
plt.grid()
plt.legend(loc='best')
plt.savefig("Plots/Plot_2_d_diff.pdf")
plt.clf()