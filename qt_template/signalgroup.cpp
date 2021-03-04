#include "stdafx.h"
#include "signalgroup.h"

// Data structure containing a description of all signal channels on a particular criteria(e.g., SPI Port A, device 2).

// Must have a default constructor to create vectors of this object.
SignalGroup::SignalGroup()
{
}

// Constructor.
SignalGroup::SignalGroup(const QString &initialName, const QString &initialPrefix)
{
	name = initialName;
	prefix = initialPrefix;
	enabled = true;
}

SignalGroup::~SignalGroup()
{
}

// Add new channel to this signal group.
void SignalGroup::addChannel()
{
	SignalChannel *newChannel = new SignalChannel(this);
	channel.append(*newChannel);
}

// Add alreay generated channel to this signal group.
void SignalGroup::addChannel(SignalChannel * newChannel)
{
	channel.append(*newChannel);
	updateAlphabeticalOrder();
}

// Add new SignalType_1 channel (with specified properties) to this signal group.
void SignalGroup::addSignalType1Channel(int nativeChannelNumber, int initGroup, int initChannel)
{
	QString nativeChannelName;
	QString customChannelName;

	auto x = SignalType_to_string_map.find(SignalType_1);

	nativeChannelName = prefix + "-" + QString(x->second.c_str()) + "-" +
		QString("%1").arg(nativeChannelNumber, 3, 10, QChar('0'));
	customChannelName = prefix + "-" + QString("%1").arg(nativeChannelNumber, 3, 10, QChar('0'));

	SignalChannel *newChannel = new SignalChannel(customChannelName, nativeChannelName,
		nativeChannelNumber, SignalType_1,
		initGroup, initChannel, this);
	channel.append(*newChannel);
	updateAlphabeticalOrder();
}

// Add new SignalType_2 channel (with specified properties) to this signal group.
void SignalGroup::addSignalType2Channel(int nativeChannelNumber, int initGroup, int initChannel)
{
	QString nativeChannelName;
	QString customChannelName;

	auto x = SignalType_to_string_map.find(SignalType_2);

	nativeChannelName = prefix + "-" + QString(x->second.c_str()) + "-" +
		QString("%1").arg(nativeChannelNumber, 3, 10, QChar('0'));
	customChannelName = prefix + "-" + QString("%1").arg(nativeChannelNumber, 3, 10, QChar('0'));

	SignalChannel *newChannel = new SignalChannel(customChannelName, nativeChannelName,
		nativeChannelNumber, SignalType_3,
		initGroup, initChannel, this);
	channel.append(*newChannel);
	updateAlphabeticalOrder();
}

// Add new SignalType_3 channel (with specified properties) to this signal group.
void SignalGroup::addSignalType3Channel(int nativeChannelNumber, int initGroup, int initChannel)
{
	QString nativeChannelName;
	QString customChannelName;

	auto x = SignalType_to_string_map.find(SignalType_3);

	nativeChannelName = prefix + "-" + QString(x->second.c_str()) + "-" +
		QString("%1").arg(nativeChannelNumber, 3, 10, QChar('0'));
	customChannelName = prefix + "-" + QString("%1").arg(nativeChannelNumber, 3, 10, QChar('0'));

	SignalChannel *newChannel = new SignalChannel(customChannelName, nativeChannelName,
		nativeChannelNumber, SignalType_3,
		initGroup, initChannel, this);
	channel.append(*newChannel);
	updateAlphabeticalOrder();
}


// Returns a pointer to a signal channel with a particular native order index.
SignalChannel* SignalGroup::channelByNativeOrder(int index)
{
	for (int i = 0; i < channel.size(); ++i) {
		if (channel[i].nativeChannelNumber == index) {
			return &channel[i];
		}
	}
	return nullptr;
}

// Returns a pointer to a signal channel with a particular alphabetical order index.
SignalChannel* SignalGroup::channelByAlphaOrder(int index)
{
	for (int i = 0; i < channel.size(); ++i) {
		if (channel[i].alphaOrder == index) {
			return &channel[i];
		}
	}
	return nullptr;
}

