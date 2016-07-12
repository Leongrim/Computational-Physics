#include <iostream>
#include <cmath>
#include <random>
#include <fstream>

//Monte-Carlo-Simulation des zweidimensionalen Ising-Modells

std::mt19937 generator;

double RANDOM(){//Zufallszahlengenerator für gleichverteilte Zufallszahlen zwischen 0 und 1
	std::uniform_real_distribution<double> distribution(0.0, 1.0);
	return distribution(generator);
}

double RANDOM_int(int min, int max){//Zufallszahlengenerator für diskrete gleichverteilte Zufallszahlen von min bis max
	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(generator);
}

double Hamilton(double spins[][100], int x_pos, int y_pos){//Berechnung der Energie
	int x_plus = x_pos + 1;//rechter Nachbar
	x_plus = x_plus - 100*floor(x_plus/100);//periodische Randbedingung
	int x_minus = x_pos - 1;//linker Nachbar
	x_minus = x_minus - 100*floor(x_minus/100);//periodische Randbedingung
	int y_plus = y_pos + 1;//oberer Nachbar
	y_plus = y_plus - 100*floor(y_plus/100);//periodische Randbedingung
	int y_minus = y_pos - 1;//unterer Nachbar
	y_minus = y_minus - 100*floor(y_minus/100);//periodische Randbedingung
	double H = -spins[x_pos][y_pos] * (spins[x_minus][y_pos] + spins[x_plus][y_pos] + spins[x_pos][y_minus] + spins[x_pos][y_plus]);
	//std::cout << H << "\n";
	return H;
}

int main(){
	std::fstream Datei;
	Datei.open("Ergebnisse/Ergebnis_2_A_geordnet_0.txt", std::ios::trunc | std::ios::out);
	//Datei << "#Position_x\tPosition_y\tSpin\n";
	//Initialisierung für geordneten Anfangszustand
	double spins_geordnet[100][100];
	for(int i = 0; i < 100; ++i){
		for(int j = 0; j < 100; ++j){
			spins_geordnet[i][j] = 1.0;
			Datei << spins_geordnet[i][j] << "\t";
		}
		Datei << "\n";
	}
	Datei.close();

	int t_MC = 10;//Anzahl der Zeitschritte
	for(int t = 0; t < t_MC; ++t){//Schleife zum Durchlaufen der Zeitschritte
		int x_pos = RANDOM_int(0, 99);
		//std::cout << x_pos << "\n";
		int y_pos = RANDOM_int(0, 99);
		//std::cout << y_pos << "\n";
		double deltaE = 0.0;
		deltaE -= Hamilton(spins_geordnet, x_pos, y_pos);//Berechne Energiedifferenz
		spins_geordnet[x_pos][y_pos] *= -1.0;
		deltaE += Hamilton(spins_geordnet, x_pos, y_pos);
		if(deltaE < 0.0){//In diesem Fall immer akzeptieren
			//spins_geordnet[x_pos][y_pos] *= -1.0;
			//spin = -spin;//Zustand wird geändert
		}
		else if(deltaE >= 0.0){//In diesem Fall Vergleich von e^(-beta deltaE) mit Zufallszahl RANDOM()
			if(RANDOM() < exp(-deltaE)){//In diesem Fall wird akzeptiert
				//spins_geordnet[x_pos][y_pos] *= -1.0;
				//spin = -spin;//Zustand wird geändert
			}
			else{
				spins_geordnet[x_pos][y_pos] *= -1.0;//sonst wird abgelehnt
			}
		}
	}

	Datei.open("Ergebnisse/Ergebnis_2_A_geordnet_10.txt", std::ios::trunc | std::ios::out);
	for(int i = 0; i < 100; ++i){
		for(int j = 0; j < 100; ++j){
			Datei << spins_geordnet[i][j] << "\t";
		}
		Datei << "\n";
	}
	Datei.close();


	Datei.open("Ergebnisse/Ergebnis_2_A_zufall_0.txt", std::ios::trunc | std::ios::out);
	Datei << "#Position_x\tPosition_y\tSpin\n";
	//Initialisierung für zufälligen Anfangszustand
	double spins_zufall[100][100];
	//int count_plus = 0;
	//int count_minus = 0;
	for(int i = 0; i < 100; ++i){
		for(int j = 0; j < 100; ++j){
			double rnd = RANDOM_int(0, 1);
			if(rnd == 1){
				spins_zufall[i][j] = 1.0;
				//count_plus += 1;
			}
			else if(rnd == 0){
				spins_zufall[i][j] = -1.0;
				//count_minus += 1;
			}
			Datei << spins_zufall[i][j] << "\t";
		}
		Datei << "\n";
	}
	//std::cout << count_plus << "\t" << count_minus << std::endl;
	Datei.close();

	for(int t = 0; t < t_MC; ++t){//Schleife zum Durchlaufen der Zeitschritte
		int x_pos = RANDOM_int(0, 99);
		//std::cout << x_pos << "\n";
		int y_pos = RANDOM_int(0, 99);
		//std::cout << y_pos << "\n";
		double deltaE = 0.0;
		deltaE -= Hamilton(spins_zufall, x_pos, y_pos);//Berechne Energiedifferenz
		spins_zufall[x_pos][y_pos] *= -1.0;
		deltaE += Hamilton(spins_zufall, x_pos, y_pos);
		if(deltaE < 0.0){//In diesem Fall immer akzeptieren
			//spins_zufall[x_pos][y_pos] *= -1.0;
			//spin = -spin;//Zustand wird geändert
		}
		else if(deltaE >= 0.0){//In diesem Fall Vergleich von e^(-beta deltaE) mit Zufallszahl RANDOM()
			if(RANDOM() < exp(-deltaE)){//In diesem Fall wird akzeptiert
				//spins_zufall[x_pos][y_pos] *= -1.0;
				//spin = -spin;//Zustand wird geändert
			}
			else{
				spins_zufall[x_pos][y_pos] *= -1.0;//sonst wird abgelehnt
			}
		}
	}

	Datei.open("Ergebnisse/Ergebnis_2_A_zufall_10.txt", std::ios::trunc | std::ios::out);
	for(int i = 0; i < 100; ++i){
		for(int j = 0; j < 100; ++j){
			Datei << spins_zufall[i][j] << "\t";
		}
		Datei << "\n";
	}
	Datei.close();


	return 0;
}