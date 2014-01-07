#include "stubs.h"
#include <iostream>
//#include "../glm/glm.hpp"

using namespace glm;

double Test_RaySphereIntersect(vec3 const& P0, vec3 const& V0, mat4 const& T) {
	// TODO fill this in so it calls your own ray-casting function.
	// See the documentation of this function in stubs.h.
	float t;
	float t0 = 1000.0f;
	float t1 = 1000.0f;
	vec3 N;
	N[0] = 0; N[1] = 0; N[2] = 0;

	vec4 V01(inverse(T)*vec4(V0,0));
	vec4 P01(inverse(T)*vec4(P0,1));

	V01 = normalize(V01);
	
	float V0dir = sqrt(V01[0]*V01[0] + V01[1]*V01[1] + V01[2]*V01[2]);

	float r = 1.0f;

	float A = V01[0]*V01[0] + V01[1]*V01[1] + V01[2]*V01[2];
	float B = 2 * (V01[0]*P01[0] + V01[1]*P01[1] + V01[2]*P01[2]);
	float C = P01[0]*P01[0] + P01[1]*P01[1] + P01[2]*P01[2] - r*r;

	if ((B*B - 4*C) < 0) return -1;
	else {
		t0 = (-B - sqrt(B*B - 4*C))/2;
		t1 = (-B + sqrt(B*B - 4*C))/2;

		vec3 Pf1 = vec3(P01[0], P01[1], P01[2]) + t0*vec3(V01[0],V01[1],V01[2]);
		vec3 Pf2 = vec3(P01[0], P01[1], P01[2]) + t1*vec3(V01[0],V01[1],V01[2]);

		vec4 Pfn1 = T*vec4(Pf1,1);
		vec4 Pfn2 = T*vec4(Pf2,1);

		Pf1 = vec3(Pfn1[0],Pfn1[1],Pfn1[2]);
		Pf2 = vec3(Pfn2[0],Pfn2[1],Pfn2[2]);
		if (t0 < 0 && t1 < 0) return -1;
		else if (t0 < 0 && t1 >= 0) {
			t1 = sqrt((Pfn2[0]-P0[0])*(Pfn2[0]-P0[0]) + (Pfn2[1]-P0[1])*(Pfn2[1]-P0[1]) + (Pfn2[2]-P0[2])*(Pfn2[2]-P0[2]));
			t = t1 + FLT_EPSILON;
		} else if (t0 >= 0 && t1 < 0) {
			t0 = sqrt((Pfn1[0]-P0[0])*(Pfn1[0]-P0[0]) + (Pfn1[1]-P0[1])*(Pfn1[1]-P0[1]) + (Pfn1[2]-P0[2])*(Pfn1[2]-P0[2]));
			t = t0 + FLT_EPSILON;
		} else {
			t0 = sqrt((Pfn1[0]-P0[0])*(Pfn1[0]-P0[0]) + (Pfn1[1]-P0[1])*(Pfn1[1]-P0[1]) + (Pfn1[2]-P0[2])*(Pfn1[2]-P0[2]));
			t1 = sqrt((Pfn2[0]-P0[0])*(Pfn2[0]-P0[0]) + (Pfn2[1]-P0[1])*(Pfn2[1]-P0[1]) + (Pfn2[2]-P0[2])*(Pfn2[2]-P0[2]));
			t = min(t0,t1) + FLT_EPSILON;
		}
		return t;
	}
	
	return -1;
}

