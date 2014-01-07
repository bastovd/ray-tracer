#include "Mesh.h"

Mesh::Mesh() {
	Tris = new vector<vector<int>>();
	Tri = new vector<int>();
	Norms = new vector<vector<float>>();
	Verts = new vector<vector<float>>();

}

bool Mesh::convexity(vector<vector<float>> *baseVerts) {
	float ax = baseVerts->at(0)[0];
	float ay = baseVerts->at(0)[1];
	float az = baseVerts->at(0)[2];
	glm::vec3 a;
	a[0] = ax; a[1] = ay; a[2] = az;

	float bx = baseVerts->at(1)[0];
	float by = baseVerts->at(1)[1];
	float bz = baseVerts->at(1)[2];
	glm::vec3 b;
	b[0] = bx; b[1] = by; b[2] = bz;

	float cx = baseVerts->at(2)[0];
	float cy = baseVerts->at(2)[1];
	float cz = baseVerts->at(2)[2];
	glm::vec3 c;
	c[0] = cx; c[1] = cy; c[2] = cz;

	glm::vec3 ba;
	glm::vec3 bc;

	ba[0] = a[0] - b[0]; ba[1] = a[1] - b[1]; ba[2] = a[2] - b[2];
	bc[0] = c[0] - b[0]; bc[1] = c[1] - b[1]; bc[2] = c[2] - b[2];

	glm::vec3 normV = glm::cross(ba,bc);
	int nDir;

	if (normV[1] >= 0) nDir = 1;
	else if (normV[1] < 0) nDir = -1;

	for (int i = 0; i < baseVerts->size()-2; i++) {
		ax = baseVerts->at(i)[0];
		ay = baseVerts->at(i)[1];
		az = baseVerts->at(i)[2];
		a[0] = ax; a[1] = ay; a[2] = az;

		bx = baseVerts->at(i+1)[0];
		by = baseVerts->at(i+1)[1];
		bz = baseVerts->at(i+1)[2];
		b[0] = bx; b[1] = by; b[2] = bz;

		cx = baseVerts->at(i+2)[0];
		cy = baseVerts->at(i+2)[1];
		cz = baseVerts->at(i+2)[2];
		c[0] = cx; c[1] = cy; c[2] = cz;

		ba[0] = a[0] - b[0]; ba[1] = a[1] - b[1]; ba[2] = a[2] - b[2];
		bc[0] = c[0] - b[0]; bc[1] = c[1] - b[1]; bc[2] = c[2] - b[2];

		normV = glm::cross(ba,bc);
		int nDir1;

		if (normV[1] >= 0) nDir1 = 1;
		else if (normV[1] < 0) nDir1 = -1;
		if (nDir1 != nDir) return false;

	}

	ax = baseVerts->at(baseVerts->size()-2)[0];
	ay = baseVerts->at(baseVerts->size()-2)[1];
	az = baseVerts->at(baseVerts->size()-2)[2];
	a[0] = ax; a[1] = ay; a[2] = az;

	bx = baseVerts->at(0)[0];
	by = baseVerts->at(0)[1];
	bz = baseVerts->at(0)[2];
	b[0] = bx; b[1] = by; b[2] = bz;

	cx = baseVerts->at(1)[0];
	cy = baseVerts->at(1)[1];
	cz = baseVerts->at(1)[2];
	c[0] = cx; c[1] = cy; c[2] = cz;

	ba[0] = a[0] - b[0]; ba[1] = a[1] - b[1]; ba[2] = a[2] - b[2];
	bc[0] = c[0] - b[0]; bc[1] = c[1] - b[1]; bc[2] = c[2] - b[2];

	normV = glm::cross(ba,bc);
	int nDir2;

	if (normV[1] >= 0) nDir2 = 1;
	else if (normV[1] < 0) nDir2 = -1;
	if (nDir2 != nDir) return false;

	return true;
}

