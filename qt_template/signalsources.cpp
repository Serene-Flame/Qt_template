#include "stdafx.h"
#include "signalsources.h"

// Data structure containing descriptions of all signal sources acquired.

SignalSources::SignalSources(int numGroup)
{
	int i;

	//  Create several signal groups divided by criteria. (e.g., device, port, signal type)
	signalGroup.resize(numGroup);

	for (i = 0; i < numGroup; i++) {
		signalGroup[i].name = signalGroup_Name + QString(QChar(65 + i));
		signalGroup[i].prefix = QString(QChar(65 + i));
		signalGroup[i].enabled = false;
	}
}


SignalSources::~SignalSources()
{
}

// Return a pointer to a SignalChannel with a particular nativeName (e.g., "A-02").
SignalChannel* SignalSources::findChannelFromName(const QString &nativeName)
{
	SignalChannel *channel;

	for (int i = 0; i < signalGroup.size(); ++i) {
		for (int j = 0; j < signalGroup[i].numChannels(); ++j) {
			if (signalGroup[i].channel[j].nativeChannelName == nativeName) {
				channel = &signalGroup[i].channel[j];
				return channel;
			}
		}
	}

	return nullptr;
}

// Return a pointer to a SignalChannel corresponding to a particular USB interface
// data stream and chip channel number.
SignalChannel* SignalSources::findSignalType1Channel(int inChannel, int inGroup)
{
	SignalChannel *channel;

	for (int i = 0; i < signalGroup.size(); ++i) {
		for (int j = 0; j < signalGroup[i].numChannels(); ++j) {
			if (signalGroup[i].channel[j].signalType == SignalType_1 &&
				signalGroup[i].channel[j].channel == inChannel &&
				signalGroup[i].channel[j].group == inGroup) {
				channel = &signalGroup[i].channel[j];
				return channel;
			}
		}
	}

	return nullptr;
}

// Stream all signal sources out to binary data stream.
QDataStream& operator<<(QDataStream &outStream, const SignalSources &a)
{
	outStream << (qint16)a.signalGroup.size();
	for (int i = 0; i < a.signalGroup.size(); ++i) {
		outStream << a.signalGroup[i];
	}
	return outStream;
}

// Stream all signal sources in from binary data stream.
QDataStream& operator >> (QDataStream &inStream, SignalSources &a)
{
	qint16 tempQint16;
	int nGroups;

	inStream >> tempQint16;
	nGroups = (int)tempQint16;
	a.signalGroup.resize(nGroups);

	for (int i = 0; i < nGroups; ++i) {
		inStream >> a.signalGroup[i];
	}

	return inStream;
}