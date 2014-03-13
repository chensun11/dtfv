#ifndef PrinCompAna_H
#define PrinCompAna_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cmath>

#include "alglib/dataanalysis.h"

using namespace std;

class PCAWrapper    {
    public:
        PCAWrapper(bool whitening = false);
        PCAWrapper(string fileName, bool whitening = false);
        ~PCAWrapper();
        
        vector<double> project(vector<double> input);
        bool train(vector<vector<double> > &inputData, int pDim, string outputFile);
        int getDim();
    private:
        double *projMat;
        double *aveVec;
        double *eigVec; // inverse of eigen values's square roots
        size_t pDim;
        size_t oDim;
        bool whitening;
};

#endif
