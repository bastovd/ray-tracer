#include "MyGLWidget.h"
#include <QDebug>
#include <cmath>
#include "../glm/gtc/matrix_transform.hpp"
#include "SceneGraph.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "Mesh.h"

////////globals////////////
Node* root;
SceneGraph* graph;
Node* selected;
int sel_id = 0;

/////raytrace globals////////////
glm::vec3 eyePos = glm::vec3(0,10,8);
glm::vec3 centerP = glm::vec3(0,0,0);
glm::vec3 dirV = glm::normalize(centerP - eyePos); //If none is specified

string FILEM;
int RESO[2];
glm::vec3 EYEP = glm::vec3(0,0,0);
glm::vec3 VDIR = glm::vec3(0,0,0);
glm::vec3 UVEC = glm::vec3(0,0,0);
float FOVY;
glm::vec3 LPOS = glm::vec3(0,0,0);
glm::vec3 LCOL;
glm::vec3 ACOL;
glm::vec3 MAT1RGB;
float MAT1S;
float MAT1R;
float MAT1E1;
float MAT1E2;
float MAT1E3;
glm::vec3 MAT2RGB;
float MAT2S;
float MAT2R;
float MAT2E1;
float MAT2E2;
float MAT2E3;
glm::vec3 MAT3RGB;
float MAT3S;
float MAT3R;
float MAT3E1;
float MAT3E2;
float MAT3E3;
vector<int> *MATS = new vector<int>();
////////////////////////////////

///////file specs//////////
int xSize, zSize, numItems;
string furnitureType;
vector<string> furnitures;//
float red, green, blue;
vector<vector<float>> rgbs;//
int xIndex, zIndex;
vector<vector<int>> xzs;//
float rotation;
vector<float> rotations; //
float xScale, yScale, zScale;
vector<vector<float>> xsyszs;


//////////HW 3/////////////
float eLength;
vector<vector<float>> *meshVerts;
float surfrevSlices;
vector<Mesh*> meshes;
string Texture = "";
string Mdata = "";
vector<string> Mdatas;
vector<string> Textures;
///////////////////////////

void MyGLWidget::readFile() {
	string fiAsizeme;
	cout << "Enter a file name:" << endl;
	getline(cin, fiAsizeme);
	ifstream infile(fiAsizeme.c_str());

	int Fnum = 0;
	int Mnum = 0;
	int Fnum1 = 0;
	int Mnum1 = 0;
	int numL = 6;

	if (infile.is_open()) {
		string line;
		int lines = 2;
		float temp = 0.0f;
		infile >> xSize >> zSize >> numItems;
		cout << xSize << zSize << numItems << endl;
		while (getline(infile, line))
		{
			for (int i = 0; i < numItems; i++) {
				
				for (int j = 0; j < numL; j++) {
					if (lines == (i*6 + Mnum) + 3) {
						infile >> furnitureType;
						furnitures.push_back(furnitureType);
						cout << furnitureType << endl;
						if (furnitureType.compare("mesh") != 0) {
							numL = 6;
							Fnum1++;
							meshes.push_back(nullptr);
						} else if (furnitureType.compare("mesh") == 0) {
							numL = 7;
							Mnum1++;
						}
					} else if (lines == (i*6 + Mnum) + 4) {
						if (furnitureType.compare("mesh") != 0) {
							int mat;
							infile >> mat;
							vector<float> rgb;
							rgb.push_back(0.7f);
							rgb.push_back(0.0f);
							rgb.push_back(0.0f);
							rgbs.push_back(rgb);
							//vector<float> rgb;
							//rgb.push_back(red);
							//rgb.push_back(green);
							//rgb.push_back(blue);
							//rgbs.push_back(rgb);
							//cout << red << green << blue << endl;
							Mdatas.push_back("");
							MATS->push_back(mat);
						} else {
							vector<float> rgb;
							rgb.push_back(0.7f);
							rgb.push_back(0.0f);
							rgb.push_back(0.0f);
							rgbs.push_back(rgb);
							infile >> Mdata;
							Mdatas.push_back(Mdata);
							if (furnitureType.compare("mesh") == 0) {
								ifstream infile1(Mdata);
								if (infile1.is_open()) {
									string line1;
									int lines1 = 3;
									Mesh mesh = *new Mesh();
									string MeshType;
									infile1 >> MeshType;
									mesh.Mtype = MeshType;
									vector<vector<float>>* Everts;
									//lines1++;
									if (MeshType.compare("extrusion") == 0) {
										int VertNum = 0;
										vector<vector<float>>* Everts1 = new vector<vector<float>>();
										infile1 >> eLength;
										mesh.ExtL = eLength;
										infile1 >> VertNum;
										while (getline(infile1, line1)) {
											for (int i = 0; i < VertNum; i++) {
												float Ex, Ey, Ez;
												Ey = 0;
												infile1 >> Ex >> Ez;
												vector<float> Evert;
												Evert.push_back(Ex); Evert.push_back(Ey); Evert.push_back(Ez);
												Everts1->push_back(Evert);
												lines1++;
											}
											break;
										}
										Mesh* m = new Mesh();
										m->extrusion(eLength, Everts1);
										meshes.push_back(m);
									} else if (MeshType.compare("surfrev") == 0) {
										int VertNum = 0;
										vector<vector<float>>* Everts1 = new vector<vector<float>>();
										infile1 >> surfrevSlices;
										mesh.SRns = surfrevSlices;
										infile1 >> VertNum;
										while (getline(infile1, line1)) {
											for (int i = 0; i < VertNum; i++) {
												float Ex, Ey, Ez;
												Ez = 0;
												infile1 >> Ex >> Ey;
												vector<float> Evert;
												Evert.push_back(Ex); Evert.push_back(Ey); Evert.push_back(Ez);
												Everts1->push_back(Evert);
												lines1++;
											}
											break;
										}
										Mesh* m = new Mesh();
										m->revolution(surfrevSlices, Everts1);
										meshes.push_back(m);
									}
								} else {
									cout << "No such file" << endl;
									readFile();
								}
							}
						}
					} else if (lines == (i*6 + Mnum) + 5) {
						if (furnitureType.compare("mesh") != 0) {
							infile >> xIndex >> zIndex;
							vector<int> xz;
							xz.push_back(xIndex);
							xz.push_back(zIndex);
							xzs.push_back(xz);
							cout << xIndex << zIndex << endl;
						} else {
							int mat;
							infile >> mat;
							MATS->push_back(mat);
							if (mat == 1) {
							} else if (mat == 2) {
							} else if (mat == 3) {
							}
							//infile >> Texture;
							//Textures.push_back(Texture);
						}
					} else if (lines == (i*6 + Mnum) + 6) {
						if (furnitureType.compare("mesh") != 0) {
							infile >> rotation;
							rotations.push_back(rotation);
							cout << rotation << endl;
						} else {
							infile >> xIndex >> zIndex;
							vector<int> xz;
							xz.push_back(xIndex);
							xz.push_back(zIndex);
							xzs.push_back(xz);
							cout << xIndex << zIndex << endl;
						}
					} else if (lines == (i*6 + Mnum) + 7) {
						if (furnitureType.compare("mesh") != 0) {
							infile >> xScale >> yScale >> zScale;
							vector<float> xyzs;
							xyzs.push_back(xScale);
							xyzs.push_back(yScale);
							xyzs.push_back(zScale);
							xsyszs.push_back(xyzs);
							cout << xScale << yScale << zScale << endl;
						} else {
							infile >> rotation;
							rotations.push_back(rotation);
							cout << rotation << endl;
						}
					} 
					if (furnitureType.compare("mesh") == 0) {
						if (lines == (i*6 + Mnum) + 8) {
							infile >> xScale >> yScale >> zScale;
							vector<float> xyzs;
							xyzs.push_back(xScale);
							xyzs.push_back(yScale);
							xyzs.push_back(zScale);
							xsyszs.push_back(xyzs);
							cout << xScale << yScale << zScale << endl;
						}
					}
					lines++;
				}
				Fnum = Fnum1;
				Mnum = Mnum1;
				//lines++;
			}
			break;
		}
	} else {
		cout << "No such file" << endl;
		readFile();
	}
}

///////////////NOT MY CODE/////////////////////////
MyGLWidget::MyGLWidget(QWidget* parent) : QGLWidget(parent) {
	
	readFile();
	setFocusPolicy(Qt::StrongFocus);
	//This starter code uses a timer to make a square rotate without
	//user intervention.  You can remove this.
	timer = new QTimer(this);
	rotation = 0;
	connect(timer, SIGNAL(timeout()), this, SLOT(updateGL()));
	timer->start(17);

	//We can set our vertex attributes rather than requesting their locations
	//I chose to do so in this constructor, maybe you would in your init() function?
	positionLocation = 0;
	normalLocation = 1;
	colorLocation = 2;
}
////////////////////////////////////////////////////

///////////////NOT MY CODE////////////////////////////////////////
MyGLWidget::~MyGLWidget() {										//
	//Release your resources, just like you'd delete pointers	//
	glDeleteBuffers(1, &vbo);									//
	glDeleteBuffers(1, &cbo);									//		
	glDeleteBuffers(1, &nbo);									//	
	glDeleteBuffers(1, &ibo);									//		
																//
	//Tear part2 the shader program in reverse of building it	//
	glDetachShader(shaderProgram, vertexShader);				//
	glDetachShader(shaderProgram, fragmentShader);				//
	glDeleteShader(vertexShader);								//
	glDeleteShader(fragmentShader);								//		
	glDeleteProgram(shaderProgram);								//
}																//
//////////////////////////////////////////////////////////////////

void MyGLWidget::traverseSG(glm::mat4 modelView, Node* r) {
	if (r->ge == 0) {
		this->makeCube(modelView, r->furn->floor, r->colorRGB);
	} else if(r->ge == 1) {
		this->makeCylinder(modelView, r->furn->t_top,r->dX,r->height - (r->height - r->parent->height)/2, r->dZ, r->colorRGB);
		this->makeCube(modelView, r->furn->t_leg1, r->colorRGB);
		this->makeCube(modelView, r->furn->t_leg2, r->colorRGB);
		this->makeCube(modelView, r->furn->t_leg3, r->colorRGB);
		this->makeCube(modelView, r->furn->t_leg4, r->colorRGB);
	} else if(r->ge == 2) {
		this->makeCube(modelView, r->furn->c_top, r->colorRGB);
		this->makeCube(modelView, r->furn->c_leg1, r->colorRGB);
		this->makeCube(modelView, r->furn->c_leg2, r->colorRGB);
		this->makeCube(modelView, r->furn->c_leg3,r->colorRGB);
		this->makeCube(modelView, r->furn->c_leg4,r->colorRGB);
		this->makeCube(modelView, r->furn->c_back, r->colorRGB);
	} else if(r->ge == 3) {
		this->makeCube(modelView, r->furn->cab_base, r->colorRGB);
		this->makeCube(modelView, r->furn->cab_door, r->colorRGB);
	} else if(r->ge == 4) {
		this->makeCylinder(modelView, r->furn->l_base,r->dX,r->height - (r->height - r->parent->height)/2, r->dZ, r->colorRGB);
		this->makeSphere(modelView, r->furn->l_lamp,r->dX,r->height - (r->height - r->parent->height)/2, r->dZ, r->colorRGB);
	} else if(r->ge == 5) {
		this->makeMesh(modelView, r->meshN);
	}
	if(r->children->size() != 0) {
		for(int i = 0; i < r->children->size(); i++) {
			Node* child = r->children->at(i);
			traverseSG(modelView, child);
		}
	}
}

bool MyGLWidget::traversePos(Node* n, Node* r) {
	bool put = false;
	if(r->xIndex == n->xIndex && r->zIndex == n->zIndex) {
		if(r->children->size() != 0) {
			for(int i = 0; i < r->children->size(); i++) {
				put = traversePos(n, r->children->at(i));
				if(put == true) {
					return true;
				}
			}
		} else {
			n->parent = r;
			graph->addChild(n,r);
			r->addChild(n);
			n->height = r->height + 1;
			n->stackUp(r->height + 0.5f);
			return true;
		}
	} else {
		for(int i = 0; i < r->children->size(); i++) {
			put = traversePos(n, r->children->at(i));
			if(put == true) {
				return true;
			}
		}
	}
	return false;
}

vector<unsigned short> MyGLWidget::SphereI(int stepy, int stepz) {
	vector<unsigned short> spherei = vector<unsigned short>();
	int one; int two; int three; int four; int five; int six;
	for(int i = 0; i < stepz; i++) {
		for(int j = 0; j <= stepy; j++) {
			if(j == stepy) {
				if (i == 0) {
					one = stepy;
					two = stepy-1;
					three = stepy-1+stepy;

					spherei.push_back(one);
					spherei.push_back(two);
					spherei.push_back(three);
				} else if (i == stepz-1) {
					one = stepy;
					two = stepy+i*(stepy-1);
					three = stepy-1;

					spherei.push_back(one);
					spherei.push_back(two);
					spherei.push_back(three);
				} else if(i != stepz-1 && i != 0) {
					one = stepy;
					two = stepy+i*(stepy-1);
					three = stepy+(i+1)*(stepy-1);

					spherei.push_back(one);
					spherei.push_back(two);
					spherei.push_back(three);
				} 
			} else if(j == 0) {
				 if (i == 0) {
					one = 0;
					two = 1;
					three = stepy-1+2;

					spherei.push_back(one);
					spherei.push_back(two);
					spherei.push_back(three);
				} else if (i == stepz-1) {
					one = 0;
					two = i*(stepy-1)+2;
					three = 1;

					spherei.push_back(one);
					spherei.push_back(two);
					spherei.push_back(three);
				} else if(i != stepz-1 && i != 0) {
					one = 0;
					two = i*(stepy-1)+2;
					three = (i+1)*(stepy-1)+2;

					spherei.push_back(one);
					spherei.push_back(two);
					spherei.push_back(three);
				} 
			} else if(j != stepy-1) {
				if (i == 0) {
					one = j;
					two = j+1;
					three = stepy+j+1;
					four = j;
					five = stepy+j;
					six = stepy+j+1;

					spherei.push_back(one);
					spherei.push_back(two);
					spherei.push_back(three);
					spherei.push_back(four);
					spherei.push_back(five);
					spherei.push_back(six);
				} else if (i == stepz-1) {
					one = i*(stepy-1)+j+1;
					two = i*(stepy-1)+j+2;
					three = j+1;
					four = i*(stepy-1)+j+1;
					five = j;
					six = j+1;

					spherei.push_back(one);
					spherei.push_back(two);
					spherei.push_back(three);
					spherei.push_back(four);
					spherei.push_back(five);
					spherei.push_back(six);
				} else if(i != stepz-1 && i != 0) {
					one = i*(stepy-1)+j+1;
					two = i*(stepy-1)+j+2;
					three = (i+1)*(stepy-1)+j+2;
					four = i*(stepy-1)+j+1;
					five = (i+1)*(stepy-1)+j+1;
					six = (i+1)*(stepy-1)+j+2;

					spherei.push_back(one);
					spherei.push_back(two);
					spherei.push_back(three);
					spherei.push_back(four);
					spherei.push_back(five);
					spherei.push_back(six);
				} 
			} else {
				continue;
			}
		}
	}
	return spherei;
}

