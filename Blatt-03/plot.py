import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from scipy.optimize import curve_fit
from matplotlib import rc
rc('font',**{'family':'sans-serif','sans-serif':['Helvetica']})
rc('text', usetex=True)

################################### Aufgabe 2 Plots
Zeit , Ort_x , Ort_y , Ort_z , V_x ,V_y , V_z = np.genfromtxt( 'Ergebnisse/Ergebnis_2_A_1.txt' , unpack=True)

plt.plot( Zeit , Ort_x ,'r-')
plt.grid()
plt.xlabel(r'$t/$s')
plt.ylabel(r'$x/$m')
plt.savefig("Plots/Plot_2_A_1.pdf")
plt.clf()

Zeit , Ort_x , Ort_y , Ort_z , V_x ,V_y , V_z  = np.genfromtxt( 'Ergebnisse/Ergebnis_2_A_2.txt' , unpack=True)

plt.plot( Ort_x , Ort_y  ,'r-')
plt.grid()
plt.xlabel(r'$x/$m')
plt.ylabel(r'$y/$m')
plt.savefig("Plots/Plot_2_A_2.pdf")
plt.clf()

plt.plot( Zeit , Ort_x  ,'r-')
plt.grid()
plt.xlabel(r'$t/$s')
plt.ylabel(r'$x/$m')
plt.savefig("Plots/Plot_2_A_3.pdf")
plt.clf()

Zeit , Energie = np.genfromtxt( 'Ergebnisse/Ergebnis_2_B_Energie.txt' , unpack=True)
plt.plot( Zeit , Energie)
plt.ylim(1.38e-10 , 1.4e-10)
plt.ylabel(r'$\Delta E$')
plt.xlabel(r'Zeit')
plt.grid()
plt.savefig("Plots/Plot_2_B_Energie.pdf")
plt.clf()

Breite , Amp , Zeit = np.genfromtxt( 'Ergebnisse/Ergebnis_2_B_Stabilitaet.txt' , unpack=True)
plt.errorbar( Breite , Amp ,  fmt='rx')
plt.xlabel(r'Schrittweite $h$')
plt.ylabel(r'Zuletzt erreichte Amplitude')
plt.grid()
plt.savefig("Plots/Plot_2_B_Stabilitaet.pdf")
plt.clf()

Breite , Amp , Zeit = np.genfromtxt( 'Ergebnisse/Ergebnis_2_B_Stabilitaet.txt' , unpack=True)
plt.errorbar( Breite , Amp ,  fmt='rx')
plt.ylim(0.98 , 1.01 )
plt.xlim(0 , 0.4)
plt.xlabel(r'Schrittweite $h$')
plt.ylabel(r'Zuletzt erreichte Amplitude')
plt.grid()
plt.savefig("Plots/Plot_2_B_Stabilitaet_Nah.pdf")
plt.clf()

Breite , Amp , Zeit = np.genfromtxt( 'Ergebnisse/Ergebnis_2_B_Stabilitaet.txt' , unpack=True)
plt.plot( Breite , Zeit , 'rx')
plt.xlabel(r'Zeit $t$')
plt.ylabel(r'Zuletzt erreichte Amplitude')
#plt.legend(loc='best')
plt.grid()
plt.savefig("Plots/Plot_2_B_Stabilitaet_Zeit.pdf")
plt.clf()

############################## Aufgabe 4 Plots

Zeit , Ort_x , Ort_y , Ort_z , V_x ,V_y , V_z = np.genfromtxt( 'Ergebnisse/Ergebnis_4_A.txt' , unpack=True)
plt.grid()
plt.xlabel(r'$x/$m')
plt.ylabel(r'$y/$m')
plt.plot( Ort_x , Ort_y  ,'r-')
plt.arrow( 0 , 0 , -2.79011e-05	, 0.500005 )
Zeit , Ort_x , Ort_y , Ort_z , V_x ,V_y , V_z = np.genfromtxt( 'Ergebnisse/Ergebnis_4_A_2.txt' , unpack=True)
plt.plot( Ort_x , Ort_y  ,'b-')
plt.gcf().set_size_inches(5 ,5 )
plt.savefig( "Plots/Plot_4_A_1.pdf")
plt.close()

plt.grid()
plt.xlabel(r'Zeit $t$')
plt.ylabel(r'$\Delta\Lambda\cdot10^6$')
Zeit_Lenz , Lenz_X , Lenz_Y , Lenz_Z , LenzRunge ,DiffLenzRunge = np.genfromtxt( 'Ergebnisse/Ergebnis_4_LR.txt' , unpack=True)
plt.plot( Zeit_Lenz , np.abs(DiffLenzRunge*1e6) , 'xr')
plt.savefig("Plots/Plots_4_LR.pdf")
plt.close()

Zeit , Ort_x , Ort_y , Ort_z , V_x ,V_y , V_z = np.genfromtxt( 'Ergebnisse/Ergebnis_4_A_3.txt' , unpack=True)
plt.grid()
plt.xlabel(r'$x/$m')
plt.ylabel(r'$y/$m')
plt.plot( Ort_x , Ort_y  ,'r-')
plt.gcf().set_size_inches(5 ,5 )
plt.savefig( "Plots/Plot_4_A_3.pdf")
plt.close()

Zeit , Ort_x , Ort_y , Ort_z , V_x ,V_y , V_z = np.genfromtxt( 'Ergebnisse/Ergebnis_4_A_4.txt' , unpack=True)
plt.grid()
plt.xlabel(r'$x/$m')
plt.ylabel(r'$y/$m')
plt.plot( Ort_x , Ort_y  ,'r-')
plt.gcf().set_size_inches(5 ,5 )
plt.savefig( "Plots/Plot_4_A_4.pdf")
plt.close()

