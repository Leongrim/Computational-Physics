#include <iostream>
#include <cmath>
#include "fstream"

//namespace Aufgabe2{
	double Potetntial_A(double Xwert){
		int Intervall = 100;
		double Grenze = 1.0;
		double Breite = 2.0*Grenze/Intervall;
		double Ort[3];
		Ort[0]= -Grenze + Breite / 2.0;
		Ort[1]= -Grenze + Breite / 2.0;
		Ort[2]= -Grenze + Breite / 2.0;
		double Integral = 1.0/sqrt(( Xwert - Ort[0])*( Xwert - Ort[0]) + Ort[1]*Ort[1] + Ort[2]*Ort[2]);
		for (int Xzaehler =0; Xzaehler < Intervall; Xzaehler++)
		{
			Ort[0] = Ort[0] + Breite;
			for (int Yzaehler = 0; Yzaehler < Intervall; Yzaehler++)
			{
				Ort[1] = Ort[1] + Breite;
				for (int Zzaehler = 0; Zzaehler < Intervall; Zzaehler++)
				{
					Ort[2] = Ort[2] +  Breite;
					Integral = Integral + 1.0/sqrt( ( Xwert - Ort[0])*( Xwert - Ort[0]) + Ort[1]*Ort[1] + Ort[2]*Ort[2] );
				}
				Ort[2] = -Grenze + Breite/2.0;
			}
			Ort[1]= -Grenze + Breite/2.0;
		}
		return Integral*Breite*Breite*Breite;
	}

	double Potetntial_C(double Xwert){
		int Intervall = 100;
		double Grenze = 1.0;
		double Breite = 2.0*Grenze/Intervall;
		double Ort[3];
		Ort[0]= -Grenze + Breite / 2.0;
		Ort[1]= -Grenze + Breite / 2.0;
		Ort[2]= -Grenze + Breite / 2.0;
		double Integral = Ort[0]/sqrt( ( Xwert - Ort[0])*( Xwert - Ort[0]) + Ort[1]*Ort[1] + Ort[2]*Ort[2]);
		for (int Xzaehler =0; Xzaehler < Intervall; Xzaehler++)
		{
			Ort[0] = Ort[0] + Breite;
			for (int Yzaehler = 0; Yzaehler < Intervall; Yzaehler++)
			{
				Ort[1] = Ort[1] + Breite;
				for (int Zzaehler = 0; Zzaehler < Intervall; Zzaehler++)
				{
					Ort[2] = Ort[2] +  Breite;
					Integral = Integral + Ort[0]/sqrt( ( Xwert - Ort[0])*( Xwert - Ort[0]) + Ort[1]*Ort[1] + Ort[2]*Ort[2] );
				}
				Ort[2] = -Grenze + Breite/2.0;
			}
			Ort[1]= -Grenze + Breite/2.0;
		}
		return Integral*Breite*Breite*Breite;
	}


	int main()
	{
		std::fstream Datei;
		Datei.open("Ergebnisse/Ergebnis.txt" , std::ios::trunc | std::ios::out);
		Datei << "#x/a" << '\t' << "Potential zu rho_a" <<  '\t' << '\t' << "Potential zu rho_c" << std::endl;

		for (int i = -00; i <= 100; ++i)
		{
			Datei << 0.1*i << '\t' << '\t' <<  Potetntial_A( (double) 0.1*i ) << '\t' << '\t' << Potetntial_C( (double) 0.1*i)  << std::endl;
		}
		Datei.close();
		return 0;
	}
//}