void Mesh::extrusion(float length,  vector<vector<float>> *baseVerts) {
	

	int bVsize = baseVerts->size();

	if (baseVerts->size() < 3) {
		cout << "Not a valid polygon" << endl;
		return;
	}
	/*if (convexity(baseVerts) == false) {
		cout << "Polygon is not convex" << endl;
		return;
	}*/
	
	for (int i = 0; i < baseVerts->size(); i++) {
		Verts->push_back(baseVerts->at(i));
	}

	
	for (int i = 0; i < baseVerts->size(); i++) {
		vector<float> basevert;
		vector<float> bV = baseVerts->at(i);
		for (int j = 0; j < 3; j++) {
			basevert.push_back(bV[j]);
		}
		basevert[1] = basevert[1] + length;
		Verts->push_back(basevert);
	}
	
	for (int i = 0; i < Verts->size()/2-2; i++) {
		vector<int> Triangle;
		Triangle.push_back(0);
		Triangle.push_back(i + 1);
		Triangle.push_back(i + 2);
		Tris->push_back(Triangle);
	}
	for (int i = Verts->size()/2; i < Verts->size()-2; i++) {
		vector<int> Triangle;
		Triangle.push_back(Verts->size()/2);
		Triangle.push_back(i + 1);
		Triangle.push_back(i + 2);
		Tris->push_back(Triangle);
	}

	

	vector<vector<float>>* VertsCopy = new vector<vector<float>>();
	for (int i = 0; i < Verts->size(); i++) {
		VertsCopy->push_back(Verts->at(i));
	}
	bool caps = false;
	if (convexity(baseVerts) == false) {
		Tris = new vector<vector<int>>();
		Verts = new vector<vector<float>>();
		cout << "Polygon is not convex" << endl;
		caps = true;
	}
	int cSize = Verts->size();

	for (int i = 0; i < bVsize; i++) {
		if (i == bVsize - 1) {
			vector<float> newV1;
			newV1 = VertsCopy->at(i);
			vector<float> newV2;
			newV2 = VertsCopy->at(bVsize + i);
			vector<float> newV3;
			newV3 = VertsCopy->at(bVsize);
			vector<float> newV4;
			newV4 = VertsCopy->at(0);
				Verts->push_back(newV1);
				Verts->push_back(newV2);
				Verts->push_back(newV3);
				Verts->push_back(newV4);	
		} else {
			vector<float> newV1;
			newV1 = VertsCopy->at(i);
			vector<float> newV2;
			newV2 = VertsCopy->at(bVsize + i);
			vector<float> newV3;
			newV3 = VertsCopy->at(bVsize + i + 1);
			vector<float> newV4;
			newV4 = VertsCopy->at(i + 1);
				Verts->push_back(newV1);
				Verts->push_back(newV2);
				Verts->push_back(newV3);
				Verts->push_back(newV4);
		}
	}
	
	
	int sSize = Verts->size() - cSize;
	int spSize = sSize/4;

	for (int i = 0; i < spSize; i++) {
		vector<int> Triangle1;
		vector<int> Triangle2;
		Triangle1.push_back(cSize + 4*i + 0);
		Triangle1.push_back(cSize + 4*i + 1);
		Triangle1.push_back(cSize + 4*i + 2);
		Tris->push_back(Triangle1);
		Triangle2.push_back(cSize + 4*i + 0);
		Triangle2.push_back(cSize + 4*i + 2);
		Triangle2.push_back(cSize + 4*i + 3);
		Tris->push_back(Triangle2);
	}
	
	getnormals(Tris,caps);
	
}

