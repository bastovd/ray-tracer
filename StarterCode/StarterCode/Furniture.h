#pragma once
#include <cmath>
#include <vector>
#include <string>
#include <iostream>
#include "../glm/ext.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "Mesh.h"

using namespace std;


class Furniture
{
public:
	string furnType;
	vector<float> furnCol;

	vector<int> furnPos;
	float furnRot;
	vector<float> furnSca;

	vector<vector<float>>* floor;
	int floorX;
	int floorZ;

	vector<vector<float>>* c_top;
	vector<vector<float>>* c_back;
	vector<vector<float>>* c_leg1;
	vector<vector<float>>* c_leg2;
	vector<vector<float>>* c_leg3;
	vector<vector<float>>* c_leg4;

	vector<vector<float>>* t_top;
	vector<vector<float>>* t_leg1;
	vector<vector<float>>* t_leg2;
	vector<vector<float>>* t_leg3;
	vector<vector<float>>* t_leg4;

	vector<vector<float>>* l_base;
	vector<vector<float>>* l_lamp;

	vector<vector<float>>* cab_base;
	vector<vector<float>>* cab_door;

	vector<vector<float>>* meshVer;

	Furniture();
	Furniture(string,vector<float>,vector<int>,float,vector<float>, Mesh*);

	vector<vector<float>>* makeRect(float c[3], float, float, float);
	vector<vector<float>>* makeSphere(float c[3], float);
	vector<vector<float>>* makeCylinder(float c[3], float, float);
};