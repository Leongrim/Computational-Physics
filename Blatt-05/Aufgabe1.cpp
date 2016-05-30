#include <iostream>
#include <cmath>
#include <cstdlib>

//Zufallszahlengenerator
double rand_gen(double min, double max){
    double f = (double)rand() /(double) RAND_MAX;
    return min + f * (max - min);
}
//Lennard-Jones-Potential
double Lennard_Jones(double ort1x, double ort1y, double ort2x, double ort2y){
    double abstandx = ort1x - ort2x;
    double abstandy = ort1y - ort2y;
    double betrag = sqrt(abstandx*abstandx + abstandy*abstandy);
    double r6 = 1.0/pow(betrag, 6.0);
    return 4.0 * r6 * (r6 - 1.0);
}
//Lennard-Jones-Kraft
double* Kraft(double ort1x, double ort1y, double ort2x, double ort2y){
    double* abstand = new double[2];
    abstand[0] = ort1x - ort2x;
    abstand[1] = ort1y - ort2y;
    double betrag = sqrt(abstand[0]*abstand[0] + abstand[1]*abstand[1]);
    double r6 = 1.0/pow(betrag, 6.0);
    abstand[0] *= 48.0 * r6 * (r6 - 1.0/2.0) / (betrag*betrag);
    abstand[1] *= 48.0 * r6 * (r6 - 1.0/2.0) / (betrag*betrag);
    return abstand;
}
//Gesamtkraft
double* Gesamtkraft(double ort1x, double ort1y, double* ort2x, double* ort2y, double L, int N){
    //double* abstand = new double[2];
    double* Gesamtkraft = new double[2];
    for(int i = 0; i < N; ++i){
        if (ort1x != ort2x[i] || ort1y != ort2y[i]){
            for (int n_x = -1; n_x <= 1; ++n_x){
                for (int n_y = -1; n_y <= 1; ++n_y){
                    //abstand[0] = ort1x - ort2x[i];
                    //abstand[1] = ort1y - ort2y[i];
                    //double betrag = sqrt((abstand[0] + n_x*L)*(abstand[0] + n_x*L) + (abstand[1] + n_y*L)*(abstand[1] + n_y*L));
                    Gesamtkraft[0] += Kraft(ort1x + n_x*L, ort1y + n_y*L, ort2x[i], ort2y[i])[0];// * (abstand[0] + n_x*L) / betrag;
                    Gesamtkraft[1] += Kraft(ort1x + n_x*L, ort1y + n_y*L, ort2x[i], ort2y[i])[1];// * (abstand[1] + n_y*L) / betrag;
                }
            }
        }
    }
    //delete[] abstand;
    return Gesamtkraft;
}
//Verlet-Algorithmus
double* Verlet(double* ort1x, double* ort1y, double* velx, double* vely, double h, double L, int N){
    double* ort2x = new double[N];
    double* vel2x = new double[N];
    for(int i = 0; i < N; ++i){
        ort2x[i] = ort1x[i] + velx[i]*h + 1.0/2.0 * Gesamtkraft(ort1x[i], ort1y[i], ort1x, ort1y, L, N)[0] * h*h;
        //vel2x[i] = velx[i] + (Gesamtkraft(ort1x[i], ort1y[i], ort1x, ort1y, L, N)[0] + Gesamtkraft(ort2x[i], ort2y[i], ort2x, ort2y, L, N)[0] * h/2.0;
    }
    return ort2x;
}
//Schwerpunktsgeschwindigkeit
double* Schwerpunkt(double* velx, double* vely, int N){
    double* sum_vel = new double[2];
    for(int i = 0; i < N; ++i){
        sum_vel[0] += velx[i];
        sum_vel[1] += vely[i];
    }
    sum_vel[0] = sum_vel[0]/N;
    sum_vel[1] = sum_vel[1]/N;
    return sum_vel;
}
//Potentielle Energie
double Pot(double* ortx, double* orty, int N){
    double Pot = 0.0;
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < N; ++j){
        if(i < j-1) Pot += Lennard_Jones(ortx[i], orty[i], ortx[j], orty[j]);
        }
    }
    return Pot;
}
//Kinetische Energie
double Kin(double* velx, double* vely, int N){
    double T = 0.0;
    for(int i = 0; i < N; ++i){
        T += velx[i]*velx[i] + vely[i]*vely[i];
    }
    T = T/2.0;
    return T;
}
//Temperatur
double Temperatur(double* velx, double* vely, int N){
    double N_f = (2.0 * N - 2.0);
    double T = 0.0;
    for(int i = 0; i < N; ++i){
        T += velx[i]*velx[i] + vely[i]*vely[i];
    }
    T = T/N_f;
    return T;
}
//Initialisierungsfunktion
void initialize(double* ortx, double* orty, double* velx, double* vely, int N, double L, double T_0){
    int Teilchenzahl = 0;//Variable zur "richtigen" Speicherung der Ortskoordinaten im Array analog zu den Geschwindigkeitskoordinaten
    for(int n = 0; n <= 3; ++n){
    	for (int m = 0; m <= 3; ++m){
    	ortx[Teilchenzahl] = 1.0/8.0 * (1.0 + 2.0*n) * L;//Plätze der x-Koordinate des Ortes
		orty[Teilchenzahl] = 1.0/8.0 * (1.0 + 2.0*m) * L;//Plätze der y-Koordinate des Ortes
        Teilchenzahl++;
		}
    }
    double sum_velx_vorher = 0;
    double sum_vely_vorher = 0;
    for(int i = 0; i < N; ++i){
		velx[i] = rand_gen(-1.0, 1.0);//Ziehe Zufallszahl für die x-Koordinate der Geschwindigkeit
		sum_velx_vorher += velx[i];//Summiere alle x-Koordinaten der Geschwindigkeit auf
		vely[i] = rand_gen(-1.0, 1.0);//Ziehe Zufallszahl für die y-Koordinate der Geschwindigkeit
		sum_vely_vorher += vely[i];//Summiere alle y-Koordinaten der Geschwindigkeit auf
	}
    sum_velx_vorher = sum_velx_vorher/N;
    sum_vely_vorher = sum_vely_vorher/N;
	std::cout << "sum_velx_vorher: " << sum_velx_vorher << "\tsum_vely_vorher: " << sum_vely_vorher << std::endl;
	//Test, ob die Schwerpunktsgeschwindigkeit nach der Reskalierung weiterhin 0 ist
    double sum_velx_nachher = 0;
    double sum_vely_nachher = 0;
    for(int i = 0; i < 16; ++i){
		velx[i] -= sum_velx_vorher;//Reskalierung, damit die Schwerpunktsgeschwindigkeit 0 ist für die x-Koordinate
		sum_velx_nachher += velx[i];
		vely[i] -= sum_vely_vorher;//Reskalierung, damit die Schwerpunktsgeschwindigkeit 0 ist für die y-Koordinate
		sum_vely_nachher += vely[i];
	}
	sum_velx_nachher = sum_velx_nachher/N;
    sum_vely_nachher = sum_vely_nachher/N;
    std::cout << "sum_velx_nachher: " << sum_velx_nachher << "\tsum_vely_nachher: " << sum_vely_nachher << std::endl;
    double N_f = (2.0 * N - 2.0);//Anzahl der Freiheitsgrade
    double T = 0.0;//Temperatur
    for(int i = 0; i < N; ++i){
        T += velx[i]*velx[i] + vely[i]*vely[i];
    }
    T = T/N_f;
    double alpha = sqrt(T_0/T);//Skalierungsfaktor
    for(int i = 0; i < N; ++i){//Skaliere Geschwindigkeiten mit Skalierungsfaktor
        velx[i] = alpha * velx[i];
        vely[i] = alpha * vely[i];
    }
    //Test, ob die Schwerpunktsgeschwindigkeit nach der Skalierung weiterhin 0 ist
    double sum_velx_nachher2 = 0;
    double sum_vely_nachher2 = 0;
    for(int i = 0; i < 16; ++i){
        sum_velx_nachher2 += velx[i];
        sum_vely_nachher2 += vely[i];
    }
    sum_velx_nachher2 = sum_velx_nachher2/N;
    sum_vely_nachher2 = sum_vely_nachher2/N;
    std::cout << "sum_velx_nachher2: " << sum_velx_nachher2 << "\tsum_vely_nachher2: " << sum_vely_nachher2 << std::endl;
}

