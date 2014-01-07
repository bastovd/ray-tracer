#include "Node.h"

	Node::Node() {

	matrix = glm::mat4();
	transform = glm::mat4x4(1,0,0,0,
							0,1,0,0,
							0,0,1,0,
							0,0,0,1);


	defaultID = -1;
	//floor
	glm::mat4x4 fcube = glm::mat4();
	//table
	glm::mat4x4 tleg1 = glm::mat4();
	glm::mat4x4 tleg2 = glm::mat4();
	glm::mat4x4 tleg3 = glm::mat4();
	glm::mat4x4 tleg4 = glm::mat4();
	glm::mat4x4 ttop = glm::mat4();
	//cabinet
	glm::mat4x4 cbody = glm::mat4();
	glm::mat4x4 cdoor = glm::mat4();
	//lamp
	glm::mat4x4 lstand = glm::mat4();
	glm::mat4x4 ltop = glm::mat4();
	//chair
	glm::mat4x4 cleg1 = glm::mat4();
	glm::mat4x4 cleg2 = glm::mat4();
	glm::mat4x4 cleg3 = glm::mat4();
	glm::mat4x4 cleg4 = glm::mat4();
	glm::mat4x4 cseat = glm::mat4();
	glm::mat4x4 cback = glm::mat4();

	parent = nullptr;
	children = new vector<Node*>();
	geometry = new vector<vector<float>>();

	tX = 0; tZ = 0; 
	rY = 0;
	sX = 0; sY = 0; sZ = 0;
	ge = 0;
	trans = glm::mat4x4();
	for (int i = 0; i < 4; i++) {
		trans[i][i] = 1;
	}
	bb1[0] = -1;
	bb1[1] = 0.5f; 
	bb1[2] = -1;

	bb2[0] = 1;
	bb2[1] = 0.5f;
	bb2[2] = -1;

	bb3[0] = 1; 
	bb3[1] = 0.5f;
	bb3[2] = 1;

	bb4[0] = -1;
	bb4[1] = 0.5f; 
	bb4[2] = 1;

	bb5[0] = -1; 
	bb5[1] = -0.5f; 
	bb5[2] = -1;

	bb6[0] = 1; 
	bb6[1] = -0.5f;
	bb6[2] = -1;

	bb7[0] = 1;
	bb7[1] = -0.5f;
	bb7[2] = 1;

	bb8[0] = -1; 
	bb8[1] = -0.5f; 
	bb8[2] = 1;
}

Node::Node(Node* p,vector<Node*>* vc,vector<vector<float>>* vg) {

	matrix = glm::mat4();
	transform = glm::mat4x4(1,0,0,0,
							0,1,0,0,
							0,0,1,0,
							0,0,0,1);

	defaultID = -1;
	//floor
	glm::mat4x4 fcube = glm::mat4();
	//table
	glm::mat4x4 tleg1 = glm::mat4();
	glm::mat4x4 tleg2 = glm::mat4();
	glm::mat4x4 tleg3 = glm::mat4();
	glm::mat4x4 tleg4 = glm::mat4();
	glm::mat4x4 ttop = glm::mat4();
	//cabinet
	glm::mat4x4 cbody = glm::mat4();
	glm::mat4x4 cdoor = glm::mat4();
	//lamp
	glm::mat4x4 lstand = glm::mat4();
	glm::mat4x4 ltop = glm::mat4();
	//chair
	glm::mat4x4 cleg1 = glm::mat4();
	glm::mat4x4 cleg2 = glm::mat4();
	glm::mat4x4 cleg3 = glm::mat4();
	glm::mat4x4 cleg4 = glm::mat4();
	glm::mat4x4 cseat = glm::mat4();
	glm::mat4x4 cback = glm::mat4();

	parent = p;
	children = vc;
	geometry = vg;

	tX = 0; tZ = 0; 
	rY = 0;
	sX = 0; sY = 0; sZ = 0;
	ge = 0;
	trans = glm::mat4x4();
	for (int i = 0; i < 4; i++) {
		trans[i][i] = 1;
	}
}

Node::~Node() {

}

void Node::removeNode() {
	delete this;
}

void Node::addChild(Node* n) {
	children->push_back(n);
}

bool Node::hasChildren() {
	if (this->children->empty() == 0) {
		return false;
	} else return true;
	return false;
}

