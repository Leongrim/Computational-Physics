#include <iostream>
#include <cmath>
#include <stdint.h>
#include "fstream"
#include <string>


void logistik( double& Wert , double RWert ){
	Wert = RWert*Wert*( 1.0 - Wert );
}
void Kubische( double& Wert , double RWert ){
	Wert = RWert * Wert - Wert * Wert * Wert;
}

void PrintFunktion( void Funktion( double& , double ) , int Iterationen , double StartX , double Startwert , double Endwert , int Anzahl , int AnzahlSpeicher, std::string Datei){
	double Schrittweite = abs( Endwert - Startwert )/(double) Anzahl;
	double RWert = Startwert;
	double XWert;
	std::fstream Save;
	bool Abfrage = false;
	if ( StartX < 0.0)
	{
		Abfrage = true;
	}
	Save.open(Datei+".txt" , std::ios::trunc | std::ios::out );
	XWert = StartX;
	for (int i = 0; i < Anzahl ; ++i)
	{
		XWert = StartX;
		for (int j = 0; j < Iterationen; ++j)
		{
			Funktion( XWert , RWert );
			if( j > Iterationen - AnzahlSpeicher){
				Save << RWert << "\t" << XWert << "\n";
			}
		}
		RWert += Schrittweite;
	}
	if (Abfrage)
	{
		RWert = Startwert;
		XWert = -1.0*StartX;
		for (int i = 0; i < Anzahl ; ++i)
		{
		XWert = -1.0*StartX;
			for (int j = 0; j < Iterationen; ++j)
			{
				Funktion( XWert , RWert );
				if( j > Iterationen - AnzahlSpeicher){
					Save << RWert << "\t" << XWert << "\n";
				}
			}
			RWert += Schrittweite;
		}
	}
	Save.close();
}


int main(){
	int Iterationen = 1000;
	double StartX = 0.5;
	double Startwert = 3.0;
	double Endwert = 5.0;
	int Anzahl = 1000;
	int AnzahlSpeicher = 500;
	std::string Datei = "Ergebnisse/Ergebnis_1_A";
	PrintFunktion( logistik , Iterationen , StartX , Startwert , Endwert , Anzahl , AnzahlSpeicher, Datei);
	Startwert = 2.0;
	Endwert = 4.0;
	Datei = "Ergebnisse/Ergebnis_1_B";
	PrintFunktion( Kubische , Iterationen , -StartX , Startwert , Endwert , Anzahl , AnzahlSpeicher, Datei);

	return 0;
}