void Mesh::revolution(float numSlices, vector<vector<float>> *lineVerts) {
	float theta = 360/numSlices;
	float Pi = 3.1415926535897931;
	theta = theta*Pi/180;
	int numP = lineVerts->size();

	bool topC = true;
	bool botC = true;

	if (numSlices < 3) {
		cout << "Invalid number of hor slices" << endl;
		return;
	}

	if (lineVerts->size() < 2) {
		cout << "Invalid number of line vertices" << endl;
		return;
	}

	//Verts = lineVerts;
	if (lineVerts->at(0)[0] == 0) {
		topC = false;
	}

	if (lineVerts->at(lineVerts->size()-1)[0] == 0) {
		botC = false;
	}

	if(lineVerts->size() > 1) {
		for(int i = 0; i < numSlices; i++) {
			for(int j = 0; j < numP -1; j++) {
				if(i == numSlices - 1) {
					float radius = lineVerts->at(j)[0];
					float xp = 0 + radius*cos(i*theta);
					float yp = lineVerts->at(j)[1];
					float zp = 0 + radius*sin(i*theta);
					vector<float> vert1 = vector<float>();
					vert1.push_back(xp); vert1.push_back(yp); vert1.push_back(zp);

					radius = lineVerts->at(j)[0];
					xp = 0 + radius*cos((0.0f));
					yp = lineVerts->at(j)[1];
					zp = 0 + radius*sin((0.0f));
					vector<float> vert2 = vector<float>();
					vert2.push_back(xp); vert2.push_back(yp); vert2.push_back(zp);

					radius = lineVerts->at(j+1)[0];
					xp = 0 + radius*cos((0.0f));
					yp = lineVerts->at(j+1)[1];
					zp = 0 + radius*sin((0.0f));
					vector<float> vert3 = vector<float>();
					vert3.push_back(xp); vert3.push_back(yp); vert3.push_back(zp);

					radius = lineVerts->at(j+1)[0];
					xp = 0 + radius*cos((i)*theta);
					yp = lineVerts->at(j+1)[1];
					zp = 0 + radius*sin((i)*theta);
					vector<float> vert4 = vector<float>();
					vert4.push_back(xp); vert4.push_back(yp); vert4.push_back(zp);

					Verts->push_back(vert1);
					Verts->push_back(vert2);
					Verts->push_back(vert3);
					Verts->push_back(vert4);

					vector<int> triangle1;
					triangle1.push_back(i*((numP-1)*4)+j*4+0);
					triangle1.push_back(i*((numP-1)*4)+j*4+1);
					triangle1.push_back(i*((numP-1)*4)+j*4+2);

					vector<int> triangle2;
					triangle2.push_back(i*((numP-1)*4)+j*4+0);
					triangle2.push_back(i*((numP-1)*4)+j*4+2);
					triangle2.push_back(i*((numP-1)*4)+j*4+3);

					Tris->push_back(triangle1);
					Tris->push_back(triangle2);
				} else {
					float radius = lineVerts->at(j)[0];
					float xp = 0 + radius*cos(i*theta);
					float yp = lineVerts->at(j)[1];
					float zp = 0 + radius*sin(i*theta);
					vector<float> vert1 = vector<float>();
					vert1.push_back(xp); vert1.push_back(yp); vert1.push_back(zp);

					radius = lineVerts->at(j)[0];
					xp = 0 + radius*cos((i+1)*theta);
					yp = lineVerts->at(j)[1];
					zp = 0 + radius*sin((i+1)*theta);
					vector<float> vert2 = vector<float>();
					vert2.push_back(xp); vert2.push_back(yp); vert2.push_back(zp);

					radius = lineVerts->at(j+1)[0];
					xp = 0 + radius*cos((i+1)*theta);
					yp = lineVerts->at(j+1)[1];
					zp = 0 + radius*sin((i+1)*theta);
					vector<float> vert3 = vector<float>();
					vert3.push_back(xp); vert3.push_back(yp); vert3.push_back(zp);

					radius = lineVerts->at(j+1)[0];
					xp = 0 + radius*cos((i)*theta);
					yp = lineVerts->at(j+1)[1];
					zp = 0 + radius*sin((i)*theta);
					vector<float> vert4 = vector<float>();
					vert4.push_back(xp);
					vert4.push_back(yp);
					vert4.push_back(zp);

					Verts->push_back(vert1);
					Verts->push_back(vert2);
					Verts->push_back(vert3);
					Verts->push_back(vert4);

					vector<int> triangle1;
					triangle1.push_back(i*((numP-1)*4)+j*4+0);
					triangle1.push_back(i*((numP-1)*4)+j*4+1);
					triangle1.push_back(i*((numP-1)*4)+j*4+2);

					vector<int> triangle2;
					triangle2.push_back(i*((numP-1)*4)+j*4+0);
					triangle2.push_back(i*((numP-1)*4)+j*4+2);
					triangle2.push_back(i*((numP-1)*4)+j*4+3);

					Tris->push_back(triangle1);
					Tris->push_back(triangle2);
				}
			}
		}

		//top and bot caps
		if(lineVerts->at(lineVerts->size() - 1)[1] == 0) {
			for (int i = 0; i < numSlices; i++) {
				float radius = lineVerts->at(0)[0];
				float xp = 0 + radius*cos(i*theta);
				float yp = lineVerts->at(0)[1];
				float zp = 0 + radius*sin(i*theta);
				vector<float> vert = vector<float>();
				vert.push_back(xp); vert.push_back(yp); vert.push_back(zp);

				Verts->push_back(vert);
			}
			for (int i = 0; i < numSlices-2; i++) {
				vector<int> triangle;
				triangle.push_back(4*numSlices*(numP-1)+0);
				triangle.push_back(4*numSlices*(numP-1)+i+1);
				triangle.push_back(4*numSlices*(numP-1)+i+2);
				Tris->push_back(triangle);
			}
		} else {
			for (int i = 0; i < numSlices; i++) {
				float radius = lineVerts->at(lineVerts->size() - 1)[0];
				float xp = 0 + radius*cos(i*theta);
				float yp = lineVerts->at(lineVerts->size() - 1)[1];
				float zp = 0 + radius*sin(i*theta);
				vector<float> vert = vector<float>();
				vert.push_back(xp); vert.push_back(yp); vert.push_back(zp);

				Verts->push_back(vert);
			}
			for (int i = 0; i < numSlices-2; i++) {
				vector<int> triangle;
				triangle.push_back(4*numSlices*(numP-1)+0);
				triangle.push_back(4*numSlices*(numP-1)+i+1);
				triangle.push_back(4*numSlices*(numP-1)+i+2);
				Tris->push_back(triangle);
			}
			
			for (int i = 0; i < numSlices; i++) {
				float radius = lineVerts->at(0)[0];
				float xp = 0 + radius*cos(i*theta);
				float yp = lineVerts->at(0)[1];
				float zp = 0 + radius*sin(i*theta);
				vector<float> vert = vector<float>();
				vert.push_back(xp); vert.push_back(yp); vert.push_back(zp);
				Verts->push_back(vert);
			}
			for (int i = 0; i < numSlices-2; i++) {
				vector<int> triangle;
				triangle.push_back(4*numSlices*(numP-1)+numSlices+0);
				triangle.push_back(4*numSlices*(numP-1)+numSlices+i+1);
				triangle.push_back(4*numSlices*(numP-1)+numSlices+i+2);
				Tris->push_back(triangle);
			}
		}
	}

	getnormals(Tris,true);
}

