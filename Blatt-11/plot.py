import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

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