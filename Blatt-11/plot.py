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
plt.savefig("Magnetisierung.pdf")
plt.close()

for i in [0, 10, 100, 1000, 10000, 11000, 12000, 15000, 20000, 50000, 100000, 1000000, 10000000]:
	Matrix = np.genfromtxt("Ergebnisse/Ergebnis_2_A_geordnet_"+str(i)+".txt", unpack=True)
	plt.imshow(Matrix, interpolation='nearest', vmin=-1, vmax=1)
	plt.xlabel(r'$x$')
	plt.ylabel(r'$y$')
	plt.title(r'$t_\mathrm{MC}=$'+str(i))	
	plt.savefig("Plots/Momentaufnahme_geordnet_"+str(i)+".pdf")

for i in [0, 10, 100, 1000, 10000, 11000, 12000, 15000, 20000, 50000, 100000, 1000000, 10000000]:
	Matrix = np.genfromtxt("Ergebnisse/Ergebnis_2_A_zufall_"+str(i)+".txt", unpack=True)
	plt.imshow(Matrix, interpolation='nearest', vmin=-1, vmax=1)
	plt.xlabel(r'$x$')
	plt.ylabel(r'$y$')
	plt.title(r'$t_\mathrm{MC}=$'+str(i))	
	plt.savefig("Plots/Momentaufnahme_zufall_"+str(i)+".pdf")