#pragma once


#include <set>
#include <string>
#include <memory>

#include "Telegram.h"

const double SEND_MSG_IMMEDIATELY = 0.0;
const int NO_ADDITIONAL_INFO = 0;
const int SENDER_ID_IRRELEVENT = -1;

class AIObject;

/**
* \class MessageDispatcher
*
* \brief Message dispatcher.
**/
class MessageDispatcher
{
public:

	/**
	* \fn void MessageDispatcher::DispatchMessage(double delay, int sender,
	* int receiver, int msg, luabind::object extraInfo);
	*
	* \brief Dispatch message.
	*
	* \param delay The delay.
	* \param sender The sender.
	* \param receiver The receiver.
	* \param msg The message.
	* \param extraInfo Information describing the extra.
	**/
	void DispatchMessage(double delay, int sender, int receiver, int msg /*, luabind::object extraInfo*/);

	/**
	* \fn void MessageDispatcher::DispatchDelayedMessages();
	*
	* \brief Dispatch delayed messages.
	**/
	void DispatchDelayedMessages();

	/**
	* \fn static boost::scoped_ptr<MessageDispatcher>* MessageDispatcher::GetInstance();
	*
	* \brief Gets the instance.
	*
	* \return null if it fails, else the instance.
	**/
	static std::unique_ptr<MessageDispatcher>* GetInstance();
private:
	std::set<Telegram> PriorityQueue; //!< Queue of priorities

	static std::unique_ptr<MessageDispatcher> singleton; //!< The singleton

	void Discharge(AIObject* pReceiver, const Telegram& msg);
};