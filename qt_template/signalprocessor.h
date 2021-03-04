#ifndef SIGNALPROCESSOR_H
#define SIGNALPROCESSOR_H

class SignalSources;
class RandomNumber;

class SignalProcessor
{
public:
	SignalProcessor(SignalSources *initSignalSources);
	~SignalProcessor();

	SignalSources *signalSources;

private:
	RandomNumber *random;

	void deleteThreads();
};

#endif // SIGNALPROCESSOR_H