void Node::calculateMatrices(float floorx, float floory, float floorz) {
	if(ge == 0) {

	} else if(ge == 1) {

	} else if(ge == 2) {

	} else if(ge == 3) {

	} else if(ge == 4) {

	} else if(ge == 5) {

	}
	//floor
	fcube = this->scaleMat(floorx, floory, floorz, fcube);

	//table
	ttop = this->scaleMat(0.5f,0.1f,0.5f,ttop);
	ttop = this->translateMat(0,0.4f,0, ttop);

	tleg1 = this->scaleMat(0.1f,0.5f,0.1f,tleg1);
	tleg1 = this->translateMat(-0.4f,0,-0.4f, tleg1);
	
	tleg2 = this->scaleMat(0.1f,0.5f,0.1f,tleg2);
	tleg2 = this->translateMat(0.4f,0,-0.4f, tleg2);
	
	tleg3 = this->scaleMat(0.1f,0.5f,0.1f,tleg3);
	tleg3 = this->translateMat(-0.4f,0,0.4f, tleg3);
	
	tleg4 = this->scaleMat(0.1f,0.5f,0.1f,tleg4);
	tleg4 = this->translateMat(0.4f,0,0.4f, tleg4);
	//cabinet
	cbody = this->scaleMat(0.5f,0.5f,0.0f,cbody);
	cbody = this->translateMat(0,0,0.0f, cbody);
	
	cdoor = this->scaleMat(0.4f,0.4f,0.5f,cdoor);
	cdoor = this->translateMat(0.2f,0,0.2f, cdoor);
	//lamp
	lstand = this->scaleMat(0.2f,0.5f,0.2f,lstand);
	lstand = this->translateMat(0,-0.5f,0, lstand);
	
	ltop = this->scaleMat(0.25f,0.25f,0.25f,ltop);
	ltop = this->translateMat(0,0.2f,0, ltop);
	//chair
	cseat = this->scaleMat(0.5f,0.3f,0.3f,cseat);

	cleg1 = this->scaleMat(0.01f,0.25f,0.01f,cleg1);
	cleg1 = this->translateMat(-0.2f,-0.25f,-0.2f, cleg1);
	
	cleg2 = this->scaleMat(0.01f,0.25f,0.01f,cleg2);
	cleg2 = this->translateMat(0.2f,-0.25f,-0.2f, cleg2);
	
	cleg3 = this->scaleMat(0.01f,0.25f,0.01f,cleg3);
	cleg3 = this->translateMat(-0.2f,-0.25f,0.2f, cleg3);
	
	cleg4 = this->scaleMat(0.01f,0.25f,0.01f,cleg4);
	cleg4 = this->translateMat(0.2f,-0.25f,0.2f, cleg4);
	
	cback = this->scaleMat(0.4f,0.3f,0.05f,cback);
	cback = this->translateMat(0,0.25f,0.2f, cback);
}

glm::mat4 Node::rotateMat(float x, float y, float z, glm::mat4 transMatrix) {
	float pi = 3.1415926f;
	float theta = y*pi/180;
	glm::mat4x4 rotmat = glm::mat4x4(cos(theta),0,sin(theta),0,
										 0,1,0,0,
										 -sin(theta),0,cos(theta),0,
										 0,0,0,1);
	transMatrix = transMatrix*rotmat;
	return transMatrix;
}

glm::mat4 Node::translateMat(float x, float y, float z, glm::mat4 transMatrix) {
	glm::mat4 transmat = glm::mat4( 1,0,0,x,
									0,1,0,y,
									0,0,1,z,
									0,0,0,1);
	transMatrix = transMatrix*transmat;
	return transMatrix;
}

glm::mat4 Node::scaleMat(float x, float y, float z, glm::mat4 transMatrix) {
	glm::mat4 scalemat =	glm::mat4(x,0,0,0,
										0,y,0,0,
										0,0,z,0,
										0,0,0,1);
	transMatrix = transMatrix*scalemat;
	return transMatrix;
}

