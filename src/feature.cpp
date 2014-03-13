#include "feature.h"

DTFeature::DTFeature()	{
	frameNum = -1;
	mean_x = 0.0;
	mean_y = 0.0;
	var_x = 0.0;
	var_y = 0.0;
	length = 0.0;
	scale = 0.0;
	x_pos = 0.0;
	y_pos = 0.0;
	t_pos = 0.0;
	traj = NULL;
	hog = NULL;
	hof = NULL;
	mbhx = NULL;
	mbhy = NULL;
}

DTFeature::DTFeature(string featureLine)	{
	stringstream ss;
	ss<<featureLine;
	ss>>frameNum>>mean_x>>mean_y>>var_x>>var_y>>length>>scale>>x_pos>>y_pos>>t_pos;
	traj = new double[TRAJ_DIM];
	for (int i = 0; i < TRAJ_DIM; i++)
		ss>>traj[i];
	hog = new double[HOG_DIM];
	for (int i = 0; i < HOG_DIM; i++)
		ss>>hog[i];
	hof = new double[HOF_DIM];
	for (int i = 0; i < HOF_DIM; i++)
		ss>>hof[i];
	mbhx = new double[MBHX_DIM];
	for (int i = 0; i < MBHX_DIM; i++)
		ss>>mbhx[i];
	mbhy = new double[MBHY_DIM];
	for (int i = 0; i < MBHY_DIM; i++)
		ss>>mbhy[i];
}

DTFeature::DTFeature(const DTFeature &f)	{
	frameNum = f.frameNum;
	mean_x = f.mean_x;
	mean_y = f.mean_y;
	var_x = f.var_x;
	var_y = f.var_y;
	length = f.length;
	scale = f.scale;
	x_pos = f.x_pos;
    y_pos = f.y_pos;
    t_pos = f.t_pos;

    traj = NULL;
    if (f.traj)   {
        traj = new double[TRAJ_DIM];
        for (int i = 0; i < TRAJ_DIM; i++)
            traj[i] = f.traj[i];
    }
    hog = NULL;
    if (f.hog)  {
        hog = new double[HOG_DIM];
        for (int i = 0; i < HOG_DIM; i++)
            hog[i] = f.hog[i];
    }
    hof = NULL;
    if (f.hof)  {
        hof = new double[HOF_DIM];
        for (int i = 0; i < HOF_DIM; i++)
            hof[i] = f.hof[i];
    }
    mbhx = NULL;
    if (f.mbhx) {
        mbhx = new double[MBHX_DIM];
        for (int i = 0; i < MBHX_DIM; i++)
            mbhx[i] = f.mbhx[i];
    }
    mbhy = NULL;
    if (f.mbhy) {
        mbhy = new double[MBHY_DIM];
        for (int i = 0; i < MBHY_DIM; i++)
            mbhy[i] = f.mbhy[i];
    }
}

DTFeature::~DTFeature()	{
    if (traj)
        delete [] traj;
    if (hog)
        delete [] hog;
    if (hof)
        delete [] hof;
    if (mbhx)
        delete [] mbhx;
    if (mbhy)
        delete [] mbhy;
}

DTFeature &DTFeature::operator=(const DTFeature &f)	{
    if (this == &f)
        return *this;

	frameNum = f.frameNum;
	mean_x = f.mean_x;
	mean_y = f.mean_y;
	var_x = f.var_x;
	var_y = f.var_y;
	length = f.length;
	scale = f.scale;
	x_pos = f.x_pos;
    y_pos = f.y_pos;
    t_pos = f.t_pos;

    if (traj)
        delete []traj;
    traj = NULL;
    if (f.traj)   {
        traj = new double[TRAJ_DIM];
        for (int i = 0; i < TRAJ_DIM; i++)
            traj[i] = f.traj[i];
    }
    if (hog)
        delete [] hog;
    hog = NULL;
    if (f.hog)  {
        hog = new double[HOG_DIM];
        for (int i = 0; i < HOG_DIM; i++)
            hog[i] = f.hog[i];
    }
    if (hof)
        delete [] hof;
    hof = NULL;
    if (f.hof)  {
        hof = new double[HOF_DIM];
        for (int i = 0; i < HOF_DIM; i++)
            hof[i] = f.hof[i];
    }
    if (mbhx)
        delete [] mbhx;
    mbhx = NULL;
    if (f.mbhx) {
        mbhx = new double[MBHX_DIM];
        for (int i = 0; i < MBHX_DIM; i++)
            mbhx[i] = f.mbhx[i];
    }
    if (mbhy)
        delete [] mbhy;
    mbhy = NULL;
    if (f.mbhy) {
        mbhy = new double[MBHY_DIM];
        for (int i = 0; i < MBHY_DIM; i++)
            mbhy[i] = f.mbhy[i];
    }

    return *this;
}


