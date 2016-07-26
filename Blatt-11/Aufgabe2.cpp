#include <iostream>
#include <cmath>
#include <random>
#include <fstream>
#include <string>
#include <sstream>
#include <omp.h>

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

int Hamilton(int spins[][100], int x_pos, int y_pos){//Berechnung der Energie
	int x_plus = x_pos + 1;//rechter Nachbar
	x_plus = x_plus - 100*floor(x_plus/100.0);//periodische Randbedingung
	int x_minus = x_pos - 1;//linker Nachbar
	x_minus = x_minus - 100*floor(x_minus/100.0);//periodische Randbedingung
	int y_plus = y_pos + 1;//unterer Nachbar
	y_plus = y_plus - 100*floor(y_plus/100.0);//periodische Randbedingung
	int y_minus = y_pos - 1;//oberer Nachbar
	y_minus = y_minus - 100*floor(y_minus/100.0);//periodische Randbedingung
	int H = -spins[x_pos][y_pos] * (spins[x_minus][y_pos] + spins[x_plus][y_pos] + spins[x_pos][y_minus] + spins[x_pos][y_plus]);
	//if(spins[x_pos][y_minus] != 1 && spins[x_pos][y_minus] != -1){std::cout << spins[x_pos][y_minus] << "\n";}
	return H;
}

void metropolis_moment(int spins[][100], const char* Dateiname_Momentaufnahme, int t_MC, double kbt){
	double deltaE = 0.0;//deltaE anfangs =0 für spätere Summation
	std::cout << "Momentaufnahmen mit kBT=" << kbt << "\n";
	int t_wert = 1;
	for(int t = 0; t <= t_MC; ++t){//Schleife zum Durchlaufen der Zeitschritte
		int x_pos = RANDOM_int(0, 99);//Ziehe zufälligen Spin-x-Position
		int y_pos = RANDOM_int(0, 99);//Ziehe zufälligen Spin-y-Position
		deltaE = -Hamilton(spins, x_pos, y_pos);//Berechne Energiedifferenz, zunächst negativer Anfangszustand
		spins[x_pos][y_pos] *= -1;//Spin-Flip
		deltaE += Hamilton(spins, x_pos, y_pos);//Addiere geflippten Zustand
		if(deltaE < 0.0){}//In diesem Fall immer akzeptieren
		else{//In diesem Fall Vergleich von e^(-beta deltaE) mit Zufallszahl RANDOM()
			if(RANDOM() < exp(-(1.0/kbt)*deltaE)){}//In diesem Fall wird akzeptiert
			else{
				spins[x_pos][y_pos] *= -1;//Sonst wird abgelehnt
			}
		}
		//std::cout << "In diesem Durchlauf sind " << 100.0*(double)t/(double)t_MC << " % geschafft.\r";
		if(t % t_wert == 0 && t > 0){//Momentaufnahmen für Aufgabenteil a)
			std::fstream Datei;//Speichere resultierende Spin-Matrix nach t_MC Zeitschritten
			std::string KBoltzmannT = static_cast<std::ostringstream*>(&(std::ostringstream() << kbt))->str();
			std::string Zeitschritte = static_cast<std::ostringstream*>(&(std::ostringstream() << t))->str();
			Datei.open(Dateiname_Momentaufnahme + Zeitschritte + "_kBT" + KBoltzmannT + ".txt", std::ios::trunc | std::ios::out);
			for(int i = 0; i < 100; ++i){
				for(int j = 0; j < 100; ++j){
					Datei << spins[i][j] << "\t";
				}
				Datei << "\n";
			}
			Datei.close();
			t_wert *= 10;
		}
	}
}

