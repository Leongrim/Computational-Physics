#include <iostream>
#include <cmath>
#include <random>
#include <fstream>

//Monte-Carlo-Simulation eines einzelnen Spins

std::mt19937 generator;

double RANDOM(){//Zufallszahlengenerator für gleichverteilte Zufallszahlen zwischen 0 und 1
	std::uniform_real_distribution<double> distribution(0.0 , 1.0);
	return distribution(generator);
}

int main(){
	//Initialisierung
	double H = -5.0;//Beginne mit dem Magnetfeld H=-5
	double m = 0.0;//Magnetisierung anfangs =0 für spätere Summation
	double spin = 1.0;//Anfangszustand: Spin=+1
	double deltaE;//Energiedifferenz
	int H_Anzahl = 1e4;//Anzahl der zu durchlaufenden Magnetfeldwerte
	int T = 1e5;//Anzahl der Zeitschritte
	//Erzeuge Ausgabedatei zur Speicherung der Werte
	std::fstream Datei;
	Datei.open("Ergebnisse/Ergebnis_1_B.txt", std::ios::trunc | std::ios::out);
	Datei << "#H\tm\n";
	//Ziehe 10^4 Werte für H zwischen -5 und 5 mit je 10^5 Zeitschritten
	for(int i = 0; i < H_Anzahl; ++i){//Schleife zum Durchlaufen der Magnetfeldwerte
		for(int t = 0; t < T; ++t){//Schleife zum Durchlaufen der Zeitschritte
			deltaE = 2.0*spin*H;//Berechne Energiedifferenz
			if(deltaE < 0.0){//In diesem Fall immer akzeptieren
				spin = -spin;//Zustand wird geändert
			}
			else if(deltaE > 0.0){//In diesem Fall Vergleich von e^(-beta deltaE) mit Zufallszahl RANDOM()
				if(RANDOM() < exp(-deltaE)){//In diesem Fall wird akzeptiert
					spin = -spin;//Zustand wird geändert
				}
				else;//sonst wird abgelehnt
			}
			m += spin;//Summation für Mittelung der Observablen, hier Magnetisierung
		}
		Datei << H << "\t" << m/(double)T << "\n";//Speichern in Datei
		m = 0.0;//Zurücksetzen der Magnetisierung für erneute Messung (bei nächstem Magnetfeldwert)
		H += 10.0/((double)H_Anzahl-1.0);//Schritt zu nächstem Magnetfeldwert
	}

	Datei.close();

	return 0;
}