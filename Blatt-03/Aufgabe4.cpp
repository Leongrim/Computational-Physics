#include <iostream>
#include "fstream"
#include <cmath>
#include <vector>
#include "Aufgabe1.h"

double* Kepler( double* Ort){ //Kraftfeld, um Planetenbahnen zu bestimmen
	double *Pointer = new double [3];
	double Norm = sqrt( Ort[0]*Ort[0] + Ort[1]*Ort[1] + Ort[2]*Ort[2]);
	for (int i = 0; i < 3  ; ++i)
	{
		Pointer[i] = -Ort[i]/(Norm*Norm*Norm);
	}
	return Pointer;
}
double* alpha09( double* Ort){ // Kraftfeld zum 1/r^0.9 Potential
	double *Pointer = new double [3];
	double Norm = sqrt( Ort[0]*Ort[0] + Ort[1]*Ort[1] + Ort[2]*Ort[2]);
	for (int i = 0; i < 3  ; ++i)
	{
		Pointer[i] = -Ort[i]/pow(Norm , 0.9);
	}
	return Pointer;
}
double* alpha11( double* Ort){ //Kraftfeld zum 1/r^1.1 Potential
	double *Pointer = new double [3];
	double Norm = sqrt( Ort[0]*Ort[0] + Ort[1]*Ort[1] + Ort[2]*Ort[2]);
	for (int i = 0; i < 3  ; ++i)
	{
		Pointer[i] = -Ort[i]/pow(Norm , 1.1);
	}
	return Pointer;
}

