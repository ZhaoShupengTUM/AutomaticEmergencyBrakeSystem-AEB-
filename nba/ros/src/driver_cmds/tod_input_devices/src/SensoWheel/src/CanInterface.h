// Copyright 20xx FTM
#pragma once

#include <iostream>
#include "PCANBasic.h"
#include <unistd.h>

#define MAX_PATH 260
typedef void *HANDLE;
class CanInterface{
protected:
    unsigned int pcan_device;
    BYTE _channel;
    WORD _baudrate;
    BYTE _channelNr;
    BYTE _senderID;
    HANDLE _hMessageReceived;
    wchar_t _szEventName[MAX_PATH];
    virtual void HandleReply(unsigned int Identifier, unsigned char Length, const BYTE* Data) = 0;
    virtual void SendCANMessage(unsigned char Sender, unsigned char IdentifierType,
        unsigned int Identifier, unsigned char Length, const BYTE* Data);

public:
    CanInterface(BYTE channel, WORD baudrate);
    ~CanInterface();
    bool _bInitSuccessfull;
    bool _bGetData;

    void run();
    void close();
    void Init();
};
