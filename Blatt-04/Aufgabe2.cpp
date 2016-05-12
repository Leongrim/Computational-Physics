#include <iostream>
#include <cmath>
#include "fstream"

double theta_1_beschleunigung(double theta_1 , double theta_2 , double theta_geschwindigkeit_1 , double theta_geschwindigkeit_2){
	double summand_1 = 0.5 * 9.81 * sin( theta_2 ) * cos( theta_2 - theta_1 ) ;  
	double summand_2 = 0.5 * theta_geschwindigkeit_1 * theta_geschwindigkeit_1 * sin( theta_2 - theta_1 ) * cos( theta_2 -theta_1 );
	double summand_3 = -9.81 * sin( theta_1 ) ;
	double summand_4 =  0.5 * theta_geschwindigkeit_2 * theta_geschwindigkeit_2 * sin( theta_2 - theta_1);
	double Norm = 1.0 - 0.5 * cos( theta_2 - theta_1) * cos( theta_2 - theta_1) ;
	return 1.0/Norm * ( summand_1 + summand_2 + summand_3 + summand_4 );
}
double theta_2_beschleunigung(double theta_1 , double theta_2 , double theta_geschwindigkeit_1 , double theta_geschwindigkeit_2){
	double summand_1 = 9.81 * sin( theta_1 ) * cos( theta_2 - theta_1);  
	double summand_2 = -0.5 * theta_geschwindigkeit_2 * theta_geschwindigkeit_2 * sin( theta_2 - theta_1) * cos( theta_2 - theta_1);
	double summand_3 = -9.81 * sin( theta_2 );
	double summand_4 = -theta_geschwindigkeit_1 * theta_geschwindigkeit_1 * sin( theta_2 - theta_1);
	double Norm = 1.0 - 0.5 * cos( theta_2 - theta_1) * cos( theta_2 - theta_1) ;
	return 1.0/Norm * (summand_1 + summand_2 + summand_3 + summand_4);
}
double* Y_Plus( double Breite , double theta_1 , double theta_2 , double theta_geschwindigkeit_1 , double theta_geschwindigkeit_2){
	double* Y_n = new double[4];
	Y_n[0] = theta_1;
	Y_n[1] = theta_2;
	Y_n[2] = theta_geschwindigkeit_1;
	Y_n[3] = theta_geschwindigkeit_2;

	double K_1[4];
	double K_2[4];
	double K_3[4];
	double K_4[4];
	double Zwischenergebnis[4];

	K_1[0] = Breite * Y_n[2];
	K_1[1] = Breite * Y_n[3];
	K_1[2] = Breite * theta_1_beschleunigung( Y_n[0] , Y_n[1] , Y_n[2] , Y_n[3]);
	K_1[3] = Breite * theta_2_beschleunigung( Y_n[0] , Y_n[1] , Y_n[2] , Y_n[3]);

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
		Zwischenergebnis[ Komponente ] = Y_n[ Komponente ]  + 1.0/2.0*K_2[ Komponente ];
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
	return Y_n;
}
void Doppelpendel( double Zeit , double Breite , double theta_1 , double theta_2 , double theta_geschwindigkeit_1 , double theta_geschwindigkeit_2 , std::fstream& Datei ){
	double* Y_n = new double[4];
	Y_n[0] = theta_1;
	Y_n[1] = theta_2;
	Y_n[2] = theta_geschwindigkeit_1;
	Y_n[3] = theta_geschwindigkeit_2;
	int Anzahl = (int)(Zeit / Breite);
	double Ort_1[2];
	double Ort_2[2];

	double Energie_Kin;
	double Energie_Pot;

	for (int Zaehler = 1; Zaehler < Anzahl ; ++Zaehler)
	{
			Y_n = Y_Plus( Breite , Y_n[0] , Y_n[1] , Y_n[2] , Y_n[3]);
			Ort_1[0] =  sin( Y_n[0]);
			Ort_1[1] = -cos( Y_n[0]);
			Ort_2[0] =  sin( Y_n[0] ) + sin( Y_n[1]);
			Ort_2[1] = -cos( Y_n[0] ) - cos( Y_n[1]);
			Energie_Pot = - 9.81 * ( 2.0*cos(Y_n[0]) + cos(Y_n[1]) );
			Energie_Kin = 0.5 * ( 2.0*Y_n[2]*Y_n[2] + Y_n[3]*Y_n[3] + 2.0*Y_n[2]*Y_n[3]*cos(Y_n[0] - Y_n[1]));


		Datei << (double) Zaehler*Breite << "\t\t" << Y_n[0] << "\t\t" << Y_n[1] << "\t\t" << Y_n[2] << "\t\t" << Y_n[3] << "\t\t" << Ort_1[0] << "\t\t" << Ort_1[1] << "\t\t" << Ort_2[0] << "\t\t" << Ort_2[1] << "\t\t"  << Energie_Kin << "\t\t"  << Energie_Pot << std::endl;
	}
	delete[] Y_n;
}

