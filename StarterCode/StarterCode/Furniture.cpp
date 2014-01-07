#include "Node.h"
#include "Furniture.h"

#include <cmath>
#include <iostream>

Furniture::Furniture() {
	furnType = "";
	float col[3] = {0,0,0};
	float pos[3] = {0,0,0};
	float sca[3] = {0,0,0};
	for (int i = 0; i < 3; i++) {
		furnCol.push_back(col[i]);
		furnPos.push_back(pos[i]);
		furnSca.push_back(sca[i]);
	}
	furnRot = 0;
}

Furniture::Furniture(string fT, vector<float> fC, vector<int> fP, float fR, vector<float> fS, Mesh* m) {
	furnType = fT;
	furnCol = fC;

	furnPos = fP;
	furnRot = fR;
	furnSca = fS;

	float temp[3];

	for (int i = 0; i < 3; i++) {
		temp[i] = 0;
	}
	
	if (furnType.compare("floor") == 0) {
		temp[0] = 0;
		temp[1] = 0;
		temp[2] = 0;
		this->floor = this->makeRect(temp, 1, 1, 1); 
	} else if(furnType.compare("table") == 0) {
		temp[0] = 0;
		temp[1] = 0.4f;
		temp[2] = 0;
		this->t_top = this->makeCylinder(temp,1.0f,0.1f);
		temp[0] = -0.4f;
		temp[1] = 0;
		temp[2] = -0.4f;
		this->t_leg1 = this->makeRect(temp,0.5f,0.1f,0.1f);
		temp[0] = 0.4f;
		temp[1] = 0;
		temp[2] = -0.4f;
		this->t_leg2 = this->makeRect(temp,0.5f,0.1f,0.1f);
		temp[0] = -0.4f;
		temp[1] = 0;
		temp[2] = 0.4f;
		this->t_leg3 = this->makeRect(temp,0.5f,0.1f,0.1f);
		temp[0] = 0.4f;
		temp[1] = 0;
		temp[2] = 0.4f;
		this->t_leg4 = this->makeRect(temp,0.5f,0.1f,0.1f);
	} else if(furnType.compare("chair") == 0) {
		temp[0] = 0;
		temp[1] = 0;
		temp[2] = 0;
		this->c_top = this->makeRect(temp,0.05f,0.3f,0.3f);
		temp[0] = 0;
		temp[1] = 0.25f;
		temp[2] = 0.2f;
		this->c_back = this->makeRect(temp,0.4f,0.3f,0.05f);
		temp[0] = -0.2f;
		temp[1] = -0.25f;
		temp[2] = -0.2f;
		this->c_leg1 = this->makeRect(temp,0.25f,0.1f,0.1f);
		temp[0] = 0.2f;
		temp[1] = -0.25f;
		temp[2] = -0.2f;
		this->c_leg2 = this->makeRect(temp,0.25f,0.1f,0.1f);
		temp[0] = -0.2f;
		temp[1] = -0.25f;
		temp[2] = 0.2f;
		this->c_leg3 = this->makeRect(temp,0.25f,0.1f,0.1f);
		temp[0] = 0.2f;
		temp[1] = -0.25f;
		temp[2] = 0.2f;
		this->c_leg4 = this->makeRect(temp,0.25f,0.1f,0.1f);
	} else if(furnType.compare("lamp") == 0) {
		temp[0] = 0;
		temp[1] = -0.5f;
		temp[2] = 0;
		this->l_base = this->makeCylinder(temp,0.05f,0.5f);
		temp[0] = 0;
		temp[1] = 0.2f;
		temp[2] = 0;
		this->l_lamp = this->makeSphere(temp,0.2f);
	} else if(furnType.compare("cabinet") == 0) {
		temp[0] = 0;
		temp[1] = 0;
		temp[2] = 0;
		this->cab_base = this->makeRect(temp,0.5f,0.5f,0.5f);
		temp[0] = 0.2f;
		temp[1] = 0;
		temp[2] = 0.2f;
		this->cab_door = this->makeRect(temp,0.4f,0.4f,0.5f);
	} else if(furnType.compare("mesh") == 0) {
		this->meshVer = m->Verts;
	}
}


