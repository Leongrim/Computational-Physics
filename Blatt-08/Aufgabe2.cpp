#include <iostream>
#include <cmath>
#include <stdint.h>
#include "fstream"
#include <string>

double Logistische( int Anzahl , double WertR , double Startwert){
	double XWert = Startwert;
	for (int i = 0; i < Anzahl; ++i)
	{
		XWert = WertR * XWert * ( 1.0 - XWert );
	}
	return XWert;
}
double g_n_r( double XWert , double RWert , int Anzahl ){
	int ReAnzahl = 1;
	for (int i = 0; i < Anzahl; ++i)
	{
		ReAnzahl *= 2;
	}
	return 0.5 - Logistische( ReAnzahl , RWert , XWert );
}
double Nulstellen( int Anzahl , double StartX , double AnfangsWert , double EndWert , double (*Funktion)( double , double , int ) ){		
	double WertX = AnfangsWert;
	double WertY = EndWert;
	double WertZ;
	double Y_n = Funktion( StartX , WertY , Anzahl );
	double X_n = Funktion( StartX , WertX , Anzahl );
	double Z_n;
	double Genauigkeit = 1e-7;
	do{
		if (std::abs(X_n) < Genauigkeit)
		{
			return WertX;
		}
		if (std::abs(Y_n) < Genauigkeit)
		{
			return WertY;
		}
		WertZ = (WertX*Y_n - WertY*X_n)/(Y_n - X_n);
		Z_n = g_n_r( StartX , WertZ , Anzahl );
		if (X_n*Z_n < 0)
		{
			WertY = WertZ;
			Y_n = g_n_r( StartX , WertY , Anzahl );
		}else{
			WertX = WertZ;
			X_n = g_n_r( StartX , WertX , Anzahl );
		}
	}while(std::abs((WertX - WertY)) > Genauigkeit);
	return WertX;
}
void AufgabenA(){
	double WertR;
	double WertInf = 3.5699;
	double WertX = 0.5;
	std::fstream Datei;
	double RAnzahl = 1e4;
	Datei.open("Ergebnisse/Ergebnis_2_a.txt" , std::ios::trunc | std::ios::out );

	for (int i = 0; i < RAnzahl; ++i)
	{
		WertR = (double) WertInf/RAnzahl*i;
		Datei << WertR << "\t" ;
		for (int Anzahl = 0 ; Anzahl < 4; ++Anzahl)
		{
			Datei << g_n_r(WertX , WertR , Anzahl ) << "\t";
		}
		Datei << "\n";

	}
}

void AufgabenB(){
	double IntervallAnfang[4]{ 1.9 , 3.2 , 3.48 , 3.54 };
	double IntervallEnde[4]{ 2.1 , 3.25 , 3.50 , 3.56 };
	double StartX = 0.5;
	double Nullen[4];
	for (int Anzahl = 0; Anzahl < 4; ++Anzahl)
	{
		Nullen[ Anzahl ] = Nulstellen( Anzahl , StartX , IntervallAnfang[ Anzahl ] , IntervallEnde[ Anzahl ] , g_n_r );
		std::cout << "Nustelle für n=" << Anzahl << ": " << Nullen[ Anzahl ] << std::endl;
	}
	std::cout << "Feigenbaumkonstante: " << (Nullen[2] - Nullen[1])/(Nullen[3] - Nullen[2]) << std::endl;
}

int main(){

	AufgabenA();
	AufgabenB();

	return 0;
}