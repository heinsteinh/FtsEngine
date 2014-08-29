#pragma once

#include <cmath>
#include <iostream>
#include <strstream>

/**
* \struct Telegram
*
* \brief Telegram.
**/
struct Telegram
{
	int sender; //!< The sender

	int receiver; //!< The receiver

	int message;	//!< The message

	double dispatchTime;	//!< Time of the dispatch

	//luabind::object ExtraInfo; //!< Additional information to accompany the message

	/**
	* \fn Telegram(void)
	*
	* \brief Default constructor.
	**/
	Telegram(void) : dispatchTime(-1), sender(-1), receiver(-1), message(-1)
	{
		//ExtraInfo = luabind::object();
	}

	/**
	* \fn Telegram(double time, int sender, int receiver, int msg,
	* luabind::object extra)
	*
	* \brief Constructor.
	*
	* \param time The time.
	* \param sender The sender.
	* \param receiver The receiver.
	* \param msg The message.
	* \param extra The extra.
	**/
	Telegram(double time, int sender, int receiver, int msg /*luabind::object extra*/)
	{
		dispatchTime = time;
		this->sender = sender;
		this->receiver = receiver;
		this->message = msg;
	}
};

const double minDelay = 0.25;

inline bool operator==(const Telegram& t1, const Telegram& t2)
{
	return (fabs(t1.dispatchTime - t2.dispatchTime) < minDelay) &&
		(t1.sender == t2.sender) &&
		(t1.receiver == t2.receiver) &&
		(t1.message == t2.message);
}

inline bool operator<(const Telegram& t1, const Telegram& t2)
{
	if (t1 == t2)
	{
		return false;
	}
	else
	{
		return (t1.dispatchTime < t2.dispatchTime);
	}
}

inline std::ostream& operator<<(std::ostream& os, const Telegram& t)
{
	os << "time: " << t.dispatchTime << " Sender: " << t.sender <<
		" Receiver: " << t.receiver << " Msg: " << t.message;
	return os;
}

