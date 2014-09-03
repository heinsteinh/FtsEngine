#pragma once


#include "Compack.h"
#include "Streaming.h"


#include <cstdint>
#include <string>
#include <exception>
#include <sstream>

namespace Framework 
{
	enum MESSAGE_TYPE : uint16_t;
	struct Message
	{
	public:
		typedef std::string bytes;
		typedef std::wstring utf16string;

		/*static Message* deserialize(const char* bytes, unsigned len);
		virtual bytes serialize() const = 0;
	*/

		static Message* Deserialize(const char* buf, unsigned len);
		virtual bytes Serialize() const = 0;




		inline virtual std::string print() const 
		{
			std::string ser = Serialize();
			std::ostringstream out;
			for (char c : ser)
				out << (unsigned)(unsigned char)c << ' ';
			out << "(length " << std::dec << ser.length() << ")";
			return out.str();
		};
	
		virtual MESSAGE_TYPE getMessageType() const = 0;
		Message() { m_pStreaming = new Gmk::Stream(); }
		Message(const Message&) = delete;

		Message& operator=(const Message&) = delete;
		virtual ~Message() = 0 {	if (m_pStreaming!=NULL)	{	delete  m_pStreaming;	m_pStreaming = NULL;	} }
	
		class ProtocolViolationException : public std::runtime_error
		{
		public:
			inline ProtocolViolationException(const std::string& what_arg) : std::runtime_error(what_arg) { }
		};
		class FormatException : public ProtocolViolationException
		{
		public:
			inline FormatException() : FormatException("Message layout expectations violated") { }
			inline FormatException(const std::string& what_arg) : ProtocolViolationException(what_arg) { }
		};

		Gmk::Stream* GetStream() { return m_pStreaming; }


	protected:
		Gmk::Stream*				m_pStreaming;




	};



	typedef enum MESSAGE_TYPE : uint16_t
	{
		CMD_PING = 1000,
		CMD_KEEPALIVE,
		GAME_CREATE

	}MESSAGE_TYPE;



struct GameCreateMessage : public Message 
{	
private: const static MESSAGE_TYPE _MESSAGE_TYPE = GAME_CREATE;

public:
	uint8_t			numPlayers;
	uint32_t		timeout;	
	uint8_t			gridSize;
	uint8_t			numPlanes;
	bool				headshots;
	bool				reveal;
	std::string gamePassword;


	std::string Serialize() const override
	{


		return "";
	}

	MESSAGE_TYPE getMessageType() const override { return _MESSAGE_TYPE; }
	~GameCreateMessage() override { Message::~Message(); }


	inline static GameCreateMessage* Deserialize(const char* buf, unsigned len)
	{
		GameCreateMessage* ret = new GameCreateMessage;
		const char *end = buf + len;
		

		
		if (buf != end) //Message was not an exact fit to length; Mistake on client side
			throw FormatException("Actual length doesn't match expected length for message");

		return ret;
	}


};



struct PingMessage : public Message
{
	
	TimeStamp _pingTime;

public:
	MESSAGE_TYPE getMessageType() const override { return CMD_PING; }
	
	PingMessage(TimeStamp time_) : _pingTime(time_)
	{		
	}
};


}