vector<vector<float>>* Furniture::makeRect(float c[3], float h, float w, float l) {
	vector<vector<float>>* rect = new vector<vector<float>>();
	//for (int i = 0; i < 2
	for (int i = 0; i < 6; i++) {
		if (i == 0) {
			for (int j = 0; j < 4; j++) {
				vector<float> points;
				float point[4];
				if (j == 0) {
					point[0] = c[0] - w;
					point[1] = c[1] + h;
					point[2] = c[2] - l;
					point[3] = 1.0f;
				} else if (j == 1) {
					point[0] = c[0] + w;
					point[1] = c[1] + h;
					point[2] = c[2] - l;
					point[3] = 1.0f;
				} else if (j == 2) {
					point[0] = c[0] + w;
					point[1] = c[1] + h;
					point[2] = c[2] + l;
					point[3] = 1.0f;
				} else if (j == 3) {
					point[0] = c[0] - w;
					point[1] = c[1] + h;
					point[2] = c[2] + l;
					point[3] = 1.0f;
				}
				for (int k = 0; k < 4; k++) {
					points.push_back(point[k]);
				}
				rect->push_back(points);
			}
		} else if (i == 1) {
			for (int j = 0; j < 4; j++) {
				vector<float> points;
				float point[4];
				if (j == 0) {
					point[0] = c[0] - w;
					point[1] = c[1] + h;
					point[2] = c[2] - l;
					point[3] = 1.0f;
				} else if (j == 1) {
					point[0] = c[0] + w;
					point[1] = c[1] + h;
					point[2] = c[2] - l;
					point[3] = 1.0f;
				} else if (j == 2) {
					point[0] = c[0] + w;
					point[1] = c[1] - h;
					point[2] = c[2] - l;
					point[3] = 1.0f;
				} else if (j == 3) {
					point[0] = c[0] - w;
					point[1] = c[1] - h;
					point[2] = c[2] - l;
					point[3] = 1.0f;
				}
				for (int k = 0; k < 4; k++) {
					points.push_back(point[k]);
				}
				rect->push_back(points);
			}
		} else if (i == 2) {
			for (int j = 0; j < 4; j++) {
				vector<float> points;
				float point[4];
				if (j == 0) {
					point[0] = c[0] + w;
					point[1] = c[1] + h;
					point[2] = c[2] - l;
					point[3] = 1.0f;
				} else if (j == 1) {
					point[0] = c[0] + w;
					point[1] = c[1] + h;
					point[2] = c[2] + l;
					point[3] = 1.0f;
				} else if (j == 2) {
					point[0] = c[0] + w;
					point[1] = c[1] - h;
					point[2] = c[2] + l;
					point[3] = 1.0f;
				} else if (j == 3) {
					point[0] = c[0] + w;
					point[1] = c[1] - h;
					point[2] = c[2] - l;
					point[3] = 1.0f;
				}
				for (int k = 0; k < 4; k++) {
					points.push_back(point[k]);
				}
				rect->push_back(points);
			}
		} else if (i == 3) {
			for (int j = 0; j < 4; j++) {
				vector<float> points;
				float point[4];
				if (j == 0) {
					point[0] = c[0] + w;
					point[1] = c[1] + h;
					point[2] = c[2] + l;
					point[3] = 1.0f;
				} else if (j == 1) {
					point[0] = c[0] + w;
					point[1] = c[1] - h;
					point[2] = c[2] + l;
					point[3] = 1.0f;
				} else if (j == 2) {
					point[0] = c[0] - w;
					point[1] = c[1] - h;
					point[2] = c[2] + l;
					point[3] = 1.0f;
				} else if (j == 3) {
					point[0] = c[0] - w;
					point[1] = c[1] + h;
					point[2] = c[2] + l;
					point[3] = 1.0f;
				}
				for (int k = 0; k < 4; k++) {
					points.push_back(point[k]);
				}
				rect->push_back(points);
			}
		} else if (i == 4) {
			for (int j = 0; j < 4; j++) {
				vector<float> points;
				float point[4];
				if (j == 0) {
					point[0] = c[0] - w;
					point[1] = c[1] + h;
					point[2] = c[2] - l;
					point[3] = 1.0f;
				} else if (j == 1) {
					point[0] = c[0] - w;
					point[1] = c[1] + h;
					point[2] = c[2] + l;
					point[3] = 1.0f;
				} else if (j == 2) {
					point[0] = c[0] - w;
					point[1] = c[1] - h;
					point[2] = c[2] + l;
					point[3] = 1.0f;
				} else if (j == 3) {
					point[0] = c[0] - w;
					point[1] = c[1] - h;
					point[2] = c[2] - l;
					point[3] = 1.0f;
				}
				for (int k = 0; k < 4; k++) {
					points.push_back(point[k]);
				}
				rect->push_back(points);
			}
		} else if (i == 5) {
			for (int j = 0; j < 4; j++) {
				vector<float> points;
				float point[4];
				if (j == 0) {
					point[0] = c[0] - w;
					point[1] = c[1] - h;
					point[2] = c[2] - l;
					point[3] = 1.0f;
				} else if (j == 1) {
					point[0] = c[0] + w;
					point[1] = c[1] - h;
					point[2] = c[2] - l;
					point[3] = 1.0f;
				} else if (j == 2) {
					point[0] = c[0] + w;
					point[1] = c[1] - h;
					point[2] = c[2] + l;
					point[3] = 1.0f;
				} else if (j == 3) {
					point[0] = c[0] - w;
					point[1] = c[1] - h;
					point[2] = c[2] + l;
					point[3] = 1.0f;
				}
				for (int k = 0; k < 4; k++) {
					points.push_back(point[k]);
				}
				rect->push_back(points);
			}
		}
	}
	
	return rect;
}

