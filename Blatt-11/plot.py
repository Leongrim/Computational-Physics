import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
from matplotlib import rc
rc('font',**{'family':'sans-serif','sans-serif':['Helvetica']})
rc('text', usetex=True)
'''
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
plt.close()

for i in [1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000]:
	Matrix = np.genfromtxt("Ergebnisse/Ergebnis_2_A_geordnet_t"+str(i)+"_kBT1.txt", unpack=True)
	plt.imshow(Matrix, interpolation='nearest', vmin=-1, vmax=1)
	plt.xlabel(r'$x$')
	plt.ylabel(r'$y$')
	plt.title(r'$t_\mathrm{MC}=$'+str(i))
	plt.savefig("Plots/2_A_Momentaufnahme_geordnet_t"+str(i)+"_kBT1.pdf")
	plt.close()

for i in [1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000]:
	Matrix = np.genfromtxt("Ergebnisse/Ergebnis_2_A_geordnet_t"+str(i)+"_kBT3.txt", unpack=True)
	plt.imshow(Matrix, interpolation='nearest', vmin=-1, vmax=1)
	plt.xlabel(r'$x$')
	plt.ylabel(r'$y$')
	plt.title(r'$t_\mathrm{MC}=$'+str(i))	
	plt.savefig("Plots/2_A_Momentaufnahme_geordnet_t"+str(i)+"_kBT3.pdf")
	plt.close()

Matrix = np.genfromtxt("Ergebnisse/Ergebnis_2_A_zufall_t0.txt", unpack=True)
plt.imshow(Matrix, interpolation='nearest', vmin=-1, vmax=1)
plt.xlabel(r'$x$')
plt.ylabel(r'$y$')
plt.title(r'$t_\mathrm{MC}=0$')	
plt.savefig("Plots/2_A_Momentaufnahme_zufall_t0.pdf")
plt.close()

for i in [1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000]:
	Matrix = np.genfromtxt("Ergebnisse/Ergebnis_2_A_zufall_t"+str(i)+"_kBT1.txt", unpack=True)
	plt.imshow(Matrix, interpolation='nearest', vmin=-1, vmax=1)
	plt.xlabel(r'$x$')
	plt.ylabel(r'$y$')
	plt.title(r'$t_\mathrm{MC}=$'+str(i))	
	plt.savefig("Plots/2_A_Momentaufnahme_zufall_t"+str(i)+"_kBT1.pdf")
	plt.close()

for i in [1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000]:
	Matrix = np.genfromtxt("Ergebnisse/Ergebnis_2_A_zufall_t"+str(i)+"_kBT3.txt", unpack=True)
	plt.imshow(Matrix, interpolation='nearest', vmin=-1, vmax=1)
	plt.xlabel(r'$x$')
	plt.ylabel(r'$y$')
	plt.title(r'$t_\mathrm{MC}=$'+str(i))	
	plt.savefig("Plots/2_A_Momentaufnahme_zufall_t"+str(i)+"_kBT3.pdf")
	plt.close()

A = ["geordnet_kBT1", "geordnet_kBT2.27", "geordnet_kBT3", "zufall_kBT1", "zufall_kBT2.27", "zufall_kBT3"]
for i in [0, 1, 2, 3, 4, 5]:
	t, e, m, absm = np.genfromtxt("Ergebnisse/Ergebnis_2_B_Energie_"+A[i]+".txt", unpack=True)
	plt.plot(t, e, 'r-')
	plt.grid()
	#ax.get_xaxis().get_major_formatter().set_useOffset(False)
	plt.xlabel(r'$t/\mathrm{Sweeps}$')
	plt.ylabel(r'$e(t)$')
	plt.savefig("Plots/2_B_Energie_"+A[i]+".pdf")
	plt.close()

	plt.plot(t, m, 'r-')
	plt.grid()
	plt.xlabel(r'$t/\mathrm{Sweeps}$')
	plt.ylabel(r'$\langle m\rangle(t)$')
	plt.savefig("Plots/2_B_Magnetisierung_"+A[i]+".pdf")
	plt.close()

	plt.plot(t, absm, 'r-')
	plt.grid()
	plt.xlabel(r'$t/\mathrm{Sweeps}$')
	plt.ylabel(r'$\langle|m|\rangle(t)$')
	plt.savefig("Plots/2_B_|Magnetisierung|_"+A[i]+".pdf")
	plt.close()

for i in [0]:
	t1, e1, m1, absm1 = np.genfromtxt("Ergebnisse/Ergebnis_2_B_Energie_"+A[i]+".txt", unpack=True)
	t2, e2, m2, absm2 = np.genfromtxt("Ergebnisse/Ergebnis_2_B_Energie_"+A[i+3]+".txt", unpack=True)
	plt.plot(t1, e1, 'r-', label='$\mathrm{geordnet}$')
	plt.plot(t2, e2, 'b-', label='$\mathrm{ungeordnet}$')
	plt.grid()
	plt.xlim(20000, 30000)
	plt.ylim(-4, -3.98)
	plt.xlabel(r'$t/\mathrm{Sweeps}$')
	plt.ylabel(r'$e(t)$')
	plt.legend(loc='best')
	plt.savefig("Plots/2_B_Energie_"+A[i]+A[i+3]+"_aequilibriert.pdf")
	plt.close()
'''
kbt1, m1, absm1 = np.genfromtxt("Ergebnisse/Ergebnis_2_C_Magnetisierung_grob.txt", unpack=True)
#plt.plot(kbt1, m1, 'r,', label='$\mathrm{geordnet}$')
kbt2, m2, absm2 = np.genfromtxt("Ergebnisse/Ergebnis_2_C_Magnetisierung_fein.txt", unpack=True)
plt.plot(kbt2, m2, 'r-', label='$\mathrm{geordnet}$')
kbt3, m3, absm3 = np.genfromtxt("Ergebnisse/Ergebnis_2_C_Magnetisierung.txt", unpack=True)
plt.plot(kbt3, m3, 'r-', label='$\mathrm{geordnet}$')
plt.grid()
plt.xlabel(r'$k_\mathrm{B}T$')
plt.ylabel(r'$\langle m\rangle(k_\mathrm{B}T)$')
#plt.legend(loc='best')
plt.savefig("Plots/2_C_Magnetisierung_grobfein_ganz.pdf")
plt.close()

