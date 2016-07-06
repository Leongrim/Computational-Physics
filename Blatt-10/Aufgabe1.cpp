#include <iostream>
#include <cmath>
#include <fstream>
#include <random>
#define _USE_MATH_DIFINES

std::mt19937 generator;

double RANDOM(){
	std::uniform_real_distribution<double> distribution(0.0 , 1.0);
	return distribution(generator);
}
void RND_Sin( double& Zufall ){
	Zufall = RANDOM();
	Zufall = std::acos( - 2.0 * Zufall + 1.0 );
}
double Omega( double Zufall ){
	double cos_ = std::cos( Zufall );
	return ( 1.5*cos_*cos_ - 0.5 );
}

int main(){
	std::fstream Datei;
	Datei.open("Ergebnisse/Ergebnis_1_A.txt" , std::ios::trunc | std::ios::out );
	std::fstream Datei_B;
	Datei_B.open("Ergebnisse/Ergebnis_1_B.txt" , std::ios::trunc | std::ios::out );
	double Zufall;
	double Zufall_Omega;
	int64_t Datenanzahl = 1e4;
	int BinAnzahl = 100;
	int64_t Hist[ BinAnzahl ];
	int64_t Hist_Omega[ BinAnzahl ];
	int bin;
	double Mittelwert_Omega = 0.0;
	for (int i = 0; i < BinAnzahl; ++i)
	{
		Hist[ i ] = 0 ;
		Hist_Omega[ i ] = 0 ;
	}
	for (int64_t i = 0 ; i < Datenanzahl ; ++i)
	{
		RND_Sin( Zufall );
		Zufall_Omega = Omega( Zufall ); 
		bin = floor( (double) BinAnzahl * Zufall / M_PI );
		Hist[ bin ] += 1;
		bin = floor((double) (Zufall_Omega+ 0.5) * BinAnzahl/1.5);
		Mittelwert_Omega += Zufall_Omega;
		Hist_Omega[ bin ] += 1 ;
	}
	Mittelwert_Omega = (double) Mittelwert_Omega/Datenanzahl;
	std::cout << "Mittelwert von Omega = " << Mittelwert_Omega << std::endl;
	for (int i = 0; i < BinAnzahl; ++i)
	{
		Datei << (double) i * M_PI /BinAnzahl << "\t" << Hist[ i ] << "\t" << (double) Hist[ i ]/Datenanzahl * BinAnzahl / M_PI << "\n";
		Datei_B << (double) i * 1.5/BinAnzahl -0.5 << "\t" << Hist_Omega[ i ] << "\t" << (double) Hist_Omega[ i ] / Datenanzahl * BinAnzahl / 1.5 << "\n";
	}
	Datei.close();

	return 0;
}