#define _USE_MATH_DEFINES 
#include "iostream"
#include "fstream"
#include "cmath"
#include <iomanip>

	double Ferromagnetisch(double Theta , int Anzahl){ // Funktion für die Wechselwirkungsenergie für den ferromagnetischen Zustand
		double Energie = 0;
		for (int ZahlerX = -Anzahl; ZahlerX < Anzahl + 1; ++ZahlerX)
		{
			for (int ZahlerY = -Anzahl; ZahlerY < Anzahl + 1 ; ++ZahlerY)
			{
				if(ZahlerX != 0 || ZahlerY != 0){
					Energie += 1/pow(ZahlerX*ZahlerX + ZahlerY*ZahlerY , 3/2) * ( -3* (ZahlerX * sin(Theta) + ZahlerY* cos( Theta ) ) * ( ZahlerY )/(ZahlerX*ZahlerX + ZahlerY*ZahlerY)+cos(Theta));
				}
			}
		}
		return Energie;
	}

	double AntiFerromagnetisch(double Theta , int Anzahl){// Funktion für die Wechselwirkungsenergie für den antiferromagnetischen Zustand
		double Energie = 0;
		for (int ZahlerX = -Anzahl; ZahlerX < Anzahl + 1; ++ZahlerX)
		{
			for (int ZahlerY = -Anzahl; ZahlerY < Anzahl + 1 ; ++ZahlerY)
			{
				if(ZahlerX != 0 || ZahlerY != 0){
					if( (int)(std::abs( ZahlerX ) + std::abs( ZahlerY ) )% 2 == 0) Energie += 1/pow( ZahlerX*ZahlerX + ZahlerY*ZahlerY , 3/2 ) * ( -3 * ( ZahlerX * sin( Theta ) + ZahlerY * cos( Theta ) ) * ( ZahlerY )/( ZahlerX*ZahlerX + ZahlerY*ZahlerY) + cos( Theta ));
					else Energie += 1/pow(ZahlerX*ZahlerX + ZahlerY*ZahlerY , 3/2) * ( -3* (ZahlerX * sin(Theta) + ZahlerY* cos(Theta) ) * ( -ZahlerY )/(ZahlerX*ZahlerX + ZahlerY*ZahlerY) - cos(Theta));
				}
			}
		}
		return Energie;
	}
	double Ableitung( double (*Funktion)(double , int ) , int Anzahl , double  Breite , double Wert){ // Ableitung für eine Funktion 2 Parameter wobei nach dem einen abgeleitet wird
		return (Funktion(Wert + Breite , Anzahl) - Funktion(Wert - Breite , Anzahl))/(2*Breite);
	}
	double DrehmomentFerromagnet( double theta , int Anzahl){ //Z-komponente des Drehmoment des ferromagnetischen Zustands via Kreuzprodukt
		double MagnetfeldX = 0;
		double MagnetfeldY = 0;
		for( int ZahlerX = - Anzahl ; ZahlerX < Anzahl +1 ; ++ZahlerX)
		{
			for (int ZahlerY = -Anzahl; ZahlerY < Anzahl + 1 ; ++ZahlerY)
			{
				if(ZahlerX != 0 || ZahlerY != 0){
				MagnetfeldX += 1/pow( ZahlerX*ZahlerX + ZahlerY*ZahlerY  , 5/2 ) * ( 3* ZahlerX * ZahlerY );
				MagnetfeldY +=1/pow( ZahlerX*ZahlerX + ZahlerY*ZahlerY  , 5/2 ) * ( 3* ZahlerY * ZahlerY ) - 1/1/pow( ZahlerX*ZahlerX + ZahlerY*ZahlerY  , 3/2 );
				}
			}
		}
		return MagnetfeldY*sin( theta ) - MagnetfeldX * cos( theta );
	}

		double DrehmomentAntiFerromagnet( double theta , int Anzahl){//Z-komponente des Drehmoment des antiferromagnetischen Zustands via Kreuzprodukt
		double MagnetfeldX = 0;
		double MagnetfeldY = 0;
		for( int ZahlerX = - Anzahl ; ZahlerX < Anzahl +1 ; ++ZahlerX)
		{
			for (int ZahlerY = -Anzahl; ZahlerY < Anzahl + 1 ; ++ZahlerY)
			{
				if(ZahlerX != 0 || ZahlerY != 0){
					if( (int)(std::abs( ZahlerX ) + std::abs( ZahlerY ) )% 2 == 0){
						MagnetfeldX += 1/pow( ZahlerX*ZahlerX + ZahlerY*ZahlerY  , 5/2 ) * ( 3* ZahlerX * ZahlerY );
						MagnetfeldY +=1/pow( ZahlerX*ZahlerX + ZahlerY*ZahlerY  , 5/2 ) * ( 3* ZahlerY * ZahlerY ) - 1/1/pow( ZahlerX*ZahlerX + ZahlerY*ZahlerY  , 3/2 );	
					}
					else{
						MagnetfeldX += 1/pow( ZahlerX*ZahlerX + ZahlerY*ZahlerY  , 5/2 ) * ( 3* ZahlerX * ZahlerY );
						MagnetfeldY +=-1/pow( ZahlerX*ZahlerX + ZahlerY*ZahlerY  , 5/2 ) * ( 3* ZahlerY * ZahlerY ) + 1/1/pow( ZahlerX*ZahlerX + ZahlerY*ZahlerY  , 3/2 );
					}
				}
			}
		}
		return MagnetfeldY * sin( theta ) - MagnetfeldX * cos( theta );
	}
	

