#pragma once
#include <vector>
#include "../glm/ext.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "Furniture.h"
#include "Mesh.h"

using namespace std;

class Node {
	public:
		Node* parent;
		vector<Node*>* children;
		vector<vector<float>>* geometry;
		glm::mat4x4 trans;
		int ge;

		Mesh* meshN; // mesh pointer

		glm::mat4x4 transform;
		glm::mat4x4 matrix;

		int defaultID;
		//floor
		glm::mat4x4 fcube;
		//table
		glm::mat4x4 tleg1;
		glm::mat4x4 tleg2;
		glm::mat4x4 tleg3;
		glm::mat4x4 tleg4;
		glm::mat4x4 ttop;
		//cabinet
		glm::mat4x4 cbody;
		glm::mat4x4 cdoor;
		//lamp
		glm::mat4x4 lstand;
		glm::mat4x4 ltop;
		//chair
		glm::mat4x4 cleg1;
		glm::mat4x4 cleg2;
		glm::mat4x4 cleg3;
		glm::mat4x4 cleg4;
		glm::mat4x4 cseat;
		glm::mat4x4 cback;

		float tX;
		float tY;
		float tZ;
		float rY;
		float sX;
		float sY;
		float sZ;

		Furniture* furn;
		float xIndex;
		float zIndex;
		float height;
		float dX;
		float dZ;

		float colorRGB[3];

		/////bounding box////
		float bb1[3];//top part
		float bb2[3];
		float bb3[3];
		float bb4[3];
		float bb5[3];//bottom part
		float bb6[3];
		float bb7[3];
		float bb8[3];
		
		Node();
		Node::~Node();
		Node(Node*,vector<Node*>*, vector<vector<float>>* );
		void removeNode();

		void addChild(Node*);
		bool hasChildren();

		void stackUp(float);
		void rotateN(float, float, float);
		void translateN(float, float);
		void scaleN(float, float, float, float, float, float, float);

		void bbTrans(glm::mat4x4);

		glm::mat4 rotateMat(float, float, float, glm::mat4);
		glm::mat4 translateMat(float, float, float, glm::mat4);
		glm::mat4 scaleMat(float, float, float, glm::mat4);

		void calculateMatrices(float, float, float);

		//void updateGeo();
		void updateMatrices(glm::mat4);
};