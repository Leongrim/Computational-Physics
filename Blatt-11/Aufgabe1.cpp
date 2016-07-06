#include <iostream>
#include <cmath>
#include <random>
#include <fstream>

std::mt19937 generator;

double RANDOM(){
	std::uniform_real_distribution<double> distribution(0.0 , 1.0);
	return distribution(generator);
}

int main(){
	//Ziehe 10^4 Werte für H zwischen -5 und 5 mit je 10^5 Zeitschritten
	double H = -5.0;
	double m = 0.0;
	double spin = 1.0;
	double deltaE;
	int H_Anzahl = 1e4;
	int T = 1e5;
	std::fstream Datei;
	Datei.open("Ergebnisse/Ergebnis_1_B.txt", std::ios::trunc | std::ios::out);
	Datei << "#H\tm\n";
	for(int i = 0; i < H_Anzahl; ++i){
		H += 10.0/(double)H_Anzahl;
		for(int t = 0; t < T; ++t){
			deltaE = 2.0*spin*H;
			if(deltaE < 0.0){
				spin = -spin;
			}
			else if(deltaE > 0.0){
				if(RANDOM() < exp(-deltaE)){
					spin = -spin;
				}
				else;
			}
			m += spin;
		}
		Datei << H << "\t" << m/(double)T << "\n";
		m = 0.0;
	}

	Datei.close();


	return 0;
}