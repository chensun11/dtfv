#ifndef DT_FEATURE_H
#define DT_FEATURE_H

/*
 * Handles a dense trajectory feature point
 * Check http://lear.inrialpes.fr/people/wang/dense_trajectories for feature format
 */

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#define TRAJ_DIM 30
#define HOG_DIM 96
#define HOF_DIM 108
#define MBHX_DIM 96
#define MBHY_DIM 96

class DTFeature	{
	public:
		DTFeature();
		DTFeature(string featureLine);
		DTFeature(const DTFeature &f);
		~DTFeature();
        DTFeature &operator=(const DTFeature &f);   // overload copy operator
	public:
		int frameNum;
		double mean_x;
		double mean_y;
		double var_x;
		double var_y;
		double length;
		double scale;
		double x_pos;
		double y_pos;
		double t_pos;
		double *traj;
		double *hog;
		double *hof;
		double *mbhx;
		double *mbhy;
};

#endif
