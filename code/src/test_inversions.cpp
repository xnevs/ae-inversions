#include <iostream>
#include <iomanip>

#include <string>
#include <sstream>
#include <map>
#include <bitset>
#include <random>
#include <chrono>
#include <vector>

#include "test_utilities.hpp"
#include "inversions.hpp"

using namespace std;

AlgFlags alg_flags;
int n;
Seq seq;
int rep;

map<string, Alg> algs = {{"bf", Alg::bf},
                         {"is1", Alg::is1},
                         {"is2", Alg::is2},
                         {"ms1", Alg::ms1},
                         {"ms2", Alg::ms2},
                         {"ms3", Alg::ms3},
                         {"ms2_is2", Alg::ms2_is2},
                         {"ms3_is2", Alg::ms3_is2},
                         {"bf_idx", Alg::bf_idx},
                         {"is1_idx", Alg::is1_idx},
                         {"is2_idx", Alg::is2_idx},
                         {"ms1_idx", Alg::ms1_idx},
                         {"ms2_idx", Alg::ms2_idx},
                         {"ms3_idx", Alg::ms3_idx}};
map<string, Seq> seqs = {{"inc", Seq::inc},
                         {"dec", Seq::dec},
                         {"rnd", Seq::rnd}};
bool parse_args(int argc, char *argv[]) {
    if(argc != 5)
        return false;
    try {
        istringstream algs_{argv[1]};
        string alg_;
        while(getline(algs_, alg_, ',')) {
            alg_flags.set(algs.at(alg_));
        }
        n = stoi(argv[2]);
        seq = seqs.at(argv[3]); 
        rep = stoi(argv[4]);
    } catch(...) {
        return false;
    }
    return true;
}

int main(int argc, char *argv[]) {
    
    if(!parse_args(argc,argv)) {
        cout << "napaka z argumenti" << endl;
        return -1;
    }

    random_device rd;
    auto seed = rd();
    default_random_engine random{seed};

    vector<decltype(generate(n, seq, random))> test_cases;
    test_cases.reserve(rep);
    for(int i=0; i<rep; ++i) {
        test_cases.push_back(generate(n, seq, random));
    }

    if(alg_flags[Alg::bf])      TEST(inversions_bf     , test_cases);
    if(alg_flags[Alg::is1])     TEST(inversions_is1    , test_cases);
    if(alg_flags[Alg::is2])     TEST(inversions_is2    , test_cases);
    if(alg_flags[Alg::ms1])     TEST(inversions_ms1    , test_cases);
    if(alg_flags[Alg::ms2])     TEST(inversions_ms2    , test_cases);
    if(alg_flags[Alg::ms3])     TEST(inversions_ms3    , test_cases);
    if(alg_flags[Alg::ms2_is2]) TEST(inversions_ms2_is2, test_cases);
    if(alg_flags[Alg::ms3_is2]) TEST(inversions_ms3_is2, test_cases);
    if(alg_flags[Alg::bf_idx])  TEST(inversions_bf_idx , test_cases);
    if(alg_flags[Alg::is1_idx]) TEST(inversions_is1_idx, test_cases);
    if(alg_flags[Alg::is2_idx]) TEST(inversions_is2_idx, test_cases);
    if(alg_flags[Alg::ms1_idx]) TEST(inversions_ms1_idx, test_cases);
    if(alg_flags[Alg::ms2_idx]) TEST(inversions_ms2_idx, test_cases);
    if(alg_flags[Alg::ms3_idx]) TEST(inversions_ms3_idx, test_cases);
}
