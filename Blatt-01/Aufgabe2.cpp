#include "iostream"
#include "cmath"
#include "math.h"

double Quadrat( double x){ //QUadratische Funktion
	return x*x;
}
double FunktionA( double x){
	return  exp(-x)/x;
}
double FunktionB( double x){ //x*sin(1/x) subtituiert mit u = 1/x => -sin(x)/x^3, Grenzen müssen angepasst werden
	return sin( x ) * 1/(x*x*x);
}

double Trapez( double (*Integrand) (double) , double Untergrenze , double Obergrenze , unsigned int  Intervall){ //Integration mithilde der Trapezregel
	double Breite = (Obergrenze - Untergrenze)/Intervall;
	double integration = ( Integrand( Obergrenze ) + Integrand( Untergrenze ) )*Breite/2.0;
	for (double i = Untergrenze + Breite; i < Obergrenze ; i = i + Breite)
	{
		integration = integration + Breite* Integrand( i );
	}
	return integration;
}
double Mittelpunktregel(double (*Integrand) (double) , double Untergrenze , double Obergrenze , unsigned int Intervall){
	double Breite = (Obergrenze - Untergrenze)/Intervall;
	double integration = 0.0;
	for (double i = Untergrenze + 1.0/2.0 * Breite ; i < Obergrenze ; i = i + Breite)
	{
		integration = integration + Breite * Integrand( i );
	}
	return integration;
}
double Simpsonregel(double (*Integrand) (double) , double Untergrenze , double Obergrenze , unsigned int Intervall){
	double Breite = ( Obergrenze - Untergrenze)/Intervall;
	double integration = Breite*( 1.0/3.0 * Integrand( Untergrenze ) + 1.0/3.0 * Integrand( Obergrenze ));
	for (int i = 1; i < Intervall; i++)
	{
		if(i % 2 == 0){
			integration = integration + Breite*2.0/3.0*Integrand(Untergrenze + i * Breite );
		}
		else {
			integration = integration + Breite*4.0/3.0*Integrand( Untergrenze + i*Breite);
		}
	}
	return integration;
}


