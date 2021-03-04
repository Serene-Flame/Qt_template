#ifndef SIGNALGROUP_H
#define SIGNALGROUP_H

#include "signalchannel.h"

class SignalGroup
{
	friend QDataStream &operator<<(QDataStream &outStream, const SignalGroup &a);
	friend QDataStream &operator>>(QDataStream &inStream, SignalGroup &a);

public:
	SignalGroup();
	SignalGroup(const QString &initialName, const QString &initialPrefix);
	~SignalGroup();

	QVector<SignalChannel> channel;
	QString name;
	QString prefix;
	bool enabled;

	void addChannel();
	void addChannel(SignalChannel *newChannel);

	void addSignalType1Channel(int nativeChannelNumber, int initGroup, int initChannel);
	void addSignalType2Channel(int nativeChannelNumber, int initGroup, int initChannel);
	void addSignalType3Channel(int nativeChannelNumber, int initGroup, int initChannel);

	SignalChannel* channelByNativeOrder(int index);
	SignalChannel* channelByAlphaOrder(int index);
	SignalChannel* channelByIndex(int index);
	int numChannels() const;
	void updateAlphabeticalOrder();
	void setOriginalChannelOrder();
	void setAlphabeticalChannelOrder();
	void print() const;
};

#endif // SIGNALGROUP_H
