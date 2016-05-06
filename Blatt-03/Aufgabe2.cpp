#include <iostream>
#include "fstream"
#include <cmath>
#include <vector>
#include "Aufgabe1.h"

double* Harmo( double* Ort ){
	double *Pointer = new double [3];
	for (int i = 0; i < 3; ++i)
	{
		Pointer[i] = -Ort[i];
	}
	return Pointer;
}
int main()
{
	std::fstream Datei;
	Datei.open( "Ergebnisse/Ergebnis_2_A_1.txt" , std::ios::trunc | std::ios::out);

	double *Start_Ort = new double [3];
	double *Start_Geschwindigkeit = new double [3];

	Start_Ort[0] = 10.0;
	Start_Ort[1] = 0.0;
	Start_Ort[2] = 0.0;

	Start_Geschwindigkeit[0] = 0.0;
	Start_Geschwindigkeit[1] = 0.0;
	Start_Geschwindigkeit[2] = 0.0;


	Runge_Kutta( 100 , Start_Ort , Start_Geschwindigkeit , Harmo , Datei , 0.1 );

	Datei.close();
	Datei.open( "Ergebnisse/Ergebnis_2_A_2.txt" , std::ios::trunc | std::ios::out);

	Start_Ort[0] = 10.0 ;
	Start_Ort[1] = 0.0 ;
	Start_Ort[2] = 0.0;

	Start_Geschwindigkeit[0] =   0.0;
	Start_Geschwindigkeit[1] =  10.0;
	Start_Geschwindigkeit[2] = 0.0;
	Runge_Kutta( 10 , Start_Ort , Start_Geschwindigkeit , Harmo , Datei , 0.1 );
	Datei.close();


	Datei.open( "Ergebnisse/Ergebnis_2_B_Energie.txt" , std::ios::trunc | std::ios::out);
	double* Ort = new double[3];
	double* Geschwindigkeit = new double[3];
	double Energie_1 = 0.0;
	double Energie = 0.0;
	for (int i = 1; i < 100; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			Ort[j] = Runge_Kutta( (double) i , Start_Ort , Start_Geschwindigkeit , Harmo , 0.01)[j];
			Geschwindigkeit[j] = Runge_Kutta( (double) i , Start_Ort , Start_Geschwindigkeit , Harmo , 0.01)[j+3];
			Energie += 1.0/2.0* ( Ort[j] * Ort[j] + Geschwindigkeit[j] * Geschwindigkeit[j] );
		}
		if( i != 1){
			Datei << i*0.1 << '\t' << std::abs(Energie_1 - Energie) << std::endl;
		}
		Energie_1 = Energie;
		Energie = 0;
	}
	Datei.close();


	Datei.open( "Ergebnisse/Ergebnis_2_B_Stabilitaet.txt" , std::ios::trunc | std::ios::out);

	Start_Ort[0] = 1.0 ;
	Start_Ort[1] = 0.0 ;
	Start_Ort[2] = 0.0;

	Start_Geschwindigkeit[0] = 0.0;
	Start_Geschwindigkeit[1] = 0.0;
	Start_Geschwindigkeit[2] = 0.0;

	double Wert_1;
	double Wert_Zeit;
	double Temp = 0;
	double Schrittweite = 100.0;

	for (double Breite = 1; Breite < Schrittweite; ++Breite)
	{
		Temp = 0.0;
		for (double Zeit = 1; Zeit < 100 ; ++Zeit)
		{
			Wert_1 = Runge_Kutta(  (double) Zeit , Start_Ort , Start_Geschwindigkeit , Harmo , (double) Breite/Schrittweite )[0];
			if (Wert_1 >= Temp)
			{
				Temp = Wert_1;
				Wert_Zeit = Zeit;
			}
		}
		Datei << Breite/Schrittweite << '\t' << Temp << '\t' << Wert_Zeit << std::endl;
	}
	Datei.close();
	delete[] Start_Geschwindigkeit;
	delete[] Start_Ort;
	delete[] Ort;
	delete[] Geschwindigkeit;
	
	return 0;
}