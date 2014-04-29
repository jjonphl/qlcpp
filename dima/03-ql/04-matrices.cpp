#include "qlpch.h"

using namespace QuantLib;
using namespace std;

void testMatrix1() {
    Matrix A(3,3);
    A[0][0]=0.2; A[0][1]=8.4; A[0][2]=1.5;
    A[1][0]=0.6; A[1][1]=1.4; A[1][2]=7.3;
    A[2][0]=0.8; A[2][1]=4.4; A[2][2]=3.2;

    Real det = determinant(A);
    QL_REQUIRE(! close(det, 0.0), "Non invertible matrix!");

    Matrix invA = inverse(A);

    cout << A << endl;
    cout << "--------------------" << endl;
    cout << transpose(A) << endl;
    cout << "--------------------" << endl;
    cout << det << endl;
    cout << "--------------------" << endl;
    cout << invA << endl;
    cout << "--------------------" << endl;
    cout << A*invA << endl;
}

// matrix decompositions
void testMatrix2() {
    Matrix A(3,3);
    A[0][0]=1.0; A[0][1]=0.9; A[0][2]=0.7;
    A[1][0]=0.9; A[1][1]=1.0; A[1][2]=0.4;
    A[2][0]=0.7; A[2][1]=0.4; A[2][2]=1.0;

    SymmetricSchurDecomposition schurDec(A);
    SVD svdDec(A);

    cout << "Schur Eigenvalues: " << endl;
    cout << schurDec.eigenvalues() << endl;
    cout << "--------------------" << endl;
    cout << "Schur Eigenvector.Mat: " << endl;
    cout << schurDec.eigenvectors() << endl;
    cout << "--------------------" << endl;
    cout << "Cholesky: " << endl;
    cout << CholeskyDecomposition(A) << endl;
    cout << "--------------------" << endl;
    cout << "SVD U: " << endl;
    cout << svdDec.U() << endl;
    cout << "--------------------" << endl;
    cout << "SVD V: " << endl;
    cout << svdDec.V() << endl;
    cout << "--------------------" << endl;
    cout << "SVD Diag D: " << endl;
    cout << svdDec.singularValues() << endl;
    cout << "--------------------" << endl;
    cout << "Pseudo Sqrt: " << endl;
    cout << pseudoSqrt(A) << endl;
    cout << "--------------------" << endl;

}
int main(int argc, char *argv[]) {
    //testMatrix1();

    testMatrix2();

    return 0;
}
