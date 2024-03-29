#include "tests.h"
#include "stubs.h"
#include "../glm/glm.hpp"

#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

using namespace glm;

void RunRaySphereTests();
void RunRayPolyTests();
void RunRayCubeTests();
void RunRayCylinderTests();
void RunYourTests();
void RunOurTests();

typedef bool (*TestFunc)();

int g_numTests = 0;
int g_numSuccessful = 0;

void ReportTest(std::string name, bool result);

template<typename T>
void RunTest(std::string name, T const& testValue, T const& expectedValue) {
	ReportTest(name, testValue == expectedValue);
}

template<>
void RunTest<double>(std::string name, double const& testValue, double const& expectedValue) {
	ReportTest(name, (std::abs(testValue-expectedValue) / std::abs(expectedValue)) < 1e-3);
}

void RunTests() {
	std::cout.sync_with_stdio(true);

	RunRaySphereTests();
	RunRayPolyTests();
	RunRayCubeTests();
	RunRayCylinderTests();
	RunYourTests();
	RunOurTests();

	std::cout << g_numSuccessful << " of " << g_numTests << " tests successful. ";
	if(g_numTests == g_numSuccessful) {
		std::cout << "A winner is you!";
	}
	std::cout << std::endl;
}

const double SQRT_HALF = 0.70710678; // square root of one half
const double SQRT_TWO = 1.41421356; // figure it out

const mat4 IDENTITY_MATRIX = mat4();
const mat4 DOUBLE_MATRIX(vec4(2.0f, 0.0f, 0.0f, 0.0f),
                         vec4(0.0f, 2.0f, 0.0f, 0.0f),
                         vec4(0.0f, 0.0f, 2.0f, 0.0f),
                         vec4(0.0f, 0.0f, 0.0f, 1.0f));
const mat4 TALLANDSKINNY_MATRIX(vec4(0.5f, 0.0f, 0.0f, 0.0f),
								vec4(0.0f, 2.0f, 0.0f, 0.0f),
								vec4(0.0f, 0.0f, 0.5f, 0.0f),
								vec4(0.0f, 0.0f, 0.0f, 1.0f));
const mat4 BACK5_MATRIX(vec4(1.0f, 0.0f, 0.0f, 0.0f),
                        vec4(0.0f, 1.0f, 0.0f, 0.0f),
                        vec4(0.0f, 0.0f, 1.0f, 0.0f),
                        vec4(0.0f, 0.0f, -5.0f, 1.0f));
const mat4 BACK5ANDTURN_MATRIX(vec4(SQRT_HALF, 0.0f, -SQRT_HALF, 0.0f),
                                  vec4(0.0f, 1.0f, 0.0f, 0.0f),
                                  vec4(SQRT_HALF, 0.0f, SQRT_HALF, 0.0f),
                                  vec4(0.0f, 0.0f, -5.0f, 1.0f));


const vec3 ZERO_VECTOR(0.0f, 0.0f, 0.0f);
const vec3 HALFX_VECTOR(0.5f, 0.0f, 0.0f);
const vec3 THIRDX_VECTOR(0.33333333333333333f, 0.0f, 0.0f);
const vec3 NEGX_VECTOR(-1.0f, 0.0f, 0.0f);
const vec3 NEGZ_VECTOR(0.0f, 0.0f, -1.0f);
const vec3 NEGY_VECTOR(0.0f, -1.0f, 0.0f);
const vec3 POSZ_VECTOR(0.0f, 0.0f, 1.0f);
const vec3 POSXPOSZ_VECTOR(1.0f, 0.0f, 1.0f);
const vec3 ZNEGTEN_VECTOR(0.0f, 0.0f, -10.0f);
const vec3 ZPOSTEN_VECTOR(0.0f, 0.0f, 10.0f);
const vec3 YPOSTEN_VECTOR(0.0f, 10.0f, 0.0f);
const vec3 XPOSTEN_VECTOR(10.0f, 0.0f, 0.0f);
const vec3 POSXNEGZ_NORM_VECTOR(SQRT_HALF, 0.0f, -SQRT_HALF);
const vec3 NEGFIVEOFIVE_VECTOR(-5.0f, 0.0f, 5.0f);

const vec3 POINT_N1N10(-1.0f, -1.0f, 0.0f);
const vec3 POINT_1N10(1.0f, -1.0f, 0.0f);
const vec3 POINT_010(0.0f, 1.0f, 0.0f);
const vec3 POINT_N2N10(-2.0f, -1.0f, 0.0f);
const vec3 POINT_2N10(2.0f, -1.0f, 0.0f);

const double TEN_KAZILLION = 1e26;

