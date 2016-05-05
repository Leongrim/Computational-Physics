#include <iostream>
#include "fstream"
#include <cmath>
#include <vector>
#include </home/leonard/FP_Repo2016/Computational-Physics/Blatt-03/Aufgabe1.h>

double* Kepler( double* Ort){
	double *Pointer = new double [3];
	double Norm = sqrt( Ort[0]*Ort[0] + Ort[1]*Ort[1] + Ort[2]*Ort[2]);
	for (int i = 0; i < 3  ; ++i)
	{
		Pointer[i] = -Ort[i]/(Norm*Norm*Norm);
	}
	return Pointer;
}

int main(){

	std::fstream Datei;

	double *Start_Ort = new double [3];
	double *Start_Geschwindigkeit = new double [3];

	Start_Ort[0] = 1.0;
	Start_Ort[1] = 0.0;
	Start_Ort[2] = 0.0;

	Start_Geschwindigkeit[0] = -0.5;
	Start_Geschwindigkeit[1] = 1.0;
	Start_Geschwindigkeit[2] = 0.0;

	//10	0.777685	0.318922	0	-0.879425	0.925222	0	N=10/0.01	

	Datei.open( "Ergebnisse/Ergebnis_4_A.txt" , std::ios::trunc | std::ios::out);
	Runge_Kutta( 100 , Start_Ort , Start_Geschwindigkeit , Kepler , Datei , 0.01);
	Datei.close();

	double *Start_Ort2 = new double [3];
	double *Start_Geschwindigkeit2 = new double [3];

	Start_Ort2[0] = Runge_Kutta( 10 , Start_Ort , Start_Geschwindigkeit , Kepler , 0.01)[0];
	Start_Ort2[1] = Runge_Kutta( 10 , Start_Ort , Start_Geschwindigkeit , Kepler , 0.01)[1];
	Start_Ort2[2] = Runge_Kutta( 10 , Start_Ort , Start_Geschwindigkeit , Kepler , 0.01)[2];



	Start_Geschwindigkeit2[0] = -Runge_Kutta( 10 , Start_Ort , Start_Geschwindigkeit , Kepler , 0.01)[3];
	Start_Geschwindigkeit2[1] = -Runge_Kutta( 10 , Start_Ort , Start_Geschwindigkeit , Kepler , 0.01)[4];
	Start_Geschwindigkeit2[2] = -Runge_Kutta( 10 , Start_Ort , Start_Geschwindigkeit , Kepler , 0.01)[5];
	//10	0.777685	0.318922	0	-0.879425	0.925222	0	N=10/0.01	

	Datei.open( "Ergebnisse/Ergebnis_4_A_Rueck.txt" , std::ios::trunc | std::ios::out);
	Runge_Kutta( 10 , Start_Ort2 , Start_Geschwindigkeit2 , Kepler , Datei , 0.01);
	Datei.close();

	Start_Ort[0] = 1.0;
	Start_Ort[1] = 0.0;
	Start_Ort[2] = 0.0;

	Start_Geschwindigkeit[0] = -0.1;
	Start_Geschwindigkeit[1] = 1.0;
	Start_Geschwindigkeit[2] = 0.0;

	//20	1.15393	-0.623457	0	0.0246166	-0.879897	0	

	Datei.open( "Ergebnisse/Ergebnis_4_A_2.txt" , std::ios::trunc | std::ios::out );
	Runge_Kutta( 9 , Start_Ort , Start_Geschwindigkeit , Kepler , Datei , 0.01);
	Datei.close();

	return 0;
}