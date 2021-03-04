#ifndef PLOTTHREAD_H
#define PLOTTHREAD_H

class PlotWidget;

class PlotThread : public QThread
{
public:
	PlotThread();
	PlotThread(PlotWidget *initPlotWidget);
	~PlotThread();

	void run();
	static void runThread(PlotThread *obj);

	void stop()
	{
		resetUpdateCount();
		bStop = true;
		bUpdatePlot = false;
	}

	bool bStop;
	bool bUpdatePlot;
	PlotWidget *plotWidget;
	int wndType = 0; //1 for WavePlot, 2 for SpikeDlg
	QMutex mMutex;
	void resetUpdateCount();
	void startElapsedTimer();

private:
	uint64_t numUpdateCount = 0;
	QElapsedTimer baseTime;
};
#endif

