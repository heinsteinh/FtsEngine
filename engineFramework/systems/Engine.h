#include <boost/shared_ptr.hpp>
#include <map>
#include <string>
#include "taskmanager.h"
#include "logger.h"
#include "eventchannel.h"
#include "config.h"

class Engine {
public:
	typedef boost::shared_ptr<System> SystemPtr;
	typedef std::map<std::string, SystemPtr> SystemMap;
	
	Engine();
	~Engine();
	
	void run();
	void stop();
	
	void add(SystemPtr s);
	SystemPtr get(const std::string& systemName) const;
	
	const boost::shared_ptr<Config>& config();
	
private:
	void initializeSystems();
	void shutdownSystems();
	
	boost::shared_ptr<Config> mConfig;
	
	SystemMap mSystemMap;
	TaskManager mTaskManager;
	EventChannel mChannel;
};