void Node::updateMatrices(glm::mat4 mat) {

	/*glm::mat4 t = glm::mat4();
	glm::mat4 s = glm::mat4(scalex, 0, 0, 0,
							0, scaley, 0, 0,
							0, 0, scalez, 0,
							0, 0, 0, 1);
	glm::mat4 r = glm::mat4(cos(roty),0,sin(roty),0,
							0,1,0,0,
							-sin(roty),0,cos(roty),0,
							0,0,0,1);
	glm::mat4 tr = glm::mat4(1, 0, 0, transx,
							 0, 1, 0, transy,
							 0, 0, 1, transz,
							 0, 0, 0, 1);
	t = tr*r*s;
	matrix = t;
	fcube = t;
	//table
	tleg1 = t;
	tleg2 = t;
	tleg3 = t;
	tleg4 = t;
	ttop = t;
	//cabinet
	cbody = t;
	cdoor = t;
	//lamp
	lstand = t;
	ltop = t;
	//chair
	cleg1 = t;
	cleg2 = t;
	cleg3 = t;
	cleg4 = t;
	cseat = t;
	cback = t;*/
	
	matrix = matrix*mat;
	fcube = fcube*mat;
	//table
	tleg1 = tleg1*mat;
	tleg2 = tleg2*mat;
	tleg3 = tleg3*mat;
	tleg4 = tleg4*mat;
	ttop = ttop*mat;
	//cabinet
	cbody = cbody*mat;
	cdoor = cdoor*mat;
	//lamp
	lstand = lstand*mat;
	ltop = ltop*mat;
	//chair
	cleg1 = cleg1*mat;
	cleg2 = cleg2*mat;
	cleg3 = cleg3*mat;
	cleg4 = cleg4*mat;
	cseat = cseat*mat;
	cback = cback*mat;
	if(ge == 3) {
		cout << endl;
	}
}

void Node::rotateN(float angle, float xi, float zi) { /// y rot;
	rY += angle;
	float Pi = 3.1415926f;
	float angl = angle*Pi/180;
	float pSize, a, b, c;
	glm::mat4x4 tr;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			tr[i][j] = 0;
		}
		tr[i][i] = 1;
	}
	float cs = cos(angl);
	float sn = sin(angl);
	tr[0][0] = cs;
	tr[0][2] = sn;
	tr[2][0] = -sn;
	tr[2][2] = cs;
	if (parent == nullptr) {
		trans = trans*tr;
	} else {
		
		glm::mat4x4 origin;
		glm::mat4x4 master;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				origin[i][j] = 0;
				master[i][j] = 0;
			}
			origin[i][i] = 1;
			master[i][i] = 1;
		}
		origin[0][3] = -xi;
		master[0][3] = xi;
		origin[2][3] = -zi;
		master[2][3] = zi;

		trans = trans*origin*tr*master;
		glm::vec4 vD = glm::vec4(dX,0,dZ,1);
		vD = vD*trans;
		dX = vD[0];
		dZ = vD[2];
	}
	
	bbTrans(trans);

	if (ge == 5) {
		for (int i = 0; i < meshN->Verts->size(); i++) {
			glm::vec4 p;
			p[0] = meshN->Verts->at(i)[0];
			p[1] = meshN->Verts->at(i)[1];
			p[2] = meshN->Verts->at(i)[2];
			p[3] = 1;
	
			p = p*trans;
			meshN->Verts->at(i)[0] = p[0];
			meshN->Verts->at(i)[1] = p[1];
			meshN->Verts->at(i)[2] = p[2];
		}
		for (int i = 0; i < meshN->Norms->size(); i++) {
			glm::vec4 p;
			p[0] = meshN->Norms->at(i)[0];
			p[1] = meshN->Norms->at(i)[1];
			p[2] = meshN->Norms->at(i)[2];
			p[3] = 0;
	
			p = p*trans;
			meshN->Norms->at(i)[0] = p[0];
			meshN->Norms->at(i)[1] = p[1];
			meshN->Norms->at(i)[2] = p[2];
		}
	} else {
		for (int i = 0; i < geometry->size(); i++) {
			glm::vec4 p;
			p[0] = geometry->at(i)[0];
			p[1] = geometry->at(i)[1];
			p[2] = geometry->at(i)[2];
			p[3] = 1;
	
			p = p*trans;
			geometry->at(i)[0] = p[0];
			geometry->at(i)[1] = p[1];
			geometry->at(i)[2] = p[2];
		}
	}
	updateMatrices(transform);
	trans = glm::mat4(1.0f);

	if(ge == 0) {
		for(int i = 0; i < geometry->size(); i++ ) {
			furn->floor->at(i) = geometry->at(i);
		}
	}
	if(ge == 1) {
		for(int i = 0; i < geometry->size(); i++ ) {
			if( i < furn->t_top->size()) {
				furn->t_top->at(i) = geometry->at(i);
			} else if (i >= furn->t_top->size() && i < furn->t_top->size() + (geometry->size() - furn->t_top->size())/4) {
				furn->t_leg1->at(i - furn->t_top->size()) = geometry->at(i);
			} else if (furn->t_top->size() + (geometry->size() - furn->t_top->size())/4 && i < furn->t_top->size() + (geometry->size() - furn->t_top->size())/2) {
				furn->t_leg2->at(i - (furn->t_top->size() + (geometry->size() - furn->t_top->size())/4)) = geometry->at(i);
			} else if (furn->t_top->size() + (geometry->size() - furn->t_top->size())/2 && i < furn->t_top->size() + (geometry->size() - furn->t_top->size())*3/4) {
				furn->t_leg3->at(i - (furn->t_top->size() + (geometry->size() - furn->t_top->size())/2)) = geometry->at(i);
			} else if (furn->t_top->size() + (geometry->size() - furn->t_top->size())*3/4 && i < geometry->size()) {
				furn->t_leg4->at(i - (furn->t_top->size() + (geometry->size() - furn->t_top->size())*3/4)) = geometry->at(i);
			}
		}
	}
	if(ge == 2) {
		for(int i = 0; i < geometry->size(); i++ ) {
			if( i < geometry->size()/6) {
				furn->c_top->at(i) = geometry->at(i);
			} else if (i >= geometry->size()/6 && i < 2*geometry->size()/6) {
				furn->c_leg1->at(i - geometry->size()/6) = geometry->at(i);
			} else if (i >= 2*geometry->size()/6 && i < 3*geometry->size()/6) {
				furn->c_leg2->at(i - 2*geometry->size()/6) = geometry->at(i);
			} else if (i >= 3*geometry->size()/6 && i < 4*geometry->size()/6) {
				furn->c_leg3->at(i - 3*geometry->size()/6) = geometry->at(i);
			} else if (i >= 4*geometry->size()/6 && i < 5*geometry->size()/6) {
				furn->c_leg4->at(i - 4*geometry->size()/6) = geometry->at(i);
			} else if (i < geometry->size()) {
				furn->c_back->at(i - 5*geometry->size()/6) = geometry->at(i);
			}
		}
	}
	if(ge == 3) {
		for(int i = 0; i < geometry->size(); i++ ) {
			if (i < furn->cab_base->size()) {
				furn->cab_base->at(i) = geometry->at(i);
			} else if (i >= furn->cab_base->size() && i < geometry->size()) {
				furn->cab_door->at(i -  furn->cab_base->size()) = geometry->at(i);
			}
		}
	}
	if(ge == 4) {
		for(int i = 0; i < geometry->size(); i++ ) {
			if(i < furn->l_base->size()) {
				furn->l_base->at(i) = geometry->at(i);
			} else if (i >= furn->l_base->size() && i < geometry->size()) {
				furn->l_lamp->at(i - furn->l_base->size()) = geometry->at(i);
			}
		}
	}
	//return tr;
}

