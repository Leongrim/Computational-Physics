import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
def Blubb( x ):
	return 0.03*x+1

def Logistik( x , r):
	return Blubb( r ) * x * ( 1 - x)
x = np.arange(0 , 1 , 0.01)
Save = "Ergebnisse/Aufgabe1a/Ergebnis"
def Kubisch( x , r):
	return Blubb( r ) * x - x**3
	pass
"""
for i in xrange(1,100):
	plt.xlabel(r"$x_n$")
	plt.ylabel(r"$X_{n+1}$")
 	xn , xnplus1 = np.genfromtxt( Save + str(i) + ".txt" , unpack=True)
 	plt.plot( x , Logistik( x , i) , "-r" , label=r"$r=$"+str( Blubb( i ) ) )
	plt.plot( xn , xnplus1 , "-b")
	plt.plot( x , x , "-g")
	plt.legend(loc='best')
	plt.savefig("Plots/Aufgabe1a/Plot_" + str(i) + ".png")
	plt.clf()
	pass

Save = "Ergebnisse/Aufgabe1b/Ergebnis"
for i in xrange(1,100):
	plt.xlabel(r"$x_n$")
	plt.ylabel(r"$X_{n+1}$")
	x = np.arange(-np.sqrt(1+Blubb( i )) , np.sqrt(1+Blubb( i )) , 0.01)
 	xn , xnplus1 = np.genfromtxt( Save + str(i) + ".txt" , unpack=True)
 	plt.plot( x , Kubisch( x , i) , "-r" , label=r"$r=$" + str( Blubb( i ) ) )
	plt.plot( xn , xnplus1 , "-b")
	plt.plot( x , x , "-g")
	plt.legend(loc='best')
	plt.savefig("Plots/Aufgabe1b/Plot_" + str(i) + ".png")
	plt.clf()
	pass
"""
r , n0 , n1 , n2 , n3  = np.genfromtxt( "Ergebnisse/Ergebnis_2_a.txt" , unpack=True)
	#double IntervallAnfang[4]{ 1.9 , 3.2 , 3.48 , 3.54 };
	#double IntervallEnde[4]{ 2.1 , 3.25 , 3.50 , 3.56 };



plt.plot( r, n0 , label='n=0' )
plt.plot( r, n1 , label='n=1' )
plt.plot( r, n2 , label='n=2' )
plt.plot( r, n3 , label='n=3' )
plt.axvline( 1.9 , ls = "--" , color ="b" )
plt.axvline( 2.1 , ls = "--" , color ="b" )
plt.axvline( 3.2 , ls = "--" , color ="g" )
plt.axvline( 3.25 , ls = "--" , color ="g")
plt.axvline( 3.48 , ls = "--" , color ="r" )
plt.axvline( 3.50 , ls = "--" , color ="r")
plt.axvline( 3.54 , ls = "--" , color ="c" )
plt.axvline( 3.56 , ls = "--" , color ="c")
plt.ylabel(r"$g_n(r)$")
plt.xlabel(r"$r$")
#plt.xlim( 0 , 4 )
plt.legend(loc='best')
#plt.show()
plt.grid()
plt.savefig("Plots/Plot_2_A.pdf")
plt.clf()
r , x  = np.genfromtxt( "Ergebnisse/Ergebnis_1_A.txt" , unpack=True)

plt.plot( r , x , "k." , markersize=1)
plt.xlabel(r"$r$")
plt.ylabel(r"$x$")
plt.grid()

plt.savefig("Plots/Plot_1_a.png")
plt.clf()

r , x  = np.genfromtxt( "Ergebnisse/Ergebnis_1_B.txt" , unpack=True)
plt.plot( r , x , "k.", markersize=1)
plt.xlabel(r"$r$")
plt.ylabel(r"$x$")
plt.grid()
plt.savefig("Plots/Plot_1_b.png")