vector<unsigned short> MyGLWidget::CylinderI(int stepy) {
	vector<unsigned short> cyli = vector<unsigned short>();
	int one; int two; int three; int four; int five; int six;
	// bot
	for(int i = 0; i < stepy-1; i++) {
		one = 0;
		two = i+2;
		three = i+3;

		cyli.push_back(one);
		cyli.push_back(two);
		cyli.push_back(three);
	}
	one = 0;
	two = stepy+1;
	three = 2;

	cyli.push_back(one);
	cyli.push_back(two);
	cyli.push_back(three);
	// top
	for(int i = 0; i < stepy-1; i++) {
		one = 1;
		two = stepy+i+2;
		three = stepy+i+3;

		cyli.push_back(one);
		cyli.push_back(two);
		cyli.push_back(three);
	}
	one = 1;
	two = 2*stepy+1;
	three = stepy+2;

	cyli.push_back(one);
	cyli.push_back(two);
	cyli.push_back(three);
	// rest
	for(int i = 0; i < stepy-1; i++) {
		one = 2*stepy+2*(i+1);
		two = 1+2*stepy+2*(i+1);
		three = 1+2*stepy+2*(i+2);
		four = 2*stepy+2*(i+1);
		five = 2*stepy+2*(i+2);
		six = 1+2*stepy+2*(i+2);

		cyli.push_back(one);
		cyli.push_back(two);
		cyli.push_back(three);
		cyli.push_back(four);
		cyli.push_back(five);
		cyli.push_back(six);
	}
	one = 4*stepy;
	two = 1+4*stepy;
	three = 3+2*stepy;
	four = 4*stepy;
	five = 2+2*stepy;
	six = 3+2*stepy;

	cyli.push_back(one);
	cyli.push_back(two);
	cyli.push_back(three);
	cyli.push_back(four);
	cyli.push_back(five);
	cyli.push_back(six);

	return cyli;
}

//this is the function i referred to as "init" in my lecture - Cory
void MyGLWidget::initializeGL() {
	//Initialize GLEW to get access to latest OpenGL support on your computer
	//GLEW 1.7.0 supplied with this starter code, it's always a good idea to update
	//about once every year or so as OpenGL is updated
	root = new Node();
	graph = new SceneGraph(root);
	
	string typeF = "floor";
	vector<float> colorF; 
	vector<int> positionF;
	vector<float> scaleF;
	for (int i = 0; i < 3; i++) {
		colorF.push_back(1);
		positionF.push_back(0); 
	}
	scaleF.push_back(xSize);
	scaleF.push_back(0.1f); 
	scaleF.push_back(zSize);
	float rotationF = 0;
	Furniture* basefurn = new Furniture(typeF,colorF,positionF,rotationF,scaleF,nullptr);
	root->furn = basefurn;
	vector<vector<float>>* furnfloor = new vector<vector<float>>();
	for(int j = 0; j < basefurn->floor->size(); j ++) {
		furnfloor->push_back(basefurn->floor->at(j));
	}
	root->geometry = furnfloor;
	root->ge = 0;
	root->dX = 0;
	root->dZ = 0;
	root->rY = 0;
	root->children = new vector<Node*>();
	root->height = 0.1f;
	graph->objects->push_back(root);
	graph->scale(xSize, 0.01f, zSize, 0, root->dX, root->dZ, root->rY, root);
	root->stackUp(-0.5f);
	float colorrgb[3] = {0.5f, 0.5f, 0.5f};
	for (int i = 0; i < 3; i++) {
		root->colorRGB[i] = colorrgb[i];
	}
	root->calculateMatrices(xSize,0.1f,zSize);
	for(int i = 0; i < furnitures.size(); i++) {
		string type = furnitures[i];
		vector<float> color = rgbs[i];
		vector<int> position = xzs[i];
		float rotation = rotations[i];
		vector<float> scale = xsyszs[i];
		
		Node* n = new Node();
		Furniture* furnrest = new Furniture(type,color,position,rotation,scale,meshes[i]);
		n->furn = furnrest;
		n->meshN = meshes[i];
		n->dX = 0;
		n->dZ = 0;
		n->rY = 0;

		if (n->meshN != nullptr) {
			if (n->meshN->Verts->size() == 0) continue; 
		}
		
		if(type.compare("table") == 0) {
			n->ge = 1;
			vector<vector<float>>* furniture = new vector<vector<float>>();
			for(int j = 0; j < furnrest->t_top->size(); j ++) {
				furniture->push_back(furnrest->t_top->at(j));
			}
			for(int j = 0; j < furnrest->t_leg1->size(); j ++) {
				furniture->push_back(furnrest->t_leg1->at(j));
			}
			for(int j = 0; j < furnrest->t_leg2->size(); j ++) {
				furniture->push_back(furnrest->t_leg2->at(j));
			}
			for(int j = 0; j < furnrest->t_leg3->size(); j ++) {
				furniture->push_back(furnrest->t_leg3->at(j));
			}
			for(int j = 0; j < furnrest->t_leg4->size(); j ++) {
				furniture->push_back(furnrest->t_leg4->at(j));
			}

			initBB(i,n);

			n->geometry = furniture;
		} else if(type.compare("chair") == 0) {
			n->ge = 2;
			vector<vector<float>>* furniture = new vector<vector<float>>();
			for(int j = 0; j < furnrest->c_top->size(); j ++) {
				furniture->push_back(furnrest->c_top->at(j));
			}
			for(int j = 0; j < furnrest->c_leg1->size(); j ++) {
				furniture->push_back(furnrest->c_leg1->at(j));
			}
			for(int j = 0; j < furnrest->c_leg2->size(); j ++) {
				furniture->push_back(furnrest->c_leg2->at(j));
			}
			for(int j = 0; j < furnrest->c_leg3->size(); j ++) {
				furniture->push_back(furnrest->c_leg3->at(j));
			}
			for(int j = 0; j < furnrest->c_leg4->size(); j ++) {
				furniture->push_back(furnrest->c_leg4->at(j));
			}
			for(int j = 0; j < furnrest->c_back->size(); j ++) {
				furniture->push_back(furnrest->c_back->at(j));
			}

			initBB(i,n);

			n->geometry = furniture;
		} else if(type.compare("cabinet") == 0) {
			n->ge = 3;
			vector<vector<float>>* furniture = new vector<vector<float>>();
			for(int j = 0; j < furnrest->cab_base->size(); j ++) {
				furniture->push_back(furnrest->cab_base->at(j));
			}
			for(int j = 0; j < furnrest->cab_door->size(); j ++) {
				furniture->push_back(furnrest->cab_door->at(j));
			}

			initBB(i,n);

			n->geometry = furniture;
		} else if(type.compare("lamp") == 0) {
			n->ge = 4;
			vector<vector<float>>* furniture = new vector<vector<float>>();
			for(int j = 0; j < furnrest->l_base->size(); j ++) {
				furniture->push_back(furnrest->l_base->at(j));
			}
			for(int j = 0; j < furnrest->l_lamp->size(); j ++) {
				furniture->push_back(furnrest->l_lamp->at(j));
			}

			initBB(i,n);

			n->geometry = furniture;
		} else if (type.compare("mesh") == 0) {
			n->ge = 5;
			n->geometry = n->meshN->Verts;
		}
		n->calculateMatrices(xSize,0.1f,zSize);

		n->xIndex = xzs[i][0];
		n->zIndex = xzs[i][1];
		for (int k = 0; k < 3; k++) {
			n->colorRGB[k] = rgbs[i][k];
		}

		if(root->children->size() != 0) {
			bool put = false;
			for(int j = 0; j < root->children->size(); j++) {
				put = traversePos(n, root->children->at(j));
				if(put == true) {
					break;
				}
			}
			if(put == false) {
				graph->addChild(n,root);
				root->addChild(n);
				n->parent = root;
				//graph->transY(root->height + 0.5f,n);
				n->height = root->height + 1;
			}
		} else {
			graph->addChild(n,root);
			root->addChild(n);
			n->parent = root;
			//graph->transY(root->height + 0.5f,n);
			n->height = root->height + 1;
		}
		
		graph->scale(xsyszs[i][0],xsyszs[i][1],xsyszs[i][2],n->parent->height, 0, 0, 0, n);
		graph->rotate(rotations[i],0, 0, n);
		graph->translate(xzs[i][0],xzs[i][1],n);
	}

	selected = root;
	//////////////
	glewInit();

	//Create the VBOs and IBO we'll be using to render images in OpenGL
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &cbo);
	glGenBuffers(1, &nbo);
	glGenBuffers(1, &ibo);
	
	//Everybody does this
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0);
	glDepthFunc(GL_LEQUAL);

	//here is stuff for setting up our shaders
	const char* fragFile = "diffuseFrag.frag";
	const char* vertFile = "diffuseVert.vert";
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	shaderProgram = glCreateProgram();
	
	//load up the source, compile and link the shader program
	const char* vertSource = textFileRead(vertFile);
	const char* fragSource = textFileRead(fragFile);
	glShaderSource(vertexShader, 1, &vertSource, 0);
	glShaderSource(fragmentShader, 1, &fragSource, 0);
	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);

	//For your convenience, i decided to throw in some compiler/linker output helper functions
	//from CIS 565
	GLint compiled;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compiled);
	if (!compiled)
	{
		printShaderInfoLog(vertexShader);
	} 
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compiled);
	if (!compiled)
	{
		printShaderInfoLog(fragmentShader);
	} 

	//set the attribute locations for our shaders
	glBindAttribLocation(shaderProgram, positionLocation, "vs_position");
	glBindAttribLocation(shaderProgram, normalLocation, "vs_normal");
	glBindAttribLocation(shaderProgram, colorLocation, "vs_color");

	//finish shader setup
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	//check for linking success
	GLint linked;
	glGetProgramiv(shaderProgram,GL_LINK_STATUS, &linked);
	if (!linked) 
	{
		printLinkInfoLog(shaderProgram);
	}

	//Get the uniform locations for our shaders, unfortunately they can not be set by us, we have
	//to ask OpenGL for them
	u_modelMatrixLocation = glGetUniformLocation(shaderProgram, "u_modelMatrix");
	u_projMatrixLocation = glGetUniformLocation(shaderProgram, "u_projMatrix");

	//Always remember that it doesn't do much good if you don't have OpenGL actually use the shaders
	glUseProgram(shaderProgram);

	/////set light//////////
	GLint myLoc = glGetUniformLocation(shaderProgram, "lightPos");
	glUniform3f(myLoc, 0.0f, 5.0f, 15.0f); ///change last 3 values to change light location
	
	GLint myLoc1 = glGetUniformLocation(shaderProgram, "lightCol");
	glUniform3f(myLoc1, 0.0f, 0.3f, 0.3f);
	///////////////////////
}

///////PARTS OF THIS CODE ARE NOT MINE////////////////
//this is what i referred to as a "paint" or "draw" function in my lecture - Cory
void MyGLWidget::paintGL() {
	//Always and only do this at the start of a frame, it wipes the slate clean
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//part of the animation
	rotation += 2.5;

	//create an identity matrix for the modelview matrix
	glm::mat4 modelView = glm::mat4(1.0); //mine
	traverseSG(modelView,root);			  //mine

	drawBB();							  //mine

	//Draw the two components of our scene separately, for your scenegraphs it will help
	//your sanity to do separate draws for each type of primitive geometry, otherwise your VBOs will
	//get very, very complicated fast
	//createRedSquare(modelView);	//PASS MODELVIEW BY COPY to get the nice scoping for hierarchical (i'm sure i spelled that wrong) transformations
								//like Norm mentioned in his Scene Graph lecture
	//createBlueSquare(modelView);
}

void MyGLWidget::makeCube(glm::mat4 modelView,vector<vector<float>>* g, float crgb[3]) {
	
	float* vertices = new float[g->size()*4];

	for(int i = 0; i < g->size(); i++) {
		vertices[i*4] = g->at(i)[0];
		vertices[i*4+1] = g->at(i)[1];
		vertices[i*4+2] = g->at(i)[2];
		vertices[i*4+3] = g->at(i)[3];
	}

	//now we put the data into the Vertex Buffer Object for the graphics system to use
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 96 * sizeof(float), vertices, GL_STATIC_DRAW); //the square vertices don't need to change, ever,
																				 //while the program runs

	//once the data is loaded, we can delete the float arrays, the data is safely stored with OpenGL