// Returns a pointer to a signal channel with a particular user-selected order index
SignalChannel* SignalGroup::channelByIndex(int index)
{
	for (int i = 0; i < channel.size(); ++i) {
		if (channel[i].userOrder == index) {
			return &channel[i];
		}
	}
	cerr << "SignalGroup::channelByIndex: index " << index << " not found." << endl;
	return nullptr;
}

// Returns the total number of channels in this signal group.
int SignalGroup::numChannels() const
{
	return channel.size();
}

// Updates the alphabetical order indices of all signal channels in this signal group.
void SignalGroup::updateAlphabeticalOrder()
{
	QString currentFirstName;
	int currentFirstIndex;
	int i, j;
	int size = channel.size();

	// Mark all alphaetical order indices with -1 to indicate they have not yet
	// been assigned an order.
	for (i = 0; i < size; ++i) {
		channel[i].alphaOrder = -1;
	}

	for (i = 0; i < size; ++i) {
		// Find the first remaining non-alphabetized item.
		j = 0;
		while (channel[j].alphaOrder != -1) {
			++j;
		}
		currentFirstName = channel[j].customChannelName;
		currentFirstIndex = j;

		// Now compare all other remaining items.
		while (++j < size) {
			if (channel[j].alphaOrder == -1) {
				if (channel[j].customChannelName.toLower() < currentFirstName.toLower()) {
					currentFirstName = channel[j].customChannelName;
					currentFirstIndex = j;
				}
			}
		}

		// Now assign correct alphabetical order to this item.
		channel[currentFirstIndex].alphaOrder = i;
	}
}

// Restores channels to their original order.
void SignalGroup::setOriginalChannelOrder()
{
	for (int i = 0; i < channel.size(); ++i) {
		channel[i].userOrder = channel[i].nativeChannelNumber;
	}
}

// Orders signal channels alphabetically.
void SignalGroup::setAlphabeticalChannelOrder()
{
	updateAlphabeticalOrder();
	for (int i = 0; i < channel.size(); ++i) {
		channel[i].userOrder = channel[i].alphaOrder;
	}
}

// Diagnostic routine to display all channels in this group (to cout).
void SignalGroup::print() const
{
	cout << "SignalGroup " << name.toStdString() << " (" << prefix.toStdString() <<
		") enabled:" << enabled << endl;

	for (int i = 0; i < channel.size(); ++i)
	{
		cout << "  SignalChannel " << channel[i].nativeChannelNumber << " " << channel[i].customChannelName.toStdString() << " (" <<
			channel[i].nativeChannelName.toStdString() << ")" << endl;
	}
	cout << endl;
}

// Streams all signal channels in this group out to binary data stream.
QDataStream& operator<<(QDataStream &outStream, const SignalGroup &a)
{
	outStream << a.name;
	outStream << a.prefix;
	outStream << (qint16)a.enabled;
	outStream << (qint16)a.numChannels();
	for (int i = 0; i < a.numChannels(); ++i) {
		outStream << a.channel[i];
	}
	return outStream;
}

// Streams all signal channels in this group in from binary data stream.
QDataStream& operator >> (QDataStream &inStream, SignalGroup &a)
{
	qint16 tempQint16;
	int nTotal, nAmps;

	inStream >> a.name;
	inStream >> a.prefix;
	inStream >> tempQint16;
	a.enabled = (bool)tempQint16;
	inStream >> tempQint16;
	nTotal = (int)tempQint16;
	inStream >> tempQint16;
	nAmps = (int)tempQint16;

	// Delete all existing SignalChannel objects in this SignalGroup
	a.channel.clear();

	for (int i = 0; i < nTotal; ++i) {
		inStream >> a.channel[i];
	}
	a.updateAlphabeticalOrder();

	return inStream;
}