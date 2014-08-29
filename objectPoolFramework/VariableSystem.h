
#ifndef _VariableSystem_H_
#define _VariableSystem_H_

#include <string>
#include <vector>
#include <list>
#include <unordered_map>


#include "TSingleton.h"
#include "LoggingSystem.h"


namespace tin 
{
#define R_WIDTH "r_width"
#define R_HEIGHT "r_height"
}


namespace tin{
	enum VariableType{
		kVariableTypeString,
		kVariableTypeDouble,
		kVariableTypeFloat,
		kVariableTypeInt,
		kVariableTypeBool
	};

	class VariableSystemLocal;
	class Variable{
	public:
		Variable() { };
		Variable(bool value);
		Variable(int value);
		Variable(float value);
		Variable(double value);
		Variable(std::string value);

		void SetValue(bool value);
		void SetValue(int value);
		void SetValue(float value);
		void SetValue(double value);
		void SetValue(std::string value);

		bool asBool();
		int asInt();
		float asFloat();
		double asDouble();
		std::string asString();

		VariableType type() { return type_; };
		std::string name() { return name_; };
	protected:
		std::string name_;
		bool bool_value_;
		int int_value_;
		float float_value_;
		double double_value_;
		std::string string_value_;
		VariableType type_;

		friend class VariableSystem;
	};


	class VariableSystem : public CSingleton<VariableSystem>
	{

		friend class CSingleton<VariableSystem>;
	public:
		VariableSystem(){};
		~VariableSystem();

		template<typename T>
		void Set(std::string name, T value){
			if (typeid(value) != typeid(int) 
				&& typeid(value) != typeid(float) 
				&& typeid(value) != typeid(std::string) 
				&& typeid(value) != typeid(bool) 
				&& typeid(value) != typeid(const char*))
			{	
				LoggingSystem::LogError("Invalid type");
				return;
			}
			Variable *var = nullptr;
			if (variables_.find(name) == variables_.end()){
				var = new Variable(value);
			}
			else {
				var = variables_[name];
			}
			var->SetValue(value);
			var->name_ = name;
			variables_[name] = var;
		}

		Variable* Get(std::string name);
		bool GetAsBool(std::string name);
		int GetAsInt(std::string name);
		float GetAsFloat(std::string name);
		double GetAsDouble(std::string name);
		std::string GetAsString(std::string name);

		void ListVariables();
		std::vector<Variable *> GetAllVariables();
	private:

		std::unordered_map<std::string, Variable *> variables_;
		void Init();
		void Shutdown();

		friend class Singleton;

	};
} // tin
#endif