#include <iostream>
#include "bit_vector.h"

using namespace std;
typedef unsigned int uint;

int main(int n_args, char* arg_vec[]) {

    uint n = 1000;

    BitVector bitvec(n);
    cout << "bitvec(n-1) = " << bitvec(n-1) << endl;
    cout << "flipping bit" << endl;
    bitvec.flip(n-1);
    cout << "bitvec(n-1) = " << bitvec(n-1) << endl;

    BitMatrix bitmat(n,n,n);
    cout << "bitmat(1,2,3) = " << bitmat(1,2,3) << endl;
    cout << "flipping bit" << endl;
    bitmat.flip(1,2,3);
    cout << "bitmat(1,2,3) = " << bitmat(1,2,3) << endl;

    return 0;
}
