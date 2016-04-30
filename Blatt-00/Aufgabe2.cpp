#include "iostream"
#include "cmath"

	double FunktionA(double x){
		return 1/sqrt( x ) - 1/sqrt( x + 1 );
	}
	double FunktionAana(double x){
		return ( sqrt( x + 1 ) - sqrt( x ) ) / (sqrt(x*x+x));
	}

	double FunktionB(double x){
		return (1- cos(x))/sin(x);
	}

	double FunktionBana(double x){
		return tan(x/2);
	}

	double FunktionC(double x , double delta){
		return sin( x + delta ) - sin( x );
	}

int main(){

	double lengthA = 100000;
	
	for (double i = 1; i <= 100 ; i++)
	{
		std::cout << FunktionA( i+lengthA )<< '\t';
		if( (int)(i) % 5 == 0) std::cout << std::endl;
	}
	
	std::cout << "================================================" << std::endl;

	for (double i = 1; i <= 100 ; i++ )
	{
		std::cout << FunktionAana( i*lengthA )<< '\t';
		if( (int)(i) % 5 == 0) std::cout << std::endl;
	}

	std::cout << "================================================" << std::endl;
	for (double i = 1; i <= 100 ; i++ )
	{
		std::cout << FunktionA( i*lengthA ) - FunktionAana( i*lengthA )<< '\t';
		if( (int)(i) % 5 == 0) std::cout << std::endl;
	}//*/

	/*double lengthB = 0.000001;

	for (double i = 1; i <= 100 ; i++)
	{
		std::cout << FunktionB( i*lengthB )<< '\t';
		if( (int)(i) % 5 == 0) std::cout << std::endl;
	}
	
	std::cout << "================================================" << std::endl;

	for (double i = 1; i <= 100 ; i++ )
	{
		std::cout << FunktionBana( i*lengthB )<< '\t';
		if( (int)(i) % 5 == 0) std::cout << std::endl;
	}


	std::cout << "================================================" << std::endl;
	for (double i = 1; i <= 100 ; i++ )
	{
		std::cout << FunktionB( i*lengthB ) - FunktionBana( i*lengthB )<< '\t';
		if( (int)(i) % 5 == 0) std::cout << std::endl;
	}*/

	/*double lengthC = 0.000001;

	for (int j = 0; j < 10; ++j)
	{
		for (double i = 1; i <= 100 ; i++)
		{
			std::cout << FunktionC( j, i*lengthC )<< '\t';
			if( (int)(i) % 5 == 0) std::cout << std::endl;
		}
		if( j % 2 == 0) std::cout << std::endl;
	}
	/*std::cout << "================================================" << std::endl;

	for (double i = 1; i <= 100 ; i++ )
	{
		std::cout << FunktionBana( i*lengthB )<< '\t';
		if( (int)(i) % 5 == 0) std::cout << std::endl;
	}

	std::cout << "================================================" << std::endl;
	for (double i = 1; i <= 100 ; i++ )
	{
		std::cout << FunktionB( i*lengthB ) - FunktionBana( i*lengthB )<< '\t';
		if( (int)(i) % 5 == 0) std::cout << std::endl;
	}
	std::cout << std::endl;*/

    return 0;
}