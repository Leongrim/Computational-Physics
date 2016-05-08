#include <iostream>
#include "fstream"
#include <cmath>
#include <vector>
#include "Aufgabe1.h"

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

	for (int  k = 0; k < (int) 1000; ++k) //Schleife, um die Bahn eines Teilchens in eine Matrix zu schreiben
	{
		for (int j = 0; j < 6; ++j)
		{
			Bahn[k][j] = Runge_Kutta( (k)*Breite , Start_Ort , Start_Geschwindigkeit , Kepler , Breite)[j];
		}
	}

	////// Lenz-Runge Vektoren
	Datei.open( "Ergebnisse/Ergebnis_4_Energie.txt" , std::ios::trunc | std::ios::out);
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
	double produkt2 = 0.0;



	for (int i = 0; i < (int) 1000 ; ++i) // Aufgabenteil b): Schleife, mit deren Hilfe die Drehimpuls- und Energieerhaltung gezeigt werden soll 
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
			Datei << i*Breite << '\t' << Energie - Energie_1 << '\t';
			Datei << Dreh_0 - Dreh_1 << std::endl;
		}
		Energie_1 = Energie;
		Dreh_1 = Dreh_0;
	}
	Datei.close();
	Datei.open("Ergebnisse/Ergebnis_4_LR.txt" , std::ios::trunc | std::ios::out);
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
	Datei.open("Ergebnisse/Ergebnis_4_Kepler_3_1.txt" , std::ios::trunc | std::ios::out);
	for (int i = 0; i < 1000 ; ++i)// Schleife, mit der die Umlaufzeit bestimmmt wird
	{
		if(std::abs(Bahn[i][0]-1) < 1e-1 && std::abs(Bahn[i][1]) < 1e-1){
			Datei << "ZEIT:" << (double) i*Breite<< '\t' << Bahn[i][0] << '\t' << Bahn[i][1] << std::endl;
		}

	}
	double temp = 0.0;
	for (int i = 0; i < 1000; ++i)//Schleife, um die Halbachse zu bestimmen
	{
		for (int j = 0; j < 1000; ++j)
		{
			Norm = sqrt( (Bahn[i][0]-Bahn[j][0])*(Bahn[i][0]-Bahn[j][0]) + (Bahn[i][1]-Bahn[j][1])*(Bahn[i][1]-Bahn[j][1]) + (Bahn[i][2]-Bahn[j][2])*(Bahn[i][2]-Bahn[j][2])   );
			if(Norm > temp)	{
				temp = Norm;
			}
		}
	}
	std::cout << "Große Halbachse für Bahn 1= "<< temp << std::endl;
	Datei.close();
	Datei.open("Ergebnisse/Ergebnis_4_Kepler_3_2.txt" , std::ios::trunc | std::ios::out);
	Start_Ort[0] = 1.0;
	Start_Ort[1] = 0.0;
	Start_Ort[2] = 0.0;

	Start_Geschwindigkeit[0] = -0.1;
	Start_Geschwindigkeit[1] = 1.0;
	Start_Geschwindigkeit[2] = 0.0;

	for (int  k = 0; k < (int) 1000; ++k) // Schleife, mit der die Bahn eines Teilchens in eine Matrix geschrieben wird
	{
		for (int j = 0; j < 6; ++j)
		{
			Bahn[k][j] = Runge_Kutta( (k)*Breite , Start_Ort , Start_Geschwindigkeit , Kepler , Breite)[j];
		}
	}
	temp = 0.0;
	for (int i = 0; i < 1000; ++i)//Schleife, um die Halbachse zubestimmen
	{
		for (int j = 0; j < 1000; ++j)
		{
			Norm = sqrt( (Bahn[i][0]-Bahn[j][0])*(Bahn[i][0]-Bahn[j][0]) + (Bahn[i][1]-Bahn[j][1])*(Bahn[i][1]-Bahn[j][1]) + (Bahn[i][2]-Bahn[j][2])*(Bahn[i][2]-Bahn[j][2])  );
			if(Norm > temp)	{
				temp = Norm;
			}
		}
	}
	std::cout << "Große Halbachse für Bahn 2= " << temp << std::endl;
	for (int i = 0; i < 1000 ; ++i)// Schleife, mit der die Umlaufzeit bestimmmt wird
	{
		if(std::abs(Bahn[i][0]-1) < 1e-1 && std::abs(Bahn[i][1]) < 1e-1){
			Datei << "ZEIT:" << (double) i*Breite<< '\t' << Bahn[i][0] << '\t' << Bahn[i][1] << std::endl;
		}

	}
	Datei.close();


	Datei.open( "Ergebnisse/Ergebnis_4_BAHN.txt" , std::ios::trunc | std::ios::out);

	for (int i = 0; i < 1000 ; ++i)
	{
		Datei << (double)i/10 << '\t' << Bahn[i][0] << '\t' << Bahn[i][1] << '\t' << Bahn[i][2] << std::endl;
	}

	Datei.close();

	return 0;
}