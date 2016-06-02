import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from scipy.optimize import curve_fit

def function( x , y ):
	phi = 0.0
	i =0.0
	for j in xrange(0,100):
		phi += 4.0/((2.0*i+1.0)*np.pi)/np.sinh((2.0*i+1.0)*np.pi)*np.sinh((2*i+1)*np.pi*y)*np.sin((2*i+1)*np.pi*x)
		i += 1.0
	return phi


Ort_x , Ort_y , phi   = np.genfromtxt( 'Ergebnisse/Ergebnis_A.txt' , unpack=True)
fig = plt.figure()
plt.xlabel(r"$x$")
plt.ylabel(r"$y$")
ax = fig.add_subplot(111 , projection = '3d' )
ax.set_xlabel(r"$x$")
ax.set_ylabel(r"$y$")
ax.set_zlabel(r"$\phi$")
plt.plot( Ort_x , Ort_y , phi , 'xb')
plt.savefig("Plots/Plots_A.pdf")
plt.clf()


Ort_x , Ort_y , phi   = np.genfromtxt( 'Ergebnisse/Ergebnis_B.txt' , unpack=True)
plt.xlabel(r"$x$")
plt.ylabel(r"$y$")
ax = fig.add_subplot(111 , projection = '3d' )
ax.set_xlabel(r"$x$")
ax.set_ylabel(r"$y$")
ax.set_zlabel(r"$\phi$")
plt.plot( Ort_x , Ort_y , phi , 'xb')
plt.savefig("Plots/Plots_B.pdf")
plt.clf()

Ort_x , Ort_y , phi   = np.genfromtxt( 'Ergebnisse/Ergebnis_C.txt' , unpack=True)
plt.xlabel(r"$x$")
plt.ylabel(r"$y$")
ax = fig.add_subplot(111 , projection = '3d' )
ax.set_xlabel(r"$x$")
ax.set_ylabel(r"$y$")
ax.set_zlabel(r"$\phi$")
plt.plot( Ort_x , Ort_y , phi , 'xb')
#plt.show()
plt.savefig("Plots/Plots_C.pdf")
plt.clf()

Ort_x , Ort_y , phi   = np.genfromtxt( 'Ergebnisse/Ergebnis_E.txt' , unpack=True)
plt.xlabel(r"$x$")
plt.ylabel(r"$y$")
ax = fig.add_subplot(111 , projection = '3d' )
ax.set_xlabel(r"$x$")
ax.set_ylabel(r"$y$")
ax.set_zlabel(r"$\phi$")
plt.plot( Ort_x , Ort_y , phi , 'xb')
plt.savefig("Plots/Plots_E.pdf")
plt.clf()



Ort_x , Ort_y , E_X , E_Y , E_Betrag   = np.genfromtxt( 'Ergebnisse/Ergebnis_A_E_Feld.txt' , unpack=True)
plt.xlabel(r"$x$")
plt.ylabel(r"$y$")
ax = fig.add_subplot(111 , projection = '3d' )
plt.plot( Ort_x , Ort_y , E_Betrag , 'xb')
ax.set_xlabel(r"$x$")
ax.set_ylabel(r"$y$")
ax.set_zlabel(r"$|\vec{E}|$")
plt.savefig("Plots/Plots_A_E_Feld.pdf")
plt.clf()



Ort_x , Ort_y , E_X , E_Y , E_Betrag   = np.genfromtxt( 'Ergebnisse/Ergebnis_B_E_Feld.txt' , unpack=True)
plt.xlabel(r"$x$")
plt.ylabel(r"$y$")
ax = fig.add_subplot(111 , projection = '3d' )
plt.plot( Ort_x , Ort_y , E_Betrag , 'xb')
ax.set_xlabel(r"$x$")
ax.set_ylabel(r"$y$")
ax.set_zlabel(r"$|\vec{E}|$")
plt.savefig("Plots/Plots_B_E_Feld.pdf")
plt.clf()
Ort_x , Ort_y , phi   = np.genfromtxt( 'Ergebnisse/Ergebnis_B.txt' , unpack=True)

ax = fig.add_subplot(111 , projection = '3d' )
x = np.arange( 0 , 1.05 , 0.05)
y = np.arange( 0 , 1.05 , 0.05)
for i in xrange(0,21):
	iy = np.ones(21)*i*0.05
	ix = np.ones(21)*i*0.05
	plt.plot( x , iy , function( x , iy ) , "-b")
	plt.plot( ix , y , function( ix , y ) , "-b")
	pass
plt.plot( Ort_x , Ort_y , phi , 'xr')
ax.set_xlabel(r"$x$")
ax.set_ylabel(r"$y$")
ax.set_zlabel(r"$\phi_{theo}$")
plt.savefig("Plots/Plots_B_Numerik_theo.pdf")
#plt.show()
plt.clf()

ax = fig.add_subplot(111 , projection = '3d' )
x = np.arange( 0 , 1.05 , 0.05)
y = np.arange( 0 , 1.05 , 0.05)
for i in xrange(0,21):
	iy = np.ones(21)*i*0.05
	ix = np.ones(21)*i*0.05
	plt.plot( x , iy , function( x , iy ) , "-b")
	plt.plot( ix , y , function( ix , y ) , "-b")
	pass
ax.set_xlabel(r"$x$")
ax.set_ylabel(r"$y$")
ax.set_zlabel(r"$\phi_{theo}$")
plt.savefig("Plots/Plots_B_theo.pdf")
#plt.show()
plt.clf()


Ort_x , Ort_y , E_X , E_Y , E_Betrag   = np.genfromtxt( 'Ergebnisse/Ergebnis_C_E_Feld.txt' , unpack=True)
fig = plt.figure()
ax = fig.add_subplot(111 , projection = '3d' )
plt.plot( Ort_x , Ort_y , E_Betrag , 'xb')
ax.set_xlabel(r"$x$")
ax.set_ylabel(r"$y$")
ax.set_zlabel(r"$|\vec{E}|$")
plt.savefig("Plots/Plots_C_E_Feld.pdf")
plt.clf()


Ort_x , Ort_y , E_X , E_Y , E_Betrag   = np.genfromtxt( 'Ergebnisse/Ergebnis_E_E_Feld.txt' , unpack=True)
ax = fig.add_subplot(111 , projection = '3d' )
plt.plot( Ort_x , Ort_y , E_Betrag , 'xb')
ax.set_xlabel(r"$x$")
ax.set_ylabel(r"$y$")
ax.set_zlabel(r"$|\vec{E}|$")
plt.savefig("Plots/Plots_E_E_Feld.pdf")
plt.clf()