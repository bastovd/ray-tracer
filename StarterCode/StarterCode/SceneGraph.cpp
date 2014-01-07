#include "SceneGraph.h"

SceneGraph::SceneGraph() {
	root = nullptr;
	tr = glm::mat4x4();
	for (int i = 0; i < 4; i++) {
		tr[i][i] = 1;
	}
	tX = 0; tY = 0; tZ = 0; 
	rY = 0;
	sX = 0; sY = 0; sZ = 0;
	objects = new vector<Node*>();
}

SceneGraph::SceneGraph(Node* r) {
	root = r;
	tr = glm::mat4x4();
	for (int i = 0; i < 4; i++) {
		tr[i][i] = 1;
	}
	tX = 0; tY = 0; tZ = 0; 
	rY = 0;
	sX = 0; sY = 0; sZ = 0;
	objects = new vector<Node*>();
}

void SceneGraph::rotate(float a, float xi, float zi, Node* r) {
	r->rotateN(a, xi, zi);
	Node* temp = new Node();
	if (r->children->size() != 0) {
		for (int i = 0; i < r->children->size(); i++) {
			Node* t = r->children->at(i);
			this->rotate(a, xi, zi, t);
		}
	}
}

void SceneGraph::translate(float x, float z, Node* r) {
	r->translateN(x, z);
	Node* temp = new Node();
	if (r->children->size() != 0) {
		for (int i = 0; i < r->children->size(); i++) {
			Node* t = r->children->at(i);
			this->translate(x, z, t);
		}
	}
}

void SceneGraph::scale(float x, float y, float z, float h, float xi, float zi, float a, Node* r) {
	r->scaleN(x, y, z, h, xi, zi, a);
	Node* temp = new Node();
	if (r->children->size() != 0) {
		for (int i = 0; i < r->children->size(); i++) {
			Node* t = r->children->at(i);
			this->scale(x, y, z, h, xi, zi, a, t);
		}
	} 
}

void SceneGraph::transY(float y, Node* r) {
	r->stackUp(y);
	Node* temp = new Node();
	if (r->children->size() != 0) {
		for (int i = 0; i < r->children->size(); i++) {
			Node* t = r->children->at(i);
			this->transY(y, t);
		}
	}
}

void SceneGraph::addChild(Node* n, Node* r) {
	vector<Node*>* nodes = new vector<Node*>();
	int index = 0;
	for(int i = 0; i < objects->size(); i++) {
		if(objects->at(i) == r) {
			break;
		}
		index++;
	}
	for(int i = 0; i <= index; i++) {
		nodes->push_back(objects->at(i));
	}
	nodes->push_back(n);
	index++;
	for(int i = index; i < objects->size(); i++) {
		nodes->push_back(objects->at(i));
	}
	objects = nodes;
}

void SceneGraph::helper(Node* r) {
	for(int i = 0; i < objects->size(); i++) {
		if(objects->at(i) == r) {
			objects->at(i) = nullptr;
			break;
		}
	}
	vector<Node*>* kids = r->children;
	r->removeNode();
	for(int i = 0; i < kids->size(); i++) {
		helper(kids->at(i));
	}
}

void SceneGraph::removeChild(Node* r) {
	int child = 0;
	vector<Node*>* nodesAdd = new vector<Node*>();
	for(int i = 0; i < objects->size(); i++) {
		Node* n = objects->at(i);
		if(r == objects->at(i)) {
			child = i;
			break;
		}
	}
	if(r->parent != nullptr) {
		for(int i = 0; i < r->parent->children->size(); i++) {
			if(r == r->parent->children->at(i)) {
				r->parent->children->erase(r->parent->children->begin()+i);
			}
		}
	}
	helper(objects->at(child));
	for(int i = 0; i < objects->size(); i++) {
		if(objects->at(i) != nullptr) {
			nodesAdd->push_back(objects->at(i));
		}
	}
	objects = nodesAdd;
}