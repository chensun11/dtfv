#ifndef GaussianMM_H
#define GaussianMM_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>

extern "C"  {
#include "vl/gmm.h"
}

using namespace std;

class GMMWrapper    {
    public:
        GMMWrapper();
        GMMWrapper(string codeBookName);
        ~GMMWrapper();

        bool train(string dataFile, vl_size numClusters, string codeBookName);
    private:
        double *loadData(string dataFile, vl_size &numData, vl_size &dimension);
    public:
        double *means;
        double *covs;
        double *priors;
        int dimension;
        int numClusters;
};

#endif
