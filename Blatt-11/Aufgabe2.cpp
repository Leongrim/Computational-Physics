#include <iostream>
#include <cmath>
#include <random>
#include <fstream>
#include <string>
#include <sstream>

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
	return H;
}

void metropolis(double spins[][100], const char* Dateiname_Momentaufnahme, const char* Dateiname_Energie, std::fstream &stream, int t_MC, double kbt){
	std::fstream Datei;
	std::string KBoltzmannT = static_cast<std::ostringstream*>( &(std::ostringstream() << kbt) )->str();

	double Energie = 0.0;
	double deltaE = 0.0;
	double m = 0.0;//Magnetisierung anfangs =0 für spätere Summation
	//Datei.open(Dateiname_Energie + KBoltzmannT + ".txt", std::ios::trunc | std::ios::out);
	//Datei << "#t/Sweeps\te(t)\tm\t|m|\n";
	for(int t = 0; t < t_MC; ++t){//Schleife zum Durchlaufen der Zeitschritte
		int x_pos = RANDOM_int(0, 99);
		int y_pos = RANDOM_int(0, 99);
		deltaE = -Hamilton(spins, x_pos, y_pos);//Berechne Energiedifferenz
		spins[x_pos][y_pos] *= -1.0;
		deltaE += Hamilton(spins, x_pos, y_pos);
		if(deltaE < 0.0){}//In diesem Fall immer akzeptieren
		else /*if(deltaE >= 0.0)*/{//In diesem Fall Vergleich von e^(-beta deltaE) mit Zufallszahl RANDOM()
			if(RANDOM() < exp(-(1.0/kbt)*deltaE)){}//In diesem Fall wird akzeptiert
			else{
				spins[x_pos][y_pos] *= -1.0;//sonst wird abgelehnt
			}
		}
		if(t % 10000 == 0 && t > 0){
			for(int i = 0; i < 100; ++i){
				for(int j = 0; j < 100; ++j){
					Energie += Hamilton(spins, i, j);
					m += spins[i][j];
				}
			}
			//Datei << t/10000 << "\t" << Energie/(double)t << "\t" << m/(double)t << "\t" << std::abs(m/(double)t) << "\n";
			std::cout << "In diesem Durchlauf sind " << 100*(double)t/(double)t_MC << " % geschafft.\r";
		}
	}
	//Datei.close();
	stream << kbt << "\t" << m/(double)t_MC << "\t" << std::abs(m/(double)t_MC) << "\n";

/*	std::string Zeitschritte = static_cast<std::ostringstream*>( &(std::ostringstream() << t_MC) )->str();
	Datei.open(Dateiname_Momentaufnahme + Zeitschritte + "_kBT" + KBoltzmannT + ".txt", std::ios::trunc | std::ios::out);
	for(int i = 0; i < 100; ++i){
		for(int j = 0; j < 100; ++j){
			Datei << spins[i][j] << "\t";
		}
		Datei << "\n";
	}
	Datei.close();
*/}

void metropolis_fluk(double spins[][100], std::fstream &stream, int t_MC, double kbt){
	double Energie = 0.0;
	double Energie2 = 0.0;
	double deltaE = 0.0;
	//Datei.open(Dateiname_Energie + KBoltzmannT + ".txt", std::ios::trunc | std::ios::out);
	//Datei << "#t/Sweeps\te(t)\tm\t|m|\n";
	for(int t = 0; t < t_MC; ++t){//Schleife zum Durchlaufen der Zeitschritte
		int x_pos = RANDOM_int(0, 99);
		int y_pos = RANDOM_int(0, 99);
		deltaE = -Hamilton(spins, x_pos, y_pos);//Berechne Energiedifferenz
		spins[x_pos][y_pos] *= -1.0;
		deltaE += Hamilton(spins, x_pos, y_pos);
		if(deltaE < 0.0){}//In diesem Fall immer akzeptieren
		else /*if(deltaE >= 0.0)*/{//In diesem Fall Vergleich von e^(-beta deltaE) mit Zufallszahl RANDOM()
			if(RANDOM() < exp(-(1.0/kbt)*deltaE)){}//In diesem Fall wird akzeptiert
			else{
				spins[x_pos][y_pos] *= -1.0;//sonst wird abgelehnt
			}
		}
		if(t % 10000 == 0 && t > 0){
			for(int i = 0; i < 100; ++i){
				for(int j = 0; j < 100; ++j){
					Energie += Hamilton(spins, i, j);
					Energie2 += Hamilton(spins, i, j) * Hamilton(spins, i, j);
				}
			}
			//std::cout << Energie/(double)t << "\n";
			std::cout << "In diesem Durchlauf sind " << 100*(double)t/(double)t_MC << " % geschafft.\r";
		}
	}
	std::cout << "\n" << kbt << "\t" << (Energie2/(double)t_MC - (Energie/(double)t_MC)*(Energie/(double)t_MC))/(kbt*kbt*10000.0) << "\n";
	std::cout << "\n" << kbt << "\t" << Energie2 << "\t" << (double)t_MC << "\t" << Energie/(double)t_MC << "\n";
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
	
	int t_MC = 100000000;

	Datei.open("Ergebnisse/Ergebnis_2_A_zufall_t0.txt", std::ios::trunc | std::ios::out);
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

/*	std::fstream Datei2;
	Datei2.open("Ergebnisse/Ergebnis_2_C_Magnetisierung.txt", std::ios::trunc | std::ios::out);
	Datei2 << "#kbt\tm\t|m|\n";
	double kbt = 1.0;
	for(int i = 0; i <= 200; ++i){
		std::cout << "kBT = " << kbt << ".                                 \r\n";
		metropolis(spins_geordnet, "Ergebnisse/Ergebnis_2_A_geordnet_t", "Ergebnisse/Ergebnis_2_B_Energie_geordnet_kBT", Datei2, t_MC, kbt);
		kbt += 0.01;
	}
	Datei2.close();*/ 
	//metropolis(spins_geordnet, "Ergebnisse/Ergebnis_2_A_geordnet_t", "Ergebnisse/Ergebnis_2_B_Energie_geordnet_kBT", t_MC, 2.27);
	//metropolis(spins_geordnet, "Ergebnisse/Ergebnis_2_A_geordnet_t", "Ergebnisse/Ergebnis_2_B_Energie_geordnet_kBT", t_MC, 3.0);

	//metropolis(spins_zufall, "Ergebnisse/Ergebnis_2_A_zufall_t", "Ergebnisse/Ergebnis_2_B_Energie_zufall_kBT", t_MC, 1.0);
	//metropolis(spins_zufall, "Ergebnisse/Ergebnis_2_A_zufall_t", "Ergebnisse/Ergebnis_2_B_Energie_zufall_kBT", t_MC, 2.27);
	//metropolis(spins_zufall, "Ergebnisse/Ergebnis_2_A_zufall_t", "Ergebnisse/Ergebnis_2_B_Energie_zufall_kBT", t_MC, 3.0);

	std::fstream Datei3;
	Datei3.open("Ergebnisse/Ergebnis_2_D_Energiefluktuation.txt", std::ios::trunc | std::ios::out);
	Datei3 << "#kBT\tc(T)\n";
	double kbt = 1.0;
	for(int i = 0; i <= 0; ++i){
		std::cout << "kBT = " << kbt << ".                                   \r\n";
		metropolis_fluk(spins_geordnet, Datei3, t_MC, kbt);
		kbt += 0.01;
	}
	Datei3.close();

	return 0;
}