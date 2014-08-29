#pragma once

//https://github.com/AlexanderKnueppel/Harmony4D/tree/6879629a669145d9bcfafb1cbe57d98cc7c318e1/Harmony4D/include/core



#include <string>
#include <map>

namespace core
{

	class ConfigFile {
	public:
		class Conversion {
		public:
			Conversion() {};
			explicit Conversion(const std::string&);
			explicit Conversion(double);
			explicit Conversion(int);
			explicit Conversion(bool);
			explicit Conversion(const char*);

			Conversion(const Conversion&);
			Conversion& operator=(const Conversion &);

			Conversion& operator=(double);
			Conversion& operator=(const std::string &);
			Conversion& operator=(bool);
			Conversion& operator=(int);

			operator std::string() const;
			operator double() const;
			operator bool() const;
			operator int() const;
		private:
			std::string value_;
		};

		ConfigFile(const std::string & configFile = "");
		void addConfigFile(const std::string & configFile);

		Conversion const& Value(const std::string & section, const std::string & entry) const;
		Conversion const& Value(const std::string & section, const std::string & entry, double value);
		Conversion const& Value(const std::string & section, const std::string & entry, int value);
		Conversion const& Value(const std::string & section, const std::string & entry, bool value);
		Conversion const& Value(const std::string & section, const std::string & entry, const std::string & value);

	private:
		std::map<std::string, Conversion> content_;
	};


}