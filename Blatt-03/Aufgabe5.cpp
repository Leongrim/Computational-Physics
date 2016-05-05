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
	const double Breite = 0.1;
	double Bahn[1000][7];


	Start_Ort[0] = 1.0;
	Start_Ort[1] = 0.0;
	Start_Ort[2] = 0.0;

	Start_Geschwindigkeit[0] = -0.5;
	Start_Geschwindigkeit[1] = 1.0;
	Start_Geschwindigkeit[2] = 0.0;

	for (int  k = 0; k < (int) 1000; ++k)
	{
		double i= (double) k;
		for (int j = 0; j < 6; ++j)
		{
			Bahn[k][j] = Runge_Kutta( (i)/10.0 , Start_Ort , Start_Geschwindigkeit , Kepler , Breite)[j];
		}
	}

	////// Lenz-Runge Vektoren
	Datei.open( "Ergebnisse/Ergebnis_4_LR.txt" , std::ios::trunc | std::ios::out);
	double Norm;
	double X_Komponente;
	double Y_Komponente;
	double Z_Komponente;
	double Energie =0.0;
	double Energie_1 =0.0;
	double* Dreh = new double[3];
	double Dreh_0 =0.0;
	double Dreh_1 =0.0;
	double LenzRunge = 0.0;
	double LenzRunge_1 = 0.0;
	double produkt1 = 0.0;



	for (int i = 0; i < (int) 1000 ; ++i)
	{	
		Norm = sqrt( Bahn[i][0]*Bahn[i][0] + Bahn[i][1]*Bahn[i][1] + Bahn[i][2]*Bahn[i][2] );
		produkt1 =  Bahn[i][3]*Bahn[i][3] + Bahn[i][4]*Bahn[i][4] + Bahn[i][5]*Bahn[i][5];
		Energie = 0.5*produkt1 - 1/Norm;
		Dreh[0] = Bahn[i][1]*Bahn[i][5] -Bahn[i][2]*Bahn[i][4];
		Dreh[1] = Bahn[i][2]*Bahn[i][3] -Bahn[i][0]*Bahn[i][5];
		Dreh[2] = Bahn[i][0]*Bahn[i][4] -Bahn[i][1]*Bahn[i][3];
		Dreh_0 = sqrt(Dreh[0]*Dreh[0] + Dreh[1]*Dreh[1] + Dreh[2]*Dreh[2]);

		if (i!=0)
		{
			Datei << Energie - Energie_1 << '\t';
			Datei << Dreh_0 - Dreh_1 << std::endl;
		}
		Energie_1 = Energie;
		Dreh_1 = Dreh_0;
	}
	for (int i = 0; i < 1000; ++i)
	{
		Norm = sqrt( Bahn[i][0]*Bahn[i][0] + Bahn[i][1]*Bahn[i][1] + Bahn[i][2]*Bahn[i][2] );
		produkt1 = Bahn[i][0]*Bahn[i][3] + Bahn[i][1]*Bahn[i][4] + Bahn[i][2]*Bahn[i][5];
		produkt2 = Bahn[i][3]*Bahn[i][3] + Bahn[i][4]*Bahn[i][4] + Bahn[i][5]*Bahn[i][5];
		X_Komponente = produkt1*Bahn[i][3] - produkt2*Bahn[i][0]-Bahn[i][0]/Norm;
		Y_Komponente = produkt1*Bahn[i][4] - produkt2*Bahn[i][1]-Bahn[i][1]/Norm;
		Z_Komponente = produkt1*Bahn[i][5] - produkt2*Bahn[i][2]-Bahn[i][2]/Norm;
		LenzRunge = sqrt( X_Komponente*X_Komponente + Y_Komponente*Y_Komponente + Z_Komponente*Z_Komponente);
		if (i != 0)
		{
			
		}
		LenzRunge_1 = LenzRunge;
	}
	/*for (int i = 0; i < (int) 1000 ; ++i)
	{
		if (std::abs( Bahn[i][0] ) < 1e-1){
			std::cout << i*Breite << '\t' << Bahn[i][0] << '\t' << Bahn[i][1] << std::endl;
		}
		if(std::abs(Bahn[i][0]-1) < 1e-1 && std::abs(Bahn[i][1]) < 1e-1){
			std::cout << "ZEIT:" << (double) i/10 << '\t' << Bahn[i][0] << '\t' << Bahn[i][1] << std::endl;
		}

	}
	Datei.close();
	Datei.open( "Ergebnisse/Ergebnis_4_BAHN.txt" , std::ios::trunc | std::ios::out);

	for (int i = 0; i < (int) 1000 ; ++i)
	{
		Datei << i/10 << '\t' << Bahn[i][0] << '\t' << Bahn[i][1] << '\t' << Bahn[i][2] << std::endl;
	}*/

	Datei.close();

	return 0;
}