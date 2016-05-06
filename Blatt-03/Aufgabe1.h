#include <iostream>
#include "fstream"
#include <cmath>

void Runge_Kutta( double Zeit , double *Ort , double *Geschwindigkeit , double* Kraftfeld(double*) , std::fstream& Datei , double Breite = 0.001){
	double *Y_n = new double[7];
	double Anzahl =  (Zeit / Breite);
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
	Datei << 0 << '\t';
	for (int i = 0; i < 6; ++i)
	{
		Datei << Y_n[i] << '\t';
	}
	Datei << std::endl;
	for (double Zaehler = 1; Zaehler <= Anzahl; ++Zaehler)
	{
		for (int Komponente = 0; Komponente < 3; ++Komponente)
		{
			K_1[ Komponente ] =    Breite * Y_n[ Komponente + 3 ];
		}
		for( int Komponente = 0 ; Komponente < 3 ; ++Komponente)
		{
			K_1[ Komponente + 3 ] = Breite * Kraftfeld( Y_n )[ Komponente ];
		}

		for (int Komponente = 0; Komponente < 6; ++Komponente)
		{
			Zwischenergebniss[ Komponente ] = Y_n[ Komponente ] + 1.0/2.0 * K_1[ Komponente ];
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
			Zwischenergebniss[ Komponente ] = Y_n[ Komponente ] +  K_3[ Komponente ];
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
			Y_n[Komponente] = Y_n[Komponente] + 1.0/6.0*( K_1[ Komponente ] + 2.0*K_2[ Komponente ] + 2.0*K_3[ Komponente ] + K_4[ Komponente ]);
		}
		Y_n[6]=Breite*Zaehler;

		Datei 	<< Y_n[6] << '\t';
		for (int Komponente = 0; Komponente < 6; Komponente++ )
		{
				Datei 	<< Y_n[ Komponente ] << '\t';
		
		}
		Datei << std::endl;
	}
}

double* Runge_Kutta( double Zeit , double *Ort , double *Geschwindigkeit , double* Kraftfeld(double*) , double Breite = 0.001){
	double *Y_n = new double[7];
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
	
	for (double Zaehler = 1; Zaehler <= Anzahl; ++Zaehler)
	{
		for (int Komponente = 0; Komponente < 3; ++Komponente)
		{
			K_1[ Komponente ] =    Breite * Y_n[ Komponente + 3 ];
		}
		for( int Komponente = 0 ; Komponente < 3 ; ++Komponente)
		{
			K_1[ Komponente + 3 ] = Breite * Kraftfeld( Y_n )[ Komponente ];
		}

		for (int Komponente = 0; Komponente < 6; ++Komponente)
		{
			Zwischenergebniss[ Komponente ] = Y_n[ Komponente ] + 1.0/2.0 * K_1[ Komponente ];
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
			Zwischenergebniss[ Komponente ] = Y_n[ Komponente ] +  K_3[ Komponente ];
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
			Y_n[Komponente] = Y_n[Komponente] + 1.0/6.0*( K_1[ Komponente ] + 2.0*K_2[ Komponente ] + 2.0*K_3[ Komponente ] + K_4[ Komponente ]);
		}
		Y_n[6]=Breite*Zaehler;
	}
	return Y_n;
}