int main(){

	std::fstream Datei;

	////////////////////////////////// Aufgabenteil a)

	double *Start_Ort = new double [3];
	double *Start_Geschwindigkeit = new double [3];

	Start_Ort[0] = 1.0;
	Start_Ort[1] = 0.0;
	Start_Ort[2] = 0.0;

	Start_Geschwindigkeit[0] = -0.5;
	Start_Geschwindigkeit[1] = 1.0;
	Start_Geschwindigkeit[2] = 0.0;

	Datei.open( "Ergebnisse/Ergebnis_4_A.txt" , std::ios::trunc | std::ios::out);
	Runge_Kutta( 10 , Start_Ort , Start_Geschwindigkeit , Kepler , Datei , 0.01);
	Datei.close();

	Start_Ort[0] = 1.0;
	Start_Ort[1] = 0.0;
	Start_Ort[2] = 0.0;

	Start_Geschwindigkeit[0] = -0.1;
	Start_Geschwindigkeit[1] = 1.0;
	Start_Geschwindigkeit[2] = 0.0;
	Datei.open( "Ergebnisse/Ergebnis_4_A_2.txt" , std::ios::trunc | std::ios::out );
	Runge_Kutta( 10 , Start_Ort , Start_Geschwindigkeit , Kepler , Datei , 0.01);
	Datei.close();

	Start_Ort[0] = 1.0;
	Start_Ort[1] = 0.0;
	Start_Ort[2] = 0.0;

	Start_Geschwindigkeit[0] = -0.5;
	Start_Geschwindigkeit[1] = 1.0;
	Start_Geschwindigkeit[2] = 0.0;
	Datei.open( "Ergebnisse/Ergebnis_4_A_3.txt" , std::ios::trunc | std::ios::out);
	Runge_Kutta( 10 , Start_Ort , Start_Geschwindigkeit , Kepler , Datei , 0.5);
	Datei.close();

	Datei.open( "Ergebnisse/Ergebnis_4_A_4.txt" , std::ios::trunc | std::ios::out);
	Runge_Kutta( 10 , Start_Ort , Start_Geschwindigkeit , Kepler , Datei , 0.7);
	Datei.close();


	Start_Geschwindigkeit[0] = 0.01;
	Start_Geschwindigkeit[1] = 0.01;
	Start_Geschwindigkeit[2] = 0.0;
	Datei.open( "Ergebnisse/Ergebnis_4_A_5.txt" , std::ios::trunc | std::ios::out);
	Runge_Kutta( 10 , Start_Ort , Start_Geschwindigkeit , Kepler , Datei , 0.7);
	Datei.close();


	///////////// Aufgabenteil d): Stabilitätstest. Die Stabilität wird getestet, indem der Wert nach einer gewissen Zeit als neuer Startwert mit umgedrehter Geschwindigkeit verwendet wird. Somit läuft das Teilchen die Bahn zurück und sollte nach der gleichen Zeit wieder am Anfangspunkt mit umgedrehter Ausgangsgeschwindigkeit ankommen.

	double *Start_Ort2 = new double [3];
	double *Start_Geschwindigkeit2 = new double [3];

	Start_Ort[0] = 1.0;
	Start_Ort[1] = 0.0;
	Start_Ort[2] = 0.0;

	Start_Geschwindigkeit[0] = -0.5;
	Start_Geschwindigkeit[1] = 1.0;
	Start_Geschwindigkeit[2] = 0.0;

	std::cout << "######## Start Position" << std::endl;
 	std::cout << "RX-Komponente: " << Start_Ort[0] << std::endl;
 	std::cout << "RY-Komponente: " << Start_Ort[1] << std::endl;
 	std::cout << "RZ-Komponente: " << Start_Ort[2] << std::endl;
 	std::cout << "VX-Komponente: " << Start_Geschwindigkeit[0] << std::endl;
 	std::cout << "VY-Komponente: " << Start_Geschwindigkeit[1] << std::endl;
 	std::cout << "VZ-Komponente: " << Start_Geschwindigkeit[2] << std::endl;

	std::cout << "######## Endposition und Endgeschwindigkeit nach T=10" << std::endl;
 	std::cout << "RX-Komponente: " << Runge_Kutta( 10 , Start_Ort , Start_Geschwindigkeit , Kepler , 0.01)[0] << std::endl;
 	std::cout << "RY-Komponente: " << Runge_Kutta( 10 , Start_Ort , Start_Geschwindigkeit , Kepler , 0.01)[1] << std::endl;
 	std::cout << "RZ-Komponente: " << Runge_Kutta( 10 , Start_Ort , Start_Geschwindigkeit , Kepler , 0.01)[2] << std::endl;
 	std::cout << "VX-Komponente: " << Runge_Kutta( 10 , Start_Ort , Start_Geschwindigkeit , Kepler , 0.01)[3] << std::endl;
 	std::cout << "VY-Komponente: " << Runge_Kutta( 10 , Start_Ort , Start_Geschwindigkeit , Kepler , 0.01)[4] << std::endl;
 	std::cout << "VZ-Komponente: " << Runge_Kutta( 10 , Start_Ort , Start_Geschwindigkeit , Kepler , 0.01)[5] << std::endl;

	Start_Ort2[0] = Runge_Kutta( 10 , Start_Ort , Start_Geschwindigkeit , Kepler , 0.01)[0];
	Start_Ort2[1] = Runge_Kutta( 10 , Start_Ort , Start_Geschwindigkeit , Kepler , 0.01)[1];
	Start_Ort2[2] = Runge_Kutta( 10 , Start_Ort , Start_Geschwindigkeit , Kepler , 0.01)[2];
	Start_Geschwindigkeit2[0] = -Runge_Kutta( 10 , Start_Ort , Start_Geschwindigkeit , Kepler , 0.01)[3];
	Start_Geschwindigkeit2[1] = -Runge_Kutta( 10 , Start_Ort , Start_Geschwindigkeit , Kepler , 0.01)[4];
	Start_Geschwindigkeit2[2] = -Runge_Kutta( 10 , Start_Ort , Start_Geschwindigkeit , Kepler , 0.01)[5];


	std::cout << "######## Rückweg Endposition und Endgeschwindigkeit nach T=10" << std::endl;
 	std::cout << "RX-Komponente: " << Runge_Kutta( 10 , Start_Ort2 , Start_Geschwindigkeit2 , Kepler , 0.01)[0] << std::endl;
 	std::cout << "RY-Komponente: " << Runge_Kutta( 10 , Start_Ort2 , Start_Geschwindigkeit2 , Kepler , 0.01)[1] << std::endl;
 	std::cout << "RZ-Komponente: " << Runge_Kutta( 10 , Start_Ort2 , Start_Geschwindigkeit2 , Kepler , 0.01)[2] << std::endl;
 	std::cout << "VX-Komponente: " << Runge_Kutta( 10 , Start_Ort2 , Start_Geschwindigkeit2 , Kepler , 0.01)[3] << std::endl;
 	std::cout << "VY-Komponente: " << Runge_Kutta( 10 , Start_Ort2 , Start_Geschwindigkeit2 , Kepler , 0.01)[4] << std::endl;
 	std::cout << "VZ-Komponente: " << Runge_Kutta( 10 , Start_Ort2 , Start_Geschwindigkeit2 , Kepler , 0.01)[5] << std::endl;



	//////////////////// Aufgabenteil e)
	Datei.open( "Ergebnisse/Ergebnis_4_E_1.txt" , std::ios::trunc | std::ios::out );
	Runge_Kutta( 20 , Start_Ort , Start_Geschwindigkeit , alpha09 , Datei , 0.01);
	Datei.close();

	Datei.open( "Ergebnisse/Ergebnis_4_E_2.txt" , std::ios::trunc | std::ios::out );
	Runge_Kutta( 20 , Start_Ort , Start_Geschwindigkeit , alpha11 , Datei , 0.01);
	Datei.close();

	Datei.open( "Ergebnisse/Ergebnis_4_E_Lenzrunge_1.txt" , std::ios::trunc | std::ios::out);
	double Bahn[1000][6];
	double X_Komponente;
	double Y_Komponente;
	double Z_Komponente;
	double Norm;
	double produkt1;
	double produkt2;
	double LenzRunge = 0.0;
	double LenzRunge_1 = 0.0;
	double Breite = 0.1;

	for (int  k = 0; k < (int) 1000; ++k) //Schleife, um die Bahn eines Teilchens in eine Matrix zu schreiben
	{
		for (int j = 0; j < 6; ++j)
		{
			Bahn[k][j] = Runge_Kutta( (k)*Breite , Start_Ort , Start_Geschwindigkeit , alpha09 , Breite)[j];
		}
	}


	for (int i = 0; i < 100; ++i) //Aufgabenteil c): Schleife, mit der die Erhaltung des Lenz-Runge-Vektors gezeigt werden soll.
	{
		Norm = sqrt( Bahn[i][0]*Bahn[i][0] + Bahn[i][1]*Bahn[i][1] + Bahn[i][2]*Bahn[i][2] );
		produkt1 = Bahn[i][0]*Bahn[i][3] + Bahn[i][1]*Bahn[i][4] + Bahn[i][2]*Bahn[i][5];
		produkt2 = Bahn[i][3]*Bahn[i][3] + Bahn[i][4]*Bahn[i][4] + Bahn[i][5]*Bahn[i][5];
		X_Komponente = produkt2*Bahn[i][0] - produkt1 * Bahn[i][3]-Bahn[i][0]/Norm;
		Y_Komponente = produkt2*Bahn[i][1] - produkt1 * Bahn[i][4]-Bahn[i][1]/Norm;
		Z_Komponente = produkt2*Bahn[i][2] - produkt1 * Bahn[i][5]-Bahn[i][2]/Norm;
		LenzRunge = sqrt( X_Komponente*X_Komponente + Y_Komponente*Y_Komponente + Z_Komponente*Z_Komponente);
		if (i != 0)
		{
			Datei << i << '\t' << X_Komponente << '\t' << Y_Komponente << '\t' << Z_Komponente << '\t' << LenzRunge << '\t' << std::abs(LenzRunge - LenzRunge_1) << std::endl;
		}
		LenzRunge_1 = LenzRunge;
	}
	Datei.close();

	Datei.open( "Ergebnisse/Ergebnis_4_E_Lenzrunge_2.txt" , std::ios::trunc | std::ios::out);
	for (int  k = 0; k < (int) 1000; ++k) //Schleife, um die Bahn eines Teilchens in eine Matrix zu schreiben
	{
		for (int j = 0; j < 6; ++j)
		{
			Bahn[k][j] = Runge_Kutta( (k)*Breite , Start_Ort , Start_Geschwindigkeit , alpha11 , Breite)[j];
		}
	}


	for (int i = 0; i < 100; ++i) //Aufgabenteil c): Schleife, mit der die Erhaltung des Lenz-Runge-Vektors gezeigt werden soll.
	{
		Norm = sqrt( Bahn[i][0]*Bahn[i][0] + Bahn[i][1]*Bahn[i][1] + Bahn[i][2]*Bahn[i][2] );
		produkt1 = Bahn[i][0]*Bahn[i][3] + Bahn[i][1]*Bahn[i][4] + Bahn[i][2]*Bahn[i][5];
		produkt2 = Bahn[i][3]*Bahn[i][3] + Bahn[i][4]*Bahn[i][4] + Bahn[i][5]*Bahn[i][5];
		X_Komponente = produkt2*Bahn[i][0] - produkt1 * Bahn[i][3]-Bahn[i][0]/Norm;
		Y_Komponente = produkt2*Bahn[i][1] - produkt1 * Bahn[i][4]-Bahn[i][1]/Norm;
		Z_Komponente = produkt2*Bahn[i][2] - produkt1 * Bahn[i][5]-Bahn[i][2]/Norm;
		LenzRunge = sqrt( X_Komponente*X_Komponente + Y_Komponente*Y_Komponente + Z_Komponente*Z_Komponente);
		if (i != 0)
		{
			Datei << i << '\t' << X_Komponente << '\t' << Y_Komponente << '\t' << Z_Komponente << '\t' << LenzRunge << '\t' << std::abs(LenzRunge - LenzRunge_1) << std::endl;
		}
		LenzRunge_1 = LenzRunge;
	}
	Datei.close();

	return 0;
}