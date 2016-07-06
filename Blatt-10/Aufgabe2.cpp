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
double EINS(double x , double y){
	return 1.0;
}
double EXP(double x , double y){
	return std::exp( - x*x );
}
double pi_print(int64_t Datenanzahl ){
	double Zufall1;
	double Zufall2;

	int Zaehler = 0;
	for (int i = 0; i < Datenanzahl; ++i)
	{
		Zufall1 = 2.0*RANDOM() - 1.0;
		Zufall1 = Zufall1*Zufall1;

		Zufall2 = 2.0* RANDOM() - 1.0;
		Zufall2 = Zufall2*Zufall2;
		if (Zufall1 + Zufall2 < 1)
		{
			Zaehler++;
		}
	}
	return (double) 4*Zaehler/(Datenanzahl);
}
double print_Ellipse(int64_t Datenanzahl , double A , double B , double (*Funktion)(double , double) ){
	double Zufall1;
	double ZufallX;
	double ZufallY;
	double Zufall2;
	double Zaehler = 0;
	for (int i = 0; i < Datenanzahl; ++i)
	{
		ZufallX = A*RANDOM();
		Zufall1= ZufallX*ZufallX;

		ZufallY = B*RANDOM() ;
		Zufall2 = ZufallY*ZufallY;
		if ( 1 > Zufall1/(A*A) + Zufall2/(B*B))
		{
			Zaehler += Funktion( ZufallX , ZufallY );
		}
	}
	return 4*A*B*Zaehler/Datenanzahl;
}
void Print_A(){
	std::fstream Datei;
	Datei.open("Ergebnisse/Ergebnis_2_A.txt" , std::ios::trunc | std::ios::out );
	int64_t Datenanzahl = 1e6;
	std::cout << "pi ist ungefaehr: " << pi_print( Datenanzahl ) << std::endl;
	int64_t Anzahl = 10;
	double pi;
	std::cout << "Vergleichsergebnis: " << M_PI << "\n";
	for (int i = 0; i < 7; ++i)
	{
		pi = pi_print( Anzahl );
		std::cout << "pi= " << pi <<"\t Error(pi)= " << std::abs( M_PI - pi )/M_PI << "\t für die Anzahl: 10^" << i+1 << "\n";
		Datei << Anzahl << "\t" << std::abs( M_PI - pi )/M_PI << "\n";
		Anzahl *= 10;
	}
}
void Print_B(){
	int64_t Anzahl = 1e3;
	double pi;
	double PI_Array[ Anzahl ];
	double PI_MAX=2.0;
	double PI_MIN=4.0;
	int bin;
	int BinAnzahl =20;
	int Histo[ BinAnzahl ];
	for (int i = 0; i < BinAnzahl; ++i)
	{
		Histo[ i ] = 0;
	}
	std::fstream Datei;
	Datei.open("Ergebnisse/Ergebnis_2_B.txt" , std::ios::trunc | std::ios::out );
	for (int i = 0; i < Anzahl; ++i)
	{
		pi = pi_print( Anzahl );
		PI_Array[ i ] = pi ;
		if( pi < PI_MIN ){
			PI_MIN = pi;
		}else if(pi > PI_MAX){
			PI_MAX = pi;
		}
	}
	for (int i = 0; i < Anzahl; ++i)
	{
		bin = floor( (double) (PI_Array[ i ] - PI_MIN) * BinAnzahl/(PI_MAX - PI_MIN));
		Histo[ bin ] += 1;
	}
	for (int i = 0; i < BinAnzahl; ++i)
	{
		Datei << (double) i*( PI_MAX - PI_MIN)/BinAnzahl + PI_MIN << "\t" << Histo[ i ] << "\t" << (double) Histo[ i ]/Anzahl << "\n";
	}
	Datei.close();
}
void Print_C(){
	int64_t Datenanzahl = 1e5;
	double Schrittweite = 0.01;
	int Anzahl = 2000;
	double a = Schrittweite;
	double b = 1.0;
	double Flaeche;

	std::fstream Datei;
	Datei.open("Ergebnisse/Ergebnis_2_C.txt" , std::ios::trunc | std::ios::out);
	for (int i = 0; i < Anzahl; ++i)
	{
		Flaeche = print_Ellipse( Datenanzahl , a , b , EINS );
		Datei << a << "\t" << b << "\t" << Flaeche << "\t" << Flaeche/(a*b) << "\n";
		a += Schrittweite;
	}
}
void Print_D(){
	int64_t Datenanzahl = 1e6;
	double A = std::sqrt(2.0);
	double B = 1.0;
	int Anzahl = 100;
	double Werte[ Anzahl ];
	double Sigma = 0.0;
	double mean = 0.0;
	for (int i = 0; i < Anzahl; ++i)
	{
		Werte[ i ] = print_Ellipse( Datenanzahl , A , B , EXP );
	}
	for (int i = 0; i < Anzahl; ++i)
	{
		mean += Werte[ i ];
	}
	mean = (double) mean / Anzahl ;
	for (int i = 0; i < Anzahl; ++i)
	{
		Sigma += (Werte[ i ] - mean )*(Werte[ i ] - mean );
	}
	Sigma = std::sqrt((double) Sigma / ( Anzahl - 1 ) );

	std::cout << mean << "+-" << Sigma << "\n";
}

int main(){

	Print_A();
	Print_B();
	Print_C();
	Print_D();
	
	return 0;
}