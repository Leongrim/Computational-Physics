#!/usr/bin/env_python
# -*- coding: utf-8 -*-

import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

Bin , Bincontent , Nomiert  = np.genfromtxt( 'Ergebnisse/Ergebnis_1_A.txt' , unpack=True)
plt.bar( Bin , Nomiert , width  = np.pi/1000 )
plt.grid()
plt.xlabel(r"$\theta$")
plt.ylabel(r"$p(\theta)$")
plt.savefig("Plots/Plot_1_A.pdf")
plt.clf()

Bin , Bincontent , Nomiert  = np.genfromtxt( 'Ergebnisse/Ergebnis_1_B.txt' , unpack=True)
plt.bar( Bin , Nomiert , width  = 1.5/1000 )
plt.grid()
plt.xlabel(r"$\omega$")
plt.ylabel(r"$p(\omega)$")
plt.savefig("Plots/Plot_1_B.pdf")
plt.clf()

Anzahl , Fehler = np.genfromtxt( 'Ergebnisse/Ergebnis_2_A.txt' , unpack=True)
plt.plot( Anzahl , Fehler , "rx")
plt.grid()
plt.xscale('log')
plt.yscale('log')
plt.xlabel(r"Anzahl")
plt.ylabel(r"Fehler($\pi$)")
plt.savefig("Plots/Plot_2_A.pdf")
plt.clf()

Bin , Bincontent , Nomiert  = np.genfromtxt( 'Ergebnisse/Ergebnis_2_B.txt' , unpack=True)
#popt, pcov = curve_fit(GAUSSIAN, Bin, Bincontent)
#print popt
plt.grid()
plt.xlabel(r"$\pi$")
plt.ylabel(r"Anzahl")
plt.bar( Bin , Bincontent , width  = 0.3/25 )
#plt.plot( Bin , GAUSSIAN( Bin , popt[ 0 ] , popt[ 1 ]) , "r")
plt.savefig("Plots/Plot_2_B.pdf")
plt.clf()

a , b , flaeche ,Nomiert = np.genfromtxt( 'Ergebnisse/Ergebnis_2_C.txt' , unpack=True)
#popt, pcov = curve_fit(GAUSSIAN, Bin, Bincontent)
#print popt
plt.xlabel(r"$a$")
plt.ylabel(r"Flaecheninhalt/$b$")
plt.grid()
plt.plot( a , flaeche , "+" )
#plt.plot( Bin , GAUSSIAN( Bin , popt[ 0 ] , popt[ 1 ]) , "r")
plt.savefig("Plots/Plot_2_C.pdf")
plt.clf()