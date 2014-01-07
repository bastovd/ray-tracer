#pragma once
#include <vector>
#include "Node.h"
#include "../glm/ext.hpp"
#include "../glm/gtc/matrix_transform.hpp"

using namespace std;

class SceneGraph {
	public:
		Node* root;

		glm::mat4x4 tr;
		vector<vector<float>> vertices;
		vector<Node*>* objects;

		float tX;
		float tY;
		float tZ;
		float rY;
		float sX;
		float sY;
		float sZ;

		SceneGraph();
		SceneGraph(Node*);

		void traverseSG(Node*);

		void rotate(float, float, float, Node*);
		void translate(float, float, Node*);
		void scale(float, float, float, float, float, float, float, Node*);
		void transY( float, Node*);

		void addChild(Node*, Node*);
		void helper(Node*);
		void removeChild(Node*);
};