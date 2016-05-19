#include <iostream>
#include <cmath>
#include <cstdlib>
#include <time.h>
#include "fstream"

double Generator(double min , double max){
	double Random = (double) rand()/ RAND_MAX;
	return min + Random*(max - min);
}

double LJ_Pot( double Ort_X_1 , double Ort_X_2 , double Ort_Y_1 , double Ort_Y_2){
	double Abstand_x = Ort_X_1 - Ort_X_2;
	double Abstand_y = Ort_Y_1 - Ort_Y_2; 
	double Abstand =  Abstand_x*Abstand_x + Abstand_y*Abstand_y;
	double Bruch = Abstand * Abstand * Abstand;
	return 4.0*(1.0/(Bruch*Bruch) - 1.0/Bruch);
}

void schwer_Geschw(double* V_X , double* V_Y , double &Sum_V_X , double &Sum_V_Y){
	Sum_V_X = 0.0;
	Sum_V_Y = 0.0;
	for( int i = 0 ; i < 16 ; ++i){
		Sum_V_X += V_X[ i ]/16.0;
		Sum_V_Y += V_Y[ i ]/16.0;
	}
}

void E_kin(double* V_X , double* V_Y , double &Energie){
	Energie = 0.0;
	for (int i = 0; i < 16; ++i)
	{
		Energie += V_X[ i ] * V_X[ i ] + V_Y[ i ]*V_Y[ i ];
	}
	Energie = 0.5 * Energie;
}

void E_pot( double* Ort_X , double* Ort_Y , double &Energie){
	Energie = 0.0;
	for (int i = 0; i < 16; ++i)
	{
		for (int j = 0; j < 16; ++j)
		{
			if( i < j - 1){
				Energie += LJ_Pot( Ort_X[ i ] , Ort_X[ j ] , Ort_Y[ i ] , Ort_Y[ j ] );
			}
		}
	}
}

void LJ_Kraftfeld( double Ort_X_1 , double Ort_X_2 , double Ort_Y_1 , double Ort_Y_2 , double &Kraft_X , double &Kraft_Y , double Laenge){
	double Abstand_x = Ort_X_1 - Ort_X_2;
	double Abstand_y = Ort_Y_1 - Ort_Y_2;
	double Abstand = Abstand_x*Abstand_x + Abstand_y*Abstand_y;
	if (sqrt( Abstand ) < 0.5*Laenge)
	{
		double Bruch = 1.0/( Abstand * Abstand *Abstand);
		double Konst = 48.0/( Abstand ) * ( Bruch * Bruch - 0.5*Bruch);
		Kraft_X += Abstand_x * Konst;
		Kraft_Y += Abstand_y * Konst;
	}
}

void Temperatur( double* V_X , double* V_Y , double &Temp){
	Temp = 0.0;
	for (int i = 0; i < 16 ; ++i)
	{
		Temp += V_X[ i ]* V_X[ i ] + V_Y[ i ]*V_Y[ i ];
	}
	Temp = Temp/(2.0*16.0-2.0);
}

void Initialisierung( double* Ort_X , double* Ort_Y , double* Geschwindigkeit_X , double* Geschwindigkeit_Y , double Tempe , double Laenge){
	int Teilchen = 0;
	for (int i = 0; i < 4; ++i)
	{
		for (int a = 0; a < 4; ++a)
		{
			Ort_X[ Teilchen ] = 1.0/8.0*(1.0 + 2.0*i) * Laenge;
			Ort_Y[ Teilchen ] = 1.0/8.0*(1.0 + 2.0*a) * Laenge;
			Geschwindigkeit_X[ Teilchen ] = Generator( -1.0 , 1.0);
			Geschwindigkeit_Y[ Teilchen ] = Generator( -1.0 , 1.0);
			Teilchen++;
		}
	}
	double Sum_V_X = 0.0;
	double Sum_V_Y = 0.0;
	schwer_Geschw( Geschwindigkeit_X , Geschwindigkeit_Y , Sum_V_X , Sum_V_Y);
	for ( int i = 0; i < Teilchen ; ++i)
	{
		Geschwindigkeit_X[ i ] -= Sum_V_X;
		Geschwindigkeit_Y[ i ] -= Sum_V_Y;
	}
	double Temp= 0.0;
	Temperatur( Geschwindigkeit_X , Geschwindigkeit_Y , Temp);
	double Alpha = sqrt(Tempe/Temp);
	for (int i = 0; i < Teilchen; ++i)
	{
		Geschwindigkeit_X[ i ] = Alpha*Geschwindigkeit_X[ i ];
		Geschwindigkeit_Y[ i ] = Alpha*Geschwindigkeit_Y[ i ];
	}
}

void Wechselwirkung( double* Ort_X_Rest , double* Ort_Y_Rest , double Ort_X , double Ort_Y , double &Kraft_X , double &Kraft_Y , double Laenge){
	for (int i = 0; i < 16; ++i)
	{
		for (int n_x = -1; n_x < 2; ++n_x)
		{
			for (int n_y = -1; n_y < 2; ++n_y)
			{
				if( Ort_X_Rest[ i ] != Ort_X || Ort_Y_Rest[ i ] != Ort_Y )
				{
					LJ_Kraftfeld( Ort_X , Ort_X_Rest[ i ] + n_x*Laenge , Ort_Y , Ort_Y_Rest[ i ] + n_y*Laenge , Kraft_X , Kraft_Y , Laenge);
				}
			}
		}
	}
}

