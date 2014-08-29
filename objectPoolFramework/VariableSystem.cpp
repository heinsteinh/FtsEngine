#include "stdafx.h"
#include "VariableSystem.h"

#include "LoggingSystem.h"
#include <unordered_map>

namespace tin {
	Variable::Variable(bool value){
		this->SetValue(value);
	}

	Variable::Variable(int value){
		this->SetValue(value);
	}

	Variable::Variable(float value){
		this->SetValue(value);
	}

	Variable::Variable(double value){
		this->SetValue(value);
	}

	Variable::Variable(std::string value){
		this->SetValue(value);
	}

	void Variable::SetValue(bool value){
		type_ = kVariableTypeBool;
		bool_value_ = value;
		int_value_ = static_cast<int>(value);
		float_value_ = static_cast<float>(value);
		double_value_ = static_cast<double>(value);
		string_value_ = std::to_string(value);
	}

	void Variable::SetValue(int value){
		type_ = kVariableTypeInt;
		bool_value_ = static_cast<bool>(value);
		int_value_ = value;
		float_value_ = static_cast<float>(value);
		double_value_ = static_cast<double>(value);
		string_value_ = std::to_string(value);

	}

	void Variable::SetValue(float value){
		type_ = kVariableTypeFloat;
		bool_value_ = static_cast<bool>(value);
		int_value_ = static_cast<int>(value);
		float_value_ = value;
		double_value_ = static_cast<double>(value);
		string_value_ = std::to_string(value);
	}

	void Variable::SetValue(double value){
		type_ = kVariableTypeDouble;
		bool_value_ = static_cast<bool>(value);
		int_value_ = static_cast<int>(value);
		float_value_ = static_cast<float>(value);
		double_value_ = value;
		string_value_ = std::to_string(value);
	}

	void Variable::SetValue(std::string value){
		type_ = kVariableTypeString;
		// bool_value_ = std::stoi(value);
		// int_value_ = std::stoi(value);
		// float_value_ = std::stof(value);
		// double_value_ = std::stod(value);
		string_value_ = value;
	}

	bool Variable::asBool(){
		return bool_value_;
	}

	int Variable::asInt(){
		return int_value_;
	}

	float Variable::asFloat(){
		return float_value_;
	}

	double Variable::asDouble(){
		return double_value_;
	}

	std::string Variable::asString(){
		return string_value_;
	}

	void VariableSystem::Init(){

	}

	void VariableSystem::Shutdown(){
		for (auto iter = variables_.begin(); iter != variables_.end(); ++iter){
			delete iter->second;
		}
		variables_.clear();
	}

	VariableSystem::~VariableSystem(){

	}

	std::vector<Variable *> VariableSystem::GetAllVariables(){
		std::vector<Variable *> vars;
		for (auto iter = variables_.begin(); iter != variables_.end(); ++iter){
			vars.push_back(iter->second);
		}
		return vars;
	}

	void VariableSystem::ListVariables(){
		for (auto iter = variables_.begin(); iter != variables_.end(); ++iter){
			LoggingSystem::LogMessage("%s", iter->first.c_str());
		}
	}

	Variable* VariableSystem::Get(std::string name){
		if (variables_.find(name) == variables_.end()){
			return nullptr;
		}

		return variables_[name];
	}

	bool VariableSystem::GetAsBool(std::string name){
		Variable *var = Get(name);
		if (var){
			return var->asBool();
		}
		return false;
	}

	int VariableSystem::GetAsInt(std::string name){
		Variable *var = Get(name);
		if (var){
			return var->asInt();
		}
		return false;
	}

	float VariableSystem::GetAsFloat(std::string name){
		Variable *var = Get(name);
		if (var){
			return var->asFloat();
		}
		return false;
	}

	double VariableSystem::GetAsDouble(std::string name){
		Variable *var = Get(name);
		if (var){
			return var->asDouble();
		}
		return false;
	}

	std::string VariableSystem::GetAsString(std::string name){
		Variable *var = Get(name);
		if (var){
			return var->asString();
		}
		return false;
	}
}