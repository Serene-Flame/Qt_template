#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

class SignalProcessor;
class SignalSources;
class MainController;
class MainWindow;
class PlotThread;

class PlotWidget : public QWidget
{
	Q_OBJECT
public:
	PlotWidget(int windowID, MainController *initMainController, MainWindow *initMainWindow, QWidget *parent = nullptr);
	~PlotWidget();
	void closeEvent(QCloseEvent *event);
	void drawWaveforms();

	bool isPlotWindow();
	void setInputData(double * inputdata);

	int id;
	bool bPlotWaveform = false;
	bool keepGoing = false;
	PlotThread *plotThread;

protected:
	void paintEvent(QPaintEvent *event);
	void resizeEvent(QResizeEvent* event);

	QSize sizeHint() const;

private:
	QPixmap pixmap;
	void initializeDisplay();
	void drawAxisLines(QPainter &painter, int frameNumber);

	MainWindow *mainWindow;
	MainController *mainController;
	SignalProcessor *signalProcessor;
	SignalSources *signalSources;

	void createLayout();

	QPushButton *resetButton;
	QPushButton *startButton;
	QPushButton *stopButton;

	QComboBox *modeCombBbox;
	QComboBox *xScaleComboBox;
	QComboBox *yScaleComboBox;

	QFrame *plotAreaFrame;
	
	QVector<QRect> frameList;
	QVector<QRect> waveFrameList;
	QVector<QRect> textFrameList;

	QVector<QVector<double>> inputData_buffer;
	QVector<double> plotDataOld;

	int xScale = 1000;
	int yScale = 10;
	double tPosition = 0;
	int numChannels;

	bool bUpdatePlot = false;

public slots:
	void startButton_clicked();
	void stopButton_clicked();
	void resetButton_clicked();
	void xScaleComboBox_changed(int index);
	void yScaleComboBox_changed(int index);
	void modeComboBox_changed(int index);
};

#endif // !PLOTDLG_H