double* Doppelpendel( double Zeit , double Breite , double theta_1 , double theta_2 , double theta_geschwindigkeit_1 , double theta_geschwindigkeit_2 ){
	double* Y_n = new double[4];
	Y_n[0] = theta_1;
	Y_n[1] = theta_2;
	Y_n[2] = theta_geschwindigkeit_1;
	Y_n[3] = theta_geschwindigkeit_2;
	int Anzahl = (int)(Zeit / Breite);

	for (int Zaehler = 1; Zaehler < Anzahl ; ++Zaehler)
	{
			Y_n = Y_Plus( Breite , Y_n[0] , Y_n[1] , Y_n[2] , Y_n[3]);
	}
	return Y_n;
}


int main(){

	std::fstream Datei;
	Datei.open( "Ergebnisse/Ergebnis_2_C_.txt" , std::ios::trunc | std::ios::out);
	std::fstream Datei_quasi;
	Datei_quasi.open( "Ergebnisse/Ergebnis_2_C_quasi.txt" , std::ios::trunc | std::ios::out);
	std::fstream Datei_Chaos;
	Datei_Chaos.open( "Ergebnisse/Ergebnis_2_C_Chaos.txt" , std::ios::trunc | std::ios::out);
	double Breite = 0.01;
	double Zeit = 500.0;
	const uint Anzahl = (uint) Zeit/Breite; 

	double Phasenraum[ Anzahl ][4];
	Phasenraum[0][0] = 0.1;
	Phasenraum[0][1] = sqrt(2)*Phasenraum[0][0];
	Phasenraum[0][2] = 0.0;
	Phasenraum[0][3] = 0.0;

	double Phasenraum_quasie[ Anzahl ][4];
	Phasenraum_quasie[0][0] = 0.0;
	Phasenraum_quasie[0][1] = 0.0;
	Phasenraum_quasie[0][2] = 0.0;
	Phasenraum_quasie[0][3] = 4.472;

	double Phasenraum_Chaos[ Anzahl ][4];
	Phasenraum_Chaos[0][0] = 0.0;
	Phasenraum_Chaos[0][1] = 0.0;
	Phasenraum_Chaos[0][2] = 0.0;
	Phasenraum_Chaos[0][3] = 11.832;

 
	for( uint Zaehler = 1 ; Zaehler <  Anzahl  ; Zaehler++){
		for (int i = 0; i < 4; ++i)
		{
			Phasenraum[ Zaehler ][ i ] = Y_Plus( Breite , Phasenraum[ Zaehler - 1 ][ 0 ] , Phasenraum[ Zaehler - 1 ][ 1 ] , Phasenraum[ Zaehler - 1 ][ 2 ] , Phasenraum[ Zaehler - 1 ][ 3 ] )[ i ];
			Phasenraum_quasie[ Zaehler ][ i ] = Y_Plus( Breite , Phasenraum_quasie[ Zaehler - 1 ][ 0 ] , Phasenraum_quasie[ Zaehler - 1 ][ 1 ] , Phasenraum_quasie[ Zaehler - 1 ][ 2 ] , Phasenraum_quasie[ Zaehler - 1 ][ 3 ] )[ i ];
			Phasenraum_Chaos[ Zaehler ][ i ] = Y_Plus( Breite , Phasenraum_Chaos[ Zaehler - 1 ][ 0 ] , Phasenraum_Chaos[ Zaehler - 1 ][ 1 ] , Phasenraum_Chaos[ Zaehler - 1 ][ 2 ] , Phasenraum_Chaos[ Zaehler - 1 ][ 3 ] )[ i ];
		}
	}

	for( uint Zaehler = 1 ; Zaehler <  Anzahl  ; Zaehler++){
		if( Phasenraum[ Zaehler ][ 1 ]/Phasenraum[ Zaehler - 1 ][ 1 ] < 0 && Phasenraum[ Zaehler ][ 3 ] + Phasenraum[ Zaehler ][ 2 ]*cos(Phasenraum[ Zaehler ][ 0] ) > 0){
			for (int i = 0; i < 4; ++i)
			{
				Datei << ( Phasenraum[ Zaehler ][ i ] + Phasenraum[ Zaehler ][ i - 1 ] )/2.0 << "\t\t" ;
			}
			Datei << std::endl;
		}
		if( Phasenraum_quasie[ Zaehler ][ 1 ]/Phasenraum_quasie[ Zaehler - 1 ][ 1 ] < 0 && Phasenraum_quasie[ Zaehler ][ 3 ] + Phasenraum_quasie[ Zaehler ][ 2 ]*cos(Phasenraum_quasie[ Zaehler ][ 0] ) > 0){
			for (int i = 0; i < 4; ++i)
			{
				Datei_quasi << ( Phasenraum_quasie[ Zaehler ][ i ] + Phasenraum_quasie[ Zaehler ][ i - 1 ] )/2.0 << "\t\t" ;
			}
			Datei_quasi << std::endl;
		}
		if( Phasenraum_Chaos[ Zaehler ][ 1 ]/Phasenraum_Chaos[ Zaehler - 1 ][ 1 ] < 0 && Phasenraum_Chaos[ Zaehler ][ 3 ] + Phasenraum_Chaos[ Zaehler ][ 2 ]*cos(Phasenraum_Chaos[ Zaehler ][ 0] ) > 0){
			for (int i = 0; i < 4; ++i)
			{
				Datei_Chaos << ( Phasenraum_Chaos[ Zaehler ][ i ] + Phasenraum_Chaos[ Zaehler ][ i - 1 ] )/2.0 << "\t\t" ;
			}
			Datei_Chaos << std::endl;
		}
	}

	return 0;
}