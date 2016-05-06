#include <iostream>
#include "fstream"
#include <cmath>
#include <vector>
#include "Aufgabe1.h"

double* Kepler( double* Ort){
	double *Pointer = new double [3];
	double Norm = sqrt( Ort[0]*Ort[0] + Ort[1]*Ort[1] + Ort[2]*Ort[2]);
	for (int i = 0; i < 3  ; ++i)
	{
		Pointer[i] = -Ort[i]/(Norm*Norm*Norm);
	}
	return Pointer;
}
double* alpha09( double* Ort){
	double *Pointer = new double [3];
	double Norm = sqrt( Ort[0]*Ort[0] + Ort[1]*Ort[1] + Ort[2]*Ort[2]);
	for (int i = 0; i < 3  ; ++i)
	{
		Pointer[i] = -Ort[i]/pow(Norm , 0.9);
	}
	return Pointer;
}
double* alpha11( double* Ort){
	double *Pointer = new double [3];
	double Norm = sqrt( Ort[0]*Ort[0] + Ort[1]*Ort[1] + Ort[2]*Ort[2]);
	for (int i = 0; i < 3  ; ++i)
	{
		Pointer[i] = -Ort[i]/pow(Norm , 1.1);
	}
	return Pointer;
}

int main(){

	std::fstream Datei;

	////////////////////////////////// Aufgaben Teil A

	double *Start_Ort = new double [3];
	double *Start_Geschwindigkeit = new double [3];

	Start_Ort[0] = 1.0;
	Start_Ort[1] = 0.0;
	Start_Ort[2] = 0.0;

	Start_Geschwindigkeit[0] = -0.5;
	Start_Geschwindigkeit[1] = 1.0;
	Start_Geschwindigkeit[2] = 0.0;

	Datei.open( "Ergebnisse/Ergebnis_4_A.txt" , std::ios::trunc | std::ios::out);
	Runge_Kutta( 10 , Start_Ort , Start_Geschwindigkeit , Kepler , Datei , 0.01);
	Datei.close();

	Start_Ort[0] = 1.0;
	Start_Ort[1] = 0.0;
	Start_Ort[2] = 0.0;

	Start_Geschwindigkeit[0] = -0.1;
	Start_Geschwindigkeit[1] = 1.0;
	Start_Geschwindigkeit[2] = 0.0;
	Datei.open( "Ergebnisse/Ergebnis_4_A_2.txt" , std::ios::trunc | std::ios::out );
	Runge_Kutta( 10 , Start_Ort , Start_Geschwindigkeit , Kepler , Datei , 0.01);
	Datei.close();

	Start_Ort[0] = 1.0;
	Start_Ort[1] = 0.0;
	Start_Ort[2] = 0.0;

	Start_Geschwindigkeit[0] = -0.5;
	Start_Geschwindigkeit[1] = 1.0;
	Start_Geschwindigkeit[2] = 0.0;
	Datei.open( "Ergebnisse/Ergebnis_4_A_3.txt" , std::ios::trunc | std::ios::out);
	Runge_Kutta( 10 , Start_Ort , Start_Geschwindigkeit , Kepler , Datei , 0.5);
	Datei.close();

	Datei.open( "Ergebnisse/Ergebnis_4_A_4.txt" , std::ios::trunc | std::ios::out);
	Runge_Kutta( 10 , Start_Ort , Start_Geschwindigkeit , Kepler , Datei , 0.7);
	Datei.close();


	Start_Geschwindigkeit[0] = 0.01;
	Start_Geschwindigkeit[1] = 0.01;
	Start_Geschwindigkeit[2] = 0.0;
	Datei.open( "Ergebnisse/Ergebnis_4_A_5.txt" , std::ios::trunc | std::ios::out);
	Runge_Kutta( 10 , Start_Ort , Start_Geschwindigkeit , Kepler , Datei , 0.7);
	Datei.close();


	///////////// Aufgabenteil D

	double *Start_Ort2 = new double [3];
	double *Start_Geschwindigkeit2 = new double [3];

	Start_Ort[0] = 1.0;
	Start_Ort[1] = 0.0;
	Start_Ort[2] = 0.0;

	Start_Geschwindigkeit[0] = -0.5;
	Start_Geschwindigkeit[1] = 1.0;
	Start_Geschwindigkeit[2] = 0.0;

	std::cout << "######## Start Position" << std::endl;
 	std::cout << "RX-Komponente: " << Start_Ort[0] << std::endl;
 	std::cout << "RY-Komponente: " << Start_Ort[1] << std::endl;
 	std::cout << "RZ-Komponente: " << Start_Ort[2] << std::endl;
 	std::cout << "VX-Komponente: " << Start_Geschwindigkeit[0] << std::endl;
 	std::cout << "VY-Komponente: " << Start_Geschwindigkeit[1] << std::endl;
 	std::cout << "VZ-Komponente: " << Start_Geschwindigkeit[2] << std::endl;

	std::cout << "######## Endposition und Endgeschwindigkeit nach T=10" << std::endl;
 	std::cout << "RX-Komponente: " << Runge_Kutta( 10 , Start_Ort , Start_Geschwindigkeit , Kepler , 0.01)[0] << std::endl;
 	std::cout << "RY-Komponente: " << Runge_Kutta( 10 , Start_Ort , Start_Geschwindigkeit , Kepler , 0.01)[1] << std::endl;
 	std::cout << "RZ-Komponente: " << Runge_Kutta( 10 , Start_Ort , Start_Geschwindigkeit , Kepler , 0.01)[2] << std::endl;
 	std::cout << "VX-Komponente: " << Runge_Kutta( 10 , Start_Ort , Start_Geschwindigkeit , Kepler , 0.01)[3] << std::endl;
 	std::cout << "VY-Komponente: " << Runge_Kutta( 10 , Start_Ort , Start_Geschwindigkeit , Kepler , 0.01)[4] << std::endl;
 	std::cout << "VZ-Komponente: " << Runge_Kutta( 10 , Start_Ort , Start_Geschwindigkeit , Kepler , 0.01)[5] << std::endl;

	Start_Ort2[0] = Runge_Kutta( 10 , Start_Ort , Start_Geschwindigkeit , Kepler , 0.01)[0];
	Start_Ort2[1] = Runge_Kutta( 10 , Start_Ort , Start_Geschwindigkeit , Kepler , 0.01)[1];
	Start_Ort2[2] = Runge_Kutta( 10 , Start_Ort , Start_Geschwindigkeit , Kepler , 0.01)[2];
	Start_Geschwindigkeit2[0] = -Runge_Kutta( 10 , Start_Ort , Start_Geschwindigkeit , Kepler , 0.01)[3];
	Start_Geschwindigkeit2[1] = -Runge_Kutta( 10 , Start_Ort , Start_Geschwindigkeit , Kepler , 0.01)[4];
	Start_Geschwindigkeit2[2] = -Runge_Kutta( 10 , Start_Ort , Start_Geschwindigkeit , Kepler , 0.01)[5];


	std::cout << "######## Rückweg Endposition und Endgeschwindigkeit nach T=10" << std::endl;
 	std::cout << "RX-Komponente: " << Runge_Kutta( 10 , Start_Ort2 , Start_Geschwindigkeit2 , Kepler , 0.01)[0] << std::endl;
 	std::cout << "RY-Komponente: " << Runge_Kutta( 10 , Start_Ort2 , Start_Geschwindigkeit2 , Kepler , 0.01)[1] << std::endl;
 	std::cout << "RZ-Komponente: " << Runge_Kutta( 10 , Start_Ort2 , Start_Geschwindigkeit2 , Kepler , 0.01)[2] << std::endl;
 	std::cout << "VX-Komponente: " << Runge_Kutta( 10 , Start_Ort2 , Start_Geschwindigkeit2 , Kepler , 0.01)[3] << std::endl;
 	std::cout << "VY-Komponente: " << Runge_Kutta( 10 , Start_Ort2 , Start_Geschwindigkeit2 , Kepler , 0.01)[4] << std::endl;
 	std::cout << "VZ-Komponente: " << Runge_Kutta( 10 , Start_Ort2 , Start_Geschwindigkeit2 , Kepler , 0.01)[5] << std::endl;



	//////////////////// Aufgaben Teil E
	Datei.open( "Ergebnisse/Ergebnis_4_E_1.txt" , std::ios::trunc | std::ios::out );
	Runge_Kutta( 20 , Start_Ort , Start_Geschwindigkeit , alpha09 , Datei , 0.01);
	Datei.close();

	Datei.open( "Ergebnisse/Ergebnis_4_E_2.txt" , std::ios::trunc | std::ios::out );
	Runge_Kutta( 20 , Start_Ort , Start_Geschwindigkeit , alpha11 , Datei , 0.01);
	Datei.close();

	return 0;
}