void metropolis_energie(int spins[][100], const char* Dateiname_Energie, long int t_MC, double kbt){
	std::fstream Datei;
	std::string KBoltzmannT = static_cast<std::ostringstream*>(&(std::ostringstream() << kbt))->str();

	double Energie = 0.0;
	double deltaE = 0.0;
	double m = 0.0;//Magnetisierung anfangs =0 für spätere Summation
	Datei.open(Dateiname_Energie + KBoltzmannT + ".txt", std::ios::trunc | std::ios::out);
	Datei << "#t/Sweeps\te(t)\tm\t|m|\n";
	std::cout << "Energie und Magnetisierung mit kBT=" << kbt << "\n";
	for(int t = 0; t <= t_MC; ++t){//Schleife zum Durchlaufen der Zeitschritte
		int x_pos = RANDOM_int(0, 99);
		int y_pos = RANDOM_int(0, 99);
		deltaE = -Hamilton(spins, x_pos, y_pos);//Berechne Energiedifferenz
		spins[x_pos][y_pos] *= -1;
		deltaE += Hamilton(spins, x_pos, y_pos);
		if(deltaE < 0.0){}//In diesem Fall immer akzeptieren
		else /*if(deltaE >= 0.0)*/{//In diesem Fall Vergleich von e^(-beta deltaE) mit Zufallszahl RANDOM()
			if(RANDOM() < exp(-(1.0/kbt)*deltaE)){}//In diesem Fall wird akzeptiert
			else{
				spins[x_pos][y_pos] *= -1;//sonst wird abgelehnt
			}
		}
		if(t % 10000 == 0 && t > 0){
			for(int i = 0; i < 100; ++i){
				for(int j = 0; j < 100; ++j){
					Energie += Hamilton(spins, i, j);
					m += spins[i][j];
				}
			}
			if(t > 300000000){Datei << t/10000 << "\t" << Energie/(double)t << "\t" << m/(double)t << "\t" << std::abs(m/(double)t)  << "\n";}
			//std::cout << "In diesem Durchlauf mit kBT=" << kbt << " sind " << 100.0*(double)t/(double)t_MC << " % geschafft.\r";
		}
	}
	Datei.close();
}

void metropolis_fluk(int spins[][100], std::fstream &stream1, std::fstream &stream2, int t_MC, double kbt){
	double Energie = 0.0;
	double Energie2 = 0.0;
	double deltaE = 0.0;
	double m = 0.0;//Magnetisierung anfangs =0 für spätere Summation
	//Datei.open(Dateiname_Energie + KBoltzmannT + ".txt", std::ios::trunc | std::ios::out);
	//Datei << "#t/Sweeps\te(t)\tm\t|m|\n";
	for(int t = 0; t <= t_MC; ++t){//Schleife zum Durchlaufen der Zeitschritte
		int x_pos = RANDOM_int(0, 99);
		int y_pos = RANDOM_int(0, 99);
		deltaE = -Hamilton(spins, x_pos, y_pos);//Berechne Energiedifferenz
		spins[x_pos][y_pos] *= -1;
		deltaE += Hamilton(spins, x_pos, y_pos);
		if(deltaE < 0.0){}//In diesem Fall immer akzeptieren
		else /*if(deltaE >= 0.0)*/{//In diesem Fall Vergleich von e^(-beta deltaE) mit Zufallszahl RANDOM()
			if(RANDOM() < exp(-(1.0/kbt)*deltaE)){}//In diesem Fall wird akzeptiert
			else{
				spins[x_pos][y_pos] *= -1;//sonst wird abgelehnt
			}
		}
		if(t % 10000 == 0 && t > 0){
			for(int i = 0; i < 100; ++i){
				for(int j = 0; j < 100; ++j){
					Energie += Hamilton(spins, i, j);
					Energie2 += Hamilton(spins, i, j) * Hamilton(spins, i, j);
					m += spins[i][j];
					//if(std::abs(Hamilton(spins, i, j))>4.0){std::cout << Hamilton(spins, i, j) << "\t" << i << "\t" << j << "\n";}
				}
			}
			//std::cout << Energie/(double)t << "\n";
			//std::cout << "In diesem Durchlauf sind " << 100*(double)t/(double)t_MC << " % geschafft.\r";
		}
	}
	stream1 << kbt << "\t" << (Energie2/(double)t_MC - (Energie/(double)t_MC)*(Energie/(double)t_MC))/(kbt*kbt*10000.0) << "\n";
	stream2 << kbt << "\t" << m/(double)t_MC << "\t" << std::abs(m/(double)t_MC) << "\n";
	//std::cout << "\n" << kbt << "\t" << Energie2 << "\t" << (double)t_MC << "\t" << Energie/(double)t_MC << "\n";
}