Zeit , Ort_x , Ort_y , Ort_z , V_x ,V_y , V_z = np.genfromtxt( 'Ergebnisse/Ergebnis_4_A_5.txt' , unpack=True)
plt.grid()
plt.xlabel(r'$x/$m')
plt.ylabel(r'$y/$m')
plt.plot( Ort_x , Ort_y  ,'r-')
plt.gcf().set_size_inches(5 ,5 )
plt.savefig( "Plots/Plot_4_A_5.pdf")
plt.close()

plt.grid()
Zeit_ , Energie_ , Dreh_ = np.genfromtxt( 'Ergebnisse/Ergebnis_4_Energie.txt' , unpack=True)
plt.plot( Zeit_ , np.abs(Energie_*1e6) , 'xr')
plt.xlabel(r'Zeit $t$')
plt.ylabel(r'$\Delta E\cdot10^{6}$')
#plt.ylim( -1e-6 , 2e-6)
plt.savefig( "Plots/Plot_4_Energie.pdf")
plt.close()

plt.grid()
plt.plot( Zeit_ , np.abs(Dreh_*1e6) , 'xr')
plt.xlabel(r'Zeit $t$')
plt.ylabel(r'$\Delta L\cdot10^{6}$')
#plt.ylim( -1e-6 , 2e-6)
plt.savefig( "Plots/Plot_4_Dreh.pdf")
plt.close()

Zeit , Ort_x , Ort_y , Ort_z , V_x ,V_y , V_z = np.genfromtxt( 'Ergebnisse/Ergebnis_4_E_1.txt' , unpack=True)
plt.grid()
plt.xlabel(r'$x/$m')
plt.ylabel(r'$y/$m')
plt.arrow( 0 , 0 , 0.000537157 , 0.492286)
plt.arrow( 0 , 0 , 0.40415 , 0.0811234)
plt.plot( Ort_x , Ort_y  ,'r-')
plt.gcf().set_size_inches(5 ,5 )
plt.savefig( "Plots/Plot_4_E_1.pdf")
plt.close()
Zeit , Ort_x , Ort_y , Ort_z , V_x ,V_y , V_z = np.genfromtxt( 'Ergebnisse/Ergebnis_4_E_2.txt' , unpack=True)
plt.grid()
plt.arrow( 0 , 0 , 0.000347801 , 0.495019)
plt.arrow( 0 , 0 , 0.289205 , 0.0204796)
plt.xlabel(r'$x/$m')
plt.ylabel(r'$y/$m')
plt.plot( Ort_x , Ort_y  ,'r-')
plt.gcf().set_size_inches(5 ,5 )
plt.savefig( "Plots/Plot_4_E_2.pdf")

plt.close()
plt.grid()
plt.xlabel(r'Zeit $t$')
plt.ylabel(r'$\Delta\Lambda$')
Zeit_Lenz , Lenz_X , Lenz_Y , Lenz_Z , LenzRunge ,DiffLenzRunge = np.genfromtxt( 'Ergebnisse/Ergebnis_4_E_Lenzrunge_1.txt' , unpack=True)
plt.plot( Zeit_Lenz , np.abs(DiffLenzRunge) , 'xr')
plt.savefig("Plots/Plots_5_E_Lenzrunge_1.pdf")
plt.close()

plt.close()
plt.grid()
plt.xlabel(r'Zeit $t$')
plt.ylabel(r'$\Delta\Lambda$')
Zeit_Lenz , Lenz_X , Lenz_Y , Lenz_Z , LenzRunge ,DiffLenzRunge = np.genfromtxt( 'Ergebnisse/Ergebnis_4_E_Lenzrunge_2.txt' , unpack=True)
plt.plot( Zeit_Lenz , np.abs(DiffLenzRunge) , 'xr')
plt.savefig("Plots/Plots_5_E_Lenzrunge_2.pdf")
plt.close()
"""
Zeit , Ort_x , Ort_y , Ort_z , V_x ,V_y , V_z = np.genfromtxt( 'Ergebnisse/Ergebnis_4_A.txt' , unpack=True)
plt.grid()
plt.plot( Ort_x , Ort_y  ,'r-')
#plt.scatter(Ort_x , Ort_y , edgecolors = "" , c=range( len( Ort_x )) )


plt.xlabel(r'$x$')
plt.ylabel(r'$y$')
plt.gcf().set_size_inches(5 ,5 )
Zeit , Ort_x , Ort_y , Ort_z , V_x ,V_y , V_z = np.genfromtxt( 'Ergebnisse/Ergebnis_4_A_2.txt' , unpack=True)

plt.plot( Ort_x , Ort_y , '-b')
plt.arrow( 0 , 0 , -2.79011e-05	, 0.500005 , head_width = 0.1 , head_length= 0.2)
plt.savefig("Plots/Plots_4_A.pdf")

Zeit , Ort_x , Ort_y , Ort_z , V_x ,V_y , V_z = np.genfromtxt( 'Ergebnisse/Ergebnis_4_A.txt' , unpack=True)
fig = plt.figure()
ax = fig.add_subplot(111 , projection = '3d')
plt.plot( Ort_x , Ort_y , Zeit , '-b')
plt.show()
plt.savefig("Plots/Plots_4_A_Zeit.pdf")
plt.close()
"""
Zeit , Ort_x , Ort_y , Ort_z  = np.genfromtxt( 'Ergebnisse/Ergebnis_4_BAHN.txt' , unpack=True)
fig = plt.figure()
ax = fig.add_subplot(111 , projection = '3d')
plt.plot( Ort_x , Ort_y , Zeit , '-b')
#plt.show()
plt.savefig("Plots/Plots_4_A_Zeit.pdf")
plt.clf()