int main(int argc, char* argv[]){
	int N = 16;//Teilchenzahl
    double L = 1.0;//Seitenlänge des Systems
    double h = 0.01;//Schrittweite
	double Temp = 1.0;//Anfangstemperatur
    double rx[N];//x-Koordinate des Ortes
    double ry[N];//y-Koordinate des Ortes
    double vx[N];//x-Koordinate der Geschwindigkeit
    double vy[N];//y-Koordinate der Geschwindigkeit
    initialize(rx, ry, vx, vy, N, L, Temp);
    std::cout << "x\ty\tv_x\t\tv_y" << std::endl;
    for(int i = 0; i < 16; ++i){
    	std::cout << rx[i] << "\t" << ry[i] << "\t" << vx[i] << "\t" << vy[i] << std::endl;
	}
    //Test der Lennard-Jones-Funktion
    std::cout << "Lennard-Jones-Potential: " << Lennard_Jones(1.0, 3.0, 2.0, 4.0) << std::endl;
    //Test der Schwerpunktsfunktion
    std::cout << "Schwerpunktsgeschwindigkeit x: " << Schwerpunkt(vx, vy, N)[0] << std::endl;
    std::cout << "Schwerpunktsgeschwindigkeit y: " << Schwerpunkt(vx, vy, N)[1] << std::endl;
    //Test der potentiellen Energiefunktion
    std::cout << "Potentielle Energie: " << Pot(rx, ry, N) << std::endl;
    //Test der kintetischen Energiefunktion
    std::cout << "Kinetische Energie: " << Kin(vx, vy, N) << std::endl;
    //Test der Temperaturfunktion
    std::cout << "Temperatur: " << Temperatur(vx, vy, N) << std::endl;
    //Test der Kraftfunktion
    double Kraftx = 0.0;
    double Krafty = 0.0;
    int Teilchen = 13;
    for(int i = 0; i < N; ++i){
        if(i != Teilchen) Kraftx += Kraft(rx[Teilchen], ry[Teilchen], rx[i], ry[i])[0];
        if(i != Teilchen) Krafty += Kraft(rx[Teilchen], ry[Teilchen], rx[i], ry[i])[1];
    }
    std::cout << "Kraft x: " << Kraftx << std::endl;
    std::cout << "Kraft y: " << Krafty << std::endl;
    //Test der Gesamtkraftfunktion
    /*double Gesamtkraftx = 0.0;
    double Gesamtkrafty = 0.0;
    int Teilchen = 0;
    for(int i = 0; i < N; ++i){
        if(i != Teilchen) Gesamtkraftx += Gesamtkraft(rx[Teilchen], ry[Teilchen], rx[i], ry[i])[0];
        if(i != Teilchen) Gesamtkrafty += Kraft(rx[Teilchen], ry[Teilchen], rx[i], ry[i])[1];
    }*/
    std::cout << "Gesamtkraft x: " << Gesamtkraft(rx[Teilchen], ry[Teilchen], rx, ry, L, N)[0] << std::endl;
    std::cout << "Gesamtkraft y: " << Gesamtkraft(rx[Teilchen], ry[Teilchen], rx, ry, L, N)[1] << std::endl;
    //Test des Verlet-Algorithmus
    //std::cout << "Verlet x: " << Verlet(rx, ry, vx, vy, h, L, N)[6] << std::endl;
    std::cout << "Verlet x" << std::endl;
    for(int i = 0; i < 16; ++i){
        std::cout << Verlet(rx, ry, vx, vy, h, L, N)[i] << std::endl;
    }

    return 0;
}

