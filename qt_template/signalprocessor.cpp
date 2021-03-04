#include "stdafx.h"
#include "signalprocessor.h"
#include "signalsources.h"
#include "randomnumber.h"

SignalProcessor::SignalProcessor(SignalSources *initSignalSources) 
{
	signalSources = initSignalSources;

	// Set up random number generator in case we are asked to generate synthetic data.
	random = new RandomNumber();
	random->setGaussianAccuracy(6);
}


SignalProcessor::~SignalProcessor()
{
	delete random;
}

void SignalProcessor::deleteThreads()
{

}