//	delete [] vertices;

	//again with colors
	float* colors = new float[72];
	
	for(int i = 0; i < 72; i = i + 3) {
		colors[i] = crgb[0];
		colors[i+1] = crgb[1];
		colors[i+2] = crgb[2];
	}

	glBindBuffer(GL_ARRAY_BUFFER, cbo);
	//always make sure you are telling OpenGL the right size to make the buffer, color data doesn't have as much data!
	glBufferData(GL_ARRAY_BUFFER, 72 * sizeof(float), colors, GL_STREAM_DRAW);	//the color is going to change every frame
																				//as it bounces between squares
	
	delete [] colors;

	//once more, this time with normals
	float* normals = new float[96];

	for(int i = 0; i < 16; i+=4 ) {
		normals[i] = 0;
		normals[i+1] = 1;
		normals[i+2] = 0;
		normals[i+3] = 0;
	}
	for(int i = 16; i < 32; i+=4 ) {
		glm::vec3 part1 = glm::vec3(vertices[4] - vertices[0],0,vertices[6] - vertices[2]);
		glm::vec3 part2 = glm::vec3(0,-1,0);
		glm::vec3 normpoint = glm::cross(part1,part2);
		normpoint = glm::normalize(normpoint);
		normals[i] = normpoint[0];
		normals[i+1] = 0;
		normals[i+2] = normpoint[2];
		normals[i+3] = 0;
	}
	for(int i = 32; i < 48; i+=4 ) {
		glm::vec3 part1 = glm::vec3(vertices[36] - vertices[32],0,vertices[38] - vertices[34]);
		glm::vec3 part2 = glm::vec3(0,-1,0);
		glm::vec3 normpoint = glm::cross(part1,part2);
		normpoint = glm::normalize(normpoint);
		normals[i] = normpoint[0];
		normals[i+1] = 0;
		normals[i+2] = normpoint[2];
		normals[i+3] = 0;
	}
	for(int i = 48; i < 64; i+=4 ) {
		glm::vec3 part1 = glm::vec3(vertices[56] - vertices[52],0,vertices[58] - vertices[54]);
		glm::vec3 part2 = glm::vec3(0,-1,0);
		glm::vec3 normpoint = glm::cross(part1,part2);
		normpoint = glm::normalize(normpoint);
		normals[i] = normpoint[0];
		normals[i+1] = 0;
		normals[i+2] = normpoint[2];
		normals[i+3] = 0;
	}
	for(int i = 64; i < 80; i+=4 ) {
		glm::vec3 part1 = glm::vec3(vertices[68] - vertices[64],0,vertices[70] - vertices[66]);
		glm::vec3 part2 = glm::vec3(0,1,0);
		glm::vec3 normpoint = glm::cross(part1,part2);
		normpoint = glm::normalize(normpoint);
		normals[i] = normpoint[0];
		normals[i+1] = 0;
		normals[i+2] = normpoint[2];
		normals[i+3] = 0;
	}
	for(int i = 80; i < 96; i+=4 ) {
		normals[i] = 0;
		normals[i+1] = -1;
		normals[i+2] = 0;
		normals[i+3] = 0;
	}
	

	glBindBuffer(GL_ARRAY_BUFFER, nbo);
	glBufferData(GL_ARRAY_BUFFER, 96 * sizeof(float), normals, GL_STATIC_DRAW); //the square normals don't need to change, ever,
																				 //while the program runs
	delete [] vertices;
	delete [] normals;

	//activate our three kinds of information
	glEnableVertexAttribArray(positionLocation);
	glEnableVertexAttribArray(colorLocation);
	glEnableVertexAttribArray(normalLocation);
	
	//we're using the vertex data first
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//define how the vertex pointer should work, in our case we're accessing floats 4 at a time with no special pattern
	glVertexAttribPointer(positionLocation, 4, GL_FLOAT, 0, 0, static_cast<char*>(0));
	
	//now use color data, remember we're not using 4 at a time anymore
	glBindBuffer(GL_ARRAY_BUFFER, cbo);
	glVertexAttribPointer(colorLocation, 3, GL_FLOAT, 0, 0, static_cast<char*>(0));
	
	//one more time with the normals
	glBindBuffer(GL_ARRAY_BUFFER, nbo);
	glVertexAttribPointer(normalLocation, 4, GL_FLOAT, 0, 0, static_cast<char*>(0));
	
	//the last thing we need to do is setup our indices
	unsigned short* indices = new unsigned short[36];

	indices[0] = 0; indices[1] = 1; indices[2] = 2; //top
	indices[3] = 3; indices[4] = 0; indices[5] = 2; //top
	indices[6] = 4; indices[7] = 5; indices[8] = 6; //front
	indices[9] = 7; indices[10] = 4; indices[11] = 6; //front
	indices[12] = 8; indices[13] = 9; indices[14] = 10; //right
	indices[15] = 11; indices[16] = 8; indices[17] = 10; //right
	indices[18] = 12; indices[19] = 13; indices[20] = 14; //back
	indices[21] = 15; indices[22] = 12; indices[23] = 14; //back
	indices[24] = 16; indices[25] = 17; indices[26] = 18; //left
	indices[27] = 19; indices[28] = 16; indices[29] = 18; //left
	indices[30] = 20; indices[31] = 21; indices[32] = 22; //bottom
	indices[33] = 23; indices[34] = 20; indices[35] = 22; //bottom

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(unsigned short), indices, GL_STATIC_DRAW);

	delete [] indices;

	//set the modelview uniform
	glUniformMatrix4fv(u_modelMatrixLocation, 1, GL_FALSE, &modelView[0][0]);

	//draw the elements
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);
	
	//shut off the information since we're done drawing
	glDisableVertexAttribArray(positionLocation);
	glDisableVertexAttribArray(colorLocation);
	glDisableVertexAttribArray(normalLocation);
}
void MyGLWidget::makeSphere(glm::mat4 modelView,vector<vector<float>>* g, float xi, float yi, float zi,  float crgb[3]) {

	vector<float>* verts = new vector<float>();
	for(int i = 0; i < g->size(); i++) {
		verts->push_back(g->at(i)[0]);
		verts->push_back(g->at(i)[1]);
		verts->push_back(g->at(i)[2]);
		verts->push_back(1);
	}

	float* vertices = new float[verts->size()];
	for(int i = 0; i < verts->size(); i++) {
		vertices[i] = verts->at(i);
	}

	//now we put the data into the Vertex Buffer Object for the graphics system to use
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, verts->size() * sizeof(float), vertices, GL_STATIC_DRAW); //the square vertices don't need to change, ever,
																				 //while the program runs

	//once the data is loaded, we can delete the float arrays, the data is safely stored with OpenGL
	delete [] vertices;

	//again with colors
	float* colors = new float[verts->size() - verts->size()/4];
	
	for(int i = 0; i < verts->size() - verts->size()/4; i+=3) {
		colors[i] = crgb[0];
		colors[i+1] = crgb[1];
		colors[i+2] = crgb[2];
	}

	glBindBuffer(GL_ARRAY_BUFFER, cbo);
	//always make sure you are telling OpenGL the right size to make the buffer, color data doesn't have as much data!
	glBufferData(GL_ARRAY_BUFFER, (verts->size() - verts->size()/4) * sizeof(float), colors, GL_STREAM_DRAW);	//the color is going to change every frame
																				//as it bounces between squares
	
	delete [] colors;

	//once more, this time with normals
	float* normals = new float[verts->size()];
	
	for(int i = 0; i < verts->size(); i+=4) {
		float dist = sqrt((float)(verts->at(i) - xi)*(verts->at(i) - xi) + (verts->at(i+1) - yi)*(verts->at(i+1) - yi) + (verts->at(i+2) - zi)*(verts->at(i+2) - zi));
		normals[i] = (verts->at(i) - xi);
		normals[i+1] = (verts->at(i+1) - yi);
		normals[i+2] = (verts->at(i+2) - zi);
		normals[i+3] = 0;
	}

	glBindBuffer(GL_ARRAY_BUFFER, nbo);
	glBufferData(GL_ARRAY_BUFFER, verts->size() * sizeof(float), normals, GL_STATIC_DRAW); //the square normals don't need to change, ever,
																				 //while the program runs

	delete [] normals;

	//activate our three kinds of information
	glEnableVertexAttribArray(positionLocation);
	glEnableVertexAttribArray(colorLocation);
	glEnableVertexAttribArray(normalLocation);
	
	//we're using the vertex data first
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//define how the vertex pointer should work, in our case we're accessing floats 4 at a time with no special pattern
	glVertexAttribPointer(positionLocation, 4, GL_FLOAT, 0, 0, static_cast<char*>(0));
	
	//now use color data, remember we're not using 4 at a time anymore
	glBindBuffer(GL_ARRAY_BUFFER, cbo);
	glVertexAttribPointer(colorLocation, 3, GL_FLOAT, 0, 0, static_cast<char*>(0));
	
	//one more time with the normals
	glBindBuffer(GL_ARRAY_BUFFER, nbo);
	glVertexAttribPointer(normalLocation, 4, GL_FLOAT, 0, 0, static_cast<char*>(0));

	//the last thing we need to do is setup our indices

	vector<unsigned short> indicesv = this->SphereI(12,18);

	unsigned short* indices = new unsigned short[indicesv.size()];

	for(int i = 0; i < indicesv.size(); i++) {
		indices[i] = indicesv[i];
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesv.size() * sizeof(unsigned short), indices, GL_STATIC_DRAW);

	delete [] indices;

	//set the modelview uniform
	glUniformMatrix4fv(u_modelMatrixLocation, 1, GL_FALSE, &modelView[0][0]);

	//draw the elements
	glDrawElements(GL_TRIANGLES, indicesv.size(), GL_UNSIGNED_SHORT, 0);
	
	//shut off the information since we're done drawing
	glDisableVertexAttribArray(positionLocation);
	glDisableVertexAttribArray(colorLocation);
	glDisableVertexAttribArray(normalLocation);

}

void MyGLWidget::makeCylinder(glm::mat4 modelView,vector<vector<float>>* g, float xi, float yi, float zi,  float crgb[3]){

	vector<float>* verts = new vector<float>();
	for(int i = 0; i < g->size(); i++) {
		verts->push_back(g->at(i)[0]);
		verts->push_back(g->at(i)[1]);
		verts->push_back(g->at(i)[2]);
		verts->push_back(1);
	}

	float* vertices = new float[verts->size()];
	for(int i = 0; i < verts->size(); i++) {
		vertices[i] = verts->at(i);
	}

	//now we put the data into the Vertex Buffer Object for the graphics system to use
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, verts->size() * sizeof(float), vertices, GL_STATIC_DRAW); //the square vertices don't need to change, ever,
																				 //while the program runs

	//once the data is loaded, we can delete the float arrays, the data is safely stored with OpenGL
	delete [] vertices;

	//again with colors
	float* colors = new float[verts->size() - verts->size()/4];
	
	for(int i = 0; i < verts->size() - verts->size()/4; i = i + 3) {
		colors[i] = crgb[0];
		colors[i+1] = crgb[1];
		colors[i+2] = crgb[2];
	}

	glBindBuffer(GL_ARRAY_BUFFER, cbo);
	//always make sure you are telling OpenGL the right size to make the buffer, color data doesn't have as much data!
	glBufferData(GL_ARRAY_BUFFER, (verts->size() - verts->size()/4) * sizeof(float), colors, GL_STREAM_DRAW);	//the color is going to change every frame
																				//as it bounces between squares
	
	delete [] colors;

	//once more, this time with normals
	float* normals = new float[verts->size()];
	

	normals[0] = 0; normals[1] = -1; normals[2] = 0; normals[3] = 0;
	normals[4] = 0; normals[5] = 1; normals[6] = 0; normals[7] = 0;
	for(int i = 8; i < 9*4 + 8; i+=4) {
		normals[i] = 0;
		normals[i+1] = -1;
		normals[i+2] = 0;
		normals[i+3] = 0;
	}
	for(int i = 9*4 + 8; i < 9*4 + 8 + 9*4; i+=4) {
		normals[i] = 0;
		normals[i+1] = 1;
		normals[i+2] = 0;
		normals[i+3] = 0;
	}
	bool is_bottom = true;
	for(int i = 9*4 + 9*4 + 8; i < verts->size(); i+=4) {
		normals[i] = verts->at(i) - xi;
		normals[i+1] = 0;
		normals[i+2] = verts->at(i+2) - zi;
		normals[i+3] = 0;
	}

	glBindBuffer(GL_ARRAY_BUFFER, nbo);
	glBufferData(GL_ARRAY_BUFFER, verts->size() * sizeof(float), normals, GL_STATIC_DRAW); //the square normals don't need to change, ever,
																				 //while the program runs

	delete [] normals;

	//activate our three kinds of information
	glEnableVertexAttribArray(positionLocation);
	glEnableVertexAttribArray(colorLocation);
	glEnableVertexAttribArray(normalLocation);
	
	//we're using the vertex data first
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//define how the vertex pointer should work, in our case we're accessing floats 4 at a time with no special pattern
	glVertexAttribPointer(positionLocation, 4, GL_FLOAT, 0, 0, static_cast<char*>(0));
	
	//now use color data, remember we're not using 4 at a time anymore
	glBindBuffer(GL_ARRAY_BUFFER, cbo);
	glVertexAttribPointer(colorLocation, 3, GL_FLOAT, 0, 0, static_cast<char*>(0));
	
	//one more time with the normals
	glBindBuffer(GL_ARRAY_BUFFER, nbo);
	glVertexAttribPointer(normalLocation, 4, GL_FLOAT, 0, 0, static_cast<char*>(0));

	//the last thing we need to do is setup our indices

	vector<unsigned short> indicesv = this->CylinderI(9);

	unsigned short* indices = new unsigned short[indicesv.size()];

	for(int i = 0; i < indicesv.size(); i++) {
		indices[i] = indicesv[i];
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesv.size() * sizeof(unsigned short), indices, GL_STATIC_DRAW);

	delete [] indices;

	//set the modelview uniform
	glUniformMatrix4fv(u_modelMatrixLocation, 1, GL_FALSE, &modelView[0][0]);

	//draw the elements
	glDrawElements(GL_TRIANGLES, indicesv.size(), GL_UNSIGNED_SHORT, 0);
	
	//shut off the information since we're done drawing
	glDisableVertexAttribArray(positionLocation);
	glDisableVertexAttribArray(colorLocation);
	glDisableVertexAttribArray(normalLocation);
}

