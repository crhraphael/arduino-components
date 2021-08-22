#ifndef IWEBSOCKETSERVERIMPLEMENTATION
#define IWEBSOCKETSERVERIMPLEMENTATION
#include <WebSocketsServer.h>
#include <InputControllers/IWirelessCommComponent.h>

	
class IWebsocketImplementation : public IWirelessCommComponent 
{
  private:
  public:
  virtual ~IWebsocketImplementation() = 0;
  virtual void listen() = 0;
	virtual void send (const char *message) = 0;
	virtual void open() = 0;
	virtual void close();

	virtual bool IsOpen() = 0;
	virtual bool HasClientsConnected() = 0;

};

IWebsocketImplementation::~IWebsocketImplementation() {};
#endif