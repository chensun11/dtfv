#include "pca.h"

PCAWrapper::PCAWrapper(bool whitening)   {
    this->whitening = whitening;
    projMat = NULL;
    aveVec = NULL;
    eigVec = NULL;
    pDim = 0;
    oDim = 0;
}

PCAWrapper::PCAWrapper(string fileName, bool whitening)  {
    ifstream fin;
    fin.open(fileName.c_str());
    if (!fin.is_open()) {
        cout<<"Cannot open "<<fileName<<endl;
        exit(-1);
    }
    this->whitening = whitening;
    fin>>oDim>>pDim;
    projMat = new double[oDim * pDim];
    aveVec = new double[oDim];
    eigVec = new double[pDim];
    for (int i = 0; i < oDim*pDim; i++)
        fin>>projMat[i];
    for (int i = 0; i < oDim; i++)
        fin>>aveVec[i];
    for (int i = 0; i < pDim; i++)
        fin>>eigVec[i];
    fin.close();
}

PCAWrapper::~PCAWrapper()   {
    if (projMat)
        delete [] projMat;
    if (aveVec)
        delete [] aveVec;
    if (eigVec)
        delete [] eigVec;
}

vector<double> PCAWrapper::project(vector<double> input)   {
    vector<double> result(pDim, 0.0);
    if (input.size() != oDim)
        return result;
    // subtract by mean
    for (int i = 0; i < oDim; i++)
        input[i] -= aveVec[i];
    for (int i = 0; i < pDim; i++)  {
        double val = 0.0;
        // project
        for (int j = 0; j < oDim; j++)  {
            val += projMat[i*oDim+j] * input[j];
        }
        // whitening
        result[i] = val;
        if (whitening)
            result[i] *= eigVec[i];
    }
    return result;
}

bool PCAWrapper::train(vector<vector<double> > &inputData, int pDim, string outputFile) {
    if (inputData.size() < 1 || inputData[0].size() < 1)
        return false;
    size_t numSamples = inputData.size();
    oDim = inputData[0].size();
    double *dataMat = new double[numSamples * oDim];
    aveVec = new double[oDim];
    for (int i = 0; i < oDim; i++)
        aveVec[i] = 0.0;
    for (int i = 0; i < numSamples; i++)
        for (int j = 0; j < oDim; j++)  {
            dataMat[i*oDim+j] = inputData[i][j];
            aveVec[j] += inputData[i][j];
        }
    for (int i = 0; i < oDim; i++)
        aveVec[i] /= (double) numSamples;
    alglib::real_2d_array ptInput;
    ptInput.setcontent(numSamples, oDim, dataMat);
    alglib::ae_int_t info;
    alglib::real_1d_array eigValues;
    alglib::real_2d_array eigVectors;
    pcabuildbasis(ptInput, numSamples, oDim, info, eigValues, eigVectors);
    delete [] dataMat;

    size_t cols = eigVectors.cols();
    if (cols < pDim)
        pDim = cols;
    this->pDim = pDim;
    
    projMat = new double[pDim * oDim];
    eigVec = new double[pDim];

    for (int i = 0; i < pDim; i++)  {
        eigVec[i] = 1 / sqrt(eigValues[i]);
        for (int j = 0; j < oDim; j++)
            projMat[i*oDim + j] = eigVectors[j][i];
    }
    // save to file
    ofstream fout;
    fout.open(outputFile.c_str());
    if (!fout.is_open())    {
        cout<<"Cannot save projection matrix to "<<outputFile<<endl;
        return false;
    }
    fout<<oDim<<" "<<pDim<<endl;
    fout<<projMat[0];
    for (int i = 1; i < oDim*pDim; i++)
        fout<<" "<<projMat[i];
    fout<<endl;
    fout<<aveVec[0];
    for (int i = 1; i < oDim; i++)
        fout<<" "<<aveVec[i];
    fout<<endl;
    fout<<eigVec[0];
    for (int i = 1; i < pDim; i++)
        fout<<" "<<eigVec[i];
    fout<<endl;
    fout.close();

    return true;
}

int PCAWrapper::getDim()    {
    return pDim;
}

