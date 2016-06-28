#include <iostream>
#include <cmath>
#define _USE_MATH_DIFINES



void RND( int64_t& Seed , int64_t Modulo , int64_t Multiplikator , int64_t Summand  ){
	Seed = (Multiplikator * Seed + Summand )%Modulo;
}
double pi_print(int64_t Datenanzahl){
	int64_t Seed =1234567;
	int64_t Modulo = 2147483648 - 1 ; 
	int64_t Multiplikator = 16807;
	int64_t Summand = 0 ;
	
	double Zufall1;
	double Zufall2;

	int Zaehler = 0;
	for (int i = 0; i < Datenanzahl; ++i)
	{
		RND( Seed  , Modulo , Multiplikator , Summand );
		Zufall1 = 2.0*((double) Seed/ Modulo) - 1.0;
		Zufall1 = Zufall1*Zufall1;
		RND( Seed  , Modulo , Multiplikator , Summand );
		Zufall2 = 2.0*((double) Seed/ Modulo) - 1.0;
		Zufall2 = Zufall2*Zufall2;
		if (Zufall1 + Zufall2 < 1)
		{
			Zaehler++;
		}
	}
	return (double) 4*Zaehler/(Datenanzahl);
}

int main(){

	int64_t Datenanzahl = 1e6;
	std::cout << "pi ist ungefaehr: " << pi_print(Datenanzahl) << std::endl;
	int64_t Anzahl = 10;
	double pi;
	std::cout << M_PI << "\n";
	for (int i = 0; i < 7; ++i)
	{
		pi = pi_print( Anzahl );
		std::cout << "pi= " << pi <<"\t Error(pi)= " << std::abs( M_PI - pi ) << "\t für die Anzahl: 10^" << i+1 << "\n";
		Anzahl *= 10;
	}

	return 0;
}