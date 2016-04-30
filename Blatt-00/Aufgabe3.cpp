#include "iostream"


	/*double FunktionA(int N , double h){
		if( N == 0) return 1;
		if( N == 1) return 1 - h;
		if( N > 1) return FunktionA( N-2 ,h) - 2*h*FunktionA( N - 1 , h);
		if( N < 0) return FunktionA( N+2 , h) + 2*h*FunktionA( N + 1 , h);
	}//*/
	/*double FunktionB(int N , double h){
		if( N == 0) return 1;
		if( N == 1) return 1 - h;
		if( N > 1) return FunktionA( N-2 ,h) + 2*h*FunktionA( N - 1 , h);
		if( N < 0) return FunktionA( N+2 , h) - 2*h*FunktionA( N + 1 , h);
	}//*/		
	double FunktionA(int N , double h){
		if( N == 0 ){
			return 1;
		}
		if( N == 1){
			return 1-h;
		}
		if ( N > 2){
			double Yn;
			double Yminus2 = 1;
			double Yminus1 = 1-h;
			for (int i = 2; i <= N; ++i)
			{
				Yn = Yminus2 - 2 * h * Yminus1;
				Yminus2 = Yminus1;
				Yminus1 = Yn;
			}
			return Yn;
		}else{
			double Yn;
			double Yplus1 = 1;
			double Yplus2 = 1-h;
			for (int i = -1; i > N; --i)
			{
				Yn = Yplus2 + 2*h*Yplus1;
				Yplus2 = Yplus1;
				Yplus1 = Yn;
			}
			return Yn;
		}
	}
	double FunktionB(int N , double h){
		if( N == 0 ){
			return 1;
		}
		if( N == 1){
			return 1-h;
		}
		if ( N > 2){
			double Yn;
			double Yminus2 = 1;
			double Yminus1 = 1-h;
			for (int i = 2; i <= N; ++i)
			{
				Yn = Yminus2 + 2 * h * Yminus1;
				Yminus2 = Yminus1;
				Yminus1 = Yn;
			}
			return Yn;
		}else{
			double Yn;
			double Yplus1 = 1;
			double Yplus2 = 1-h;
			for (int i = -1; i > N; --i)
			{
				Yn = Yplus2 - 2*h*Yplus1;
				Yplus2 = Yplus1;
				Yplus1 = Yn;
			}
			return Yn;
		}
	}//*/

int main()
{
	int n = -100;
	double h = 0.0001;
	std::cout << "exp(" << n*h << ")="<< FunktionA( n , h) << std::endl;
	std::cout << "exp(" << n*h << ")="<< FunktionB( -n , h) << std::endl;

	return 0;
}