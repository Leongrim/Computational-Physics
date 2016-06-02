#include <iostream>
#include <cmath>
#include <string>
#include "fstream"

const int Anzahl = 21;

void E_Feld( int Ort_x , int Ort_y , double phi[ Anzahl ][ Anzahl ] , double& E_X , double& E_Y , double Delta){
	E_X = ( phi[ Ort_x - 1 ][ Ort_y ] - phi[ Ort_x + 1 ][ Ort_y ] )/(2.0*Delta*Delta);
	E_Y = ( phi[ Ort_x ][ Ort_y - 1 ] - phi[ Ort_x ][ Ort_y + 1 ] )/(2.0*Delta*Delta);
}

bool Genauigkeit( double phi[ Anzahl ][ Anzahl ] , double phi_temp[ Anzahl ][ Anzahl] ){
	double Praezision = 1e-5;
	int zahler = 0;
	for (int i = 1; i < Anzahl - 1; ++i)
	{
		for (int j = 1; j < Anzahl-1; ++j)
		{
			if (  phi[ i ][ j ] - phi_temp[ i ][j ]   < Praezision)
			{
				zahler++;
			}
		}
	}
	if (zahler == ( Anzahl - 2 )*( Anzahl - 2))
	{
		return false;
	}else return true;
}

double rho_A( int Ort_x , int Ort_y){
	return 0;
}
double rho_C( int Ort_x , int Ort_y){
	if (Ort_x == 10 && Ort_y == 10)
	{
		return 1.0;
	}else return 0.0;
}
double rho_E( int Ort_x , int Ort_y){
	if (Ort_x == 5 && Ort_y == 5)
	{
		return 1.0;
	}else if( Ort_x == 15 && Ort_y == 15){
		return -1.0;
	}else return 0.0;
}

void Poisson( double phi[ Anzahl ][ Anzahl ] , double (*rho)(int , int) , double Delta , std::string Datei){
	double phi_temp[ Anzahl ][ Anzahl ];
	do{
		for (int i = 0; i < Anzahl  ; ++i)
		{
			for (int j = 0; j < Anzahl  ; ++j)
			{
				phi_temp[ i ][ j ] = phi[ i ][ j ];		
			}
		}
		for (int i = 1; i < Anzahl - 1 ; ++i)
		{
			for (int j = 1; j < Anzahl - 1 ; ++j)
			{
				phi[ i ][ j ] = 0.25*( phi_temp[ i - 1 ][ j ] + phi_temp[ i + 1 ][ j ] + phi_temp[ i ][ j - 1] + phi_temp[ i ][ j + 1] + Delta * Delta * rho( i , j) );		
			}
		}
	}while( Genauigkeit( phi , phi_temp ));
	std::fstream Save;
	Save.open( (Datei + ".txt").data() , std::ios::trunc | std::ios::out);

	double E_X;
	double E_Y;

	for (int i = 0; i < Anzahl ; ++i)
	{
		for (int j = 0; j < Anzahl ; ++j)
		{
			Save << i*Delta << "\t\t" << j*Delta << "\t\t" << phi[ i ][ j ] << "\n";
		}
	}
	Save.close();
	Save.open( (Datei + "_E_Feld.txt").data() , std::ios::trunc | std::ios::out );
	for (int i = 1; i < Anzahl - 1 ; ++i)
	{
		for (int j = 1; j < Anzahl - 1 ; ++j)
		{
			E_Feld( i , j , phi , E_X , E_Y , Delta );
			Save << i*Delta << "\t\t" << j*Delta << "\t\t" << E_X << "\t\t" << E_Y << "\t\t" << sqrt(E_X*E_X + E_Y*E_Y) << "\n";
		}
	}	
}


int main(){
	std::string Aufgabe = "Ergebnisse/Ergebnis_A";
	double Delta = 0.05;
	double phi[ Anzahl ][ Anzahl ];
	for (int i = 0; i < Anzahl ; ++i)
	{
		for (int j = 0; j < Anzahl ; ++j)
		{
			phi[ i ][ j ] = 0.0;
		}
	}
	Poisson( phi , rho_A , Delta , Aufgabe);

	Aufgabe = "Ergebnisse/Ergebnis_B";
	for (int i = 0; i < Anzahl ; ++i)
	{
		for (int j = 0; j < Anzahl  ; ++j)
		{
			if (j == Anzahl-1 )
			{
				phi[ i ][ j ] = 1.0;			
			}else{
				phi[ i ][ j ] = 0.0;	
			}
		}
	}
	Poisson( phi , rho_A , Delta , Aufgabe);

	Aufgabe = "Ergebnisse/Ergebnis_C";
	for (int i = 0; i < Anzahl ; ++i)
	{
		for (int j = 0; j < Anzahl ; ++j)
		{
			phi[ i ][ j ] = 0.0;
		}
	}
	Poisson( phi , rho_C , Delta , Aufgabe);

	Aufgabe = "Ergebnisse/Ergebnis_E";
	for (int i = 0; i < Anzahl ; ++i)
	{
		for (int j = 0; j < Anzahl ; ++j)
		{
			phi[ i ][ j ] = 0.0;
		}
	}
	Poisson( phi , rho_E , Delta , Aufgabe);


	return 0;
}