#include "stdafx.h"
#include "maincontroller.h"
#include "mainwindow.h"
#include "signalprocessor.h"
#include "signalsources.h"

MainController::MainController(MainWindow *initMainWindow)
{
#ifdef DEBUG
	cout << "MainController(MainWindow *initMainWindow)" << endl;
#endif // DEBUG

	mainWindow = initMainWindow;
	signalProcessor = nullptr;
	signalSources = nullptr;
}

MainController::~MainController()
{
	delete signalSources;
	delete signalProcessor;
}

void MainController::connect()
{
#ifdef DEBUG
	cout << "MainController::connect()" << endl;
#endif // DEBUG

	signalSources = new SignalSources(NUM_SIGNAL_GROUP);
	signalProcessor = new SignalProcessor(signalSources);

	for (int group = 0; group < NUM_SIGNAL_GROUP; group++)
	{
		int numChannel = 0;

		for (int j = 0; j < NUM_SignalType_1; j++)
			signalSources->signalGroup[group].addSignalType1Channel(numChannel++, SignalType_1, j);

		for (int j = 0; j < NUM_SignalType_2; j++)
			signalSources->signalGroup[group].addSignalType2Channel(numChannel++, SignalType_2, j);

		for (int j = 0; j < NUM_SignalType_3; j++)
			signalSources->signalGroup[group].addSignalType3Channel(numChannel++, SignalType_3, j);

		signalSources->signalGroup[group].enabled = true;

#ifdef DEBUG
		cout << '\n' << "signalGroup[" << group << "] numChannel : " << signalSources->signalGroup[group].numChannels() << endl;
		signalSources->signalGroup[group].print();
#endif // DEBUG
	}
}

void MainController::run()
{
#ifdef DEBUG
	cout << "MainControl::run()" << endl;
#endif // DEBUG

}
