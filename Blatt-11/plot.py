import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
from matplotlib import rc
rc('font',**{'family':'sans-serif','sans-serif':['Helvetica']})
rc('text', usetex=True)

x, y = np.genfromtxt("Ergebnisse/Ergebnis_1_B.txt", unpack=True)
plt.plot(x, y, 'rx', label='$\mathrm{MC}$')
x_plot = np.linspace(-5, 5, 1000)
plt.plot(x_plot, np.tanh(x_plot), 'b-', label='$\mathrm{tanh}(H)$')
plt.xlim(-5, 5)
plt.ylim(-1.2, 1.2)
plt.grid()
plt.xlabel(r'$H$')
plt.ylabel(r'$m$')
plt.legend(loc='best')
plt.savefig("Plots/1_B_Magnetisierung.pdf")
plt.close()

Matrix = np.genfromtxt("Ergebnisse/Ergebnis_2_A_geordnet_t0.txt", unpack=True)
plt.imshow(Matrix, interpolation='nearest', vmin=-1, vmax=1)
plt.xlabel(r'$x$')
plt.ylabel(r'$y$')
plt.title(r'$t_\mathrm{MC}=0$')	
plt.savefig("Plots/2_A_Momentaufnahme_geordnet_t0.pdf")

for i in [10, 100, 1000, 10000, 100000, 1000000, 10000000]:
	Matrix = np.genfromtxt("Ergebnisse/Ergebnis_2_A_geordnet_t"+str(i)+"_kBT1.txt", unpack=True)
	plt.imshow(Matrix, interpolation='nearest', vmin=-1, vmax=1)
	plt.xlabel(r'$x$')
	plt.ylabel(r'$y$')
	plt.title(r'$t_\mathrm{MC}=$'+str(i))	
	plt.savefig("Plots/2_A_Momentaufnahme_geordnet_t"+str(i)+"_kBT1.pdf")

for i in [10, 100, 1000, 10000, 100000, 1000000, 10000000]:
	Matrix = np.genfromtxt("Ergebnisse/Ergebnis_2_A_geordnet_t"+str(i)+"_kBT3.txt", unpack=True)
	plt.imshow(Matrix, interpolation='nearest', vmin=-1, vmax=1)
	plt.xlabel(r'$x$')
	plt.ylabel(r'$y$')
	plt.title(r'$t_\mathrm{MC}=$'+str(i))	
	plt.savefig("Plots/2_A_Momentaufnahme_geordnet_t"+str(i)+"_kBT3.pdf")

Matrix = np.genfromtxt("Ergebnisse/Ergebnis_2_A_zufall_t0.txt", unpack=True)
plt.imshow(Matrix, interpolation='nearest', vmin=-1, vmax=1)
plt.xlabel(r'$x$')
plt.ylabel(r'$y$')
plt.title(r'$t_\mathrm{MC}=0$')	
plt.savefig("Plots/2_A_Momentaufnahme_zufall_t0.pdf")

for i in [10, 100, 1000, 10000, 100000, 1000000, 10000000]:
	Matrix = np.genfromtxt("Ergebnisse/Ergebnis_2_A_zufall_t"+str(i)+"_kBT1.txt", unpack=True)
	plt.imshow(Matrix, interpolation='nearest', vmin=-1, vmax=1)
	plt.xlabel(r'$x$')
	plt.ylabel(r'$y$')
	plt.title(r'$t_\mathrm{MC}=$'+str(i))	
	plt.savefig("Plots/2_A_Momentaufnahme_zufall_t"+str(i)+"_kBT1.pdf")

for i in [10, 100, 1000, 10000, 100000, 1000000, 10000000]:
	Matrix = np.genfromtxt("Ergebnisse/Ergebnis_2_A_zufall_t"+str(i)+"_kBT3.txt", unpack=True)
	plt.imshow(Matrix, interpolation='nearest', vmin=-1, vmax=1)
	plt.xlabel(r'$x$')
	plt.ylabel(r'$y$')
	plt.title(r'$t_\mathrm{MC}=$'+str(i))	
	plt.savefig("Plots/2_A_Momentaufnahme_zufall_t"+str(i)+"_kBT3.pdf")