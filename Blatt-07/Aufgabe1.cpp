#include <iostream>
#include <cmath>
#include <stdint.h>
#include "fstream"
#include <string>

void RND( int64_t& Seed , int64_t Modulo , int64_t Multiplikator , int64_t Summand ){
	Seed = (Multiplikator * Seed + Summand )%Modulo;
}
void Aufgabe( std::string Datei , int BinAnzahl , int64_t Seed , int64_t Modulo , int64_t Multiplikator , int64_t Summand , int Anzahl){
	int64_t Seed_Temp = Seed;
	int Histo[ BinAnzahl ];
	for (int i = 0; i < BinAnzahl; ++i)
	{
		Histo[ i ] = 0 ;
	}
	int bin;
	std::fstream Save;
	Save.open( (Datei + "_B.txt").data() , std::ios::trunc | std::ios::out );
	for (int i = 0; i < Anzahl; ++i)
	{
		RND( Seed_Temp , Modulo , Multiplikator , Summand);
		bin = floor( (double) Seed_Temp/Modulo*BinAnzahl);
		Histo[ bin ] += 1;
	}
	for (int i = 0; i < BinAnzahl; ++i)
	{
		Save << (double) i/BinAnzahl << "\t" << Histo[ i ] << "\n";
	}
	Save.close();

	Save.open( (Datei + "_C.txt").data() , std::ios::trunc | std::ios::out );
	Seed_Temp = Seed;
	if (Anzahl > Modulo)
	{
		Anzahl = Modulo - 1;
	}
	for (int i = 0; i < Anzahl/2; ++i)
	{
		RND( Seed_Temp , Modulo , Multiplikator , Summand);
		Save << (double) Seed_Temp/Modulo << "\t";
		RND( Seed_Temp , Modulo , Multiplikator , Summand);
		Save << (double) Seed_Temp/Modulo << "\n";
	}
	Save.close();
}


int main(){
	int Anzahl = 1e5;
	int64_t Seed = 1234;
	int64_t Modulo = 6075;
	int64_t Multiplikator = 20;
	int64_t Summand = 120;
	int BinAnzahl = 10;
	std::string Datei = "Ergebnisse/Ergebnis_1_1";
	Aufgabe( Datei , BinAnzahl , Seed , Modulo , Multiplikator , Summand , Anzahl);

	Seed = 1234;
	Modulo = 256;
	Multiplikator = 137;
	Summand = 187;
	Datei = "Ergebnisse/Ergebnis_1_2";
	Aufgabe( Datei , BinAnzahl , Seed , Modulo , Multiplikator , Summand , Anzahl);

	Anzahl = 1e5;
	Seed = 123456789;
	Modulo = 2147483648;
	Multiplikator = 65539;
	Summand = 0;
	Datei = "Ergebnisse/Ergebnis_1_3";
	Aufgabe( Datei , BinAnzahl , Seed , Modulo , Multiplikator , Summand , Anzahl);

	Anzahl = 1e5;
	Seed = 1234;
	Modulo = 2147483648 - 1;
	Multiplikator = 16807;
	Summand = 0;
	Datei = "Ergebnisse/Ergebnis_1_4";
	Aufgabe( Datei , BinAnzahl , Seed , Modulo , Multiplikator , Summand , Anzahl);

	return 0;
}