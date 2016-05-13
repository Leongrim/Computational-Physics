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
void Y_Plus( double Breite , double &theta_1 , double &theta_2 , double &theta_geschwindigkeit_1 , double &theta_geschwindigkeit_2){ // Funktion die einen Schritt des Runge-Kutta-Verfahrens ausführt und die übergebenen Parameter überschreibt
	double Y_n[4];
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
	theta_1 = Y_n[0];
	theta_2 = Y_n[1];
	theta_geschwindigkeit_1 = Y_n[2];
	theta_geschwindigkeit_2 = Y_n[3];

}
bool Vorzeichen( double A , double B){ //überprüfung opb ein Vorzeichen Wechsel statt gefunden hat
	if( A > 0 && B < 0)
	{
		return true;
	}else if( A < 0 && B > 0)
	{
		return true;
	}else return false;
}
bool Bedingung( double* array){ // überprüfung ob ein Rechtsdurchlauf statt findet
	if( array[3] + array[2] * cos(array[0]) > 0){
		return true;
	}else return false;
}
void Poincare( double Breite , double Zeit , double* Phasenraum , std::fstream& Datei){ //Funktion die die Poincare schitte eines Doppelpendels bestimmt und in eine Datei schreibt
	double temp[4];
	const uint Anzahl = (uint) Zeit/Breite; 
	for (int i = 0; i < 4; ++i)
	{
		temp[i] = Phasenraum[i];
	}
 
	for( uint Zaehler = 0 ; Zaehler <  Anzahl  ; Zaehler++){
		for (int i = 0; i < 4; ++i)
		{
			Y_Plus( Breite , Phasenraum[0] , Phasenraum[1] , Phasenraum[2] , Phasenraum[3]);
		}
		//if( std::abs(Phasenraum[ 1 ]) < 1e-4 && Phasenraum[ 3 ] + Phasenraum[ 2 ]*cos(Phasenraum[ 0] ) > 0)
		if( Vorzeichen( Phasenraum[1] , temp[1] ))
		{
			if( Bedingung( Phasenraum ))
			{
				for (int i = 0; i < 4; ++i)
				{
					Datei <<  ( Phasenraum[ i ] + temp[ i ] )/2.0 << "\t\t" ;
				}
				Datei << std::endl;				
			}

		}
		for (int i = 0; i < 4; ++i)
		{
			temp[i] = Phasenraum[i];
		}
	}

}

int main(){

	std::fstream Datei;
	Datei.open( "Ergebnisse/Ergebnis_2_C_Chaos.txt" , std::ios::trunc | std::ios::out);
	std::fstream Datei_quasi;
	double Breite = 1e-2;
	double Zeit = 5e3;
	double theta_v_quasi = 11.382;
	double theta_v_Chaos = 4.472;
	//double theta_v_Chaos = theta_v_quasi;

	/*E=E_kin muss = E' sein*/

	double Phasenraum[4];
	Phasenraum[0] = 0.0;
	Phasenraum[1] = 0.0;
	Phasenraum[2] = 0.0;
	Phasenraum[3] = theta_v_Chaos;//*/
	Poincare(Breite , Zeit , Phasenraum , Datei);

	// E' mit theta_V_2 = 0.0 und theta_1 = theta_2 = 0.0
	Phasenraum[0] = 0.0;
	Phasenraum[1] = 0.0;
	Phasenraum[2] = theta_v_Chaos/sqrt(2);
	Phasenraum[3] = 0.0;
	Poincare(Breite , Zeit , Phasenraum , Datei);

	// E' mit theta_V_1 = theta_V_2 und theta_1 = theta_2 = 0.0
	Phasenraum[0] = 0.0;
	Phasenraum[1] = 0.0;
	Phasenraum[2] = 1.0/2.0*theta_v_Chaos;
	Phasenraum[3] = 1.0/2.0*theta_v_Chaos;
	Poincare(Breite , Zeit , Phasenraum , Datei);

	//E' mit mit theta_v_1 =0.5 theta_v_2 und theta_1=theta_2 =0.0
	Phasenraum[0] = 0.0;
	Phasenraum[1] = 0.0;
	Phasenraum[2] = 0.5*theta_v_Chaos/sqrt(2.0);
	Phasenraum[3] = theta_v_Chaos/sqrt(2.0);
	Poincare(Breite , Zeit , Phasenraum , Datei);

	//theta_v_1 = 0.25 theta_V_2 und theta_1 = theta_2 = 0.0
	Phasenraum[0] = 0.0;
	Phasenraum[1] = 0.0;
	Phasenraum[2] = 1.0/4.0*theta_v_Chaos*sqrt(8.0/11.0);
	Phasenraum[3] = theta_v_Chaos*sqrt(8.0/11.0);
	Poincare(Breite , Zeit , Phasenraum , Datei);

	//thete'_v_2 = 0.0 , theta'_v_1 = alpha theta_v_2 und theta'_1 = 0.0 
	double alpha = 0.25;
	Phasenraum[0] = 0.0;
	Phasenraum[1] = acos( ( alpha*alpha - 0.5 ) * theta_v_Chaos*theta_v_Chaos / 9.81 + 1.0 );
	Phasenraum[2] = alpha * theta_v_Chaos;
	Phasenraum[3] = 0.0;
	Poincare(Breite , Zeit , Phasenraum , Datei);

	alpha = 0.1;
	Phasenraum[0] = 0.0;
	Phasenraum[1] = acos( ( alpha*alpha - 0.5 ) * theta_v_Chaos*theta_v_Chaos / 9.81 + 1.0 );
	Phasenraum[2] = alpha * theta_v_Chaos;
	Phasenraum[3] = 0.0;
	Poincare(Breite , Zeit , Phasenraum , Datei);

	alpha = 0.2;
	Phasenraum[0] = 0.0;
	Phasenraum[1] = acos( ( alpha*alpha - 0.5 ) * theta_v_Chaos*theta_v_Chaos / 9.81 + 1.0 );
	Phasenraum[2] = alpha * theta_v_Chaos;
	Phasenraum[3] = 0.0;
	Poincare(Breite , Zeit , Phasenraum , Datei);

	alpha = 0.0;
	Phasenraum[0] = 0.0;
	Phasenraum[1] = acos( ( alpha*alpha - 0.5 ) * theta_v_Chaos*theta_v_Chaos / 9.81 + 1.0 );
	Phasenraum[2] = alpha * theta_v_Chaos;
	Phasenraum[3] = 0.0;
	Poincare(Breite , Zeit , Phasenraum , Datei);

	Datei.close();
	Datei.open( "Ergebnisse/Ergebnis_2_C_Harmonisch.txt" , std::ios::trunc | std::ios::out);
	Phasenraum[0] = 0.1;
	Phasenraum[1] = sqrt(2)*Phasenraum[0];
	Phasenraum[2] = 0.0;
	Phasenraum[3] = 0.0;
	Poincare(Breite , Zeit , Phasenraum , Datei);


	return 0;
}