void Mesh::getnormals(vector<vector<int>>* polys, bool caps) {
	//if (polys->empty() != 0) {
	vector<float> testv = vector<float>();
	for (int i = 0; i < Verts->size(); i++) {
		Norms->push_back(testv);
	}

	for (int i = 0; i < polys->size(); i++) {
		int i1 = polys->at(i)[0];
		int i2 = polys->at(i)[1];
		int i3 = polys->at(i)[2];

		vector<float> p1 = Verts->at(i1);
		vector<float> p2 = Verts->at(i2);
		vector<float> p3 = Verts->at(i3);

		vector<float> v1;
		vector<float> v2;

		v1.push_back(p1[0] - p2[0]);
		v1.push_back(p1[1] - p2[1]);
		v1.push_back(p1[2] - p2[2]);

		v2.push_back(p3[0] - p2[0]);
		v2.push_back(p3[1] - p2[1]);
		v2.push_back(p3[2] - p2[2]);

		glm::vec3 vc1; glm::vec3 vc2;
		for (int j = 0; j < 3; j++) {
			vc1[j] = v1[j];
			vc2[j] = v2[j];
		}
		
		glm::vec3 c1;
		if (caps == true) {
			c1 = glm::cross(vc1, vc2);
		} else if (caps == false) {
			c1 = glm::cross(vc2, vc1);
		}

		vector<float> pb1;

		for (int j = 0; j < 3; j++) {
			pb1.push_back(c1[j]);
		}

		Norms->at(i1) = pb1;
		Norms->at(i2) = pb1;
		Norms->at(i3) = pb1;
	}
	//}
}
