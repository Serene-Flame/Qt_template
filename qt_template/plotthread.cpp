#include "stdafx.h"
#include "plotthread.h"
#include "plotwidget.h"

PlotThread::PlotThread()
{
	bStop = false;
}

PlotThread::PlotThread(PlotWidget * initPlotWidget)
{
#ifdef DEBUG
	cout << "PlotThread::PlotThread(PlotWidget * initPlotWidget)" << endl;
#endif // DEBUG

	plotWidget = initPlotWidget;
	wndType = 1;
	numUpdateCount = 0;
}

PlotThread::~PlotThread()
{
}

void PlotThread::run()
{
#ifdef DEBUG
	cout << "PlotThread::run()" << endl;
#endif // DEBUG
	switch (wndType)
	{
	case 1:
	{
		mMutex.lock();
		plotWidget->drawWaveforms();

		numUpdateCount++;

		QString str;
		str = QDateTime::fromMSecsSinceEpoch(baseTime.elapsed()).toUTC().toString("hh:mm:ss");

		mMutex.unlock();
		break;
	}
	}
}

void PlotThread::runThread(PlotThread * obj)
{
	obj->run();
}

void PlotThread::resetUpdateCount()
{
	numUpdateCount = 0;
}

void PlotThread::startElapsedTimer()
{
	baseTime.start();
}