int main(){

	double (*Funktion) (double) = *Quadrat;

	double Anfang = 1;
	double Ende = 2;
	double Intervallanzahl = 100;
	double Intervallbreite = 1/Intervallanzahl;

	std::cout << "==========================================================================="<< std::endl << "Lösung des Integrals von x*x im bereich von 1 zu 2" << std::endl;
	std::cout << "Integral mittels der Trapezregel:"      	<< Trapez( Funktion , Anfang , Ende , Intervallanzahl)<< std::endl;
	
	std::cout << "Integral mittels der Mittelpunktregel:" 	<< Mittelpunktregel( Funktion , Anfang , Ende , Intervallanzahl)<< std::endl;

	std::cout << "Integral mittels der Simpsonpunktregel:" 	<< Simpsonregel( Funktion , Anfang , Ende , Intervallanzahl)<< std::endl;

	Anfang = 1;
	Ende = 100;
	Intervallanzahl = 1000;
	Intervallbreite = 1/Intervallanzahl;
	std::cout << "===========================================================================" << std::endl << "Lösung des Integrals für die Funkiton exp(-x)/x von 1 bis 100" << std::endl;

	std::cout << "Integral mittels der Trapezregel:" << Trapez( FunktionA , Anfang , Ende , Intervallanzahl)<< std::endl;
	
	std::cout << "Integral mittels der Mittelpunktregel:" << Mittelpunktregel( FunktionA , Anfang , Ende , Intervallanzahl)<< std::endl;

	std::cout << "Integral mittels der Simpsonpunktregel:" << Simpsonregel( FunktionA , Anfang , Ende , Intervallanzahl)<< std::endl;

	Anfang = 1;
	Ende = 100;
	Intervallanzahl = 4000;
	Intervallbreite = (Ende - Anfang)/Intervallanzahl;
	std::cout << "===========================================================================" << std::endl << "Lösung des Integrals für die Funkiton x sin(1/x) von 0 bis 1" << std::endl;

	std::cout << "Integral mittels der Trapezregel:" << Trapez( FunktionB , Anfang , Ende , Intervallanzahl)<< std::endl;
	
	std::cout << "Integral mittels der Mittelpunktregel:" << Mittelpunktregel( FunktionB , Anfang , Ende , Intervallanzahl)<< std::endl;

	std::cout << "Integral mittels der Simpsonpunktregel:" << Simpsonregel( FunktionB , Anfang , Ende , Intervallanzahl)<< std::endl;	
	std::cout << "===========================================================================" << std::endl << "Trapezregel in genauigkeit 10^-4 für exp(-x)/x" << std::endl;
	Anfang = 1;
	Ende = 1000;
	Intervallanzahl = 1000;
	Intervallbreite = (Ende - Anfang)/Intervallanzahl;
	double Abfrage1 = Trapez( FunktionA , Anfang , Ende , Intervallanzahl);
	double Abfrage2;
	do{
		Abfrage2 = Abfrage1;
		Intervallbreite *= 0.5;
		Intervallanzahl = (Ende -Anfang)/Intervallbreite;
		Abfrage1 = Trapez( FunktionA , Anfang , Ende , Intervallanzahl);
	} while( std::abs( Abfrage1 - Abfrage2 )/Abfrage1 > 0.0001);

	std::cout << "Ergebnis: " << Abfrage1 << '\t' << "Breite: " << (Ende - Anfang)/Intervallanzahl <<'\t' <<  "Intervallanzahl: " << Intervallanzahl << std::endl;
	std::cout << "===========================================================================" << std::endl << "Mittelpunktregel in genauigkeit 10^-4 für exp(-x)/x" << std::endl;
	Intervallanzahl = 1000;
	Intervallbreite = (Ende - Anfang)/Intervallanzahl;
	Abfrage1 = Mittelpunktregel( FunktionA , Anfang , Ende , Intervallanzahl);
	Abfrage2;
	do{
		Abfrage2 = Abfrage1;
		Intervallbreite *= 0.5;
		Intervallanzahl = (Ende -Anfang)/Intervallbreite;
		Abfrage1 = Mittelpunktregel( FunktionA , Anfang , Ende , Intervallanzahl);	
	} while( std::abs( Abfrage1 - Abfrage2 )/Abfrage1 > 0.0001);
	std::cout << "Ergebnis: "<<Abfrage1 << '\t' << "Breite:" << (Ende - Anfang)/Intervallanzahl <<'\t' <<  "Intervallanzahl: " << Intervallanzahl << std::endl;	
	std::cout << "===========================================================================" << std::endl << "Simpsonsregel in genauigkeit 10^-4 für exp(-x)/x" << std::endl;
	Intervallanzahl = 1000;
	Intervallbreite = (Ende - Anfang)/Intervallanzahl;
	Abfrage1 = Simpsonregel( FunktionA , Anfang , Ende , Intervallanzahl);
	Abfrage2;
	do{
		Abfrage2 = Abfrage1;
		Intervallbreite *= 0.5;
		Intervallanzahl = (Ende -Anfang)/Intervallbreite;
		Abfrage1 = Simpsonregel( FunktionA , Anfang , Ende , Intervallanzahl);	
	} while( std::abs( Abfrage1 - Abfrage2 )/Abfrage1 > 0.0001);

	std::cout << "Ergebnis: " << Abfrage1 << '\t' << "Breite: " << (Ende - Anfang)/Intervallanzahl<< '\t' << "Intervallanzahl: " << Intervallanzahl << std::endl;

	std::cout << "===========================================================================" << std::endl << "Trapezregel in genauigkeit 10^-4 für x sin1/x" << std::endl;
	Anfang = 1;
	Ende = 1000;
	Intervallanzahl = 1000;
	Intervallbreite = (Ende - Anfang)/Intervallanzahl;
	Abfrage1 = Trapez( FunktionB , Anfang , Ende , Intervallanzahl);
	Abfrage2;
	do{
		Abfrage2 = Abfrage1;
		Intervallbreite *= 0.5;
		Intervallanzahl = (Ende -Anfang)/Intervallbreite;
		Abfrage1 = Trapez( FunktionB , Anfang , Ende , Intervallanzahl);
	} while( std::abs( Abfrage1 - Abfrage2 )/Abfrage1 > 0.0001);

	std::cout << "Ergebnis: " << Abfrage1 << '\t' << "Breite : " << (Ende - Anfang)/Intervallanzahl << '\t' <<  "Intervallanzahl: " << Intervallanzahl << std::endl;
	std::cout << "===========================================================================" << std::endl << "Mittelpunktregel in genauigkeit 10^-4 für x sin 1/x" << std::endl;
	Intervallanzahl = 1000;
	Intervallbreite = (Ende - Anfang)/Intervallanzahl;
	Abfrage1 = Mittelpunktregel( FunktionB , Anfang , Ende , Intervallanzahl);
	Abfrage2;
	do{
		Abfrage2 = Abfrage1;
		Intervallbreite *= 0.5;
		Intervallanzahl = (Ende -Anfang)/Intervallbreite;
		Abfrage1 = Mittelpunktregel( FunktionB , Anfang , Ende , Intervallanzahl);		
	} while( std::abs( Abfrage1 - Abfrage2 )/Abfrage1 > 0.0001);
	std::cout << "Ergebnis: " << Abfrage1 << '\t' << "Breite: " << (Ende - Anfang)/Intervallanzahl <<'\t' <<  "Intervallanzahl: " << Intervallanzahl << std::endl;	
	std::cout << "===========================================================================" << std::endl << "Simpsonsregel für in genauigkeit 10^-4 für x sin 1/x" << std::endl;
	Intervallanzahl = 1000;
	Intervallbreite = (Ende - Anfang)/Intervallanzahl;
	Abfrage1 = Simpsonregel( FunktionB , Anfang , Ende , Intervallanzahl);
	Abfrage2;
	do{
		Abfrage2 = Abfrage1;
		Intervallbreite *= 0.5;
		Intervallanzahl = (Ende -Anfang)/Intervallbreite;
		Abfrage1 = Simpsonregel( FunktionB , Anfang , Ende , Intervallanzahl);	
	} while( std::abs( Abfrage1 - Abfrage2 )/Abfrage1 > 0.0001);

	std::cout << "Ergebnis: " << Abfrage1 << '\t' << "Breite: " <<(Ende - Anfang)/Intervallanzahl <<'\t' <<  "Intervallanzahl: " << Intervallanzahl  << std::endl;

    return 0;
}