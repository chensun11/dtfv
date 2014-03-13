#include "gmm.h"

GMMWrapper::GMMWrapper()    {
    means = NULL;
    covs = NULL;
    priors = NULL;
    dimension = 0;
    numClusters = 0;
}

GMMWrapper::GMMWrapper(string codeBookName) {
    ifstream fin;
    fin.open(codeBookName.c_str());
    if (!fin.is_open()) {
        cout<<"Cannot load "<<codeBookName<<endl;
        exit(-1);
    }
    fin>>dimension>>numClusters;
    means = new double[numClusters * dimension];
    covs = new double[numClusters * dimension];
    priors = new double[numClusters];

    for (int i = 0; i < numClusters * dimension; i++)
        fin >> means[i];
    for (int i = 0; i < numClusters * dimension; i++)
        fin >> covs[i];
    for (int i = 0; i < numClusters; i++)
        fin >> priors[i];

    fin.close();
}

GMMWrapper::~GMMWrapper()   {
    if (means)
        delete [] means;
    if (covs)
        delete [] covs;
    if (priors)
        delete [] priors;
}

double *GMMWrapper::loadData(string dataFile, vl_size &numData, vl_size &dimension)    {
    ifstream fin;
    fin.open(dataFile.c_str());
    if (!fin.is_open()) {
        cout<<"Cannot open "<<dataFile<<endl;
        return NULL;
    }

    vector<vector<double> > inputData;
    string line;
    stringstream ss;
    double val;
    while (getline(fin, line))  {
        ss<<line;
        vector<double> feat;
        while (ss>>val)
            feat.push_back(val);
        inputData.push_back(feat);
        ss.clear();
        ss.str("");
    }
    fin.close();

    numData = inputData.size();
    dimension = inputData[0].size();

    double *data = new double[numData*dimension];
    for (int dataIdx = 0; dataIdx < numData; dataIdx++) {
        for (int d = 0; d < dimension; d++) {
            data[dataIdx*dimension+d] = inputData[dataIdx][d];
        }
    }
    return data;
}

bool GMMWrapper::train(string dataFile, vl_size numClusters, string codeBookName) {
    double sigmaLowerBound = 0.000001;
    vl_size numData = 0;
    vl_size dimension = 0;
    vl_size maxiter = 300;
    vl_size maxrep = 3;
    vl_size maxiterKM = 100;
    vl_size ntrees = 2;
    vl_size maxComp = 100;

    double * data = loadData(dataFile, numData, dimension);
    if (data == NULL)   {
        return false;
    }
    vl_set_num_threads(0) ;

    VlGMM *gmm = vl_gmm_new (VL_TYPE_DOUBLE, dimension, numClusters) ;

    // init with KMeans
    VlKMeans *kmeans = vl_kmeans_new(VL_TYPE_DOUBLE,VlDistanceL2);
    vl_kmeans_set_verbosity (kmeans,1);
    vl_kmeans_set_max_num_iterations (kmeans, maxiterKM);
    vl_kmeans_set_max_num_comparisons (kmeans, maxComp);
    vl_kmeans_set_num_trees (kmeans, ntrees);
    vl_kmeans_set_algorithm (kmeans, VlKMeansANN);
    vl_kmeans_set_initialization(kmeans, VlKMeansRandomSelection);

    vl_gmm_set_initialization (gmm,VlGMMKMeans);
    vl_gmm_set_kmeans_init_object(gmm,kmeans);

    vl_gmm_set_max_num_iterations (gmm, maxiter);
    vl_gmm_set_num_repetitions(gmm, maxrep);
    vl_gmm_set_verbosity(gmm,1);
    vl_gmm_set_covariance_lower_bound (gmm,sigmaLowerBound);
   
    // training
    vl_gmm_cluster (gmm, data, numData);
    delete [] data;

    double *vl_means = (double *) vl_gmm_get_means(gmm);
    double *vl_covs = (double *) vl_gmm_get_covariances(gmm);
    double *vl_priors = (double *) vl_gmm_get_priors(gmm);

    means = new double[numClusters * dimension];
    covs = new double[numClusters * dimension];
    priors = new double[numClusters];
    
    for (int i = 0; i < numClusters * dimension; i++)   {
        means[i] = vl_means[i];
        covs[i] = vl_covs[i];
    }
    for (int i = 0; i < numClusters; i++)
        priors[i] = vl_priors[i];

    vl_kmeans_delete(kmeans);
    vl_gmm_delete(gmm);

    // save codebook
    ofstream fout;
    fout.open(codeBookName.c_str());
    if (!fout.is_open())    {
        cout<<"Cannot save "<<codeBookName<<endl;
        return false;
    }
    fout<<dimension<<" "<<numClusters<<endl;

    fout<<means[0];
    for (int i = 1; i < numClusters * dimension; i++)
        fout<<" "<<means[i];
    fout<<endl;
    fout<<covs[0];
    for (int i = 1; i < numClusters * dimension; i++)
        fout<<" "<<covs[i];
    fout<<endl;
    fout<<priors[0];
    for (int i = 1; i < numClusters; i++)
        fout<<" "<<priors[i];
    fout<<endl;
    fout.close();

    return true;
}