////////////////////////////////////////////////////
void MyGLWidget::makeMesh(glm::mat4 modelView, Mesh* g) {

	vector<vector<float>>* verts = g->Verts;
	vector<vector<float>>* norms = g->Norms;
	vector<vector<int>>* faces = g->Tris;

	float* vertices = new float[verts->size()*4];
	for(int i = 0; i < verts->size(); i++) {
		vertices[i*4] = verts->at(i)[0];
		vertices[i*4+1] = verts->at(i)[1];
		vertices[i*4+2] = verts->at(i)[2];
		vertices[i*4+3] = 1;
	}

	//now we put the data into the Vertex Buffer Object for the graphics system to use
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, verts->size()*4 * sizeof(float), vertices, GL_STATIC_DRAW); //the square vertices don't need to change, ever,
																				 //while the program runs

	//once the data is loaded, we can delete the float arrays, the data is safely stored with OpenGL
	//delete [] vertices;

	//again with colors
	float* colors = new float[verts->size()*3];
	
	for(int i = 0; i < verts->size()*3; i+= 3) {
		colors[i] = 0.5f;
		colors[i+1] = 0.5f;
		colors[i+2] = 0.5f;
	}

	glBindBuffer(GL_ARRAY_BUFFER, cbo);
	//always make sure you are telling OpenGL the right size to make the buffer, color data doesn't have as much data!
	glBufferData(GL_ARRAY_BUFFER, verts->size()*3 * sizeof(float), colors, GL_STREAM_DRAW);	//the color is going to change every frame
																				//as it bounces between squares
	
	delete [] colors;

	//once more, this time with normals
	float* normals = new float[verts->size()*4];
	for(int i = 0; i < verts->size(); i++) {
		normals[i*4] = norms->at(i)[0];
		normals[i*4+1] = norms->at(i)[1];
		normals[i*4+2] = norms->at(i)[2];
		normals[i*4+3] = 1;
	}

	glBindBuffer(GL_ARRAY_BUFFER, nbo);
	glBufferData(GL_ARRAY_BUFFER, norms->size()*4 * sizeof(float), normals, GL_STATIC_DRAW); //the square normals don't need to change, ever,
																				 //while the program runs
	
	delete [] normals;
	delete [] vertices;

	//activate our three kinds of information
	glEnableVertexAttribArray(positionLocation);
	glEnableVertexAttribArray(colorLocation);
	glEnableVertexAttribArray(normalLocation);
	
	//we're using the vertex data first
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//define how the vertex pointer should work, in our case we're accessing floats 4 at a time with no special pattern
	glVertexAttribPointer(positionLocation, 4, GL_FLOAT, 0, 0, static_cast<char*>(0));
	
	//now use color data, remember we're not using 4 at a time anymore
	glBindBuffer(GL_ARRAY_BUFFER, cbo);
	glVertexAttribPointer(colorLocation, 3, GL_FLOAT, 0, 0, static_cast<char*>(0));
	
	//one more time with the normals
	glBindBuffer(GL_ARRAY_BUFFER, nbo);
	glVertexAttribPointer(normalLocation, 4, GL_FLOAT, 0, 0, static_cast<char*>(0));
	
	//the last thing we need to do is setup our indices
	unsigned short* indices = new unsigned short[faces->size()*3];

	for(int i = 0; i < faces->size(); i++) {
		indices[i*3] = (unsigned short) faces->at(i)[0];
		indices[i*3+1] = (unsigned short) faces->at(i)[1];
		indices[i*3+2] = (unsigned short) faces->at(i)[2];
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, faces->size()*3 * sizeof(unsigned short), indices, GL_STATIC_DRAW);

	delete [] indices;

	//set the modelview uniform
	glUniformMatrix4fv(u_modelMatrixLocation, 1, GL_FALSE, &modelView[0][0]);

	//draw the elements
	glDrawElements(GL_TRIANGLES, faces->size()*3, GL_UNSIGNED_SHORT, 0);
	
	//shut off the information since we're done drawing
	glDisableVertexAttribArray(positionLocation);
	glDisableVertexAttribArray(colorLocation);
	glDisableVertexAttribArray(normalLocation);

}
///////////////////////////////////////////////

void MyGLWidget::createRedSquare(glm::mat4 modelView) {
	//set up a transformation matrix, in this case we're doing rotation only
	modelView = glm::rotate(modelView, rotation, glm::vec3(0, 0, 1));

	//these four points define where the quad would be BEFORE transformations
	//this is referred to as object-space and it's best to center geometry at the origin for easier transformations
	float* vertices = new float[16];
	vertices[0] = -4.0f; vertices[1] = 4.0f; vertices[2] = -1.0f; vertices[3] = 1.0f;
	vertices[4] = -4.0f; vertices[5] = -4.0f; vertices[6] = -1.0f; vertices[7] = 1.0f;
	vertices[8] = 4.0f; vertices[9] = -4.0f; vertices[10] = -1.0f; vertices[11] = 1.0f;
	vertices[12] = 4.0f; vertices[13] = 4.0f; vertices[14] = -1.0f; vertices[15] = 1.0f;

	//now we put the data into the Vertex Buffer Object for the graphics system to use
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 16 * sizeof(float), vertices, GL_STATIC_DRAW); //the square vertices don't need to change, ever,
																				 //while the program runs

	//once the data is loaded, we can delete the float arrays, the data is safely stored with OpenGL
	delete [] vertices;

	//again with colors
	float* colors = new float[12];
	
	colors[0] = 1; colors[1] = 0; colors[2] = 0;
	colors[3] = 1; colors[4] = 0; colors[5] = 0;
	colors[6] = 1; colors[7] = 0; colors[8] = 0;
	colors[9] = 1; colors[10] = 0; colors[11] = 0;

	glBindBuffer(GL_ARRAY_BUFFER, cbo);
	//always make sure you are telling OpenGL the right size to make the buffer, color data doesn't have as much data!
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), colors, GL_STREAM_DRAW);	//the color is going to change every frame
																				//as it bounces between squares
	
	delete [] colors;

	//once more, this time with normals
	float* normals = new float[16];
	
	normals[0] = 0; normals[1] = 0; normals[2] = 1; normals[3] = 0;
	normals[4] = 0; normals[5] = 0; normals[6] = 1; normals[7] = 0;
	normals[8] = 0; normals[9] = 0; normals[10] = 1; normals[11] = 0;
	normals[12] = 0; normals[13] = 0; normals[14] = 1; normals[15] = 0;

	glBindBuffer(GL_ARRAY_BUFFER, nbo);
	glBufferData(GL_ARRAY_BUFFER, 16 * sizeof(float), normals, GL_STATIC_DRAW); //the square normals don't need to change, ever,
																				 //while the program runs
	
	delete [] normals;

	//activate our three kinds of information
	glEnableVertexAttribArray(positionLocation);
	glEnableVertexAttribArray(colorLocation);
	glEnableVertexAttribArray(normalLocation);
	
	//we're using the vertex data first
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//define how the vertex pointer should work, in our case we're accessing floats 4 at a time with no special pattern
	glVertexAttribPointer(positionLocation, 4, GL_FLOAT, 0, 0, static_cast<char*>(0));
	
	//now use color data, remember we're not using 4 at a time anymore
	glBindBuffer(GL_ARRAY_BUFFER, cbo);
	glVertexAttribPointer(colorLocation, 3, GL_FLOAT, 0, 0, static_cast<char*>(0));
	
	//one more time with the normals
	glBindBuffer(GL_ARRAY_BUFFER, nbo);
	glVertexAttribPointer(normalLocation, 4, GL_FLOAT, 0, 0, static_cast<char*>(0));
	
	//the last thing we need to do is setup our indices
	unsigned short* indices = new unsigned short[6];

	indices[0] = 0; indices[1] = 1; indices[2] = 2;
	indices[3] = 3; indices[4] = 0; indices[5] = 2;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned short), indices, GL_STATIC_DRAW);

	delete [] indices;

	//set the modelview uniform
	glUniformMatrix4fv(u_modelMatrixLocation, 1, GL_FALSE, &modelView[0][0]);

	//draw the elements
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
	
	//shut off the information since we're done drawing
	glDisableVertexAttribArray(positionLocation);
	glDisableVertexAttribArray(colorLocation);
	glDisableVertexAttribArray(normalLocation);
}

void MyGLWidget::createBlueSquare(glm::mat4 modelView) {
	//two transformations put into the modelview matrix
	modelView = glm::translate(modelView, glm::vec3(-2.0f, 2.0f, -0.1f));
	modelView = glm::rotate(modelView, -rotation, glm::vec3(0, 0, 1));

	//the only difference between a red square and a blue square is the color, so we can leave the other VBOs as they are
	float* colors = new float[12];
	
	colors[0] = 0; colors[1] = 0; colors[2] = 1;
	colors[3] = 0; colors[4] = 0; colors[5] = 1;
	colors[6] = 0; colors[7] = 0; colors[8] = 1;
	colors[9] = 0; colors[10] = 0; colors[11] = 1;

	glBindBuffer(GL_ARRAY_BUFFER, cbo);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), colors, GL_STREAM_DRAW);
	
	delete [] colors;

	//activate our three kinds of information
	glEnableVertexAttribArray(positionLocation);
	glEnableVertexAttribArray(colorLocation);
	glEnableVertexAttribArray(normalLocation);
	
	//bind again
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(positionLocation, 4, GL_FLOAT, 0, 0, static_cast<char*>(0));
	
	glBindBuffer(GL_ARRAY_BUFFER, cbo);
	glVertexAttribPointer(colorLocation, 3, GL_FLOAT, 0, 0, static_cast<char*>(0));
	
	glBindBuffer(GL_ARRAY_BUFFER, nbo);
	glVertexAttribPointer(normalLocation, 4, GL_FLOAT, 0, 0, static_cast<char*>(0));

	//set the modelview matrix again since it changed
	glUniformMatrix4fv(u_modelMatrixLocation, 1, GL_FALSE, &modelView[0][0]);

	//draw again, even the indices from before are good
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
	
	//shut off the information since we're done drawing
	glDisableVertexAttribArray(positionLocation);
	glDisableVertexAttribArray(colorLocation);
	glDisableVertexAttribArray(normalLocation);
}

