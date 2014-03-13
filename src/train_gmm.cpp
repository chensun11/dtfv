#include "gmm.h"

int main(int argc, char **argv) {
    if (argc < 4)   {
        cout<<"Usage: "<<argv[0]<<" inputData outputCodeBook numClusters"<<endl;
        return 0;
    }
    string inputData(argv[1]);
    string outputCodeBook(argv[2]);
    int numClusters = atoi(argv[3]);

    GMMWrapper gmm;
    cout<<"Start to train GMM..."<<endl;
    if (!gmm.train(inputData, numClusters, outputCodeBook)) {
        cout<<"Training failed."<<endl;
        return 0;
    }
    cout<<"Training complete."<<endl;
    return 0;
}