void Node::translateN(float x, float z) {
	tX += x;
	tZ += z;
	glm::mat4x4 tr;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			tr[i][j] = 0;
		}
	}
	for (int i = 0; i < 4; i++) {
		tr[i][i] = 1;
	}
	tr[0][3] = x;
	tr[1][3] = 0;
	tr[2][3] = z;
	trans = trans*tr;

	glm::vec4 vD = glm::vec4(dX,0,dZ,1);
	vD = vD*trans;
	dX = vD[0];
	dZ = vD[2];

	bbTrans(trans);

	if (ge == 5) {
		for (int i = 0; i < meshN->Verts->size(); i++) {
			glm::vec4 p;
			p[0] = meshN->Verts->at(i)[0];
			p[1] = meshN->Verts->at(i)[1];
			p[2] = meshN->Verts->at(i)[2];
			p[3] = 1;
	
			p = p*trans;
			meshN->Verts->at(i)[0] = p[0];
			meshN->Verts->at(i)[1] = p[1];
			meshN->Verts->at(i)[2] = p[2];
		}
		for (int i = 0; i < meshN->Norms->size(); i++) {
			glm::vec4 p;
			p[0] = meshN->Norms->at(i)[0];
			p[1] = meshN->Norms->at(i)[1];
			p[2] = meshN->Norms->at(i)[2];
			p[3] = 0;
	
			p = p*trans;
			meshN->Norms->at(i)[0] = p[0];
			meshN->Norms->at(i)[1] = p[1];
			meshN->Norms->at(i)[2] = p[2];
		}
	} else {
		for (int i = 0; i < geometry->size(); i++) {
			glm::vec4 p;
			p[0] = geometry->at(i)[0];
			p[1] = geometry->at(i)[1];
			p[2] = geometry->at(i)[2];
			p[3] = 1;
	
			p = p*trans;
			geometry->at(i)[0] = p[0];
			geometry->at(i)[1] = p[1];
			geometry->at(i)[2] = p[2];
		}
	}
	updateMatrices(transform);
	trans = glm::mat4(1.0f);
	
	if(ge == 0) {
		for(int i = 0; i < geometry->size(); i++ ) {
			furn->floor->at(i) = geometry->at(i);
		}
	}
	if(ge == 1) {
		for(int i = 0; i < geometry->size(); i++ ) {
			if( i < furn->t_top->size()) {
				furn->t_top->at(i) = geometry->at(i);
			} else if (i >= furn->t_top->size() && i < furn->t_top->size() + (geometry->size() - furn->t_top->size())/4) {
				furn->t_leg1->at(i - furn->t_top->size()) = geometry->at(i);
			} else if (furn->t_top->size() + (geometry->size() - furn->t_top->size())/4 && i < furn->t_top->size() + (geometry->size() - furn->t_top->size())/2) {
				furn->t_leg2->at(i - (furn->t_top->size() + (geometry->size() - furn->t_top->size())/4)) = geometry->at(i);
			} else if (furn->t_top->size() + (geometry->size() - furn->t_top->size())/2 && i < furn->t_top->size() + (geometry->size() - furn->t_top->size())*3/4) {
				furn->t_leg3->at(i - (furn->t_top->size() + (geometry->size() - furn->t_top->size())/2)) = geometry->at(i);
			} else if (furn->t_top->size() + (geometry->size() - furn->t_top->size())*3/4 && i < geometry->size()) {
				furn->t_leg4->at(i - (furn->t_top->size() + (geometry->size() - furn->t_top->size())*3/4)) = geometry->at(i);
			}
		}
	}
	if(ge == 2) {
		for(int i = 0; i < geometry->size(); i++ ) {
			if( i < geometry->size()/6) {
				furn->c_top->at(i) = geometry->at(i);
			} else if (i >= geometry->size()/6 && i < 2*geometry->size()/6) {
				furn->c_leg1->at(i - geometry->size()/6) = geometry->at(i);
			} else if (i >= 2*geometry->size()/6 && i < 3*geometry->size()/6) {
				furn->c_leg2->at(i - 2*geometry->size()/6) = geometry->at(i);
			} else if (i >= 3*geometry->size()/6 && i < 4*geometry->size()/6) {
				furn->c_leg3->at(i - 3*geometry->size()/6) = geometry->at(i);
			} else if (i >= 4*geometry->size()/6 && i < 5*geometry->size()/6) {
				furn->c_leg4->at(i - 4*geometry->size()/6) = geometry->at(i);
			} else if (i < geometry->size()) {
				furn->c_back->at(i - 5*geometry->size()/6) = geometry->at(i);
			}
		}
	}
	if(ge == 3) {
		for(int i = 0; i < geometry->size(); i++ ) {
			if (i < furn->cab_base->size()) {
				furn->cab_base->at(i) = geometry->at(i);
			} else if (i >= furn->cab_base->size() && i < geometry->size()) {
				furn->cab_door->at(i -  furn->cab_base->size()) = geometry->at(i);
			}
		}
	}
	if(ge == 4) {
		for(int i = 0; i < geometry->size(); i++ ) {
			if(i < furn->l_base->size()) {
				furn->l_base->at(i) = geometry->at(i);
			} else if (i >= furn->l_base->size() && i < geometry->size()) {
				furn->l_lamp->at(i - furn->l_base->size()) = geometry->at(i);
			}
		}
	}
}