vector<vector<float>>* Furniture::makeSphere(float c[3], float r) {
	vector<vector<float>>* sphere = new vector<vector<float>>();
	float Pi = 3.1415926f;
	bool zero = true; bool piovertwo = true;
	float x, y, z;
	for(int a = 0; a < 360; a += 20) {
		for(int b = 0; b <= 180; b += 15) {
			if(b == 0 && zero == true) {
				zero = false;
			} else if (b == 0 && zero == false) {
				continue;
			}
			if(b == 180 && piovertwo == true) {
				piovertwo = false;
			} else if (b == 180 && piovertwo == false) {
				continue;
			}
			x = c[0] + r*cos((float)a*Pi/180)*sin((float)b*Pi/180);
			y = c[1] + r*cos((float)b*Pi/180);
			z = c[2] + r*sin((float)a*Pi/180)*sin((float)b*Pi/180);
			
			vector<float> vertex;
			vertex.push_back(x);
			vertex.push_back(y);
			vertex.push_back(z);

			sphere->push_back(vertex);
		}
	}
	return sphere;
}

vector<vector<float>>* Furniture::makeCylinder(float c[3], float r, float h) {
	vector<vector<float>>* cyl = new vector<vector<float>>();
	float Pi = 3.1415926f;
	float bot[3]; float top[3];
	float x, y, z;
	for (int i = 0; i < 3; i++) {
		bot[i] = c[i];
		top[i] = c[i];
	}
	top[1] = c[1] + h;
	vector<float> botp;
	vector<float> topp;
	for (int i = 0; i < 3; i++) {
		botp.push_back(bot[i]);
		topp.push_back(top[i]);
	}
	
	cyl->push_back(botp);
	
	cyl->push_back(topp);
	
	////////////caps//////////////////////////
	vector<vector<float>> caps;
	for(int b = 0; b < 360; b += 40) {
		x = c[0] + r*cos((float)b*Pi/180);
		y = c[1];
		z = c[2] + r*sin((float)b*Pi/180);
		vector<float> vt;
		vt.push_back(x);
		vt.push_back(y);
		vt.push_back(z);
		vector<float> vb;
		vb.push_back(x);
		vb.push_back(y+h);
		vb.push_back(z);
		caps.push_back(vb);
		cyl->push_back(vt);
	}
	for (int i = 0; i < caps.size(); i++) {
		cyl->push_back(caps[i]);
	}
	
	////////////sides/////////////////////
	for(int b = 0; b < 360; b += 40) {
		x = c[0] + r*cos((float)b*Pi/180);
		y = c[1];
		z = c[2] + r*sin((float)b*Pi/180);
		vector<float> vs1;
		vs1.push_back(x);
		vs1.push_back(y);
		vs1.push_back(z);
		vector<float> vs2;
		vs2.push_back(x);
		vs2.push_back(y + h);
		vs2.push_back(z);

		cyl->push_back(vs1);
		cyl->push_back(vs2);
	}
	return cyl;
}
