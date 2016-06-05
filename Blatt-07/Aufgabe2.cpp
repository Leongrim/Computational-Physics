#include <iostream>
#include <cmath>
#include <stdint.h>
#include "fstream"
#include <string>

void RND( int64_t& Seed , int64_t Modulo  , int64_t Multiplikator , int64_t Summand ){
	Seed = (Multiplikator * Seed + Summand )%Modulo;
}

void Neumann( std::string Datei , int Anzahl , int BinAnzahl ,  int64_t Seed , int64_t Modulo = 2147483648 - 1 , int64_t Multiplikator = 16807, int64_t Summand = 0)
{
	double Norm = (double) BinAnzahl/(Anzahl * M_PI);
	double Zufall1 = 0.0;
	double Zufall2 = 0.0;
	double Zufall3 = 0.0;
	int64_t Bin[ BinAnzahl ];
	int64_t bin;
	for (int i = 0; i < BinAnzahl ; ++i)
	{
		Bin[ i ] = 0;
	}
	for (int i = 0; i < Anzahl; ++i)
	{
		do
		{
			RND( Seed , Modulo, Multiplikator , Summand );
			Zufall1 = 0.5*Seed/Modulo;
			RND( Seed , Modulo, Multiplikator , Summand );
			Zufall2 = ((double) Seed/Modulo)*M_PI;
			Zufall3 = 0.5*sin( Zufall2 );
		} while ( Zufall1 > Zufall3 );
		bin = floor( (double) Zufall2 * BinAnzahl / M_PI );
		Bin[ bin ] += 1;
	}
	std::fstream Save;
	Save.open( (Datei + ".txt").data() , std::ios::trunc | std::ios::out);
	for (int i = 0; i < BinAnzahl; ++i)
	{
		Save << (double) (i + 1) * M_PI / BinAnzahl << "\t" << Bin[ i ] << "\t" << (double) Bin[ i ]*Norm << "\n";
	}
}

void Gaus_Grenzwert( std::string Datei , int N , int Anzahl , int BinAnzahl ,  int64_t Seed , int64_t Modulo = 2147483648 - 1 , int64_t Multiplikator = 16807, int64_t Summand = 0){
	double Zufall;
	int64_t Bin[ BinAnzahl ];
	double Norm = (double) BinAnzahl/ ( N * Anzahl);
	for (int i = 0; i < BinAnzahl; ++i)
	{
		Bin[ i ] = 0;
	}
	int64_t bin;
	for (int i = 0; i < Anzahl; ++i)
	{
		RND( Seed , Modulo, Multiplikator , Summand );
		Zufall = (double) pow( Seed/Modulo , 1.0/3.0);
		bin = floor((double) Zufall);
	}
	for (int i = 0; i < Anzahl; ++i)
	{
		Zufall = 0;
		for (int j = 0; j < N; ++j)
		{
			RND( Seed , Modulo, Multiplikator , Summand );
			Zufall += (double) Seed/Modulo;
		}
		bin = floor( (double) Zufall * BinAnzahl / N);
		Bin[ bin ] += 1;
	}
	std::fstream Save;
	Save.open( (Datei + ".txt").data() , std::ios::trunc | std::ios::out);
	for (int j = 0; j < BinAnzahl; ++j)
	{
		Save << (double) (j + 1) * N /BinAnzahl - N  *0.5  << "\t" << Bin[ j ] << "\t" << (double)Bin[ j ]*Norm << "\n";
	}
	Save.close();
}
void Trafo( std::string Datei , int Anzahl , int BinAnzahl ,  int64_t Seed , int64_t Modulo = 2147483648 - 1 , int64_t Multiplikator = 16807, int64_t Summand = 0)
{
	double Zufall;
	int64_t Bin[ BinAnzahl ];
	double Norm = (double) BinAnzahl / Anzahl;
	for (int i = 0; i < BinAnzahl; ++i)
	{
		Bin[ i ] = 0;
	}
	int64_t bin;
	for (int i = 0; i < Anzahl; ++i)
	{
		RND( Seed , Modulo, Multiplikator , Summand );
		Zufall = pow((double) Seed / Modulo , 1.0/3.0);
		bin = floor((double) Zufall*BinAnzahl);
		Bin[ bin ] += 1;
	}
	std::fstream Save;
	Save.open( (Datei + ".txt").data() , std::ios::trunc | std::ios::out);
	for (int i = 0; i < BinAnzahl; ++i)
	{
		Save << (i+1)/BinAnzahl << "\t" << Bin[ i ] << "\t" << (double) Bin[ i ]*Norm<< "\n";
	}

}
int main(){

	int Anzahl = 1e6;
	int BinAnzahl = 100;
	int64_t Seed = 1234;
	std::string Ergebnis = "Ergebnisse/Ergebnis_2_b";
	Gaus_Grenzwert( Ergebnis , 12 , Anzahl , BinAnzahl , Seed );

	Ergebnis = "Ergebnisse/Ergebnis_2_c";
	Neumann( Ergebnis , Anzahl , BinAnzahl , Seed );
	
	Ergebnis = "Ergebnisse/Ergebnis_2_d";
	Trafo( Ergebnis , Anzahl , BinAnzahl , Seed );

	return 0;
}