void Node::scaleN(float x, float y, float z, float h, float xi, float zi, float a) {
	sX *= x;
	sY *= y;
	sZ *= z;
	float Pi = 3.1415926f;
	float aor = -a*Pi/180;
	float ama = a*Pi/180;
	glm::mat4x4 tr;
	glm::vec4 vH = glm::vec4(0,height,0,1); // height 
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			tr[i][j] = 0;
		}
	}
	for (int i = 0; i < 4; i++) {
		tr[i][i] = 1;
	}
	tr[0][0] = x;
	tr[1][1] = y;
	tr[2][2] = z;

	glm::mat4x4 a_origin;
	glm::mat4x4 a_master;
	float cso = cos(aor);
	float sno = sin(aor);
	float csm = cos(ama);
	float snm = sin(ama);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			a_origin[i][j] = 0;
			a_master[i][j] = 0;
		}
		a_origin[i][i] = 1;
		a_master[i][i] = 1;
	}
	a_origin[0][0] = cso;
	a_origin[0][2] = sno;
	a_origin[2][0] = -sno;
	a_origin[2][2] = cso;
	a_master[0][0] = csm;
	a_master[0][2] = snm;
	a_master[2][0] = -snm;
	a_master[2][2] = csm;

	if (parent == nullptr) {
		trans = trans*a_origin*tr*a_master;
	} else {
		glm::mat4x4 origin;
		glm::mat4x4 master;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				origin[i][j] = 0;
				master[i][j] = 0;
			}
			origin[i][i] = 1;
			master[i][i] = 1;
		}
		origin[0][3] = -xi;
		master[0][3] = xi;
		origin[2][3] = -zi;
		master[2][3] = zi;
		origin[1][3] = -h;
		master[1][3] = h;
		trans = trans*origin*a_origin*tr*a_master*master;
	}
	vH = glm::vec4(dX,height,dZ,1);
	vH = vH*trans;
	dX = vH[0];
	height = vH[1];
	dZ = vH[2];

	bbTrans(trans);

	if (ge == 5) {
		for (int i = 0; i < meshN->Verts->size(); i++) {
			glm::vec4 p;
			p[0] = meshN->Verts->at(i)[0];
			p[1] = meshN->Verts->at(i)[1];
			p[2] = meshN->Verts->at(i)[2];
			p[3] = 1;
	
			p = p*trans;
			meshN->Verts->at(i)[0] = p[0];
			meshN->Verts->at(i)[1] = p[1];
			meshN->Verts->at(i)[2] = p[2];
		}
		for (int i = 0; i < meshN->Norms->size(); i++) {
			glm::vec4 p;
			p[0] = meshN->Norms->at(i)[0];
			p[1] = meshN->Norms->at(i)[1];
			p[2] = meshN->Norms->at(i)[2];
			p[3] = 0;
	
			p = p*trans;
			meshN->Norms->at(i)[0] = p[0];
			meshN->Norms->at(i)[1] = p[1];
			meshN->Norms->at(i)[2] = p[2];
		}
	} else {
		for (int i = 0; i < geometry->size(); i++) {
			glm::vec4 p;
			p[0] = geometry->at(i)[0];
			p[1] = geometry->at(i)[1];
			p[2] = geometry->at(i)[2];
			p[3] = 1;
	
			p = p*trans;
			geometry->at(i)[0] = p[0];
			geometry->at(i)[1] = p[1];
			geometry->at(i)[2] = p[2];
		}
	}
	updateMatrices(transform);
	trans = glm::mat4(1.0f);

	if(ge == 0) {
		for(int i = 0; i < geometry->size(); i++ ) {
			furn->floor->at(i) = geometry->at(i);
		}
	}
	if(ge == 1) {
		for(int i = 0; i < geometry->size(); i++ ) {
			if( i < furn->t_top->size()) {
				furn->t_top->at(i) = geometry->at(i);
			} else if (i >= furn->t_top->size() && i < furn->t_top->size() + (geometry->size() - furn->t_top->size())/4) {
				furn->t_leg1->at(i - furn->t_top->size()) = geometry->at(i);
			} else if (furn->t_top->size() + (geometry->size() - furn->t_top->size())/4 && i < furn->t_top->size() + (geometry->size() - furn->t_top->size())/2) {
				furn->t_leg2->at(i - (furn->t_top->size() + (geometry->size() - furn->t_top->size())/4)) = geometry->at(i);
			} else if (furn->t_top->size() + (geometry->size() - furn->t_top->size())/2 && i < furn->t_top->size() + (geometry->size() - furn->t_top->size())*3/4) {
				furn->t_leg3->at(i - (furn->t_top->size() + (geometry->size() - furn->t_top->size())/2)) = geometry->at(i);
			} else if (furn->t_top->size() + (geometry->size() - furn->t_top->size())*3/4 && i < geometry->size()) {
				furn->t_leg4->at(i - (furn->t_top->size() + (geometry->size() - furn->t_top->size())*3/4)) = geometry->at(i);
			}
		}
	}
	if(ge == 2) {
		for(int i = 0; i < geometry->size(); i++ ) {
			if( i < geometry->size()/6) {
				furn->c_top->at(i) = geometry->at(i);
			} else if (i >= geometry->size()/6 && i < 2*geometry->size()/6) {
				furn->c_leg1->at(i - geometry->size()/6) = geometry->at(i);
			} else if (i >= 2*geometry->size()/6 && i < 3*geometry->size()/6) {
				furn->c_leg2->at(i - 2*geometry->size()/6) = geometry->at(i);
			} else if (i >= 3*geometry->size()/6 && i < 4*geometry->size()/6) {
				furn->c_leg3->at(i - 3*geometry->size()/6) = geometry->at(i);
			} else if (i >= 4*geometry->size()/6 && i < 5*geometry->size()/6) {
				furn->c_leg4->at(i - 4*geometry->size()/6) = geometry->at(i);
			} else if (i < geometry->size()) {
				furn->c_back->at(i - 5*geometry->size()/6) = geometry->at(i);
			}
		}
	}
	if(ge == 3) {
		for(int i = 0; i < geometry->size(); i++ ) {
			if (i < furn->cab_base->size()) {
				furn->cab_base->at(i) = geometry->at(i);
			} else if (i >= furn->cab_base->size() && i < geometry->size()) {
				furn->cab_door->at(i -  furn->cab_base->size()) = geometry->at(i);
			}
		}
	}
	if(ge == 4) {
		for(int i = 0; i < geometry->size(); i++ ) {
			if(i < furn->l_base->size()) {
				furn->l_base->at(i) = geometry->at(i);
			} else if (i >= furn->l_base->size() && i < geometry->size()) {
				furn->l_lamp->at(i - furn->l_base->size()) = geometry->at(i);
			}
		}
	}
	//return tr;
}

