#include <iostream>
#include <cmath>
#include <random>
#include <fstream>
#include <string>

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

void momentaufnahme(double spins[][100], const char* Dateiname, int Zeitschritte, double beta){
	std::fstream Datei;

	double deltaE;
	int t_MC = Zeitschritte;//Anzahl der Zeitschritte
	for(int t = 0; t < t_MC; ++t){//Schleife zum Durchlaufen der Zeitschritte
		int x_pos = RANDOM_int(0, 99);
		int y_pos = RANDOM_int(0, 99);
		deltaE = -Hamilton(spins, x_pos, y_pos);//Berechne Energiedifferenz
		spins[x_pos][y_pos] *= -1.0;
		deltaE += Hamilton(spins, x_pos, y_pos);
		if(deltaE < 0.0){}//In diesem Fall immer akzeptieren
		else if(deltaE >= 0.0){//In diesem Fall Vergleich von e^(-beta deltaE) mit Zufallszahl RANDOM()
			if(RANDOM() < exp(-beta*deltaE)){}//In diesem Fall wird akzeptiert
			else{
				spins[x_pos][y_pos] *= -1.0;//sonst wird abgelehnt
			}
		}
	}

	Datei.open(Dateiname, std::ios::trunc | std::ios::out);
	for(int i = 0; i < 100; ++i){
		for(int j = 0; j < 100; ++j){
			Datei << spins[i][j] << "\t";
		}
		Datei << "\n";
	}
	Datei.close();

}

int main(){
	std::fstream Datei;
	Datei.open("Ergebnisse/Ergebnis_2_A_geordnet_t0.txt", std::ios::trunc | std::ios::out);
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

	momentaufnahme(spins_geordnet, "Ergebnisse/Ergebnis_2_A_geordnet_t10_kBT1.txt", 10, 1.0);
	momentaufnahme(spins_geordnet, "Ergebnisse/Ergebnis_2_A_geordnet_t100_kBT1.txt", 100, 1.0);
	momentaufnahme(spins_geordnet, "Ergebnisse/Ergebnis_2_A_geordnet_t1000_kBT1.txt", 1000, 1.0);
	momentaufnahme(spins_geordnet, "Ergebnisse/Ergebnis_2_A_geordnet_t10000_kBT1.txt", 10000, 1.0);
	momentaufnahme(spins_geordnet, "Ergebnisse/Ergebnis_2_A_geordnet_t100000_kBT1.txt", 100000, 1.0);
	momentaufnahme(spins_geordnet, "Ergebnisse/Ergebnis_2_A_geordnet_t1000000_kBT1.txt", 1000000, 1.0);
	momentaufnahme(spins_geordnet, "Ergebnisse/Ergebnis_2_A_geordnet_t10000000_kBT1.txt", 10000000, 1.0);

	momentaufnahme(spins_geordnet, "Ergebnisse/Ergebnis_2_A_geordnet_t10_kBT3.txt", 10, 1.0/3.0);
	momentaufnahme(spins_geordnet, "Ergebnisse/Ergebnis_2_A_geordnet_t100_kBT3.txt", 100, 1.0/3.0);
	momentaufnahme(spins_geordnet, "Ergebnisse/Ergebnis_2_A_geordnet_t1000_kBT3.txt", 1000, 1.0/3.0);
	momentaufnahme(spins_geordnet, "Ergebnisse/Ergebnis_2_A_geordnet_t10000_kBT3.txt", 10000, 1.0/3.0);
	momentaufnahme(spins_geordnet, "Ergebnisse/Ergebnis_2_A_geordnet_t100000_kBT3.txt", 100000, 1.0/3.0);
	momentaufnahme(spins_geordnet, "Ergebnisse/Ergebnis_2_A_geordnet_t1000000_kBT3.txt", 1000000, 1.0/3.0);
	momentaufnahme(spins_geordnet, "Ergebnisse/Ergebnis_2_A_geordnet_t10000000_kBT3.txt", 10000000, 1.0/3.0);

	Datei.open("Ergebnisse/Ergebnis_2_A_zufall_t0.txt", std::ios::trunc | std::ios::out);
	Datei << "#Position_x\tPosition_y\tSpin\n";
	//Initialisierung für zufälligen Anfangszustand
	double spins_zufall[100][100];
	for(int i = 0; i < 100; ++i){
		for(int j = 0; j < 100; ++j){
			double rnd = RANDOM_int(0, 1);
			if(rnd == 1){
				spins_zufall[i][j] = 1.0;
			}
			else if(rnd == 0){
				spins_zufall[i][j] = -1.0;
			}
			Datei << spins_zufall[i][j] << "\t";
		}
		Datei << "\n";
	}
	Datei.close();

	momentaufnahme(spins_zufall, "Ergebnisse/Ergebnis_2_A_zufall_t10_kBT1.txt", 10, 1.0);
	momentaufnahme(spins_zufall, "Ergebnisse/Ergebnis_2_A_zufall_t100_kBT1.txt", 100, 1.0);
	momentaufnahme(spins_zufall, "Ergebnisse/Ergebnis_2_A_zufall_t1000_kBT1.txt", 1000, 1.0);
	momentaufnahme(spins_zufall, "Ergebnisse/Ergebnis_2_A_zufall_t10000_kBT1.txt", 10000, 1.0);
	momentaufnahme(spins_zufall, "Ergebnisse/Ergebnis_2_A_zufall_t100000_kBT1.txt", 100000, 1.0);
	momentaufnahme(spins_zufall, "Ergebnisse/Ergebnis_2_A_zufall_t1000000_kBT1.txt", 1000000, 1.0);
	momentaufnahme(spins_zufall, "Ergebnisse/Ergebnis_2_A_zufall_t10000000_kBT1.txt", 10000000, 1.0);

	momentaufnahme(spins_zufall, "Ergebnisse/Ergebnis_2_A_zufall_t10_kBT3.txt", 10, 1.0/3.0);
	momentaufnahme(spins_zufall, "Ergebnisse/Ergebnis_2_A_zufall_t100_kBT3.txt", 100, 1.0/3.0);
	momentaufnahme(spins_zufall, "Ergebnisse/Ergebnis_2_A_zufall_t1000_kBT3.txt", 1000, 1.0/3.0);
	momentaufnahme(spins_zufall, "Ergebnisse/Ergebnis_2_A_zufall_t10000_kBT3.txt", 10000, 1.0/3.0);
	momentaufnahme(spins_zufall, "Ergebnisse/Ergebnis_2_A_zufall_t100000_kBT3.txt", 100000, 1.0/3.0);
	momentaufnahme(spins_zufall, "Ergebnisse/Ergebnis_2_A_zufall_t1000000_kBT3.txt", 1000000, 1.0/3.0);
	momentaufnahme(spins_zufall, "Ergebnisse/Ergebnis_2_A_zufall_t10000000_kBT3.txt", 10000000, 1.0/3.0);


	return 0;
}