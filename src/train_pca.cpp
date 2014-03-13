#include <sstream>
#include "pca.h"

int main(int argc, char **argv) {
    if (argc < 4)   {
        cout<<"Usage: "<<argv[0]<<" inputFile outputMat projDimension [projectedFile]"<<endl;
        return 0;
    }
    string inputFile(argv[1]);
    string outputFile(argv[2]);
    int pDim = atoi(argv[3]);

    vector<vector<double> > inputData;

    ifstream fin;
    fin.open(argv[1]);
    if (!fin.is_open()) {
        cout<<"Cannot open "<<inputFile<<endl;
        return 0;
    }
    string line;

    while (getline(fin, line))  {
        vector<double> feat;
        stringstream ss;
        ss<<line;
        double val;
        while (ss>>val)
            feat.push_back(val);
        inputData.push_back(feat);
    }
    fin.close();
    cout<<"Loading complete."<<endl;
    cout<<"#pts = "<<inputData.size()<<endl;

    PCAWrapper pca;
    cout<<"Start to train PCA projection matrix..."<<endl;
    if (pca.train(inputData, pDim, outputFile))
        cout<<"Training complete."<<endl;
    else    {
        cout<<"Failed!"<<endl;
        return 0;
    }

    if (argc > 4)   {
        ofstream fout;
        fout.open(argv[4]);
        if (!fout.is_open())    {
            cout<<"Cannot save projected file."<<endl;
            return 0;
        }
        for (int i = 0; i < inputData.size(); i++)  {
            vector<double> projected = pca.project(inputData[i]);
            fout<<projected[0];
            for (int j = 1; j < projected.size(); j++)
                fout<<" "<<projected[j];
            fout<<endl;
        }
        fout.close();
    }

    return 0;
}