/*

int main(){
    
    
    // ===================
    //     Initialize
    // ===================
    
    // Set configuration parameters
    int nPart = 16;        // Number of particles
    double density = 0.85;     // Density of particles
    double mass = 1.0;           // Particles' mass
    int nDim = 2;           // The dimensionality of the system (3D in our case)
    
    // Set simulation parameters
    double dt = 0.0001;        // Integration time
    double dt2 = dt*dt;        // Integration time, squared
    double Temp = 2.0;         // Simulation temperature
    double nu = 0.1;           // Thermostat parameter - frequency of collisions with the heat bath
    double velSTD = sqrt(Temp/mass); // Thermostat parameter - standard deviation of the velocity
    
    int nSteps = 10000;     // Total simulation time (in integration steps)
    double sampleFreq = 10.0;    // Sampling frequency
    int sampleCounter = 0;  // Sampling counter
    double printFreq = 100.0;    // Printing frequency
    
    // Set initial configuration
    [coords L] = initCubicGrid(nPart,density);
    
    // Set initial velocities with random numbers
    vels = zeros(nDim,nPart);
    for(int part = 1, part <= nPart, ++part){
        vels(:,part) = randGauss(0,velSTD,nDim);
    }
    
    // Set initial momentum to zero
    double totV = sum(vels,2)/nPart; // Center of mass velocity
    for(int dim = 1; dim <= nDim; ++dim){
        vels(dim,:) = vels(dim,:) - totV(dim);    // Fix any center-of-mass drift
    }
    
    // Set initial kinetic energy to nDim*KbT/2
    double totV2 = sum(dot(vels,vels))/nPart;  // Mean-squared velocity
    double velScale = sqrt(nDim*Temp/totV2);   // Velocity scaling factor
    for(int dim = 1, dim <= nDim; ++dim){
        vels(dim,:) = vels(dim,:)*velScale;    
    }
    
    // Calculate initial forces
    forces = LJ_Force(coords,L);
    
    // Start up an empty histogram to follow the velocity of the particles 
    h.count = 0;
    h.range = [-10 10];
    h.increment = 0.1;
    h.outFreq = 1000;
    h.saveFileName = 'LJvel_hist.dat';
    
    
    // ===================
    // Molecular Dynamics
    // ===================
    
    time = 0; // Following simulation time
    
    for step = 1:nSteps
        
        // === First integration step ===
        
        // Update positions - All coordinates are updated at once
        coords = coords + dt*vels + 0.5*dt2*forces; 
        
        // Apply periodic boundary conditions
        for part=1:nPart
            coords(:,part) = PBC3D(coords(:,part),L);
        end
        
        // Update velocities - All velocities are updated at once
        vels = vels + 0.5*dt*forces;
         
        // === Calculate new forces ===
        forces = LJ_Force(coords,L);
        
        // === Second integration step ===
        
        // Update velocities - All velocities are updated at once
        vels = vels + 0.5*dt*forces;
        
        // Implement the Andersen thermostat
        for part =1:nPart
            // Test for collisions with the Andersen heat bath
            if (rand < nu*dt)
                // If the particle collided with the bath, draw a new velocity
                // out of a normal distribution
                vels(:,part) = randGauss(0,velSTD,nDim);
            end
        end
        
       
        // === Move time forward ===
        time = time + dt;
        
        // === Sample ===
        if mod(step,sampleFreq) == 0
            sampleCounter = sampleCounter + 1;
            
            for part=1:nPart
                // Sample the velocity of the particles (only x component)
                h = histogram(h,vels(1,part));
            end
           
        end
        
        if mod(step,printFreq) == 0
            step // Print the step 
        end
        
    end
    
    
    // ===================
    // Simulation results
    // ===================
    
    // Plot the resulting velocity histogram
    h.histo = h.histo/(h.count*h.increment); // Normalize
    bar(h.values,h.histo);


	return 0;
}
*/