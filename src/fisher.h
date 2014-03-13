#ifndef FISHER_VECTOR_H
#define FISHER_VECTOR_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <climits>

#include "gmm.h"
#include "pca.h"

using namespace std;

/*
 * An online implementation of Fisher Vector
 * Suitable for handling large feature files
 *
 * initFV()     allocate fv space and update fv parameters
 * addPoint()   add a feature point to fv computation
 * getFV()      normalize and return fv
 * clearFV()    release fv space and reset fv parameters
 *
 * Use sqrt and l2 normalization
 */

class FisherVector  {
    public:
        FisherVector(string pcaDictFile, string codeBookFile, bool whitening = false);
        ~FisherVector();
        bool initFV(int numSP, int startFrame = 0, int endFrame = INT_MAX);
        bool addPoint(vector<double> feat, double x_pos, double y_pos);
        vector<double> & getFV();
        bool clearFV();

    private:
        GMMWrapper* codeBook;
        PCAWrapper* pcaMat;
        double* sqrtInvSigma;

        int numSP;
        int startFrame;
        int endFrame;

        vector<double> fv;
        int numPts;
};

#endif

