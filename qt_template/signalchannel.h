#ifndef SIGNALCHANNEL_H
#define SIGNALCHANNEL_H

class SignalGroup;

class SignalChannel
{
	friend QDataStream &operator<<(QDataStream &outStream, const SignalChannel &a);
	friend QDataStream &operator >> (QDataStream &inStream, SignalChannel &a);

public:
	SignalChannel();
	SignalChannel(SignalGroup *initSignalGroup);
	SignalChannel(const QString &initCustomChannelName, const QString &initNativeChannelName,
		int initNativeChannelNumber, SignalType initSignalType,
		int initGroup, int initChannel, SignalGroup *initSignalGroup);
	~SignalChannel();

	SignalGroup *signalGroup;

	QString nativeChannelName;
	QString customChannelName;
	int nativeChannelNumber;
	int alphaOrder;
	int userOrder;

	SignalType signalType;
	bool enabled;

	int group;
	int channel;

	QString saveFileName;
	QFile *saveFile;
	QDataStream *saveStream;
};

#endif