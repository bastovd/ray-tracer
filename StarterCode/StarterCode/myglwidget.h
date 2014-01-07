#ifndef MYGLWIDGET
#define MYGLWIDGET

#include "glew.h"
#include <QGLWidget>
#include <QTimer>
#include "../glm/glm.hpp"
#include "qwidget.h"
#include <QKeyEvent>
#include "SceneGraph.h"
#include "EasyBMP.h"

class MyGLWidget : public QGLWidget {
private:
	//vertex arrays needed for drawing
	unsigned int vbo;
	unsigned int cbo;
	unsigned int nbo;
	unsigned int ibo;

	//attributes
	unsigned int positionLocation;
	unsigned int colorLocation;
	unsigned int normalLocation;

	//uniforms
	unsigned int u_modelMatrixLocation;
	unsigned int u_projMatrixLocation;
	
	//needed to compile and link and use the shaders
	unsigned int vertexShader;
	unsigned int fragmentShader;
	unsigned int shaderProgram;

	//Animation/transformation stuff
	QTimer* timer;
	float rotation;

	//helper function to read shader source and put it in a char array
	//thanks to Swiftless
	char* textFileRead(const char*);

	//some other helper functions from CIS 565
	void printLinkInfoLog(int);
	void printShaderInfoLog(int);

public:
	void readFile();

	MyGLWidget(QWidget*);
	~MyGLWidget(void);
	void initializeGL(void);
	void paintGL(void);
	void resizeGL(int, int);
	void makeFloor(glm::mat4);
	void makeCube(glm::mat4,vector<vector<float>>* ,float[3] );
	void makeSphere(glm::mat4,vector<vector<float>>* , float, float, float, float[3]);
	void makeCylinder(glm::mat4,vector<vector<float>>*, float, float, float, float[3] );
	void makeMesh(glm::mat4,Mesh* );
	void createRedSquare(glm::mat4);
	void createBlueSquare(glm::mat4);
	void keyPressEvent(QKeyEvent*);
	vector<unsigned short> SphereI(int,int);
	vector<unsigned short> CylinderI(int);
	void traverseSG(glm::mat4,Node*);
	bool traversePos(Node*,Node*);

	////bounding box////
	void initBB(int, Node* );
	void drawBB();

	///ray tracing//////////
	glm::vec3 TraceRay(glm::vec3, glm::vec3, int, glm::vec3);
	void raytracer();
	//float RayIntersect(Furniture);
	glm::vec3 computeNormal(Node*, glm::vec3);
	bool ShadowRayUnblocked(glm::vec3,glm::vec3);
	glm::vec3 ReflectedRay(glm::vec3,glm::vec3,glm::vec3);
	bool inside(glm::vec3, Node*);

	double Test_RaySphereIntersect(glm::vec3 P0, glm::vec3 V0, glm::mat4 T);
	double Test_RayPolyIntersect(glm::vec3 P0, glm::vec3 V0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::mat4 T);
	double Test_RayCubeIntersect(glm::vec3 P0, glm::vec3 V0, glm::mat4 T);
	double Test_RayCylinderIntersect(glm::vec3 P0, glm::vec3 V0, glm::mat4 T);
};

#endif