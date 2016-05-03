#include <iostream>
#include "fstream"
#include <cmath>
#include <vector>

double* Harmo( double* Ort ){
	double *Pointer = new double [3];
	for (int i = 0; i < 3; ++i)
	{
		Pointer[i] = -Ort[i];
	}
	return Pointer;
}

void Runge_Kutta( double Zeit , double *Ort , double *Geschwindigkeit , double* Kraftfeld(double*) ){
	std::fstream Datei;
	Datei.open("Ergebnisse/Ergebnis_A.txt" , std::ios::trunc | std::ios::out);
	double *Y_n = new double[6];
	double Breite = 1;
	double Anzahl = Zeit / Breite;
	for (int i = 0; i < 3; ++i)
	{
		Y_n[i] = Ort[i];
	}
	for( int i = 0; i< 3 ; ++i){
		Y_n[i+3] = Geschwindigkeit[i];
	}
	double *Zwischenergebniss = new double[6];
	double *K_1=new double[6];
	double *K_2=new double[6];
	double *K_3=new double[6];
	double *K_4=new double[6];
	for (int Zaehler = 0; Zaehler <= Anzahl; ++Zaehler)
	{
		for (int Komponente = 0; Komponente < 3; ++Komponente)
		{
			K_1[Komponente] =     Y_n[ Komponente + 3 ];
		}
		for( int Komponente = 0 ; Komponente < 3 ; ++Komponente)
		{
			K_1[Komponente+3] = Kraftfeld( Y_n )[ Komponente ];
		}

		for (int Komponente = 0; Komponente < 6; ++Komponente)
		{
			Zwischenergebniss[ Komponente ] = Y_n[ Komponente ]+ 1.0/2.0 * K_1[ Komponente ];
		}

		for (int Komponente = 0; Komponente < 3; ++Komponente)
		{
			K_2[ Komponente ] = Breite * Zwischenergebniss[ Komponente + 3 ];	
		}
		for (int Komponente = 0; Komponente < 3; ++Komponente)
		{
			K_2[ Komponente + 3 ] = Breite * Kraftfeld( Zwischenergebniss )[ Komponente ];
		}

		for (int Komponente = 0; Komponente < 6; ++Komponente)
		{
			Zwischenergebniss[ Komponente ] = Y_n[Komponente] + 1.0/2.0 * K_2[ Komponente ];
		}

		for (int Komponente = 0; Komponente < 3; ++Komponente)
		{
			K_3[ Komponente ] = Breite * Zwischenergebniss[ Komponente + 3];
		}
		for (int Komponente = 0; Komponente < 3; ++Komponente)
		{
			K_3[ Komponente +3 ] = Breite * Kraftfeld( Zwischenergebniss )[ Komponente ];
		}

		for(int Komponente = 0 ; Komponente < 6 ; ++Komponente)
		{
			Zwischenergebniss[ Komponente ] = Y_n[ Komponente ] + 1.0/2.0 * K_3[ Komponente ];
		}

		for (int Komponente = 0; Komponente < 3; ++Komponente)
		{
			K_4[ Komponente ] = Breite * Zwischenergebniss[ Komponente + 3 ];
		}
		for (int Komponente = 0; Komponente < 3; ++Komponente)
		{
			K_4[ Komponente + 3 ] = Breite * Kraftfeld( Zwischenergebniss )[Komponente];
		}
		for (int Komponente = 0; Komponente < 6; ++Komponente)
		{
			Y_n[Komponente] =+ 1.0/6.0*K_1[ Komponente ] + 1.0/3.0*K_2[ Komponente ] + 1.0/3.0*K_3[ Komponente ] + 1.0/6.0*K_4[ Komponente ];
		}
		Datei << Zaehler*Breite << '\t';
		for (int Komponente = 0; Komponente < 6; ++Komponente)
		{
		Datei 	<< Y_n[ Komponente ] << '\t';
		}
		Datei << std::endl;
	}
}


int main(){



	double *Start_Ort = new double [3];
	double *Start_Geschwindigkeit = new double [3];

	Start_Ort[0] = 10.0;
	Start_Ort[1] = 5.0;
	Start_Ort[2] = 0.0;

	Start_Geschwindigkeit[0]= 1.0;
	Start_Geschwindigkeit[1]= -2.0;
	Start_Geschwindigkeit[2]= 10.0;


	Runge_Kutta( 10000 , Start_Ort , Start_Geschwindigkeit , Harmo );
	return 0;
}