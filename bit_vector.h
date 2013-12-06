/*
    Bool/bit vector and 3D bool/bit matrix implemented using std::bitset.

    Values can be set using operator(), and flipped using flip().

    We leave it as an exercise to the reader to implement 2D- or higher-dimensional matrices.

    For range checking in BitMatrix or BitVector, use something like this (note thatbitset[local_bitset_index] won't be out 
    of range, since the calculation of local_bitset_index above makes sure that local_bitset_index < n_bits_per_bitsets)
    try {
        return mem_local.at(vector_index)[local_bitset_index];
    } catch (...) {
        cout << "something went wrong" << endl;
    }
*/

// #include <iostream>
#include <bitset>
#include <vector>
#include <cmath>    // ceil

using namespace std;

typedef unsigned int uint;

inline int convert_3d_indices_to_linear_index_inline(int x_index, int y_index, int z_index, int n_x, int n_y, int n_z) {
    /* Converts 3d indices to linear index */
    return x_index*n_y*n_z + y_index*n_z + z_index;
}

inline void convert_linear_index_to_3d_indices_inline(int linear_index, int n_x, int n_y, int n_z, int &x_index, int &y_index, int &z_index) {
    /* Converts linear index to 3d indices */
    x_index = linear_index/(n_y*n_z);
    y_index = (linear_index/n_z) % n_y;
    z_index = linear_index % n_z;
}

class BitMatrix{
public:
    uint n_rows, n_cols, n_slices, n_elem;
    uint n_bitsets;

private:
    static const uint n_bits_per_bitset = 8192; // This can/should be tuned, or maybe implemented differently
    vector<bitset<n_bits_per_bitset> > mem_local;

public:
    BitMatrix(uint n_rows, uint n_cols, uint n_slices):
            n_rows(n_rows), 
            n_cols(n_cols), 
            n_slices(n_slices), 
            n_elem(n_rows*n_cols*n_slices), 
            n_bitsets(uint(ceil(double(n_elem)/n_bits_per_bitset))), // We need at least n_bitsets of size n_bits_per_bitset to store n_elem bits
            mem_local(vector<bitset<n_bits_per_bitset> > (n_bitsets)) {

        // cout << "n_bitsets = " << n_bitsets << endl;
        // uint size_of_mem_local = sizeof(mem_local[0])*n_bitsets;
        // cout << "size of mem_local = " << size_of_mem_local << " bits = ";
        // if (size_of_mem_local/1024 < 1)
        //     cout << size_of_mem_local/8 << " bytes.";
        // else if (size_of_mem_local/pow(1024,2) < 1)
        //     cout << size_of_mem_local/1024 << " kilobytes.";
        // else if (size_of_mem_local/pow(1024,3) < 1)
        //     cout << size_of_mem_local/pow(1024,2) << " megabytes.";
        // cout << endl;
    };

    // for non-const BitMatrix
    inline std::bitset<n_bits_per_bitset>::reference operator()(const int x, const int y, const int z) {
        uint linear_index = convert_3d_indices_to_linear_index_inline(x, y, z, n_rows, n_cols, n_slices);
        uint vector_index = linear_index/n_bits_per_bitset;
        uint local_bitset_index = linear_index % n_bits_per_bitset; // we hope that the compiler uses the remainder from the integer division above for this

        return mem_local[vector_index][local_bitset_index];
    };

    // for const BitMatrix
    inline bool operator()(const int x, const int y, const int z) const {
        uint linear_index = convert_3d_indices_to_linear_index_inline(x, y, z, n_rows, n_cols, n_slices);
        uint vector_index = linear_index/n_bits_per_bitset;
        uint local_bitset_index = linear_index % n_bits_per_bitset; // we hope that the compiler uses the remainder from the integer division above for this

        return mem_local[vector_index][local_bitset_index];
    };

    void flip(const int x, const int y, const int z) {
        this->operator()(x, y, z) = !(this->operator()(x, y, z));
    }
};

class BitVector{
public:
    uint n_elem;
    uint n_bitsets;

private:
    static const uint n_bits_per_bitset = 128; // This can/should be tuned, or maybe implemented differently
    vector<bitset<n_bits_per_bitset> > mem_local;

public:
    BitVector(uint n_elem):
            n_elem(n_elem), 
            n_bitsets(uint(ceil(double(n_elem)/n_bits_per_bitset))), // We need at least n_bitsets of size n_bits_per_bitset to store n_elem bits
            mem_local(vector<bitset<n_bits_per_bitset> > (n_bitsets)) {

        cout << "n_bitsets = " << n_bitsets << endl;
        uint size_of_mem_local = sizeof(mem_local[0])*n_bitsets;
        cout << "size of mem_local = " << size_of_mem_local << " bits" << endl;
    };

    // for non-const BitVector
    inline std::bitset<n_bits_per_bitset>::reference operator()(const int x) {

        uint vector_index = x/n_bits_per_bitset;
        uint local_bitset_index = x % n_bits_per_bitset; // we hope that the compiler uses the remainder from the integer division above for this

        return mem_local[vector_index][local_bitset_index];
    };

    // for const BitVector
    inline bool operator()(const int x) const {

        uint vector_index = x/n_bits_per_bitset;
        uint local_bitset_index = x % n_bits_per_bitset; // we hope that the compiler uses the remainder from the integer division above for this

        return mem_local[vector_index][local_bitset_index];
    };

    void flip(const int x) {
        this->operator()(x) = !(this->operator()(x));
    }
};
