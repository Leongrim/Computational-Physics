#include <iostream>
#include <cmath>
#include <stdint.h>
#include "fstream"
#include <string>


void logistik( int Iterationen , double AnfangswertWert , double R , std::string Save){
	std::fstream Datei;
	Datei.open( (Save + ".txt").data() , std::ios::trunc | std::ios::out );
	double x = AnfangswertWert;
	double x_temp;
	Datei << "# R = " << R << std::endl;
	for (int i = 0; i < Iterationen; ++i)
	{
		x_temp = R*x*(1.0-x);
		Datei << x << "\t" << x_temp << std::endl;
		Datei << x_temp << "\t" << x_temp << std::endl;
		x = x_temp;
	}
}
void Kubische( int Iterationen , double AnfangswertWert , double R , std::string Save){
	std::fstream Datei;
	Datei.open( (Save + ".txt").data() , std::ios::trunc | std::ios::out );
	double x = AnfangswertWert;
	double x_temp;
	Datei << "# R = " << R << std::endl;
	for (int i = 0; i < Iterationen; ++i)
	{
		x_temp = R*x - x*x*x;
		Datei << x << "\t" << x_temp << std::endl;
		Datei << x_temp << "\t" << x_temp << std::endl;
		x = x_temp;
	}
}

void PrintFunktion( void Funktion( int , double , double , std::string ) , int Iterationen , double Startwert , double Schrittweite , double WertR , int Anzahl , std::string Datei){
	for (int i = 0; i < Anzahl ; ++i)
	{
		WertR += Schrittweite ;
		Funktion( Iterationen , Startwert , WertR , (std::string) Datei + std::to_string( i + 1 ));
	}
}


int main(){
	int Iterationen = 100;
	double Startwert = 0.01;
	double WertR = 1.0;
	double Schrittweite = 0.03;
	std::string Datei = "Ergebnisse/Aufgabe1a/Ergebnis";
	int Anzahl = 100;
	PrintFunktion( logistik , Iterationen , Startwert , Schrittweite , WertR , Anzahl , Datei);
	Datei = "Ergebnisse/Aufgabe1b/Ergebnis";
	PrintFunktion( Kubische , Iterationen , Startwert , Schrittweite , WertR , Anzahl , Datei);

	return 0;
}