int main(){
	std::fstream Datei;
	Datei.open("Ergebnisse/Ergebnis_2_A_geordnet_t0.txt", std::ios::trunc | std::ios::out);
	//Initialisierung für geordneten Anfangszustand
	int spins_geordnet[100][100];
	for(int i = 0; i < 100; ++i){
		for(int j = 0; j < 100; ++j){
			spins_geordnet[i][j] = 1;
			Datei << spins_geordnet[i][j] << "\t";//Speichern der Spin-Matrix
		}
		Datei << "\n";
	}
	Datei.close();
	
	Datei.open("Ergebnisse/Ergebnis_2_A_zufall_t0.txt", std::ios::trunc | std::ios::out);
	//Initialisierung für zufälligen Anfangszustand
	int spins_zufall[100][100];
	for(int i = 0; i < 100; ++i){
		for(int j = 0; j < 100; ++j){
			int rnd = RANDOM_int(0, 1);
			if(rnd == 1){
				spins_zufall[i][j] = 1;
			}
			else if(rnd == 0){
				spins_zufall[i][j] = -1;
			}
			Datei << spins_zufall[i][j] << "\t";//Speichern der Spin-Matrix
		}
		Datei << "\n";
	}
	Datei.close();

	int t_MC = 2e9;//Anzahl der Simulationsschritte
	//Aufgabenteil a)
	std::cout << "Aufgabenteil a):\nGeordneter Anfangszustand:\n";
	metropolis_moment(spins_geordnet, "Ergebnisse/Ergebnis_2_A_geordnet_t", t_MC, 1.0);
	metropolis_moment(spins_geordnet, "Ergebnisse/Ergebnis_2_A_geordnet_t", t_MC, 3.0);
	std::cout << "Ungeordneter Anfangszustand:\n";
	metropolis_moment(spins_zufall, "Ergebnisse/Ergebnis_2_A_zufall_t", t_MC, 1.0);
	metropolis_moment(spins_zufall, "Ergebnisse/Ergebnis_2_A_zufall_t", t_MC, 3.0);

	//Aufgabenteil b)
	std::cout << "Aufgabenteil b):\nGeordneter Anfangszustand:\n";
	metropolis_energie(spins_geordnet, "Ergebnisse/Ergebnis_2_B_Energie_geordnet_kBT", 3e8, 1.0);
	metropolis_energie(spins_geordnet, "Ergebnisse/Ergebnis_2_B_Energie_geordnet_kBT", 2e9, 2.27);
	metropolis_energie(spins_geordnet, "Ergebnisse/Ergebnis_2_B_Energie_geordnet_kBT", 3e8, 3.0);
	std::cout << "Ungeordneter Anfangszustand:\n";
	metropolis_energie(spins_zufall, "Ergebnisse/Ergebnis_2_B_Energie_zufall_kBT", 3e8, 1.0);
	metropolis_energie(spins_zufall, "Ergebnisse/Ergebnis_2_B_Energie_zufall_kBT", 2e9, 2.27);
	metropolis_energie(spins_zufall, "Ergebnisse/Ergebnis_2_B_Energie_zufall_kBT", 3e8, 3.0);
	
	//Aufgabenteil c)
	std::cout << "Aufgabenteil b):\nGeordneter Anfangszustand:\n";
	metropolis_energie(spins_geordnet, "Ergebnisse/Ergebnis_2_B_Energie_geordnet_aequilibriert_kBT", 1300000000, 1.0);
	metropolis_energie(spins_geordnet, "Ergebnisse/Ergebnis_2_B_Energie_geordnet_aequilibriert_kBT", 3000000000, 2.27);
	metropolis_energie(spins_geordnet, "Ergebnisse/Ergebnis_2_B_Energie_geordnet_aequilibriert_kBT", 1300000000, 3.0);
	std::cout << "Ungeordneter Anfangszustand:\n";
	metropolis_energie(spins_zufall, "Ergebnisse/Ergebnis_2_B_Energie_zufall_aequilibriert_kBT", 1300000000, 1.0);
	metropolis_energie(spins_zufall, "Ergebnisse/Ergebnis_2_B_Energie_zufall_aequilibriert_kBT", 3000000000, 2.27);
	metropolis_energie(spins_zufall, "Ergebnisse/Ergebnis_2_B_Energie_zufall_aequilibriert_kBT", 1300000000, 3.0);

	//Aufgabenteil c) und d)
	std::cout << "Aufgabenteil c) und d):\nGeordneter Anfangszustand:\n";
	std::fstream Datei2;
	Datei2.open("Ergebnisse/Ergebnis_2_C_Magnetisierung_grob.txt", std::ios::trunc | std::ios::out);
	Datei2 << "#kbt\tm\t|m|\n";
	std::fstream Datei3;
	Datei3.open("Ergebnisse/Ergebnis_2_D_Energiefluktuation_grob.txt", std::ios::trunc | std::ios::out);
	Datei3 << "#kBT\tc(T)\n";
	double kbt = 1.0;
	{
		#pragma omp parallel for//Parallelisierung
		for(int i = 0; i <= 400; ++i){//Berechnung der spezifischen Wärme und der Magnetisierung
			std::cout << "kBT = " << kbt << "\n";
			metropolis_fluk(spins_geordnet, Datei3, Datei2, t_MC, kbt);
			kbt += 0.005;
		}
	}
	Datei2.close();
	Datei3.close();

	return 0;
}