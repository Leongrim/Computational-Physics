#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <string>
#include "Eigen/Dense"
#include "Eigen/Eigenvalues"

using namespace std;
using Eigen::MatrixXd;
using Eigen::VectorXcd;




MatrixXd init_matrix(){
    MatrixXd A(4, 4);
    A(0, 0) = 1;
    A(1, 0) =-2;
    A(2, 0) = 2;
    A(3, 0) = 4;
    A(0, 1) = -2;
    A(1, 1) = 3;
    A(2, 1) = -1;
    A(3, 1) = 0;
    A(0, 2) = 2;
    A(1, 2) =-1;
    A(2, 2) = 6;
    A(3, 2) = 3;
    A(0, 3) = 4;
    A(1, 3) = 0;
    A(2, 3) = 3;
    A(3, 3) = 5;
    return A;
}

MatrixXd unit_matrix(int d){
  MatrixXd unit(d,d);
  unit.setZero();
  for(int k=0; k<d; k++){
    unit(k,k) = 1;
  }
return unit;
}


MatrixXd jacobi_matrix(MatrixXd unit, int p, int q, double theta){

  double tan_phi = pow(-1,signbit(theta))/(abs(theta) + sqrt(theta*theta + 1));
  double cos_phi = 1/sqrt(tan_phi*tan_phi + 1);
  double sin_phi = tan_phi * cos_phi;

  unit(p,p) = cos_phi;
  unit(q,q) = cos_phi;
  unit(p,q) = sin_phi;
  unit(q,p) = -1 * sin_phi;

  MatrixXd J = unit;

  return J;
}





MatrixXd jacobi_rotation(MatrixXd A, int iterations){
  MatrixXd E = unit_matrix(4);
  MatrixXd A_rotated = A;
  while(iterations > 0){
  for(int p=0; p<4; p++){
    for(int q=1; p<4; p++){
      double theta = (A(q,q) - A(p,p))/2*A(q,p);
      MatrixXd J_pq = jacobi_matrix(E, p, q, theta);
      MatrixXd J_pq_T = J_pq.transpose();
      cout << p <<","<< q<<":\n" << J_pq << "\n";
      cout << p <<","<< q<<":\n" << J_pq_T<< "\n";
      A_rotated = J_pq_T * A_rotated * J_pq;
      iterations--;
   }
    }
  }




  return A_rotated;
}



int main() {


  MatrixXd A = init_matrix();
  cout << A << "\n";
  VectorXcd eigenvalues = A.eigenvalues();
  cout << eigenvalues << "\n";

  cout << jacobi_rotation(A, 100) << "\n";

  // cout << cos(M_PI)<<"\n";

  return 0;

}