double Test_RayPolyIntersect(vec3 const& P0, vec3 const& V0, vec3 const& p1, vec3 const& p2, vec3 const& p3, mat4 const& T) {
	// TODO fill this in so it calls your own ray-casting function.
	// See the documentation of this function in stubs.h.
	float t = 0.0f;
	float t0 = -1000.0f;
	vec3 N;
	N[0] = 0; N[1] = 0; N[2] = 0;

	vec4 V01(inverse(T)*vec4(V0,0));
	vec4 P01(inverse(T)*vec4(P0,1));

	V01 = normalize(V01);
	
	float V0dir = sqrt(V01[0]*V01[0] + V01[1]*V01[1] + V01[2]*V01[2]);

	vec3 Pf(P01[0],P01[1],P01[2]);

	float hp, hp1, hp2, hp3;
	float s, s1, s2, s3;
	float l1, l2, l3;
	float s1l1, s1l2, s1l3;
	float s2l1, s2l2, s2l3;
	float s3l1, s3l2, s3l3;

	vec3 side1, side2, side3;
	vec3 s1side1, s1side2, s1side3;
	vec3 s2side1, s2side2, s2side3;
	vec3 s3side1, s3side2, s3side3;

	vec3 pt = p1;
	
	for (int i = 0; i < 3; i++) {
		side1[i] = p2[i] - p1[i];
		side2[i] = p3[i] - p2[i];
		side3[i] = p1[i] - p3[i];
	}

	l1 = sqrt(side1[0]*side1[0] + side1[1]*side1[1] + side1[2]*side1[2]);
	l2 = sqrt(side2[0]*side2[0] + side2[1]*side2[1] + side2[2]*side2[2]);
	l3 = sqrt(side3[0]*side3[0] + side3[1]*side3[1] + side3[2]*side3[2]);

	vec3 s1n = normalize(side1);
	vec3 s2n = normalize(side2);
	
	hp = (l1+l2+l3)/2.0f;
	s = sqrt(hp*(hp-l1)*(hp-l2)*(hp-l3));
	
	vec3 V02(V01[0],V01[1],V01[2]);
	V02 = normalize(V02);

	vec3 Pfn;
	Pfn[0] = Pf[0]+V02[0]*100.0f;
	Pfn[1] = Pf[1]+V02[1]*100.0f;
	Pfn[2] = Pf[2]+V02[2]*100.0f;

	if(s1n!=s2n){
		vec3 N = cross(s1n, s2n);
		t =(float) (dot(N,(p1-Pf)))/(dot(N,(Pf-Pfn)));
		vec3 P = Pf+t*(Pf-Pfn);
		t = t * (-100);

		vec3 ps1,ps2,ps3;
		for (int i = 0; i < 3; i++) {
			ps1[i] = P[i] - p1[i];
			ps2[i] = p2[i] - P[i];
			ps3[i] = p3[i] - P[i];
		}
		s1l1 = length(ps1);
		s1l2 = length(ps2);
		s1l3 = l1;
		float s1l4 = length(ps3);
			
		s2l1 = length(s1l2);
		s2l2 = length(s1l4);
		s2l3 = l2;

		s3l1 = length(s1l4);
		s3l2 = length(s1l1);
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
					vec4 P01f((Pf+t*vec3(V01[0],V01[1],V01[2])),1);
					P01f = T*P01f;
					Pf = vec3(P01f[0],P01f[1],P01f[2]);
					t = sqrt((Pf[0]-P0[0])*(Pf[0]-P0[0])+(Pf[1]-P0[1])*(Pf[1]-P0[1])+(Pf[2]-P0[2])*(Pf[2]-P0[2]));
					t0 = t + FLT_EPSILON;
					return t0;
				} else return -1;
			}
		}

	}

	return -1;
}

double Test_RayCubeIntersect(vec3 const& P0, vec3 const& V0, mat4 const& T) {
	// TODO fill this in so it calls your own ray-casting function.
	// See the documentation of this function in stubs.h.
	double t = 1000.0f;
	vec3 N;
	N[0] = 0; N[1] = 0; N[2] = 0;
	mat4 InverseMat = inverse(T);
	vec3 V01(inverse(T)*vec4(V0,0));
	V01 = normalize(V01);
	vec3 P01(inverse(T)*vec4(P0,1));

	float V0dir = sqrt(V01[0]*V01[0] + V01[1]*V01[1] + V01[2]*V01[2]);

	float Tnear = -500.0f;
	float Tfar = -500.0f;

	vec3 Bl, Bh;
	for (int i = 0; i < 3; i++) {
		Bl[i] = -0.5f;
		Bh[i] = 0.5f;
	}

	vec3 Pr1, Pr2;

	for (int i = 0; i < 3; i++) {
		if (V01[i] == 0) {
			if (P01[i] < Bl[i] || P01[i] > Bh[i]) return -1;
		} else {
			float T1 = (Bl[i] - P01[i])/V01[i];
			float T2 = (Bh[i] - P01[i])/V01[i];
			if (T1 > T2) {
				float Tt = T1;
				T1 = T2;
				T2 = Tt;
			}
			if (T1 > Tnear) Tnear = T1;
			if (T2 > Tfar) Tfar = T2;
			if (Tnear > Tfar) return -1;
			if (Tfar < 0) return -1;
		}
	}

	for	(int i = 0; i < 3; i++) {
		Pr1[i] = P01[i]+Tnear*V01[i];
		Pr2[i] = P01[i]+Tfar*V01[i];
	}
	vec4 Pr14 = (T*vec4(Pr1,1));
	vec4 Pr24 = (T*vec4(Pr2,1));

	for	(int i = 0; i < 3; i++) {
		Pr1[i] = Pr14[i];
		Pr2[i] = Pr24[i];
	}
	Tnear = sqrt((Pr1[0]-P0[0])*(Pr1[0]-P0[0])+(Pr1[1]-P0[1])*(Pr1[1]-P0[1])+(Pr1[2]-P0[2])*(Pr1[2]-P0[2]));
	Tfar = sqrt((Pr2[0]-P0[0])*(Pr2[0]-P0[0])+(Pr2[1]-P0[1])*(Pr2[1]-P0[1])+(Pr2[2]-P0[2])*(Pr2[2]-P0[2]));
	if(Tnear < 0 && Tfar >= 0) {
		t = Tnear + FLT_EPSILON;
		return t;
	} else if (Tnear >= 0 && Tfar < 0) {
		t = Tnear + FLT_EPSILON;
		return t;
	} else if (Tnear <0 && Tfar < 0) {
		return -1;
	} else {
		t =  min(Tnear,Tfar) + FLT_EPSILON;
		return t;
	}
	return -1;
}

