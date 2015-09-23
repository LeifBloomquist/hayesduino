/***********************************************
HAYESDUINO PROJECT - COPYRIGHT 2013, PAYTON BYRD

Project homepage: http://hayesduino.codeplex.com
License: http://hayesduino.codeplex.com/license
***********************************************/
#include "HardwareSerial.h"

#define __UNO__


#ifndef _MODEMBASE_h
#define _MODEMBASE_h

#include <Stream.h>
#include "Arduino.h"
#include "DEBUG.h"
#include "Global.h"

#define STATUS_LED		 8

#ifdef __UNO__
#define RTS  A5
#define DTR  A4
#define RI   A3
#define DCD  A2
#define CTS  A1
#define DSR  A0
#endif

class ModemBase : public Stream
{
 private:
	int _escapeCount;
	char _lastCommandBuffer[81];
	char _commandBuffer[81];

	HardwareSerial* _serial;

	uint32_t _baudRate;
	
	bool _isCommandMode;
	bool _isConnected;
	bool _isRinging;
	uint8_t _isDcdInverted;

	bool _echoOn;
	bool _verboseResponses;
	bool _quietMode;

	bool _S0_autoAnswer;			// Default false
	uint8_t _S1_ringCounter;		// Default 0
	uint8_t _S2_escapeCharacter;	// Default 43
	uint8_t _S3_crCharacter;		// Default 13
	uint8_t _S4_lfCharacter;		// Default 10
	uint8_t _S5_bsCharacter;		// Default 8
	uint8_t _S6_waitBlindDial;		// Default 2 seconds
	uint8_t _S7_waitForCarrier;		// Default 50 seconds
	uint8_t _S8_pauseForComma;		// Default 2 seconds
	uint8_t _S9_cdResponseTime;		// Default 6 (0.6 seconds)
	uint8_t _S10_delayHangup;		// Default 14 (1.4 seconds)
	uint8_t _S11_dtmf;				// Default 95 miliseconds
	uint8_t _S12_escGuardTime;		// Default 50 (1.0 second)
	uint8_t _S18_testTimer;			// Default 0 seconds
	uint8_t _S25_delayDTR;			// Default 5
	uint8_t _S26_delayRTS2CTS;		// Default 5 miliseconds
	uint8_t _S30_inactivityTimer;	// Default 0 (disable)
	uint8_t _S37_lineSpeed;			// Default 0 (auto)
	uint8_t _S38_delayForced;		// Default 20 seconds
	/*
S37 Command options:
0 Attempt auto mode connection
1 Attempt to connect at 300 bit/s
2 Attempt to connect at 300 bit/s
3 Attempt to connect at 300 bit/s
5 Attempt to connect at 1200 bit/s
6 Attempt to connect at 2400 bit/s
7 Attempt to connect in V.23 75/1200 mode.
8 Attempt to connect at 9600 bit/s
9 Attempt to connect at 12000 bit/s
10 Attempt to connect at 14400 bit/s
	*/

	void resetCommandBuffer(bool);

//	void (*onDisconnect)(EthernetClient *client);
	void (*onDialout)(char*, ModemBase*);

	void setLineSpeed(void);
	void loadDefaults(void);
	void saveDefaults(void);
	void writeAddressBook(uint16_t, char *);
	char* getAddressBook(uint16_t);
#ifndef __UNO__
	bool processCommandBufferExtended(EthernetClient *client);
#endif
	void printOK(void);
	void printResponse(const char* code, const char* msg);
	void printResponse(const char* code, const __FlashStringHelper * msg);
	int getString(Stream *client, char *buffer, int maxLength);

 public:
	 ModemBase();

	 void begin(Stream*, Stream*, void(*)(char*, ModemBase*));

  	 virtual int available(void);
     virtual int peek(void);
     virtual int read(void);
     virtual void flush(void);
     virtual size_t write(uint8_t);

	 void factoryReset(void);
	 uint32_t getBaudRate(void);
	 void setDefaultBaud(uint32_t baudRate);
	 void setDcdInverted(char isInverted);
	 bool getDcdInverted(void);
	 bool getIsConnected(void);
	 bool getIsRinging(void);
	 void setIsRinging(bool);
	 bool getIsCommandMode(void);
	 int toggleCarrier(boolean isHigh);
	 void disconnect();
	 void connect(Stream *client);
	 void connectOut(void);

	 void processCommandBuffer(Stream *client);
	 void processData(Stream *client);
	 
	 void resetToDefaults(void);

	 using Print::write;
};

#endif

