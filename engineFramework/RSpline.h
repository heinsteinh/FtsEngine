#pragma once

#include "Lib.h"

namespace core
{


	class CRSpline {
	public:

		// Constructors and destructor
		CRSpline();
		CRSpline(const CRSpline&);
		~CRSpline();

		// Operations
		void addSplinePoint(const glm::vec3& v);
		glm::vec3 getInterpolatedSplinePoint(float t); // t = 0...1; 0=vp[0] ... 1=vp[max]
		int getNumPoints();
		glm::vec3& getNthPoint(int n);

		// Static method for computing the Catmull-Rom parametric equation
		// given a time (t) and a vector quadruple (p1,p2,p3,p4).
		static glm::vec3 eq(float t, const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec3& p4);

	private:
		//helper
		void bounds(int &pp);
		std::vector<glm::vec3> vp;
		float delta_t;
	};


}