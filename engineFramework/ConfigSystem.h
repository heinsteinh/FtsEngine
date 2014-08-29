#pragma once

#include "System.h"
#include "ConfigFile.h"

namespace core {

	class Config : public System
	{
	public:
		Config() : System("Config") 
		{
			mConfigFile = std::unique_ptr<ConfigFile>(new ConfigFile());
		}

		virtual ~Config() { }

		bool load(const std::string &filename) 
		{
			try {
				mConfigFile->addConfigFile(filename);
			}
			catch (const std::string str) {
				mLog << "Failed to open config file: " << filename;
				return false;
			}
			return true;
		}

		void parseCommandLine(int argc, char* argv[]) 
		{
			/* TODO */
		}

		//get sprecified variable
		template <typename T>
		T get(std::string const& section, std::string const& entry) const {
			try {
				ConfigFile::Conversion cv = mConfigFile->Value(section, entry);
				return (T)cv;
			}
			catch (const char *str) 
			{
				gLog << "Failed to find variable: " << section << "/" << entry;
				return T();
			}
		}

		//get specified variable with default value
		template <typename T>
		T get(std::string const& section, std::string const& entry, const T value) const
		{
			ConfigFile::Conversion cv = mConfigFile->Value(section, entry, value);
			return (T)cv;
		}

		//spceial case for const char*
		std::string get(std::string const& section, std::string const& entry, const char *value) const 
		{
			std::string strValue(value);
			ConfigFile::Conversion cv = mConfigFile->Value(section, entry, strValue);
			return (std::string)cv;
		}

	private:
		std::unique_ptr<ConfigFile> mConfigFile;
	};

}