//This function is called automatically when the widget is resized, including the first "sizing"
void MyGLWidget::resizeGL(int width, int height) {
    //set the viewport, more boilerplate
	glViewport(0, 0, width, height);

	//
	glm::mat4 projection = glm::perspective(60.0f, static_cast<float>(width) / static_cast<float>(height), 0.1f, 30.0f);
	glm::mat4 camera = glm::lookAt(glm::vec3(0, 5, 10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	projection = projection * camera;		// ^ 0
	

	//set the projection matrix here, it only needs to be changed if the screen is resized otherwise it can stay the same
	glUniformMatrix4fv(u_projMatrixLocation, 1, GL_FALSE, &projection[0][0]);
}

void MyGLWidget::keyPressEvent(QKeyEvent *e){
	//a good place to process keystrokes
	if (e->key() == Qt::Key_E) {
		if (selected != root) {
			graph->removeChild(selected);
			selected = root;
		}
	}
	if (e->key() == Qt::Key_N) {
		sel_id ++;
		if(sel_id > graph->objects->size() - 1) {
			sel_id = 0;
			selected = root;
		} else {
			selected = graph->objects->at(sel_id);
		}
     }
	if (!(e->modifiers() & Qt::ShiftModifier)) {
		if (e->key() == Qt::Key_R) {
			this->rotation = -10;
			if(selected->parent != nullptr) {
				 graph->rotate(rotation, selected->dX, selected->dZ, selected);
			} else {
				 graph->rotate(rotation, 0, 0, selected);
			}
		}
	}
	if (e->modifiers() & Qt::ShiftModifier) {
		if (e->key() == Qt::Key_R) {
			this->rotation = 10;
			if(selected->parent != nullptr) {
				 graph->rotate(rotation, selected->dX, selected->dZ, selected);
			} else {
				 graph->rotate(rotation, 0, 0, selected);
			}
		}
    }
	if (e->key() == Qt::Key_A) {
		graph->translate(-0.5f,0, selected);
    }
	if (e->key() == Qt::Key_D) {
		graph->translate(0.5f,0, selected);
    }
	if (e->key() == Qt::Key_S) {
		graph->translate(0,0.5f, selected);
    }
	if (e->key() == Qt::Key_W) {
		graph->translate(0,-0.5f, selected);
    }
	if (e->key() == Qt::Key_X) {
		if (selected->parent != nullptr) {
			graph->scale(1.5f,1,1,selected->parent->height, selected->dX, selected->dZ, selected->rY, selected);
		} else {
			graph->scale(1.5f,1,1,0, selected->dX, selected->dZ, selected->rY, selected);
		}
    }
	if (e->key() == Qt::Key_Y) {
		if (selected->parent != nullptr) {
			graph->scale(1,1.5f,1,selected->parent->height, selected->dX, selected->dZ, selected->rY,  selected);
		} else {
			graph->scale(1,1.5f,1,0, selected->dX, selected->dZ, selected->rY, selected);
		}
    }
	if (e->key() == Qt::Key_Z) {
		if (selected->parent != nullptr) {
			graph->scale(1,1,1.5f,selected->parent->height, selected->dX, selected->dZ, selected->rY, selected);
		} else {
			graph->scale(1,1,1.5f,0,selected->dX, selected->dZ, selected->rY, selected);
		}
    }
	if (e->modifiers() & Qt::ShiftModifier) {
		if (e->key() == Qt::Key_X) {
		if (selected->parent != nullptr) {
			graph->scale(0.5f,1,1,selected->parent->height, selected->dX, selected->dZ,selected->rY,  selected);
		} else {
			graph->scale(0.5f,1,1,0,selected->dX, selected->dZ, selected->rY, selected);
		}
		}
    }
	if (e->modifiers() & Qt::ShiftModifier) {
		if (e->key() == Qt::Key_Y) {
		if (selected->parent != nullptr) {
			graph->scale(1,0.5f,1,selected->parent->height,selected->dX, selected->dZ,selected->rY,  selected);
		} else {
			graph->scale(1,0.5f,1,0,selected->dX, selected->dZ,selected->rY,  selected);
		}
		}
    }
	if (e->modifiers() & Qt::ShiftModifier) {
		if (e->key() == Qt::Key_Z) {
		if (selected->parent != nullptr) {
			graph->scale(1,1,0.5f,selected->parent->height,selected->dX, selected->dZ,selected->rY,  selected);
		} else {
			graph->scale(1,1,0.5f,0, selected->dX, selected->dZ, selected->rY, selected);
		}
		}
    }
	if (e->key() == Qt::Key_P) {
		string fileN;
		//string line;
		cout << "Enter a file name:" << endl;
		getline(cin, fileN);
		ifstream inf(fileN);
		string line;

		if (inf.is_open()) {
			string line;
			int lines = 0;
			inf >> line >> FILEM;
			inf >> line >> RESO[0] >> RESO[1];
			inf >> line >> EYEP[0] >> EYEP[1] >> EYEP[2];
			inf >> line >> VDIR[0] >> VDIR[1] >> VDIR[2];
			inf >> line >> UVEC[0] >> UVEC[1] >> UVEC[2];
			inf >> line >> FOVY;
			inf >> line >> LPOS[0] >> LPOS[1] >> LPOS[2];
			inf >> line >> LCOL[0] >> LCOL[1] >> LCOL[2];
			inf >> line >> ACOL[0] >> ACOL[1] >> ACOL[2];
			inf >> line >> MAT1RGB[0] >> MAT1RGB[1] >> MAT1RGB[2] >> MAT1S >> MAT1R >> MAT1E1 >> MAT1E2 >> MAT1E3;
			inf >> line >> MAT2RGB[0] >> MAT2RGB[1] >> MAT2RGB[2] >> MAT2S >> MAT2R >> MAT2E1 >> MAT2E2 >> MAT2E3;
			inf >> line >> MAT3RGB[0] >> MAT3RGB[1] >> MAT3RGB[2] >> MAT3S >> MAT3R >> MAT3E1 >> MAT3E2 >> MAT3E3;
		}
		raytracer();
	}
}

//from swiftless.com
char* MyGLWidget::textFileRead(const char* fiAsizeme) {
    char* text;
    
    if (fiAsizeme != nullptr) {
        FILE *file = fopen(fiAsizeme, "rt");
        
        if (file != nullptr) {
            fseek(file, 0, SEEK_END);
            int count = ftell(file);
            rewind(file);
            
            if (count > 0) {
                text = (char*)malloc(sizeof(char) * (count + 1));
                count = fread(text, sizeof(char), count, file);
                text[count] = '\0';	//cap off the string with a terminal symbol, fixed by Cory
            }
            fclose(file);
        }
    }
    return text;
}

void MyGLWidget::printLinkInfoLog(int prog) 
{
	int infoLogLen = 0;
	int charsWritten = 0;
	GLchar *infoLog;

	glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &infoLogLen);

	// should additionally check for OpenGL errors here

	if (infoLogLen > 0)
	{
		infoLog = new GLchar[infoLogLen];
		// error check for fail to allocate memory omitted
		glGetProgramInfoLog(prog,infoLogLen, &charsWritten, infoLog);
		qDebug() << "InfoLog:" << endl << infoLog << endl;
		delete [] infoLog;
	}
}

void MyGLWidget::printShaderInfoLog(int shader)
{
	int infoLogLen = 0;
	int charsWritten = 0;
	GLchar *infoLog;

	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLen);

	// should additionally check for OpenGL errors here

	if (infoLogLen > 0)
	{
		infoLog = new GLchar[infoLogLen];
		// error check for fail to allocate memory omitted
		glGetShaderInfoLog(shader,infoLogLen, &charsWritten, infoLog);
		qDebug() << "InfoLog:" << endl << infoLog << endl;
		delete [] infoLog;
	}

	// should additionally check for OpenGL errors here
}

//////EXTRA CREDIT//////////////////
void MyGLWidget::initBB(int i, Node* n) {
	string type = furnitures[i];
	if(type.compare("table") == 0) {
		n->bb1[0] = -1; n->bb1[1] = -0.5f; n->bb1[2] = -1;
		n->bb2[0] = 1; n->bb2[1] = -0.5f; n->bb2[2] = -1;
		n->bb3[0] = 1; n->bb3[1] = -0.5f; n->bb3[2] = 1;
		n->bb4[0] = -1; n->bb4[1] = -0.5f; n->bb4[2] = 1;
		n->bb5[0] = -1; n->bb5[1] = 0.5f; n->bb5[2] = -1;
		n->bb6[0] = 1; n->bb6[1] = 0.5f; n->bb6[2] = -1;
		n->bb7[0] = 1; n->bb7[1] = 0.5f; n->bb7[2] = 1;
		n->bb8[0] = -1; n->bb8[1] = 0.5f; n->bb8[2] = 1;
	} else if(type.compare("chair") == 0) {
		n->bb1[0] = -0.3f; n->bb1[1] = -0.65f; n->bb1[2] = -0.3f;
		n->bb2[0] = 0.3f; n->bb2[1] = -0.65f; n->bb2[2] = -0.3f;
		n->bb3[0] = 0.3f; n->bb3[1] = -0.65f; n->bb3[2] = 0.3f;
		n->bb4[0] = -0.3f; n->bb4[1] = -0.65f; n->bb4[2] = 0.3f;
		n->bb5[0] = -0.3f; n->bb5[1] = 0.65f; n->bb5[2] = -0.3f;
		n->bb6[0] = 0.3f; n->bb6[1] = 0.65f; n->bb6[2] = -0.3f;
		n->bb7[0] = 0.3f; n->bb7[1] = 0.65f; n->bb7[2] = 0.3f;
		n->bb8[0] = -0.3f; n->bb8[1] = 0.65f; n->bb8[2] = 0.3f;
	} else if(type.compare("cabinet") == 0) {
		n->bb1[0] = -0.5f; n->bb1[1] = -0.5f; n->bb1[2] = -0.5f;
		n->bb2[0] = 0.5f; n->bb2[1] = -0.5f; n->bb2[2] = -0.5f;
		n->bb3[0] = 0.5f; n->bb3[1] = -0.5f; n->bb3[2] = 0.5f;
		n->bb4[0] = -0.5f; n->bb4[1] = -0.5f; n->bb4[2] = 0.5f;
		n->bb5[0] = -0.5f; n->bb5[1] = 0.5f; n->bb5[2] = -0.5f;
		n->bb6[0] = 0.5f; n->bb6[1] = 0.5f; n->bb6[2] = -0.5f;
		n->bb7[0] = 0.5f; n->bb7[1] = 0.5f; n->bb7[2] = 0.5f;
		n->bb8[0] = -0.5f; n->bb8[1] = 0.5f; n->bb8[2] = 0.5f;
	} else if(type.compare("lamp") == 0) {
		n->bb1[0] = -0.5f; n->bb1[1] = -0.5f; n->bb1[2] = -0.5f;
		n->bb2[0] = 0.5f; n->bb2[1] = -0.5f; n->bb2[2] = -0.5f;
		n->bb3[0] = 0.5f; n->bb3[1] = -0.5f; n->bb3[2] = 0.5f;
		n->bb4[0] = -0.5f; n->bb4[1] = -0.5f; n->bb4[2] = 0.5f;
		n->bb5[0] = -0.5f; n->bb5[1] = 0.5f; n->bb5[2] = -0.5f;
		n->bb6[0] = 0.5f; n->bb6[1] = 0.5f; n->bb6[2] = -0.5f;
		n->bb7[0] = 0.5f; n->bb7[1] = 0.5f; n->bb7[2] = 0.5f;
		n->bb8[0] = -0.5f; n->bb8[1] = 0.5f; n->bb8[2] = 0.5f;
	}
}

void MyGLWidget::drawBB() {
	glBegin(GL_LINES);
	  glVertex3f(selected->bb1[0], selected->bb1[1], selected->bb1[2]);
	  glVertex3f(selected->bb2[0], selected->bb2[1], selected->bb2[2]);
	glEnd();
	glBegin(GL_LINES);
	  glVertex3f(selected->bb2[0], selected->bb2[1], selected->bb2[2]);
	  glVertex3f(selected->bb3[0], selected->bb3[1], selected->bb3[2]);
	glEnd();
	glBegin(GL_LINES);
	  glVertex3f(selected->bb3[0], selected->bb3[1], selected->bb3[2]);
	  glVertex3f(selected->bb4[0], selected->bb4[1], selected->bb4[2]);
	glEnd();
	glBegin(GL_LINES);
	  glVertex3f(selected->bb4[0], selected->bb4[1], selected->bb4[2]);
	  glVertex3f(selected->bb1[0], selected->bb1[1], selected->bb1[2]);
	glEnd();
	glBegin(GL_LINES);
	  glVertex3f(selected->bb5[0], selected->bb5[1], selected->bb5[2]);
	  glVertex3f(selected->bb6[0], selected->bb6[1], selected->bb6[2]);
	glEnd();
	glBegin(GL_LINES);
	  glVertex3f(selected->bb6[0], selected->bb6[1], selected->bb6[2]);
	  glVertex3f(selected->bb7[0], selected->bb7[1], selected->bb7[2]);
	glEnd();
	glBegin(GL_LINES);
	  glVertex3f(selected->bb7[0], selected->bb7[1], selected->bb7[2]);
	  glVertex3f(selected->bb8[0], selected->bb8[1], selected->bb8[2]);
	glEnd();
	glBegin(GL_LINES);
	  glVertex3f(selected->bb8[0], selected->bb8[1], selected->bb8[2]);
	  glVertex3f(selected->bb5[0], selected->bb5[1], selected->bb5[2]);
	glEnd();
	glBegin(GL_LINES);
	  glVertex3f(selected->bb1[0], selected->bb1[1], selected->bb1[2]);
	  glVertex3f(selected->bb5[0], selected->bb5[1], selected->bb5[2]);
	glEnd();
	glBegin(GL_LINES);
	  glVertex3f(selected->bb2[0], selected->bb2[1], selected->bb2[2]);
	  glVertex3f(selected->bb6[0], selected->bb6[1], selected->bb6[2]);
	glEnd();
	glBegin(GL_LINES);
	  glVertex3f(selected->bb3[0], selected->bb3[1], selected->bb3[2]);
	  glVertex3f(selected->bb7[0], selected->bb7[1], selected->bb7[2]);
	glEnd();
	glBegin(GL_LINES);
	  glVertex3f(selected->bb4[0], selected->bb4[1], selected->bb4[2]);
	  glVertex3f(selected->bb8[0], selected->bb8[1], selected->bb8[2]);
	glEnd();
}

///////////////////ray tracer//////////////////////////////
//glm::vec4 P = glm::vec4(0,0,0,1);
//glm::vec4 M = glm::vec4(0,0,0,1);
//glm::vec4 H = glm::vec4(0,0,0,1);
//glm::vec4 V = glm::vec4(0,0,0,1);
//glm::vec4 D = glm::vec4(0,0,0,1);
//glm::vec4 E = glm::vec4(0,0,0,1);
//glm::vec3 color = glm::vec3(255,0,0);

//glm::vec3 BackgroundColor = glm::vec3(0,0,0);
//glm::vec3 ambient;
//int MaxDepth = 5;
//int n = 10;
//vector<Furniture> objs = *new vector<Furniture>();
//vector<glm::vec4*> *intersects = new vector<glm::vec4*>();
//vector<float> ts = *new vector<float>();
//vector<glm::vec3> *LtSource = new vector<glm::vec3>();
//vector<glm::vec3> C = new vector<glm::vec3>();

//vector<glm::vec3> L = new vector<glm::vec3>();
		


