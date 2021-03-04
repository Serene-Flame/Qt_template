#include "stdafx.h"
#include "signalchannel.h"
#include "signalgroup.h"

// Data structure containing description of a particular signal channel (e.g., an amplifier channel on a particular chip, a digital input from the USB interface board, etc.).

// Default constructor.
SignalChannel::SignalChannel()
{
	signalGroup = 0;

	enabled = true;
	alphaOrder = -1;
	userOrder = -1;
}

// Contructor linking new signal channel to a particular signal group.
SignalChannel::SignalChannel(SignalGroup *initSignalGroup)
{
	signalGroup = initSignalGroup;
	alphaOrder = -1;
}

// Detailed constructor with all signal channel information supplied.
SignalChannel::SignalChannel(const QString &initCustomChannelName, const QString &initNativeChannelName,
	int initNativeChannelNumber, SignalType initSignalType,
	int initGroup, int initChannel, SignalGroup *initSignalGroup)
{
	signalGroup = initSignalGroup;

	customChannelName = initCustomChannelName;
	nativeChannelName = initNativeChannelName;
	nativeChannelNumber = initNativeChannelNumber;
	signalType = initSignalType;
	group = initGroup;
	channel = initChannel;

	enabled = true;
	alphaOrder = -1;
	userOrder = initNativeChannelNumber;
}

SignalChannel::~SignalChannel()
{
}

// Streams this signal channel out to binary data stream.
QDataStream& operator<<(QDataStream &outStream, const SignalChannel &a)
{
	outStream << a.nativeChannelName;
	outStream << a.customChannelName;
	outStream << (qint16)a.nativeChannelNumber;
	outStream << (qint16)a.userOrder;
	outStream << (qint16)a.signalType;
	outStream << (qint16)a.enabled;
	return outStream;
}

// Streams this signal channel in from binary data stream.
QDataStream& operator >> (QDataStream &inStream, SignalChannel &a)
{
	qint16 tempQint16;

	inStream >> a.nativeChannelName;
	inStream >> a.customChannelName;
	inStream >> tempQint16;
	a.nativeChannelNumber = (int)tempQint16;
	inStream >> tempQint16;
	a.userOrder = (int)tempQint16;
	inStream >> tempQint16;
	a.signalType = (SignalType)tempQint16;
	inStream >> tempQint16;
	a.enabled = (bool)tempQint16;
	return inStream;
}