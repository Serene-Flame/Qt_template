#ifndef SIGNALSOURCES_H
#define SIGNALSOURCES_H

#include "signalchannel.h"
#include "signalgroup.h"

class SignalGroup;
class SignalChannel;

class SignalSources
{
	friend QDataStream &operator<<(QDataStream &outStream, const SignalSources &a);
	friend QDataStream &operator >> (QDataStream &inStream, SignalSources &a);
public:
	SignalSources(int numGroup);
	~SignalSources();
	SignalChannel* findChannelFromName(const QString &nativeName);
	SignalChannel* findSignalType1Channel(int boardStream, int chipChannel);

	QVector<SignalGroup> signalGroup;
};

#endif 