void MyGLWidget::raytracer() {
	eyePos = EYEP;

	char file[256];
	strcpy(file, FILEM.c_str());

	BMP output;
	output.SetSize(RESO[0], RESO[1]);
	output.SetBitDepth(24);

	glm::vec3 E, VD, UV, EP;
	E = eyePos;
	VD = VDIR;
	UV = UVEC;
	EP = EYEP;
	float theta = FOVY/4;
	float Pi = 3.14159265f;
	//V = glm::normalize(glm::cross(M-E,glm::vec3(1,0,0))); //?
	//H = glm::normalize(glm::cross(M-E,V)); //?

	glm::vec3 A,B,M;
	glm::vec3 H,V;
	glm::vec3 color;

	A = glm::normalize(glm::vec3(VD[1]*UV[2] - VD[2]*UV[1], VD[0]*UV[2] - VD[2]*UV[0], VD[0]*UV[1] - VD[1]*UV[0]));
	B = glm::vec3(A[1]*VD[2] - A[2]*VD[1], A[2]*VD[0] - A[0]*VD[2], A[0]*VD[1] - A[1]*VD[0]);
	M = glm::vec3(EP[0] + VD[0], EP[1] + VD[1], EP[2] + VD[2]);
	//float Csize = 200;
	float Asize = sqrt((float) (A[0] * A[0] + A[1] * A[1] + A[2] * A[2]));
	float Bsize = sqrt((float) (B[0] * B[0] + B[1] * B[1] + B[2] * B[2]));
	float Csize = sqrt((float) (VD[0] * VD[0] + VD[1] * VD[1] + VD[2] * VD[2]));

	for (int k = 0; k < 3; k++) {
		V[k] = (float) B[k] * Csize * tan(theta*Pi/180)/Bsize;
		H[k] = (float) A[k] * RESO[0] * tan(theta*Pi/180)/RESO[1];
		color[k] = 0.5f;
	}
	
	for(unsigned int x = 0; x < RESO[0]; x++) {
		cout << "x = " << x << endl;
		for(unsigned int y = 0; y < RESO[1]; y++) {
			//float sx = (float)x/(RESO[0] - 1);
			//float sy = 1 - ((float)y/(RESO[1] - 1));
			glm::vec3 P, D;
			for (int k = 0; k < 3; k++) {
				P[k] = M[k] + ((float)2*x/(RESO[0] - 1)-1)*H[k]+((float)2*(1 - ((float) y/(RESO[1] - 1)))-1)*V[k];
			}

			float size = sqrt((P[0]-E[0])*(P[0]-E[0])+(P[1]-E[1])*(P[1]-E[1])+(P[2]-E[2])*(P[2]-E[2]));
			for (int k = 0; k < 3; k++) {
				D[k] = (P[k]-E[k])/size;
			}
			
		//	dirVector = D;
			// test if D and VD are the same
		//	dirVector = VD;
		//	D = VD;
			color = TraceRay(E,D,0,color);
			output(x,y)->Red = color[0]*255*5;
			output(x,y)->Green = color[1]*255*5;
			output(x,y)->Blue = color[2]*255*5;

			if(color[0]*255 > 255) output(x,y)->Red = 255;
			if(color[1]*255 > 255) output(x,y)->Green = 255;
			if(color[2]*255 > 255) output(x,y)->Blue = 255;
		}
	}
	output.WriteToFile(file);
}

bool MyGLWidget::ShadowRayUnblocked(glm::vec3 P1,glm::vec3 P2) {
	eyePos = EYEP; dirV = VDIR;
	glm::vec3 E, D, IP, LPos;

	E = EYEP;
	D = VDIR;
	bool result = false;

	glm::vec3 P2P1 = glm::normalize(P2-P1);

	//for (int i = 0; i < 3; i++) {
	//	E[i] = EYEP[i];
	//	D[i] = VD[i];
	//	IP[i] = IntersectPoint[i];
	//	LPos[i] = LPOS[i] - IP[i];
	//}

	for(int i = 0; i < graph->objects->size(); i++) {
		float tNear = 1000;
		Node* n = graph->objects->at(i);
		if(n->ge == 0) {
			float t = (float) this->Test_RayCubeIntersect(P1, P2P1,n->fcube);
			if(t < tNear && t >= 0) {
				tNear = t;
				return true;
			}
		} else if(n->ge == 1) {
			float t = (float) this->Test_RayCubeIntersect(P1, P2P1,n->tleg1);
			if(t < tNear && t >= 0) {
				tNear = t;
				return true;
			}
			t = (float) this->Test_RayCubeIntersect(P1, P2P1,n->tleg2);
			if(t < tNear && t >= 0) {
				tNear = t;
				return true;
			}
			t = (float) this->Test_RayCubeIntersect(P1,P2P1,n->tleg3);
			if(t < tNear && t >= 0) {
				tNear = t;
				return true;
			}
			t = (float) this->Test_RayCubeIntersect(P1,P2P1,n->tleg4);
			if(t < tNear && t >= 0) {
				tNear = t;
				return true;
			}
			t = (float) this->Test_RayCylinderIntersect(P1,P2P1,n->ttop);
			if(t < tNear && t >= 0) {
				tNear = t;
				return true;
			}
		} else if(n->ge == 2) {
			float t = (float) this->Test_RayCubeIntersect(P1,P2P1,n->cleg1);
			if(t < tNear && t >= 0) {
				tNear = t;
				return true;
			}
			t = (float) this->Test_RayCubeIntersect(P1,P2P1,n->cleg2);
			if(t < tNear && t >= 0) {
				tNear = t;
				return true;
			}
			t = (float) this->Test_RayCubeIntersect(P1,P2P1,n->cleg3);
			if(t < tNear && t >= 0) {
				tNear = t;
				return true;
			}
			t = (float) this->Test_RayCubeIntersect(P1,P2P1,n->cleg4);
			if(t < tNear && t >= 0) {
				tNear = t;
				return true;
			}
			t = (float) this->Test_RayCubeIntersect(P1,P2P1,n->cseat);
			if(t < tNear && t >= 0) {
				tNear = t;
				return true;
			}
			t = (float) this->Test_RayCubeIntersect(P1,P2P1,n->cback);
			if(t < tNear && t >= 0) {
				tNear = t;
				return true;
			}
		} else if(n->ge == 3) {
			float t = (float) this->Test_RayCubeIntersect(E,P2P1,n->cbody);
			if(t < tNear && t >= 0) {
				tNear = t;
				return true;
			}
			t = (float) this->Test_RayCubeIntersect(E,P2P1,n->cdoor);
			if(t < tNear && t >= 0) {
				tNear = t;
				return true;
			}
		} else if(n->ge == 4) {
			float t = (float) this->Test_RayCylinderIntersect(E,P2P1,n->lstand);
			if(t < tNear && t >= 0) {
				tNear = t;
				return true;
			}
			t = (float) this->Test_RaySphereIntersect(E,P2P1,n->ltop);
			if(t < tNear && t >= 0) {
				tNear = t;
				return true;
			}
		} else if(n->ge == 5) {

		}
	}
	return false;

	//glm::vec4 P1P2 = glm::vec4(P2[0]- P1[0], P2[1] - P1[1], P2[2] - P1[2], 0);
	//bool blocked;
	//if (blocked == false) return false;
	//else return true;
}

glm::vec3 MyGLWidget::ReflectedRay(glm::vec3 P1,glm::vec3 PN,glm::vec3 P0) {
	glm::vec3 PR;
	PR = glm::reflect((P0 - P1), PN);
	return PR;
}

glm::vec3 MyGLWidget::computeNormal(Node* node, glm::vec3 P) {
	//compute normal at P for the object in node
	glm::vec3 norm;
	if(node->ge == 0) {
		if(P[0] >= -0.5f && P[0] <= 0.5f && P[1] >= -0.5f && P[1] <= 0.5f && P[2] == -0.5f) {
			norm = glm::vec3(0,0,-1);
		} else if(P[0] >= -0.5f && P[0] <= 0.5f && P[1] >= -0.5f && P[1] <= 0.5f && P[2] == 0.5f) {
			norm = glm::vec3(0,0,1);
		} else if(P[0] >= -0.5f && P[0] <= 0.5f && P[2] >= -0.5f && P[2] <= 0.5f && P[1] == -0.5f) {
			norm = glm::vec3(0,-1,0);
		} else if(P[0] >= -0.5f && P[0] <= 0.5f && P[2] >= -0.5f && P[2] <= 0.5f && P[1] == 0.5f) {
			norm = glm::vec3(0,1,0);
		} else if(P[2] >= -0.5f && P[2] <= 0.5f && P[1] >= -0.5f && P[1] <= 0.5f && P[0] == -0.5f) {
			norm = glm::vec3(-1,0,0);
		} else if(P[2] >= -0.5f && P[2] <= 0.5f && P[1] >= -0.5f && P[1] <= 0.5f && P[0] == 0.5f) {
			norm = glm::vec3(1,0,0);
		} else {

		}
		norm = glm::vec3(0,1,0);
	} else if (node->ge == 1) {
		if(P[0] >= -0.5f && P[0] <= 0.5f && P[1] >= -0.5f && P[1] <= 0.5f && P[2] == -0.5f) {
			norm = glm::vec3(0,0,-1);
		} else if(P[0] >= -0.5f && P[0] <= 0.5f && P[1] >= -0.5f && P[1] <= 0.5f && P[2] == 0.5f) {
			norm = glm::vec3(0,0,1);
		} else if(P[0] >= -0.5f && P[0] <= 0.5f && P[2] >= -0.5f && P[2] <= 0.5f && P[1] == -0.5f) {
			norm = glm::vec3(0,-1,0);
		} else if(P[0] >= -0.5f && P[0] <= 0.5f && P[2] >= -0.5f && P[2] <= 0.5f && P[1] == 0.5f) {
			norm = glm::vec3(0,1,0);
		} else if(P[2] >= -0.5f && P[2] <= 0.5f && P[1] >= -0.5f && P[1] <= 0.5f && P[0] == -0.5f) {
			norm = glm::vec3(-1,0,0);
		} else if(P[2] >= -0.5f && P[2] <= 0.5f && P[1] >= -0.5f && P[1] <= 0.5f && P[0] == 0.5f) {
			norm = glm::vec3(1,0,0);
		} else {

		}
	} else if (node->ge == 2) {
		if(P[0] >= -0.5f && P[0] <= 0.5f && P[1] >= -0.5f && P[1] <= 0.5f && P[2] == -0.5f) {
			norm = glm::vec3(0,0,-1);
		} else if(P[0] >= -0.5f && P[0] <= 0.5f && P[1] >= -0.5f && P[1] <= 0.5f && P[2] == 0.5f) {
			norm = glm::vec3(0,0,1);
		} else if(P[0] >= -0.5f && P[0] <= 0.5f && P[2] >= -0.5f && P[2] <= 0.5f && P[1] == -0.5f) {
			norm = glm::vec3(0,-1,0);
		} else if(P[0] >= -0.5f && P[0] <= 0.5f && P[2] >= -0.5f && P[2] <= 0.5f && P[1] == 0.5f) {
			norm = glm::vec3(0,1,0);
		} else if(P[2] >= -0.5f && P[2] <= 0.5f && P[1] >= -0.5f && P[1] <= 0.5f && P[0] == -0.5f) {
			norm = glm::vec3(-1,0,0);
		} else if(P[2] >= -0.5f && P[2] <= 0.5f && P[1] >= -0.5f && P[1] <= 0.5f && P[0] == 0.5f) {
			norm = glm::vec3(1,0,0);
		} else {

		}
	} else if (node->ge == 3) {
		if(P[0] >= -0.5f && P[0] <= 0.5f && P[1] >= -0.5f && P[1] <= 0.5f && P[2] == -0.5f) {
			norm = glm::vec3(0,0,-1);
		} else if(P[0] >= -0.5f && P[0] <= 0.5f && P[1] >= -0.5f && P[1] <= 0.5f && P[2] == 0.5f) {
			norm = glm::vec3(0,0,1);
		} else if(P[0] >= -0.5f && P[0] <= 0.5f && P[2] >= -0.5f && P[2] <= 0.5f && P[1] == -0.5f) {
			norm = glm::vec3(0,-1,0);
		} else if(P[0] >= -0.5f && P[0] <= 0.5f && P[2] >= -0.5f && P[2] <= 0.5f && P[1] == 0.5f) {
			norm = glm::vec3(0,1,0);
		} else if(P[2] >= -0.5f && P[2] <= 0.5f && P[1] >= -0.5f && P[1] <= 0.5f && P[0] == -0.5f) {
			norm = glm::vec3(-1,0,0);
		} else if(P[2] >= -0.5f && P[2] <= 0.5f && P[1] >= -0.5f && P[1] <= 0.5f && P[0] == 0.5f) {
			norm = glm::vec3(1,0,0);
		} else {

		}
	} else if (node->ge == 4) {
		if(node->defaultID == 0) {
			if(P[1] == 0.5) {
				norm = glm::vec3(0,1,0);
			} else if (P[1] == -0.5) {
				norm = glm::vec3(0,-1,0);
			} else {
				norm = glm::vec3(P[0],0,P[2]);
			}
		} else if(node->defaultID == 1) {
			norm = glm::vec3(P);
		}
	} else if (node->ge == 5) {

	}
	return norm;
}

bool MyGLWidget::inside(glm::vec3 V, Node* N) {
	return false;
}

double MyGLWidget::Test_RaySphereIntersect(glm::vec3 P1, glm::vec3 V1, glm::mat4 T) {
	// TODO fill this in so it calls your own ray-casting function.
	// See the documentation of this function in stubs.h.
	
	glm::mat4 T1 = glm::inverse(T);
	//T1 = glm::transpose(T1);

	glm::vec4 P0 = glm::vec4(P1,1);
	P0 = T1*P0;

	glm::vec4 V0 = glm::vec4(V1,0);
	V0 = T1*V0;
	//V0 = glm::normalize(V0);

	float Sr = 1;
	glm::vec3 C0 = glm::vec3(0,0,0);
	//V0 = normalize(V0);
	float A = V0[0] * V0[0] + V0[1] * V0[1] + V0[2] * V0[2];
	float B = 2*(V0[0]*(P0[0]-C0[0]) + V0[1]*(P0[1]-C0[1]) + V0[2]*(P0[2]-C0[2]));
	float C = (P0[0]-C0[0])*(P0[0]-C0[0]) + (P0[1]-C0[1])*(P0[1]-C0[1]) + (P0[2]-C0[2])*(P0[2]-C0[2]) - Sr*Sr;
	if(B*B - 4*A*C < 0) {
		return -1;
		// no intersection
	} else if(B*B - 4*A*C >= 0) {
		float t0 = (-B - sqrt(B*B - 4*A*C))/(A*2);
		float t1 = (-B + sqrt(B*B - 4*A*C))/(A*2);

		glm::vec3 Point1 = glm::vec3(P0[0],P0[1],P0[2]) + t0*glm::vec3(V0[0],V0[1],V0[2]);
		glm::vec3 Point2 = glm::vec3(P0[0],P0[1],P0[2]) + t1*glm::vec3(V0[0],V0[1],V0[2]);
		glm::vec4 Point14 = glm::vec4(Point1,1);
		glm::vec4 Point24 = glm::vec4(Point2,1);
		Point14 = T*Point14;
		Point24 = T*Point24;
		Point1 = glm::vec3(Point14[0],Point14[1],Point14[2]);
		Point2 = glm::vec3(Point24[0],Point24[1],Point24[2]);

		if(t0 >= 0 && t1 < 0) {
			t0 = sqrt((Point1[0]-P1[0])*(Point1[0]-P1[0]) + (Point1[1]-P1[1])*(Point1[1]-P1[1]) + (Point1[2]-P1[2])*(Point1[2]-P1[2]));
			//std::cout << t0 + FLT_EPSILON << std::endl;
			 return t0;
		} else if(t0 < 0 && t1 >=0) {
			t1 = sqrt((Point2[0]-P1[0])*(Point2[0]-P1[0]) + (Point2[1]-P1[1])*(Point2[1]-P1[1]) + (Point2[2]-P1[2])*(Point2[2]-P1[2]));
			//std::cout << t1 + FLT_EPSILON << std::endl;
			 return t1;
		} else if(t0 < 0 && t1< 0){
			return -1;
		} else {
			t0 = sqrt((Point1[0]-P1[0])*(Point1[0]-P1[0]) + (Point1[1]-P1[1])*(Point1[1]-P1[1]) + (Point1[2]-P1[2])*(Point1[2]-P1[2]));
			t1 = sqrt((Point2[0]-P1[0])*(Point2[0]-P1[0]) + (Point2[1]-P1[1])*(Point2[1]-P1[1]) + (Point2[2]-P1[2])*(Point2[2]-P1[2]));
			//std::cout << min(t0,t1) + FLT_EPSILON << std::endl;
			return min(t0,t1) + FLT_EPSILON;
		}
	} 

	return -1;
}

