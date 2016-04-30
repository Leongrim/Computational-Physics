#include <iostream>
#include <cmath>

//Simpsonregel von Blatt 1
double Simpsonregel(double (*Integrand)(double), double unten, double oben, unsigned int Intervallanzahl){
	double Intervallbreite = (oben-unten)/Intervallanzahl;
	double stuetzstelle = unten + Intervallbreite;
	double Summe = 0;
	for (int i = 1; i < Intervallanzahl/2; ++i){
		Summe += 4.0/3.0*Integrand(stuetzstelle);
		stuetzstelle += Intervallbreite;
		Summe += 2.0/3.0*Integrand(stuetzstelle);
		stuetzstelle += Intervallbreite;
	}
	Summe += 4.0/3.0*Integrand(stuetzstelle) + 1.0/3.0*(Integrand(unten) + Integrand(oben));
	Summe *= Intervallbreite;
	return Summe;
}


//Zu Aufgabenteil a)
double f(double x){//Funktion fuer das erste Integral
	return exp(x)/x;
}

double g(double s){//Funktion zur Berechnung des Hauptwertes
	double delta = 0.0000001;//Achtung! Dieses delta muss dasselbe sein wie in der main().
	return (exp(delta*s)-1)/s;
}

//Zu Aufgabenteil b)
double h(double x){//Funktion fuer das zweite Integral nach partieller Integration
	return 2*exp(-x)*sqrt(x);
}

int main(){
	//Zu Aufgabenteil a)

	//Variable fuer die Verschiebung bei der Hauptwertberechnung
	double delta = 0.0000001;//Achtung! Dieses delta muss dasselbe sein wie in g(double s).
	//Berechnung des Hauptwertes:
	double int1 = Simpsonregel(f, -1.0, -delta, 5000)+Simpsonregel(f, delta, 1.0, 5000)+Simpsonregel(g, -1.0, 1.0, 5000);
	std::cout.precision(8);
	std::cout << "Integral 1 via Simpsonregel: " << int1 << "\n\n";

	//Zu Aufgabenteil b)

	//Berechnung des Integralwertes bei Variation der Intervallanzahl respektive Intervallbreite der Integrationsroutine
	//Wie bei auf Blatt 1 wird die Intervallbreite in jedem Schritt halbiert bzw. die Intervallanzahl verdoppelt.
	int n = 1;
	do {
		n++;
	} while (std::abs((Simpsonregel(h, 0.0, 100.0, pow(2, n+1))-Simpsonregel(h, 0.0, 100.0, pow(2, n)))/Simpsonregel(h, 0.0, 100.0, pow(2, n)))>1e-5);

	double int2 = Simpsonregel(h, 0.0, 100.0, pow(2, n+1));//Dies ist der Wert des Integrals bei einer relativen Abweichung <10^-5
	double Abweichung = std::abs((int2-Simpsonregel(h, 0.0, 100.0, pow(2, n)))/Simpsonregel(h, 0.0, 100.0, pow(2, n)));//genauer Wert der Abweichung
	//Ausgaben:
	std::cout.precision(9);
	std::cout << "Integral 2 via Simpsonregel: " << int2 << " bei einer Intervallanzahl von " << pow(2, n+1) << std::endl;
	std::cout << "Die Abweichung beträgt: " << Abweichung << std::endl;

	//Analytisch ergibt sich der exakte Wert sqrt(pi)
	double exakt = sqrt(M_PI);
	std::cout << "Exakter Wert sqrt(pi): " << exakt << std::endl;
	//Dazu relativer Fehler:
	double rel = std::abs((int2-exakt)/exakt);
	std::cout << "Relativer Fehler: " << rel << std::endl;
	std::cout << "Integral 2 via Simpsonregel bei einer Intervallanzahl von 10000000 ergibt den 'exakten' Wert: " << Simpsonregel(h, 0.0, 100.0, 10000000) << std::endl;


	return 0;
}