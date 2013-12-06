/*
    Bool/bit vector and 3D bool/bit matrix implemented using std::bitset and std::vector.

    Values can be set using operator(), and flipped using flip().

    We leave it as an exercise to the reader to implement 2D- or higher-dimensional matrices.

    The reason for doing this:
        Having 1000^3 ints in memory would take up 1000^3 * 16 bits = 16 Gbit ~ 1907 MiB
        Using one bit for each number only takes up          1000^3 =  1 Gbit ~  119 MiB
*/

// #include <iostream>
#include <bitset>
#include <vector>
#include <cmath>    // ceil

using namespace std;

typedef unsigned int uint;

class BitVector{
public:
    uint n_elem;
    uint n_bitsets;

private:
    static const uint n_bits_per_bitset = 128; // This can/should be tuned, or maybe implemented differently -- REMEMBER TO CHANGE THIS VALUE IN LINE 81 AS WELL
    vector<bitset<n_bits_per_bitset> > mem_local;

public:
    BitVector(uint n_elem):
            n_elem(n_elem), 
            n_bitsets(uint(ceil(double(n_elem)/n_bits_per_bitset))), // We need at least n_bitsets of size n_bits_per_bitset to store n_elem bits
            mem_local(vector<bitset<n_bits_per_bitset> > (n_bitsets)) {
    };

    void flip(const int x) {
        this->operator()(x) = !(this->operator()(x));
    }

    // for non-const BitVector
    inline std::bitset<n_bits_per_bitset>::reference operator()(const int x) {

        uint vector_index = x/n_bits_per_bitset;
        uint local_bitset_index = x % n_bits_per_bitset; // We hope that the compiler uses the remainder from the integer division above for this

        return mem_local[vector_index][local_bitset_index];
    };

    // for non-const BitVector
    inline std::bitset<n_bits_per_bitset>::reference operator[](const int x) {

        uint vector_index = x/n_bits_per_bitset;
        uint local_bitset_index = x % n_bits_per_bitset;

        return mem_local[vector_index][local_bitset_index];
    };

    // for const BitVector
    inline bool operator()(const int x) const {

        uint vector_index = x/n_bits_per_bitset;
        uint local_bitset_index = x % n_bits_per_bitset;

        return mem_local[vector_index][local_bitset_index];
    };

    // for const BitVector
    inline bool operator[](const int x) const {

        uint vector_index = x/n_bits_per_bitset;
        uint local_bitset_index = x % n_bits_per_bitset;

        return mem_local[vector_index][local_bitset_index];
    };
};

class BitMatrix{
public:
    uint n_rows, n_cols, n_slices, n_elem;
    uint n_bitsets;

private:
    static const uint n_bits_per_bitset = 128; // Should be the same as in BitVector
    vector<vector<BitVector> > mem_local;

public:
    BitMatrix(uint n_rows, uint n_cols, uint n_slices):
            n_rows(n_rows), 
            n_cols(n_cols), 
            n_slices(n_slices), 
            n_elem(n_rows*n_cols*n_slices), 
            mem_local(vector<vector<BitVector> > (n_rows, vector<BitVector>(n_cols, BitVector(n_slices)))) {

        // cout << "Approximate size of BitMatrix = " << n_elem << " bits = " << double(n_elem)/double(8*1024*1024) << " megabyte" << endl;
    };

    void flip(const int x, const int y, const int z) {
        this->operator()(x, y, z) = !(this->operator()(x, y, z));
    }

    // for non-const BitMatrix
    inline std::bitset<n_bits_per_bitset>::reference operator()(const int x, const int y, const int z) {

        return mem_local[x][y][z];
    };

    // for const BitMatrix
    inline bool operator()(const int x, const int y, const int z) const {

        return mem_local[x][y][z];
    };
};