void Verlet( double Breite , double Temp , double Laenge , double Zeit , std::fstream& Energie_Datei , std::fstream& Orte_Datei  ){
	int Anzahl = (int) ( Zeit / Breite ) ;
	double Energie_kin;
	double Energie_pot;
	double V_S_X;
	double V_S_Y;
	double Ort_X[16];
	double Ort_Y[16];
	double V_X[16];
	double V_Y[16];
	Initialisierung( Ort_X , Ort_Y , V_X , V_Y , Temp , Laenge );
	double Kraft_0_X[16];
	double Kraft_1_X[16];
	double Kraft_0_Y[16];
	double Kraft_1_Y[16];
	for (int i = 0; i < 16; ++i)
	{
		Wechselwirkung( Ort_X , Ort_Y , Ort_X[ i ] , Ort_Y[ i ] , Kraft_0_X[ i ] , Kraft_0_Y[ i ] , Laenge);
	}
	E_kin( V_X , V_Y , Energie_kin );
	E_pot( Ort_X , Ort_Y , Energie_pot );
	schwer_Geschw( V_X , V_Y , V_S_X , V_S_Y);
	Temperatur( V_X , V_Y , Temp);
	Energie_Datei << "#Zeit" << "\t\t" << "Energie_kin" << "\t\t" << "Energie_pot" << "\t\t" << "Energie_ges" << "\t\t" << "Temperatur" << "\t\t" << "V_S_X" <<"\t\t" << "V_S_Y" << std::endl;
	Energie_Datei << 0 << "\t\t" << Energie_kin << "\t\t" << Energie_pot << "\t\t" << Energie_kin + Energie_pot << "\t\t" << Temp << "\t\t" << V_S_X <<"\t\t" << V_S_Y << std::endl;
	for (int zaehler = 1; zaehler < Anzahl ; ++zaehler)
	{
		for(int i = 0; i < 16; ++i)
		{
			Ort_X[ i ] = Ort_X[ i ] + Breite * V_X[ i ] + 0.5 * Breite * Breite * Kraft_0_X[ i ];
			Ort_Y[ i ] = Ort_Y[ i ] + Breite * V_Y[ i ] + 0.5 * Breite * Breite * Kraft_0_Y[ i ];
		}
		for (int i = 0; i < 16; ++i)
		{
			Wechselwirkung( Ort_X , Ort_Y , Ort_X[ i ] , Ort_Y[ i ] , Kraft_1_X[ i ] , Kraft_1_Y[ i ] , Laenge);
		}
		for (int i = 0; i < 16; ++i)
		{
			V_X[ i ] = V_X[ i ] + Breite * 0.5 * ( Kraft_0_X[ i ] + Kraft_1_X[ i ]);
			V_Y[ i ] = V_Y[ i ] + Breite * 0.5 * ( Kraft_0_Y[ i ] + Kraft_1_Y[ i ]);
		}
		for (int i = 0; i < 16; ++i)
		{
			Kraft_0_X[ i ] = Kraft_1_X[ i ];
			Kraft_0_Y[ i ] = Kraft_1_Y[ i ];
		}
		for (int i = 0; i < 16; ++i)
		{
			Ort_X[ i ] = Ort_X[ i ] - Laenge * floor( Ort_X[ i ]/ Laenge);
			Ort_Y[ i ] = Ort_Y[ i ] - Laenge * floor( Ort_Y[ i ]/ Laenge);
		}
		E_kin( V_X , V_Y , Energie_kin );
		E_pot( Ort_X , Ort_Y , Energie_pot );
		schwer_Geschw( V_X , V_Y , V_S_X , V_S_Y);
		Temperatur( V_X , V_Y , Temp);
		Energie_Datei << zaehler * Breite << "\t\t" << Energie_kin << "\t\t" << Energie_pot << "\t\t" << Energie_kin + Energie_pot << "\t\t" << Temp << "\t\t" << V_S_X <<"\t\t" << V_S_Y << std::endl;
		for (int i = 0; i < 16; ++i)
		{
			Orte_Datei << Ort_X[ i ] << "\t\t" << Ort_Y[ i ] << std::endl;
		}
	}
}

int main(){
	srand (time(NULL));
	std::fstream Datei;
	Datei.open("Ergebnisse/Ergebnis_1.txt" , std::ios::trunc | std::ios::out);
	std::fstream Orte;
	Orte.open("Ergebnisse/Ergebnis_1_Orte.txt" , std::ios::trunc | std::ios::out);

	double Tempe = 1.0;
	double Laenge = 8.0;
	double Zeit = 6;
	double Breite = 1e-2;
	/*double Ort_X[16];
	double Ort_Y[16];
	double Geschwindigkeit_X[16];
	double Geschwindigkeit_Y[16];
	double Sum_V_X = 0.0;
	double Sum_V_Y = 0.0;
	double Energie = 0.0;

	double Kraft_X = 0.0;
	double Kraft_Y = 0.0;

	Initialisierung( Ort_X , Ort_Y , Geschwindigkeit_X , Geschwindigkeit_Y , Tempe , Laenge );

	schwer_Geschw( Geschwindigkeit_X , Geschwindigkeit_Y , Sum_V_X , Sum_V_Y);

	Wechselwirkung( Ort_X , Ort_Y , Ort_X[ 10 ] , Ort_Y[ 10 ] , Kraft_X , Kraft_Y , Laenge);
	std::cout << Kraft_X << "\t\t" << Kraft_Y << std::endl;

	/*double Temp= 0.0;
	Temperatur( Geschwindigkeit_X , Geschwindigkeit_Y , Temp);
	std::cout << Temp << std::endl;
	E_pot( Ort_X , Ort_Y , Energie);
	std::cout << Energie << std::endl;
	E_kin( Geschwindigkeit_X , Geschwindigkeit_Y , Energie);
	std::cout << Energie << std::endl;*/

	std::cout << "######################" << std::endl;
	Verlet( Breite , Tempe , Laenge , Zeit , Datei , Orte);

	return 0;
}