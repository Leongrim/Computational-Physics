#include <iostream>
#include <cmath>
#include "fstream"

double theta_1_beschleunigung(double theta_1 , double theta_2 , double theta_geschwindigkeit_1 , double theta_geschwindigkeit_2){
	double summand_1 = 1.0/2.0*9.81*sin( theta_2 )*cos(theta_2 - theta_1) ;  
	double summand_2 = 1.0/2.0*theta_geschwindigkeit_1*theta_geschwindigkeit_1*sin( theta_2 - theta_1)*cos( theta_2 -theta_1);
	double summand_3 = -9.81*sin( theta_2 ) ;
	double summand_4 =  1.0/2.0*theta_geschwindigkeit_2*theta_geschwindigkeit_2*sin( theta_2 - theta_1);
	double Norm = 1.0 - 1.0/2.0 * cos( theta_2 - theta_1) * cos( theta_2 - theta_1) ;
	return 1.0/Norm * (summand_1 + summand_2 + summand_3 + summand_4);
}
double theta_2_beschleunigung(double theta_1 , double theta_2 , double theta_geschwindigkeit_1 , double theta_geschwindigkeit_2){
	double summand_1 = 9.81 * sin( theta_1 ) * cos( theta_2 - theta_1);  
	double summand_2 = -1.0/2.0*theta_geschwindigkeit_2 * theta_geschwindigkeit_2 * sin( theta_2 - theta_1) * cos( theta_2 - theta_1);
	double summand_3 = -9.81*sin( theta_2 );
	double summand_4 = -theta_geschwindigkeit_1*theta_geschwindigkeit_1*sin( theta_2 - theta_2);
	double Norm = (1.0-1.0/2.0*cos( theta_2 - theta_1) * cos( theta_2 - theta_1) );
	return 1.0/Norm * (summand_1 + summand_2 + summand_3 + summand_4);
}
void Doppelpendel( double Zeit , double Breite , double theta_1 , double theta_2 , double theta_geschwindigkeit_1 , double theta_geschwindigkeit_2 , std::fstream& Datei ){
	double *Y_n = new double[4];
	Y_n[0] = theta_1;
	Y_n[1] = theta_2;
	Y_n[2] = theta_geschwindigkeit_1;
	Y_n[3] = theta_geschwindigkeit_2;
	int Anzahl = (int)(Zeit / Breite);
	double *K_1 = new double[4];
	double *K_2 = new double[4];
	double *K_3 = new double[4];
	double *K_4 = new double[4];
	double *Ort_1 = new double[2];
	double *Ort_2 = new double[2];
	double *Geschwindigkeit_1 = new double[4];
	double *Geschwindigkeit_2 = new double[4];


	double *Zwischenergebnis = new double[4];

	for (int Zaehler = 0; Zaehler < Anzahl ; ++Zaehler)
	{
		K_1[0] = Breite*Y_n[2];
		K_1[1] = Breite*Y_n[3];
		K_1[2] = theta_1_beschleunigung( Y_n[0] , Y_n[1] , Y_n[2] , Y_n[3]);
		K_1[3] = theta_2_beschleunigung( Y_n[0] , Y_n[1] , Y_n[2] , Y_n[3]);

		for (int Komponente = 0; Komponente < 4 ; ++Komponente)
		{
			Zwischenergebnis[ Komponente ] = Y_n[ Komponente ] +1.0/2.0*K_1[ Komponente ];
		}
		K_2[0] = Breite * Zwischenergebnis[2];
		K_2[1] = Breite * Zwischenergebnis[3];
		K_2[2] = Breite * theta_1_beschleunigung( Zwischenergebnis[ 0 ] , Zwischenergebnis[ 1 ] , Zwischenergebnis[ 2 ] , Zwischenergebnis[ 3 ] );
		K_2[3] = Breite * theta_2_beschleunigung( Zwischenergebnis[ 0 ] , Zwischenergebnis[ 1 ] , Zwischenergebnis[ 2 ] , Zwischenergebnis[ 3 ] );

		for (int Komponente = 0; Komponente < 4 ; ++Komponente)
		{
			Zwischenergebnis[ Komponente ] = Y_n[ Komponente ]  +1.0/2.0*K_2[ Komponente ];
		}
		K_3[0] = Breite * Zwischenergebnis[2];
		K_3[1] = Breite * Zwischenergebnis[3];
		K_3[2] = Breite * theta_1_beschleunigung( Zwischenergebnis[ 0 ] , Zwischenergebnis[ 1 ] , Zwischenergebnis[ 2 ] , Zwischenergebnis[ 3 ] );
		K_3[3] = Breite * theta_2_beschleunigung( Zwischenergebnis[ 0 ] , Zwischenergebnis[ 1 ] , Zwischenergebnis[ 2 ] , Zwischenergebnis[ 3 ] );

		for (int Komponente = 0; Komponente < 4 ; ++Komponente)
		{
			Zwischenergebnis[ Komponente ] = Y_n[ Komponente ] + K_3[ Komponente ];
		}
		K_4[0] = Breite * Zwischenergebnis[2];
		K_4[1] = Breite * Zwischenergebnis[3];
		K_4[2] = Breite * theta_1_beschleunigung( Zwischenergebnis[ 0 ] , Zwischenergebnis[ 1 ] , Zwischenergebnis[ 2 ] , Zwischenergebnis[ 3 ] );
		K_4[3] = Breite * theta_2_beschleunigung( Zwischenergebnis[ 0 ] , Zwischenergebnis[ 1 ] , Zwischenergebnis[ 2 ] , Zwischenergebnis[ 3 ] );
		for (int Komponente = 0; Komponente < 4 ; ++Komponente)
		{
			Y_n[ Komponente] = Y_n[ Komponente ] + 1.0/6.0 * ( K_1[ Komponente ] + 2.0* K_2[ Komponente ] + 2.0*K_3[Komponente] + K_4[ Komponente ] );
		}
		Datei << (double) Zaehler*Breite << '\t' << Y_n[0] << '\t' << Y_n[1] << '\t' << Y_n[2] << '\t' << Y_n[3] << std::endl;
	}
	delete[] Y_n;
	delete[] K_1;
	delete[] K_2;
	delete[] K_3;
	delete[] K_4;
	delete[] Zwischenergebnis;

}


int main(){

	std::fstream Datei;
	double theta_1 = 0.1;
	double theta_2 = sqrt(2) * theta_1;
	double theta_geschwindigkeit_1 = 0.0;
	double theta_geschwindigkeit_2 = 0.0;
	double Breite = 0.01;

	Datei.open("Ergebnisse/Ergebnis_1_C_1.txt" , std::ios::trunc | std::ios::out);
	Doppelpendel( 10 , Breite , theta_1 , theta_2 , theta_geschwindigkeit_1 , theta_geschwindigkeit_2 , Datei);
	Datei.close();

	theta_1 = 0.1;
	theta_2 = -sqrt(2) * theta_1;
	theta_geschwindigkeit_1 = 0.0;
	theta_geschwindigkeit_2 = 0.0;

	Datei.open("Ergebnisse/Ergebnis_1_C_2.txt" , std::ios::trunc | std::ios::out);
	Doppelpendel( 1 , Breite , theta_1 , theta_2 , theta_geschwindigkeit_1 , theta_geschwindigkeit_2 , Datei);
	Datei.close();

	return 0;
}