double MyGLWidget::Test_RayPolyIntersect(glm::vec3 P0, glm::vec3 V0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::mat4 T) {
	// TODO fill this in so it calls your own ray-casting function.
	// See the documentation of this function in stubs.h.
	float t = 0.0f;
	float t0 = -1000.0f;
	glm::vec3 N;
	N[0] = 0; N[1] = 0; N[2] = 0;

	glm::vec4 V01(glm::inverse(T)*glm::vec4(V0,0));
	glm::vec4 P01(glm::inverse(T)*glm::vec4(P0,1));

	//V01 = glm::normalize(V01);
	
	float V0dir = sqrt(V01[0]*V01[0] + V01[1]*V01[1] + V01[2]*V01[2]);

	glm::vec3 Pf(P01[0],P01[1],P01[2]);

	float hp, hp1, hp2, hp3;
	float s, s1, s2, s3;
	float l1, l2, l3;
	float s1l1, s1l2, s1l3;
	float s2l1, s2l2, s2l3;
	float s3l1, s3l2, s3l3;

	glm::vec3 side1, side2, side3;
	glm::vec3 s1side1, s1side2, s1side3;
	glm::vec3 s2side1, s2side2, s2side3;
	glm::vec3 s3side1, s3side2, s3side3;

	glm::vec3 pt = p1;
	
	for (int i = 0; i < 3; i++) {
		side1[i] = p2[i] - p1[i];
		side2[i] = p3[i] - p2[i];
		side3[i] = p1[i] - p3[i];
	}

	l1 = sqrt(side1[0]*side1[0] + side1[1]*side1[1] + side1[2]*side1[2]);
	l2 = sqrt(side2[0]*side2[0] + side2[1]*side2[1] + side2[2]*side2[2]);
	l3 = sqrt(side3[0]*side3[0] + side3[1]*side3[1] + side3[2]*side3[2]);

	glm::vec3 s1n = glm::normalize(side1);
	glm::vec3 s2n = glm::normalize(side2);
	
	hp = (l1+l2+l3)/2.0f;
	s = sqrt(hp*(hp-l1)*(hp-l2)*(hp-l3));
	
	glm::vec3 V02(V01[0],V01[1],V01[2]);
	V02 = glm::normalize(V02);

	glm::vec3 Pfn;
	Pfn[0] = Pf[0]+V02[0]*100.0f;
	Pfn[1] = Pf[1]+V02[1]*100.0f;
	Pfn[2] = Pf[2]+V02[2]*100.0f;

	if(s1n!=s2n){
		glm::vec3 N = glm::cross(s1n, s2n);
		t =(float) (glm::dot(N,(p1-Pf)))/(glm::dot(N,(Pf-Pfn)));
		glm::vec3 P = Pf+t*(Pf-Pfn);
		t = t * (-100);

		glm::vec3 ps1,ps2,ps3;
		for (int i = 0; i < 3; i++) {
			ps1[i] = P[i] - p1[i];
			ps2[i] = p2[i] - P[i];
			ps3[i] = p3[i] - P[i];
		}
		s1l1 = glm::length(ps1);
		s1l2 = glm::length(ps2);
		s1l3 = l1;
		float s1l4 = glm::length(ps3);
			
		s2l1 = glm::length(s1l2);
		s2l2 = glm::length(s1l4);
		s2l3 = l2;

		s3l1 = glm::length(s1l4);
		s3l2 = glm::length(s1l1);
		s3l3 = l3;

		hp1 = (s1l1 + s1l2 + s1l3)/2.0f;
		s1 = sqrt(hp1*(hp1-s1l1)*(hp1-s1l2)*(hp1-s1l3));

		hp2 = (s2l1 + s2l2 + s2l3)/2.0f;
		s2 = sqrt(hp2*(hp2-s2l1)*(hp2-s2l2)*(hp2-s2l3));

		hp3 = (s3l1 + s3l2 + s3l3)/2.0f;
		s3 = sqrt(hp3*(hp3-s3l1)*(hp3-s3l2)*(hp3-s3l3));
		//
		float eps = 0.0001f;
		if(abs(s1+s2+s3 - s) < eps) {
			if (t0 < t) {
				if (t >= 0) {
					glm::vec4 P01f((Pf+t*glm::vec3(V01[0],V01[1],V01[2])),1);
					P01f = T*P01f;
					Pf = glm::vec3(P01f[0],P01f[1],P01f[2]);
					t = sqrt((Pf[0]-P0[0])*(Pf[0]-P0[0])+(Pf[1]-P0[1])*(Pf[1]-P0[1])+(Pf[2]-P0[2])*(Pf[2]-P0[2]));
					t0 = t + FLT_EPSILON;
					return t0;
				} else return -1;
			}
		}

	}

	return -1;
}

double MyGLWidget::Test_RayCubeIntersect(glm::vec3 P1, glm::vec3 V1, glm::mat4 T1) {
	// TODO fill this in so it calls your own ray-casting function.
	// See the documentation of this function in stubs.h.
	

	glm::mat4 T = glm::inverse(T1);
	//T = glm::transpose(T);

	glm::vec4 P0 = glm::vec4(P1,1);
	P0 = P0*T;

	glm::vec4 V0 = glm::vec4(V1,0);
	V0 = V0*T;

	glm::vec3 Bl = glm::vec3(-0.5f, -0.5f, -0.5f);
	glm::vec3 Bh = glm::vec3(0.5f, 0.5f, 0.5f);
	//V0 = glm::normalize(V0);
	float Tnear = - 100;
	float Tfar = 100;
	if(V0[0] == 0) {
		if (P0[0] < Bl[0] || P0[0] > Bh[0]) {
			return -1;
			//no intersection
		}
	} else {
		float T1 = (Bl[0] - P0[0])/V0[0];
		float T2 = (Bh[0] - P0[0])/V0[0];
		if( T1 > T2) {
			float temp = T1;
			T1 = T2;
			T2 = temp;
		}
		if( T1 > Tnear) Tnear = T1;
		if( T2 < Tfar) Tfar = T2;
		if( Tnear > Tfar) {
			return -1;
			// no intersection
		}
		if( Tfar < 0) {
			return -1;
			// no intersection
		}
	}

	if(V0[1] == 0) {
		if (P0[1] < Bl[1] || P0[1] > Bh[1]) {
			return -1;
			//no intersection
		}
	} else {
		float T1 = (Bl[1] - P0[1])/V0[1];
		float T2 = (Bh[1] - P0[1])/V0[1];
		if( T1 > T2) {
			float temp = T1;
			T1 = T2;
			T2 = temp;
		}
		if( T1 > Tnear) Tnear = T1;
		if( T2 < Tfar) Tfar = T2;
		if( Tnear > Tfar) {
			return -1;
			// no intersection
		}
		if( Tfar < 0) {
			return -1;
			// no intersection
		}
	}
	
	if(V0[2] == 0) {
		if (P0[2] < Bl[2] || P0[2] > Bh[2]) {
			return -1;
			//no intersection
		}
	} else {
		float T1 = (Bl[2] - P0[2])/V0[2];
		float T2 = (Bh[2] - P0[2])/V0[2];
		if( T1 > T2) {
			float temp = T1;
			T1 = T2;
			T2 = temp;
		}
		if( T1 > Tnear) Tnear = T1;
		if( T2 < Tfar) Tfar = T2;
		if( Tnear > Tfar) {
			return -1;
			// no intersection
		}
		if( Tfar < 0) {
			return -1;
			// no intersection
		}
	}

	glm::vec3 Point1 = glm::vec3(P0[0],P0[1],P0[2]) + Tnear*glm::vec3(V0[0],V0[1],V0[2]);
	glm::vec3 Point2 = glm::vec3(P0[0],P0[1],P0[2]) + Tfar*glm::vec3(V0[0],V0[1],V0[2]);
	glm::vec4 Point14 = glm::vec4(Point1,1);
	glm::vec4 Point24 = glm::vec4(Point2,1);
	Point14 = T1*Point14;
	Point24 = T1*Point24;
	Point1 = glm::vec3(Point14[0],Point14[1],Point14[2]);
	Point2 = glm::vec3(Point24[0],Point24[1],Point24[2]);
	Tnear = sqrt((Point1[0]-P1[0])*(Point1[0]-P1[0]) + (Point1[1]-P1[1])*(Point1[1]-P1[1]) + (Point1[2]-P1[2])*(Point1[2]-P1[2]));
	Tfar = sqrt((Point2[0]-P1[0])*(Point2[0]-P1[0]) + (Point2[1]-P1[1])*(Point2[1]-P1[1]) + (Point2[2]-P1[2])*(Point2[2]-P1[2]));

	if(Tnear < 0 && Tfar >= 0) {
		//std::cout << Tfar+ FLT_EPSILON << std::endl;
		return Tnear+ FLT_EPSILON;
	} else if (Tnear >= 0 && Tfar <0) {
		//std::cout << Tnear+ FLT_EPSILON << std::endl;
		return Tnear+ FLT_EPSILON;
	} else if (Tnear <0 && Tfar < 0) {
		return -1;
	} else {
		//std::cout << min(Tnear,Tfar) + FLT_EPSILON << std::endl;
		return min(Tnear,Tfar)+ FLT_EPSILON;
	}
	return -1;
}

double MyGLWidget::Test_RayCylinderIntersect(glm::vec3 P1, glm::vec3 V1, glm::mat4 T1) {
	// TODO fill this in so it calls your own ray-casting function.
	// See the documentation of this function in stubs.h.

	glm::mat4 T = glm::inverse(T1);
	//T = glm::transpose(T);

	glm::vec3 B0 = glm::vec3(0,-0.5f,0);
	glm::vec3 B1 = glm::vec3(0,0.5f,0);

	glm::vec4 V2 = glm::vec4(V1,0);
	V2 = V2*T;
	glm::vec3 V0 = glm::vec3(V2[0],V2[1],V2[2]);
	float dist = sqrt(V0[0]*V0[0] + V0[1]*V0[1] + V0[2]*V0[2]);
	//V0 = glm::normalize(V0);

	glm::vec4 P2 = glm::vec4(P1,1);
	P2 = P2*T; /// I FLIPPED THE MULTIPLICATION! CHNAGE BACK IF SHIT HAPPENS! here and Sphere (Original P2*T, Correct? T*P2)

	glm::vec3 P0 = glm::vec3(P2[0],P2[1],P2[2]);

	float R = 0.5f;

	float A = V0[0]*V0[0] + V0[2]*V0[2];
	float B = (P0[0] - B0.x)*V0[0] + (P0[2] - B0.z)*V0[2];
	float C = (P0[0] - B0.x)*(P0[0] - B0.x) + (P0[2] - B0.z)*(P0[2] - B0.z) - R*R;

	float bigNum = 1000;
	float in1 = bigNum;
	float in2 = bigNum;
	float in3 = bigNum;
	float in4 = bigNum;

	float disc = B*B - A*C;
	float t1 = bigNum;
	float t2 = bigNum;
	float n = 1;
	if(disc >= 0) {
		if(glm::abs(A) > 0) {
			t1 = (-B-sqrt(B*B - A*C))/A;
			t2 = (-B+sqrt(B*B - A*C))/A;
		}
		float uplim = 1;
		float lowlim = 0;
		float yHit = P0[1]+V0[1]*t1;
		if(t1 >= 0 && yHit <= uplim && yHit >= lowlim) {
			// intersect
			n += 1;
			in1 = t1;
		}
		yHit = P0[1]+V0[1]*t2;
		if(t2 >= 0 && yHit <= uplim && yHit >= lowlim) {
			// intersect
			n += 1;
			in2 = t2;
		}
	} 

	glm::vec3 Point1 = P0 + in1*V0;
	glm::vec3 Point2 = P0 + in2*V0;
	glm::vec4 Point14 = glm::vec4(Point1,1);
	glm::vec4 Point24 = glm::vec4(Point2,1);
	Point14 = T1*Point14;
	Point24 = T1*Point24;
	Point1 = glm::vec3(Point14[0],Point14[1],Point14[2]);
	Point2 = glm::vec3(Point24[0],Point24[1],Point24[2]);
	in1 = sqrt((Point1[0]-P1[0])*(Point1[0]-P1[0]) + (Point1[1]-P1[1])*(Point1[1]-P1[1]) + (Point1[2]-P1[2])*(Point1[2]-P1[2]));
	in2 = sqrt((Point2[0]-P1[0])*(Point2[0]-P1[0]) + (Point2[1]-P1[1])*(Point2[1]-P1[1]) + (Point2[2]-P1[2])*(Point2[2]-P1[2]));

	//caps
	float tb = bigNum;
	float tc = bigNum;
	tb = (B0.y - P0[1])/V0[1];
	tc = (B1.y - P0[1])/V0[1];
	glm::vec3 I1 = P0 + tb*V0;
	glm::vec3 I2 = P0 + tc*V0;
	if( I1[0]*I1[0] + I1[2]*I1[2] < R*R) {
		n += 1;
		in3 = tb;
	}
	if( I2[0]*I2[0] + I2[2]*I2[2] < R*R) {
		n += 1;
		in4 = tc;
	}

	Point1 = P0 + in3*V0;
	Point2 = P0 + in4*V0;
	Point14 = glm::vec4(Point1,1);
	Point24 = glm::vec4(Point2,1);
	Point14 = T1*Point14;
	Point24 = T1*Point24;
	Point1 = glm::vec3(Point14[0],Point14[1],Point14[2]);
	Point2 = glm::vec3(Point24[0],Point24[1],Point24[2]);
	in3 = sqrt((Point1[0]-P1[0])*(Point1[0]-P1[0]) + (Point1[1]-P1[1])*(Point1[1]-P1[1]) + (Point1[2]-P1[2])*(Point1[2]-P1[2]));
	in4 = sqrt((Point2[0]-P1[0])*(Point2[0]-P1[0]) + (Point2[1]-P1[1])*(Point2[1]-P1[1]) + (Point2[2]-P1[2])*(Point2[2]-P1[2]));

	in1 += FLT_EPSILON;
	in2 += FLT_EPSILON;
	in3 += FLT_EPSILON;
	in4 += FLT_EPSILON;

	if(n > 2) {
		float t = 0;
		t = min(in1, in2); 
		t = min(t, in3);
		t = min(t, in4);
		//std::cout << t << std::endl;
		return t;
	} else {
		return -1;
		// no intersection
	}

	return -1;
}