#plt.plot(kbt1, absm1, 'r,', label='$\mathrm{geordnet}$')
plt.plot(kbt2, absm2, 'r-', label='$\mathrm{geordnet}$')
plt.plot(kbt3, absm3, 'r-', label='$\mathrm{geordnet}$')
plt.grid()
plt.xlabel(r'$k_\mathrm{B}T$')
plt.ylabel(r'$\langle|m|\rangle(k_\mathrm{B}T)$')
#plt.legend(loc='best')
plt.savefig("Plots/2_C_|Magnetisierung|_grobfein_ganz.pdf")
plt.close()

kbt1, c1 = np.genfromtxt("Ergebnisse/Ergebnis_2_D_Energiefluktuation_grob.txt", unpack=True)
kbt2, c2 = np.genfromtxt("Ergebnisse/Ergebnis_2_D_Energiefluktuation_fein.txt", unpack=True)
kbt3, c3 = np.genfromtxt("Ergebnisse/Ergebnis_2_D_Energiefluktuation.txt", unpack=True)
#plt.plot(kbt1, c1, 'r,', label='$\mathrm{geordnet}$')
plt.plot(kbt2, c2, 'r-', label='$\mathrm{geordnet}$')
plt.plot(kbt3, c3, 'r-', label='$\mathrm{geordnet}$')
plt.grid()
plt.xlabel(r'$k_\mathrm{B}T$')
plt.ylabel(r'$c(k_\mathrm{B}T)$')
#plt.legend(loc='best')
plt.savefig("Plots/2_D_Energiefluktuation_grobfein_ganz.pdf")
plt.close()
'''
t, e, m, absm = np.genfromtxt("Ergebnisse/Ergebnis_2_B_Energie_zufall_aequilibriert_kBT1.txt", unpack=True)
plt.plot(t, e, 'r-')
plt.grid()
plt.xlabel(r'$t/\mathrm{Sweeps}$')
plt.ylabel(r'$e(t)$')
plt.savefig("Plots/2_B_Energie_zufall_aequilibriert_kBT1.pdf")
plt.close()

plt.plot(t, m, 'r-')
plt.grid()
plt.xlabel(r'$t/\mathrm{Sweeps}$')
plt.ylabel(r'$\langle m\rangle(t)$')
plt.savefig("Plots/2_B_Magnetisierung_zufall_aequilibriert_kBT1.pdf")
plt.close()

plt.plot(t, absm, 'r-')
plt.grid()
plt.xlabel(r'$t/\mathrm{Sweeps}$')
plt.ylabel(r'$\langle|m|\rangle(t)$')
plt.savefig("Plots/2_B_|Magnetisierung|_zufall_aequilibriert_kBT1.pdf")
plt.close()'''