int main(){
	double Schrittweite = 0.04; // Schrittweite für den Winkel theta
	double Grenze = M_PI; // Grenze für ein Symmetrisches Intervall um 0


	std::fstream Datei("Ergebnisse/Ergebnis_A_N=2.txt" );
	Datei << "#theta/rad" << '\t' << "Energie[mu_0/(4*pi) M^2/a^3] Ferro" << '\t' << "Energie[mu_0/(4*pi) M^2/a^3] Antiferro" << std::endl;
	for (double Zaehler = -Grenze; Zaehler <= Grenze; Zaehler += Schrittweite ){
		Datei << std::setprecision(6) << Zaehler << '\t' << std::setprecision(8) << Ferromagnetisch( Zaehler , 2) << '\t' << '\t' << AntiFerromagnetisch( Zaehler , 2) << std::endl;
	}
	Datei.close();

	Datei.open("Ergebnisse/Ergebnis_A_N=5.txt");
	Datei << "#theta/rad" << '\t' << "Energie[mu_0/(4*pi) M^2/a^3] Ferro" << '\t' << "Energie[mu_0/(4*pi) M^2/a^3] Antiferro" << std::endl;
	for (double Zaehler = -Grenze; Zaehler <= Grenze; Zaehler += Schrittweite ){
		Datei << std::setprecision(6) << Zaehler << '\t' << std::setprecision(8) << Ferromagnetisch( Zaehler , 5) << '\t'<< '\t' << AntiFerromagnetisch( Zaehler , 5) << std::endl;
	}
	Datei.close();

	Datei.open("Ergebnisse/Ergebnis_A_N=10.txt" );
	Datei << "#theta/rad" << '\t' << "Energie[mu_0/(4*pi) M^2/a^3] Ferro" << '\t' << "Energie[mu_0/(4*pi) M^2/a^3] Antiferro" << std::endl;
	for (double Zaehler = -Grenze; Zaehler <= Grenze; Zaehler += Schrittweite ){
		Datei << std::setprecision(6) << Zaehler << '\t' << std::setprecision(8) << Ferromagnetisch( Zaehler , 10) << '\t' << '\t' << AntiFerromagnetisch( Zaehler , 10)  << std::endl;
	}
	Datei.close();



	double Breite = 0.01; // Breite zur bestimmung der Ableitung

	Datei.open("Ergebnisse/Ergebnis_B_N=2.txt" );
	Datei << "#theta/rad" << '\t' << "Drehmoment[mu_0/(4*pi) M^2/a^3] Ferro durch Ableitung" << '\t' << "Drehmoment[mu_0/(4*pi) M^2/a^3] Antiferro durch Ableitung" << '\t' << "Drehmoment[mu_0/(4*pi) M^2/a^3] Ferro durch Kreuz" << '\t' << "Drehmoment[mu_0/(4*pi) M^2/a^3] Antiferro durch Kreuz" << std::endl;
	for (double Zaehler = -Grenze; Zaehler <= Grenze; Zaehler += Schrittweite ){
		Datei << std::setprecision(6) << Zaehler << '\t' << std::setprecision(8) << std::abs( Ableitung( Ferromagnetisch , 2 , Breite , Zaehler)) << '\t' << std::abs(Ableitung( AntiFerromagnetisch , 2 , Breite , Zaehler)) << '\t' << '\t'  << std::abs(DrehmomentFerromagnet( Zaehler , 2 )) << '\t' << '\t'  << std::abs(DrehmomentAntiFerromagnet( Zaehler , 2 ))  << std::endl;
	}
	Datei.close();

	Datei.open("Ergebnisse/Ergebnis_B_N=5.txt" , std::ios::trunc);
	Datei << "#theta/rad" << '\t' << "Drehmoment[mu_0/(4*pi) M^2/a^3] Ferro durch Ableitung" << '\t' << "Drehmoment[mu_0/(4*pi) M^2/a^3] Antiferro durch Ableitung" << '\t' << "Drehmoment[mu_0/(4*pi) M^2/a^3] Ferro durch Kreuz" << '\t' << "Drehmoment[mu_0/(4*pi) M^2/a^3] Antiferro durch Kreuz" << std::endl;
	for (double Zaehler = -Grenze; Zaehler <= Grenze; Zaehler += Schrittweite ){
		Datei << std::setprecision(6) << Zaehler << '\t' << std::setprecision(8) << std::abs( Ableitung( Ferromagnetisch , 5 , Breite , Zaehler)) << '\t' << std::abs(Ableitung( AntiFerromagnetisch , 5 , Breite , Zaehler)) << '\t' << '\t' << std::abs(DrehmomentFerromagnet( Zaehler , 5 )) << '\t' << '\t'  << std::abs(DrehmomentAntiFerromagnet( Zaehler , 5 )) << std::endl;
	}
	Datei.close();
	
	Datei.open("Ergebnisse/Ergebnis_B_N=10.txt" );
	Datei << "#theta/rad" << '\t' << "Drehmoment[mu_0/(4*pi) M^2/a^3] Ferro durch Ableitung" << '\t' << "Drehmoment[mu_0/(4*pi) M^2/a^3] Antiferro durch Ableitung" << '\t' << "Drehmoment[mu_0/(4*pi) M^2/a^3] Ferro durch Kreuz" << '\t' << "Drehmoment[mu_0/(4*pi) M^2/a^3] Antiferro durch Kreuz" << std::endl;
	for (double Zaehler = -Grenze; Zaehler <= Grenze; Zaehler += Schrittweite ){
		Datei << std::setprecision(6) << Zaehler << '\t' << std::setprecision(8) << std::abs( Ableitung( Ferromagnetisch , 10 , Breite , Zaehler)) << '\t' << std::abs(Ableitung( AntiFerromagnetisch , 10 , Breite , Zaehler)) << '\t' << '\t' << std::abs(DrehmomentFerromagnet( Zaehler , 10 )) << '\t' << '\t'  << std::abs(DrehmomentAntiFerromagnet( Zaehler , 10 )) << std::endl;
	}
	Datei.close();

    return 0;
}