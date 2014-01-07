#pragma once
#include <vector>
#include "../glm/ext.hpp"
#include "../glm/gtc/matrix_transform.hpp"

using namespace std;

class Mesh {
	public:
		
		Mesh();
		string Mtype;
		float ExtL;
		float SRns;

		vector<vector<int>>* Tris;
		vector<int>* Tri;
		vector<vector<float>>* Norms;
		vector<vector<float>>* Verts;

		void extrusion(float length, vector<vector<float>> *baseVerts);
		void revolution(float numSlices, vector<vector<float>> *lineVerts);

		bool convexity(vector<vector<float>> *baseVerts);
		void getnormals(vector<vector<int>>*, bool);
};