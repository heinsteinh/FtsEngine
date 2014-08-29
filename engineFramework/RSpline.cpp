#include "stdafx.h"
#include "RSpline.h"

//https://github.com/AlexanderKnueppel/Harmony4D/blob/56fcc9623232bacf7cc1a71f97652236bd616c11/Harmony4D/include/core/CRSpline.h

namespace core
{

	void CRSpline::bounds(int &pp) {
		if (pp < 0)
			pp = 0;
		else if (pp >= (int)vp.size() - 1)
			pp = vp.size() - 1;
	}

	CRSpline::CRSpline()
		: vp(), delta_t(0)
	{
	}

	CRSpline::CRSpline(const CRSpline& s)
	{
		for (int i = 0; i < (int)s.vp.size(); i++)
			vp.push_back(s.vp[i]);
		delta_t = s.delta_t;
	}

	CRSpline::~CRSpline()
	{}

	// Solve the Catmull-Rom parametric equation for a given time(t) and vector quadruple (p1,p2,p3,p4)
	glm::vec3 CRSpline::eq(float t, const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec3& p4)
	{
		float t2 = t * t;
		float t3 = t2 * t;

		float b1 = (float)(0.5 * (-t3 + 2 * t2 - t));
		float b2 = (float)(0.5 * (3 * t3 - 5 * t2 + 2));
		float b3 = (float)(0.5 * (-3 * t3 + 4 * t2 + t));
		float b4 = (float)(0.5 * (t3 - t2));

		return (p1*b1 + p2*b2 + p3*b3 + p4*b4);
	}

	void CRSpline::addSplinePoint(const glm::vec3& v)
	{
		vp.push_back(v);
		delta_t = (float)1 / (float)vp.size();
	}

	glm::vec3 CRSpline::getInterpolatedSplinePoint(float t)
	{
		// Find out in which interval we are on the spline
		int p = (int)(t / delta_t);
		// Compute local control point indices

		int p0 = p - 1; bounds(p0);
		int p1 = p - 0; bounds(p1);
		int p2 = p + 1; bounds(p2);
		int p3 = p + 2; bounds(p3);

		// Relative (local) time
		float lt = (t - delta_t*(float)p) / delta_t;
		// Interpolate
		return CRSpline::eq(lt, vp[p0], vp[p1], vp[p2], vp[p3]);
	}

	int CRSpline::getNumPoints()
	{
		return vp.size();
	}

	glm::vec3& CRSpline::getNthPoint(int n)
	{
		return vp[n];
	}
}