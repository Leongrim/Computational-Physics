#include <iostream>
#include "fstream"
#include <cmath>
#include <vector>
#include </home/leonard/FP_Repo2016/Computational-Physics/Blatt-03/Aufgabe1.h>

double* Kepler( double* Ort){
	double *Pointer = new double [3];
	double Norm = sqrt( Ort[1]*Ort[1] + Ort[2]*Ort[2] + Ort[3]*Ort[3]);
	for (int i = 0; i < 3  ; ++i)
	{
		Pointer[i] = -Ort[i]/(Norm*Norm*Norm);
	}
	return Pointer;
}

int main(){

	std::fstream Datei;

	Datei.open( "Ergebnisse/Ergebnis_4_A.txt" , std::ios::trunc | std::ios::out);

	double *Start_Ort = new double [3];
	double *Start_Geschwindigkeit = new double [3];

	Start_Ort[0] = 10.0;
	Start_Ort[1] = 10.0;
	Start_Ort[2] = 0.0;

	Start_Geschwindigkeit[0] = 0.0;
	Start_Geschwindigkeit[1] = 0.0;
	Start_Geschwindigkeit[2] = 0.0;

	Start_Ort[0] = 1.0;
	Start_Ort[1] = 0.0;
	Start_Ort[2] = 0.0;

	Start_Geschwindigkeit[0] = 0.1;
	Start_Geschwindigkeit[1] = 1.0;
	Start_Geschwindigkeit[2] = 0.0;

	Runge_Kutta( 50 , Start_Ort , Start_Geschwindigkeit , Kepler , Datei , 0.0002);
	Datei.close();

	return 0;
}