void Node::stackUp(float y) {
	glm::mat4x4 tr;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			tr[i][j] = 0;
		}
	}
	for (int i = 0; i < 4; i++) {
		tr[i][i] = 1;
	}
	tr[0][3] = 0;
	tr[1][3] = y;
	tr[2][3] = 0;
	trans = trans*tr;

	bbTrans(trans);

	if (ge == 5) {
		for (int i = 0; i < meshN->Verts->size(); i++) {
			glm::vec4 p;
			p[0] = meshN->Verts->at(i)[0];
			p[1] = meshN->Verts->at(i)[1];
			p[2] = meshN->Verts->at(i)[2];
			p[3] = 1;
	
			p = p*trans;
			meshN->Verts->at(i)[0] = p[0];
			meshN->Verts->at(i)[1] = p[1];
			meshN->Verts->at(i)[2] = p[2];
		}
		for (int i = 0; i < meshN->Norms->size(); i++) {
			glm::vec4 p;
			p[0] = meshN->Norms->at(i)[0];
			p[1] = meshN->Norms->at(i)[1];
			p[2] = meshN->Norms->at(i)[2];
			p[3] = 0;
	
			p = p*trans;
			meshN->Norms->at(i)[0] = p[0];
			meshN->Norms->at(i)[1] = p[1];
			meshN->Norms->at(i)[2] = p[2];
		}
	} else {
		for (int i = 0; i < geometry->size(); i++) {
			glm::vec4 p;
			p[0] = geometry->at(i)[0];
			p[1] = geometry->at(i)[1];
			p[2] = geometry->at(i)[2];
			p[3] = 1;
	
			p = p*trans;
			geometry->at(i)[0] = p[0];
			geometry->at(i)[1] = p[1];
			geometry->at(i)[2] = p[2];
		}
	}
	updateMatrices(transform);
	trans = glm::mat4(1.0f);
	
	if(ge == 0) {
		for(int i = 0; i < geometry->size(); i++ ) {
			furn->floor->at(i) = geometry->at(i);
		}
	}
	if(ge == 1) {
		for(int i = 0; i < geometry->size(); i++ ) {
			if( i < furn->t_top->size()) {
				furn->t_top->at(i) = geometry->at(i);
			} else if (i >= furn->t_top->size() && i < furn->t_top->size() + (geometry->size() - furn->t_top->size())/4) {
				furn->t_leg1->at(i - furn->t_top->size()) = geometry->at(i);
			} else if (furn->t_top->size() + (geometry->size() - furn->t_top->size())/4 && i < furn->t_top->size() + (geometry->size() - furn->t_top->size())/2) {
				furn->t_leg2->at(i - (furn->t_top->size() + (geometry->size() - furn->t_top->size())/4)) = geometry->at(i);
			} else if (furn->t_top->size() + (geometry->size() - furn->t_top->size())/2 && i < furn->t_top->size() + (geometry->size() - furn->t_top->size())*3/4) {
				furn->t_leg3->at(i - (furn->t_top->size() + (geometry->size() - furn->t_top->size())/2)) = geometry->at(i);
			} else if (furn->t_top->size() + (geometry->size() - furn->t_top->size())*3/4 && i < geometry->size()) {
				furn->t_leg4->at(i - (furn->t_top->size() + (geometry->size() - furn->t_top->size())*3/4)) = geometry->at(i);
			}
		}
	}
	if(ge == 2) {
		for(int i = 0; i < geometry->size(); i++ ) {
			if( i < geometry->size()/6) {
				furn->c_top->at(i) = geometry->at(i);
			} else if (i >= geometry->size()/6 && i < 2*geometry->size()/6) {
				furn->c_leg1->at(i - geometry->size()/6) = geometry->at(i);
			} else if (i >= 2*geometry->size()/6 && i < 3*geometry->size()/6) {
				furn->c_leg2->at(i - 2*geometry->size()/6) = geometry->at(i);
			} else if (i >= 3*geometry->size()/6 && i < 4*geometry->size()/6) {
				furn->c_leg3->at(i - 3*geometry->size()/6) = geometry->at(i);
			} else if (i >= 4*geometry->size()/6 && i < 5*geometry->size()/6) {
				furn->c_leg4->at(i - 4*geometry->size()/6) = geometry->at(i);
			} else if (i < geometry->size()) {
				furn->c_back->at(i - 5*geometry->size()/6) = geometry->at(i);
			}
		}
	}
	if(ge == 3) {
		for(int i = 0; i < geometry->size(); i++ ) {
			if (i < furn->cab_base->size()) {
				furn->cab_base->at(i) = geometry->at(i);
			} else if (i >= furn->cab_base->size() && i < geometry->size()) {
				furn->cab_door->at(i -  furn->cab_base->size()) = geometry->at(i);
			}
		}
	}
	if(ge == 4) {
		for(int i = 0; i < geometry->size(); i++ ) {
			if(i < furn->l_base->size()) {
				furn->l_base->at(i) = geometry->at(i);
			} else if (i >= furn->l_base->size() && i < geometry->size()) {
				furn->l_lamp->at(i - furn->l_base->size()) = geometry->at(i);
			}
		}
	}
}