double Test_RayCylinderIntersect(vec3 const& P0, vec3 const& V0, mat4 const& T) {
	// TODO fill this in so it calls your own ray-casting function.
	// See the documentation of this function in stubs.h.

	vec3 BC,TC;
	float t = 1000.0f;
	float t0 = 1000.0f;
	BC[0] = 0.0f; BC[1] = -0.5f; BC[2] = 0.0f;
	TC[0] = 0.0f; TC[1] = 0.5f; TC[2] = 0.0f;
	float L = 1.0f;
	float R = 0.5f;
	float eps = 0.000001f;

	mat4 InverseMat = inverse(T);
	vec3 V01(inverse(T)*vec4(V0,0));
	vec3 P01(inverse(T)*vec4(P0,1));

	float V0dir = sqrt(V01[0]*V01[0] + V01[1]*V01[1] + V01[2]*V01[2]);

	float A = V01[0]*V01[0] + V01[2]*V01[2];
	float B = (P01[0] - BC[0])*V01[0] + (P01[2] - BC[2])*V01[2];
	float C = (P01[0]-BC[0])*(P01[0]-BC[0]) + (P01[2]-BC[2])*(P01[2]-BC[2]) - R*R;

	float comp1 = 1000.0f;
	float comp2 = 1000.0f;
	float comp3 = 1000.0f;
	float comp4 = 1000.0f;

	float discrim = B*B - A*C;
	float t1 = 1000.0f;
	float t2 = 1000.0f;
	float n = 1;
	if (discrim >= 0) {
		if (abs(A) > 0) {
			t1 = (-B-sqrt(B*B - A*C))/A;
			t2 = (-B+sqrt(B*B - A*C))/A;
		}
		float upLim = 1;
		float lowLim = 0;
		float yHit = P01[1] + V01[1]*t1;
		if (t1 >= 0 && yHit <= upLim && yHit >= lowLim) {
			n++;
			comp1 = t1;
		}
		yHit = P01[1] + V01[1]*t2;
		if (t2 >= 0 && yHit <= upLim && yHit >= lowLim) {
			n++;
			comp2 = t2;
		}
	}

	vec4 Pf1((P01 + comp1*(V01)),1);
	vec4 Pf2((P01 + comp2*(V01)),1);

	vec4 Pf14 = T*Pf1;
	vec4 Pf24 = T*Pf2;

	vec3 Pfn1, Pfn2;

	for(int i = 0; i < 3; i++) {
		Pfn1[i] = Pf14[i];
		Pfn2[i] = Pf24[i];
	}

	comp1 = sqrt((Pfn1[0]-P0[0])*(Pfn1[0]-P0[0])+(Pfn1[1]-P0[1])*(Pfn1[1]-P0[1])+(Pfn1[2]-P0[2])*(Pfn1[2]-P0[2]));
	comp2 = sqrt((Pfn2[0]-P0[0])*(Pfn2[0]-P0[0])+(Pfn2[1]-P0[1])*(Pfn2[1]-P0[1])+(Pfn2[2]-P0[2])*(Pfn2[2]-P0[2]));

	//caps
	float tb,tc;
	tb = (BC[1]-P01[1])/V01[1];
	tc = (TC[1]-P01[1])/V01[1];

	vec3 C1(P01+tb*V01);
	vec3 C2(P01+tc*V01);

	if( C1[0]*C1[0] + C1[2]*C1[2] < R*R) {
		n ++;
		comp3 = tb;
	}
	if( C2[0]*C2[0] + C2[2]*C2[2] < R*R) {
		n ++;
		comp4 = tc;
	}

	vec4 Pf3((P01 + comp3*(V01)),1);
	vec4 Pf4((P01 + comp4*(V01)),1);

	vec4 Pf34 = T*Pf3;
	vec4 Pf44 = T*Pf4;

	vec3 Pfn3, Pfn4;

	for(int i = 0; i < 3; i++) {
		Pfn3[i] = Pf34[i];
		Pfn4[i] = Pf44[i];
	}

	comp3 = sqrt((Pfn3[0]-P0[0])*(Pfn3[0]-P0[0])+(Pfn3[1]-P0[1])*(Pfn3[1]-P0[1])+(Pfn3[2]-P0[2])*(Pfn3[2]-P0[2]));
	comp4 = sqrt((Pfn4[0]-P0[0])*(Pfn4[0]-P0[0])+(Pfn4[1]-P0[1])*(Pfn4[1]-P0[1])+(Pfn4[2]-P0[2])*(Pfn4[2]-P0[2]));

	if(n > 2) {
		float t = 0;
		if (comp1 != 0 && comp2 == 0){
			t = comp1 + FLT_EPSILON;
		} else if (comp1 == 0 && comp2 != 0) {
			t = comp2 + FLT_EPSILON;
		} else if(comp1 != 0 && comp2 != 0) {
			t = min(comp1, comp2) + FLT_EPSILON;
		}
		if(comp3 != 0) t = min(t, comp3) + FLT_EPSILON;
		if(comp4 != 0) t = min(t, comp4) + FLT_EPSILON;
		if(t != 0) {
			return t + FLT_EPSILON;
		} else {
			return -1;
		}
	} else {
		return -1;
	}

	return -1;
}