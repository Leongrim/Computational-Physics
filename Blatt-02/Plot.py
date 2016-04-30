import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

def function(x):
	return 8/x

def functionC(x):
	return 8/(3*x*x) 
def functionFit(x , A , B):
	return A/(x*x) + B /x

xplot = np.arange(0 , 1 , 0.1)
#plt.xlim( 15 , 20)
plt.ylim( 0 , 10)
x ,y , z= np.genfromtxt( 'Ergebnisse/Ergebnis.txt' , unpack=True)
plt.grid()
plt.xlabel(r'$x/a$')
plt.ylabel(r'$\phi(x/a)/_\frac{a^2\varrho_0}{4\pi\epsilon_0}$')
plt.plot( x , y , 'rx' , label = r'$\varrho_A/\varrho_0$')
plt.plot( x , function(x) , 'g-' , label = r'$f(x/a)=\frac{8a}{x}$')



#plt.savefig('Plots/Plot_A_B.pdf')
#plt.clf()
#plt.xlabel(r'$x/a$')
#plt.ylabel(r'$\Phi(x)/_\frac{a^2\varrho_0}{4\pi\epsilon_0}$')
plt.plot( x , z , 'b+' , label = r'$\varrho_C/\varrho_0$')
plt.fill_between( xplot , 0, 10  , facecolor='green', alpha=0.5, )
plt.plot( x , functionC(x) , 'k-' , label = r'$f(x/a)=\frac{8a^2}{3x^2}$')
plt.legend(loc='best')
plt.savefig('Plots/Plot.pdf')
plt.clf()