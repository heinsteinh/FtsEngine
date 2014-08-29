#pragma once


#include <stdio.h>
#include <iostream>
#include <time.h>
#include <math.h>
#include <stdarg.h>
#include <memory.h>
#include <assert.h>

template<class T>
inline T Limits(const T& _Val, const T& _Min, const T& _Max)
{
	if (_Val > _Max) { return _Max; }
	else if (_Val < _Min) { return _Min; }

	return _Val;
}

template<class T>
inline bool IsRegion(const T& _Val, const T& _Min, const T& _Max)
{
	return (_Val >= _Min && _Val <= _Max) ? true : false;
}

inline int RandLimits(const int _Min, const int _Max)
{
	return (rand() % (_Max - _Min + 1) + _Min);
}

template<class T>
inline T Min(const T& _Left, const T& _Right)
{
	return (_Left < _Right ? _Left : _Right);
}



//https://github.com/codinghao/XServer/blob/5fc38c4ac3447e35eb884d243c2a7083e556830c/GameFrame/src/Common/UnitTest.h
void ObjectPoolTest();


void MemAllocTest();

void TestFunction();