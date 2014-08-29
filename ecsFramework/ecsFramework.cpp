// ecsFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "LoggerEx.h"

#include <cassert>
#include <string>
#include <iostream>

#include <map> // Component-entity system in 16 lines of C++11. 2013 rlyeh, MIT licensed
#include <set> // Code fragment from kult engine - https://github.com/r-lyeh/kult

enum { JOIN, MERGE, EXCLUDE };
using set = std::set<unsigned>;
template<typename T> set&system()
{
	static set entities;
	return entities;
}

template<typename T, int MODE>set subsystem(const set &B)
{
	set newset; const set&A = system<T>(); 
	
	if (MODE == MERGE){
		newset = B;
		for (auto&id : A)
			newset.insert(id);
	}
	else if (MODE == EXCLUDE){
		newset = B; 
		for (auto&id : A)
			newset.erase(id);
	}
	else if (A.size()< B.size()){
		for (auto&id : A)
		if (B.find(id) != B.end())
			newset.insert(id);
	}
	else{
		for (auto&id : B)if (A.find(id) != A.end())
			newset.insert(id);
	}return newset;
}
template<typename T>std::map<unsigned, T>&components(){
	static std::map<unsigned, T>objects; return objects;
}

template<typename T>bool has(unsigned id){
	return components<T>().find(id) != components<T>().end();
}

template<typename T>decltype(T::value_type)&get(unsigned id){
	static decltype(T::value_type)invalid, reset; return has<T>(id) ? components<T>()[id].value_type : invalid = reset;
}



template<typename T>decltype(T::value_type)&add(unsigned id){ return system<T>().insert(id), components<T>()[id] = components<T>()[id], get<T>(id); }
template<typename T> bool del(unsigned id){ return add<T>(id), components<T>().erase(id), system<T>().erase(id), !has<T>(id);}
template<typename T, int>
struct component{ T value_type; };


// gamedev types and constants
typedef std::pair<int, int> vec2i;
typedef std::pair<float, float> vec2f;
const vec2f zero = { 0.f, 0.f }, one = { 1.f, 1.f };
// component aliases
using friendly = component< bool, 'team' >;
using health = component< int, 'heal' >;
using mana = component< int, 'mana' >;
using coins = component< int, 'coin' >;
using name = component< std::string, 'name' >;
using position = component< vec2f, 'pos2' >;

// sugars
template<class T, class U> std::set< unsigned > join() { return subsystem<T, JOIN>(system<U>()); }
template<class T, class U, class V> std::set< unsigned > join() { return subsystem<T, JOIN>(join<U, V>()); }
template<class T, class U, class V, class W> std::set< unsigned > join() { return subsystem<T, JOIN>(join<U, V, W>()); }
template<class T> std::set< unsigned > exclude(const set &B) { return subsystem<T, EXCLUDE>(B); }



int _tmain(int argc, _TCHAR* argv[])
{
	

	// entities
	int none = 0, player = 1, enemy = 2;

	// components
	assert(!has<name>(player));
	assert(!has<position>(player));
	assert(!has<coins>(enemy));
	assert(!has<health>(enemy));

	add<name>(player) = "Hero";
	add<position>(player) = zero;
	add<health>(player) = 100;
	add<coins>(player) = 200;
	add<mana>(player) = 4000;
	add<friendly>(player) = true;
	add<name>(enemy) = "Orc";
	add<position>(enemy) = one;
	add<health>(enemy) = 200;
	add<coins>(enemy) = 50;
	add<mana>(enemy) = 10;

	assert(get<health>(player) == 100); // :>

	assert(has<name>(player));
	assert(!has<vec2i>(player));
	assert(has<position>(player));
	assert(has<health>(player));

	assert(get<name>(player) == "Hero");
	assert(get<position>(player) == zero);
	assert(get<health>(player) == 100);

	// systems; here we intersect a system of all elements with <name> and <position>.
	assert((join<name, position>().size() == 2));

	// systems; render game state
	auto display = []() {
		std::cout << "- ";
		for (auto &id : join<name, coins, health, position>()) {
			std::cout
				<< get<name>(id) << " at "
				<< "(" << get<position>(id).first << "," << get<position>(id).second << ")"
				<< " " << get<health>(id) << "HP"
				<< " " << get<coins>(id) << "$, ";
		}
		std::cout << std::endl;
	};

	display();
	return 0;
}