void Node::bbTrans(glm::mat4x4 tr) {
	glm::vec4 bvt1 = glm::vec4(bb1[0],bb1[1],bb1[2],1);
	bvt1 = bvt1*tr;
	for (int i = 0; i < 3; i++) {
		bb1[i] = bvt1[i];
	}

	glm::vec4 bvt2 = glm::vec4(bb2[0],bb2[1],bb2[2],1);
	bvt2 = bvt2*tr;
	for (int i = 0; i < 3; i++) {
		bb2[i] = bvt2[i];
	}

	glm::vec4 bvt3 = glm::vec4(bb3[0],bb3[1],bb3[2],1);
	bvt3 = bvt3*tr;
	for (int i = 0; i < 3; i++) {
		bb3[i] = bvt3[i];
	}

	glm::vec4 bvt4 = glm::vec4(bb4[0],bb4[1],bb4[2],1);
	bvt4 = bvt4*tr;
	for (int i = 0; i < 3; i++) {
		bb4[i] = bvt4[i];
	}


	glm::vec4 bvt5 = glm::vec4(bb5[0],bb5[1],bb5[2],1);
	bvt5 = bvt5*tr;
	for (int i = 0; i < 3; i++) {
		bb5[i] = bvt5[i];
	}

	glm::vec4 bvt6 = glm::vec4(bb6[0],bb6[1],bb6[2],1);
	bvt6 = bvt6*tr;
	for (int i = 0; i < 3; i++) {
		bb6[i] = bvt6[i];
	}

	glm::vec4 bvt7 = glm::vec4(bb7[0],bb7[1],bb7[2],1);
	bvt7 = bvt7*tr;
	for (int i = 0; i < 3; i++) {
		bb7[i] = bvt7[i];
	}

	glm::vec4 bvt8 = glm::vec4(bb8[0],bb8[1],bb8[2],1);
	bvt8 = bvt8*tr;
	for (int i = 0; i < 3; i++) {
		bb8[i] = bvt8[i];
	}
}
