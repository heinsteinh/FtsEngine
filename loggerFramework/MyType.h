#pragma once


#include <array>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <cmath>
#include <cassert>
#include <chrono>
#include <tuple>
#include <ppl.h>
#include <mutex>
#include <iostream>
#include <string>
#include <initializer_list>
#include <thread>

#include <functional>
#include <mutex>
#include <condition_variable>


//typedef void	Dvoid;
//typedef bool	Dbool;
//typedef int		Dint;
//typedef char	Dchar;
//typedef long	Dlong;
//typedef float	Dfloat;
//typedef double	Ddouble;
//typedef unsigned int	Duint;
//typedef unsigned char	Duchar;
//typedef unsigned long	Dulong;

//using namespace std;
//using namespace Concurrency;	


enum TransType
{
	WORLD,
	VIEW,
	PERSPECTIVE,
	VIEWPORT,
	TRANSFORM_END
};


enum MeshType
{
	MSH,
	PLY,
	MESHTYPE_END
};



using Func_void_initList = void(*)(std::initializer_list<std::string>);	//c++11 using syntax
//using Func_void_initList = std::function<void(std::initializer_list<std::string>)>;