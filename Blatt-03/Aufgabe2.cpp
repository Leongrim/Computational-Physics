#include <iostream>
#include "fstream"
#include <cmath>
#include <vector>
#include </home/leonard/FP_Repo2016/Computational-Physics/Blatt-03/Aufgabe1.h>

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
	Datei.open( "Ergebnisse/Ergebnis_2_A.txt" , std::ios::trunc | std::ios::out);

	double *Start_Ort = new double [3];
	double *Start_Geschwindigkeit = new double [3];

	Start_Ort[0] = 10.0;
	Start_Ort[1] = 10.0;
	Start_Ort[2] = 0.0;

	Start_Geschwindigkeit[0] = 0.0;
	Start_Geschwindigkeit[1] = 0.0;
	Start_Geschwindigkeit[2] = 0.0;


	Runge_Kutta( 10 , Start_Ort , Start_Geschwindigkeit , Harmo , Datei);

	Datei.close();
	Datei.open( "Ergebnisse/Ergebnis_2_B.txt" , std::ios::trunc | std::ios::out);

	Start_Ort[0] = 10.0 ;
	Start_Ort[1] = 0.0 ;
	Start_Ort[2] = 0.0;

	Start_Geschwindigkeit[0] =   0.0;
	Start_Geschwindigkeit[1] =  10.0;
	Start_Geschwindigkeit[0] = 0.0;

	Runge_Kutta( 10 , Start_Ort , Start_Geschwindigkeit , Harmo , Datei);
	Datei.close();

	
	return 0;
}