void RunRaySphereTests() {
	RunTest(
		"Easy sphere",
		Test_RaySphereIntersect(ZERO_VECTOR, NEGZ_VECTOR, BACK5_MATRIX),
		4.0);

	RunTest(
		"Offset a bit",
		Test_RaySphereIntersect(HALFX_VECTOR, NEGZ_VECTOR, BACK5_MATRIX),
		4.13397);

	RunTest(
		"What sphere",
		Test_RaySphereIntersect(ZNEGTEN_VECTOR, NEGZ_VECTOR, BACK5_MATRIX),
		-1.0);

	RunTest(
		"Looking back",
		Test_RaySphereIntersect(ZNEGTEN_VECTOR, POSZ_VECTOR, BACK5_MATRIX),
		4.0); // TODO change this to the right number

	RunTest(
		"West pole",
		Test_RaySphereIntersect(ZERO_VECTOR, NEGZ_VECTOR, BACK5ANDTURN_MATRIX),
		4.0);

	RunTest(
		"Another angle",
		Test_RaySphereIntersect(NEGFIVEOFIVE_VECTOR, POSXNEGZ_NORM_VECTOR, IDENTITY_MATRIX),
		(5.0 * SQRT_TWO) - 1);
}

void RunRayPolyTests() {
	RunTest(
		"Hi, Tri",
		Test_RayPolyIntersect(POSZ_VECTOR, NEGZ_VECTOR, POINT_N1N10, POINT_1N10, POINT_010, IDENTITY_MATRIX),
		1.0);

	RunTest(
		"Bye, Tri",
		Test_RayPolyIntersect(POSXPOSZ_VECTOR, NEGZ_VECTOR, POINT_N1N10, POINT_1N10, POINT_010, IDENTITY_MATRIX),
		-1.0);

	RunTest(
		"Looking back",
		Test_RayPolyIntersect(POSZ_VECTOR, POSZ_VECTOR, POINT_N1N10, POINT_1N10, POINT_010, IDENTITY_MATRIX),
		-1.0);

	RunTest(
		"Flip it good",
		Test_RayPolyIntersect(POSZ_VECTOR, NEGZ_VECTOR, POINT_010, POINT_1N10, POINT_N1N10, IDENTITY_MATRIX),
		1.0);

	RunTest(
		"It moves",
		Test_RayPolyIntersect(ZERO_VECTOR, NEGZ_VECTOR, POINT_N1N10, POINT_1N10, POINT_010, BACK5ANDTURN_MATRIX),
		5.0);

	RunTest(
		"And turns",
		Test_RayPolyIntersect(HALFX_VECTOR, NEGZ_VECTOR, POINT_N2N10, POINT_2N10, POINT_010, BACK5ANDTURN_MATRIX),
		5.5); // TODO change this to the right number
}

void RunRayCubeTests() {
	RunTest(
		"Behold the cube",
		Test_RayCubeIntersect(ZERO_VECTOR, NEGZ_VECTOR, BACK5_MATRIX),
		4.5);

	RunTest(
		"The cube abides",
		Test_RayCubeIntersect(THIRDX_VECTOR, NEGZ_VECTOR, BACK5_MATRIX),
		4.5);

	RunTest(
		"Cuuuube!",
		Test_RayCubeIntersect(NEGX_VECTOR, NEGZ_VECTOR, BACK5_MATRIX),
		-1.0);

	RunTest(
		"Looking sharp, edge",
		Test_RayCubeIntersect(ZERO_VECTOR, NEGZ_VECTOR, BACK5ANDTURN_MATRIX),
		5.0 - SQRT_HALF);

	RunTest(
		"Big cube",
		Test_RayCubeIntersect(ZPOSTEN_VECTOR, NEGZ_VECTOR, DOUBLE_MATRIX),
		9.0);

	RunTest(
		"Strafing the cube",
		Test_RayCubeIntersect(NEGFIVEOFIVE_VECTOR, POSXNEGZ_NORM_VECTOR, IDENTITY_MATRIX),
		4.5/SQRT_HALF); // TODO change this to the right number
}

void RunRayCylinderTests() {
	RunTest(
		"On the can",
		Test_RayCylinderIntersect(ZPOSTEN_VECTOR, NEGZ_VECTOR, IDENTITY_MATRIX), 
		9.5);

	RunTest(
		"Same difference",
		Test_RayCylinderIntersect(XPOSTEN_VECTOR, NEGX_VECTOR, IDENTITY_MATRIX),
		9.5);

	RunTest(
		"Can opener",
		Test_RayCylinderIntersect(YPOSTEN_VECTOR, NEGY_VECTOR, TALLANDSKINNY_MATRIX),
		9.0);

	RunTest(
		"Swing and a miss",
		Test_RayCylinderIntersect(ZERO_VECTOR, POSZ_VECTOR, BACK5_MATRIX),
		-1.0);

	RunTest(
		"Plink",
		Test_RayCylinderIntersect(ZERO_VECTOR, NEGZ_VECTOR, BACK5ANDTURN_MATRIX),
		4.5);
	
	RunTest(
		"DIY",
		Test_RayCylinderIntersect(POSXNEGZ_NORM_VECTOR, NEGFIVEOFIVE_VECTOR, DOUBLE_MATRIX),
		2.0);	//TODO change this to the right number
}

void RunYourTests() {
	// It can be very useful to put tests of your own here. The unit tests above do NOT test everything!
}

void RunOurTests() {
	// Leave this function alone; we'll put stuff in it for grading.
}

void ReportTest(std::string name, bool result) {
	std::cout << std::setfill('.') << std::setw(50) << std::left << name;
	std::cout << (result ? "SUCCESS" : "**FAILURE**") << std::endl;
	g_numTests++;
	if(result) {
		g_numSuccessful++;
	}
	else {
		// It can be very useful to put a breakpoint here
	}

}