glm::vec3 MyGLWidget::TraceRay(glm::vec3 E, glm::vec3 D, int depth, glm::vec3 color) {
	
	vector<float> tempd = vector<float>();
	vector<float> temps = vector<float>();
	vector<float> tempn = vector<float>();
	vector<float> tempa = vector<float>();
	for (int i = 0; i < graph->objects->size(); i++) {
		tempd.push_back(0.5f); 
		temps.push_back(0); 
		tempn.push_back(0.25f);
		tempa.push_back(0.5f); 
	}
	vector<float> Kd = tempd;		
	vector<float> Ks= temps;		 
	vector<float> Kn= tempn;		 
	vector<float> Kt;		 
	vector<float> Ka= tempa;		
	vector<float> Kr;//= tempa;
	glm::vec3 ambient = glm::vec3(0.2f,0.2f,0.2f);

	glm::vec3 ReflectedDirection;
	glm::vec3 RefractedDirection;
	glm::vec3 TransmittedDirection;

	glm::vec3 spec;
	glm::vec3 ReflectedColor;
	glm::vec3 refr;
	glm::vec3 RefractedColor;
	glm::vec3 trans;
	glm::vec3 TransmittedColor;
	
	glm::vec3 BackgroundColor = glm::vec3(0,0,0);

	int MaxDepth = 1;
	if(depth > MaxDepth) {
		color = BackgroundColor;
		return color;
	}

	int object_index = -1;
	vector<Node*>* object_list = graph->objects;
	Node* closest_node;
	double closest_t = 1000;
	glm::vec3 intersectionPoint;
	glm::mat4 PtoLocal = glm::mat4();

	if(glm::abs(glm::length(D - VDIR)) < 0.001f) {
		cout << endl;
	}
	for(int i = 0; i < object_list->size(); i++) {
		Node* node = object_list->at(i);
		///finish the calls for intersections
		if(node->ge == 0) {
			float t = (float) this->Test_RayCubeIntersect(E,D,node->fcube);
			if (t != -1) {
				cout << "floor is lava" << endl;
			}
			if(t < closest_t && t >= 0) {
				closest_t = t;
				closest_node = node;
				object_index = i;
				node->defaultID = 0;
				PtoLocal = node->fcube;
			}
		} else if(node->ge == 1) {
			float t = (float) this->Test_RayCubeIntersect(E,D,node->tleg1);
			if(t < closest_t && t >= 0) {
				closest_t = t;
				closest_node = node;
				object_index = i;
				node->defaultID = 0;
				PtoLocal = node->tleg1;
			}
			t = (float) this->Test_RayCubeIntersect(E,D,node->tleg2);
			if(t < closest_t && t >= 0) {
				closest_t = t;
				closest_node = node;
				object_index = i;
				node->defaultID = 1;
				PtoLocal = node->tleg2;
			}
			t = (float) this->Test_RayCubeIntersect(E,D,node->tleg3);
			if(t < closest_t && t >= 0) {
				closest_t = t;
				closest_node = node;
				object_index = i;
				node->defaultID = 2;
				PtoLocal = node->tleg3;
			}
			t = (float) this->Test_RayCubeIntersect(E,D,node->tleg4);
			if(t < closest_t && t >= 0) {
				closest_t = t;
				closest_node = node;
				object_index = i;
				node->defaultID = 3;
				PtoLocal = node->tleg4;
			}
			t = (float) this->Test_RayCylinderIntersect(E,D,node->ttop);
			if(t < closest_t && t >= 0) {
				closest_t = t;
				closest_node = node;
				object_index = i;
				node->defaultID = 4;
				PtoLocal = node->ttop;
			}
		} else if(node->ge == 3) {
			float t = (float) this->Test_RayCubeIntersect(E,D,node->cbody);
			if(t < closest_t && t >= 0) {
				closest_t = t;
				closest_node = node;
				object_index = i;
				node->defaultID = 0;
				PtoLocal = node->cbody;
			}
			t = (float) this->Test_RayCubeIntersect(E,D,node->cdoor);
			if(t < closest_t && t >= 0) {
				closest_t = t;
				closest_node = node;
				object_index = i;
				node->defaultID = 1;
				PtoLocal = node->cdoor;
			}
		} else if(node->ge == 4) {
			float t = (float) this->Test_RayCylinderIntersect(E,D,node->lstand);
			if(t != -1) {
			//	cout << "hit cylinder" << endl;
			}
			if(t < closest_t && t >= 0) {
				closest_t = t;
				closest_node = node;
				object_index = i;
				node->defaultID = 0;
				PtoLocal = node->lstand;
			}
			t = (float) this->Test_RaySphereIntersect(E,D,node->ltop);
			if(t != -1) {
				cout << "hit sphere" << endl;
			}
			if(t < closest_t && t >= 0) {
				closest_t = t;
				closest_node = node;
				object_index = i;
				node->defaultID = 1;
				PtoLocal = node->ltop;
			}
		} else if(node->ge == 2) {
			float t = (float) this->Test_RayCubeIntersect(E,D,node->cleg1);
			if(t < closest_t && t >= 0) {
				closest_t = t;
				closest_node = node;
				object_index = i;
				node->defaultID = 0;
				PtoLocal = node->cleg1;
			}
			t = (float) this->Test_RayCubeIntersect(E,D,node->cleg2);
			if(t < closest_t && t >= 0) {
				closest_t = t;
				closest_node = node;
				object_index = i;
				node->defaultID = 1;
				PtoLocal = node->cleg2;
			}
			t = (float) this->Test_RayCubeIntersect(E,D,node->cleg3);
			if(t < closest_t && t >= 0) {
				closest_t = t;
				closest_node = node;
				object_index = i;
				node->defaultID = 2;
				PtoLocal = node->cleg3;
			}
			t = (float) this->Test_RayCubeIntersect(E,D,node->cleg4);
			if(t < closest_t && t >= 0) {
				closest_t = t;
				closest_node = node;
				object_index = i;
				node->defaultID = 3;
				PtoLocal = node->cleg4;
			}
			t = (float) this->Test_RayCubeIntersect(E,D,node->cseat);
			if(t < closest_t && t >= 0) {
				closest_t = t;
				closest_node = node;
				object_index = i;
				node->defaultID = 4;
				PtoLocal = node->cseat;
			}
			t = (float) this->Test_RayCubeIntersect(E,D,node->cback);
			if(t < closest_t && t >= 0) {
				closest_t = t;
				closest_node = node;
				object_index = i;
				node->defaultID = 5;
				PtoLocal = node->cback;
			}
		} else if(node->ge == 5) {

		}
	}
	glm::vec4 E1 = glm::vec4(E,1);
	E1 = glm::inverse(PtoLocal)*E1;
	glm::vec4 D1 = glm::vec4(D,0);
	D1 = glm::inverse(PtoLocal)*D1;
	glm::vec4 ipl = E1 + closest_t*D1;
	glm::vec4 ip = PtoLocal*ipl;
	intersectionPoint = glm::vec3(ip.x,ip.y,ip.z);
	glm::vec3 intersectionPointLocal = glm::vec3(ipl.x,ipl.y,ipl.z);
	////intersectionPoint = E + glm::vec3(D.x*closest_t,D.y*closest_t,D.z*closest_t);
	//glm::vec4 interPoint = glm::vec4(intersectionPoint,1);
	//glm::vec3 intersectionPointLocal = glm::vec3((glm::inverse(PtoLocal)*interPoint).x,(glm::inverse(PtoLocal)*interPoint).y,(glm::inverse(PtoLocal)*interPoint).z);

	vector<glm::vec3> list_of_lights;
	list_of_lights.push_back(glm::vec3(LPOS[0],LPOS[1],LPOS[2]));
	vector<glm::vec3> list_of_light_colors;
	list_of_light_colors.push_back(glm::vec3(LCOL[0],LCOL[1],LCOL[2]));

	if(closest_t == 1000) {
		bool parallel_to_light = false;
		for(int i = 0; i < list_of_lights.size(); i++) {
			glm::vec3 lightPosition = list_of_lights[i];
			if(glm::cross(D,lightPosition) == glm::vec3(0)) {
				color = list_of_light_colors[i];
				parallel_to_light = true;
				break;
			}
		}
		if(!parallel_to_light) {
			color = BackgroundColor;
		}
	} else {

		//reflection + refraction

		glm::vec3 normal = computeNormal(closest_node, intersectionPointLocal);
		if(closest_node->ge == 4) {
			glm::vec4 normal4 = glm::vec4(normal,0);
			normal = glm::vec3((glm::transpose(PtoLocal)*normal4).x,(glm::transpose(PtoLocal)*normal4).y,(glm::transpose(PtoLocal)*normal4).z);
		} else {
			glm::vec4 normal4 = glm::vec4(normal,0);
			normal = glm::vec3((PtoLocal*normal4).x,(PtoLocal*normal4).y,(PtoLocal*normal4).z);
		}
		/*if(Ks[object_index] > 0) {
			ReflectedDirection = glm::reflect(D,normal);
			ReflectedColor = traceRay(intersectionPoint,ReflectedDirection,depth+1,ReflectedColor);
			spec = Ks[object_index]*ReflectedColor;
		} else {
			spec = glm::vec3(0);
		}
		if(Kt[object_index] >0 ) {
			float index_of_refr1;
			float index_of_refr2;
			float refr_ratio = index_of_refr1/index_of_refr2;
			RefractedDirection = glm::refract(D,normal,refr_ratio);
			RefractedColor = traceRay(intersectionPoint,RefractedDirection,depth+1,RefractedColor);
			refr = Kt[object_index]*RefractedColor;
		} else {
			refr = glm::vec3(0);
		}*/
		
		//shadows
		//if(checkInside(E,closest_node)) {
			//color = glm::vec3(0,0,0);
		//} else {
			glm::vec3 C = glm::vec3(closest_node->colorRGB[0],closest_node->colorRGB[1],closest_node->colorRGB[2]);
			if(C[1] == 1) {
				cout << endl;
			}
			//C = glm::vec3(0.5f,0.5f,0.5f);
			color = Ka[object_index]*ambient*C + refr;
			glm::vec3 cRGB = glm::vec3(closest_node->colorRGB[0],closest_node->colorRGB[1],closest_node->colorRGB[2]);
			//color = cRGB;
			//color = ambient*C;
			spec = glm::vec3(0,0,0);
			//color = glm::vec3(0,0,0);
			for(int i = 0; i < list_of_lights.size(); i++) {
				if(!ShadowRayUnblocked(intersectionPoint,list_of_lights[i])) {
					/*float dotpr = glm::dot(normal,list_of_lights[i]);
					glm::vec3 col1= C*dotpr;
					glm::vec3 col2 = Kd[object_index]*col1;
					glm::vec3 col3 = list_of_light_colors[i]*col2;
					glm::vec3 col4 = ReflectedRay(list_of_lights[i],normal,intersectionPoint);
					float col5 = glm::abs(glm::dot(col4,E));
					float col6 = glm::pow(col5,Kn[object_index]);
					glm::vec3 col7 = spec*col6;*/
					color += list_of_light_colors[i]*(Kd[object_index]*C*(glm::dot(normal,list_of_lights[i])
						+ spec*glm::pow(glm::abs(glm::dot(ReflectedRay(list_of_lights[i],normal,intersectionPoint),E)),Kn[object_index])));
					//color = glm::vec3(0,1,0);
				//} else {
					//color = glm::vec3(0,0,0);
					//color += list_of_light_colors[i]*(C*(glm::dot(normal,list_of_lights[i])));
				} else {
					cout << endl;
				}
				//cout << glm::dot(normal,list_of_lights[i]) << endl;
				//color += list_of_light_colors[i]*(C*(glm::dot(normal,list_of_lights[i])));
			}
		//}

	}

	return color;
}