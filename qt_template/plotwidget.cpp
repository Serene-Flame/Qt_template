#include "stdafx.h"
#include "plotwidget.h"

#include "mainwindow.h"
#include "maincontroller.h"
#include "signalprocessor.h"
#include "signalsources.h"
#include "plotthread.h"

const short numInputBuffer = 1;
const double sampleRate = 100;

PlotWidget::PlotWidget(int windowID, MainController *initMainController, MainWindow *initMainWindow, QWidget *parent)
{
#ifdef DEBUG
	cout << "PlotWidget::PlotWidget(MainController * initMainController, QWidget *parent)" << endl;
#endif // DEBUG

	setWindowFlags(Qt::Window);

	id = windowID;
	mainController = initMainController;
	mainWindow = initMainWindow;
	signalProcessor = mainController->signalProcessor;
	signalSources = mainController->signalSources;

	numChannels = signalSources->signalGroup[id].numChannels();
	frameList.resize(numChannels);
	waveFrameList.resize(numChannels);
	textFrameList.resize(numChannels);

	inputData_buffer.resize(numChannels);
	for (int i = 0; i < (numChannels); i++)	inputData_buffer[i].resize(numInputBuffer);
	plotDataOld.resize(numChannels);

	plotThread = new PlotThread(this);

	createLayout();

	initializeDisplay();

	startButton_clicked();
}

PlotWidget::~PlotWidget()
{
	delete plotThread;
}

void PlotWidget::closeEvent(QCloseEvent * event)
{
	keepGoing = false;
}

void PlotWidget::drawWaveforms()
{
#ifdef DEBUG
	cout << "PlotWidget::drawWaveforms() " << id << endl;
#endif // DEBUG

	bPlotWaveform = true;

	QPainter painter(&pixmap);
	if (!painter.isActive())
	{
		qDebug() << "drawWaveforms: painter is not active!!!";
		return;
	}
	painter.initFrom(this);
	QPen pen;

	int xOffset, yOffset, length;
	double tStepMsec, xScaleFactor, yScaleFactor;
	double yAxisLength, xAxisLength;
	QRect adjustedFrame, eraseBlock;


	length = numInputBuffer;
	QPointF *polyline = new QPointF[length + 1];

	// Assume all frames are the same size.
	yAxisLength = (waveFrameList[0].height() - 2);
	xAxisLength = waveFrameList[0].width() - 1;

	tStepMsec = 1000.0 / sampleRate;
	xScaleFactor = xAxisLength * tStepMsec / xScale;

	if (keepGoing)
	{
		for (int i = 0; i < waveFrameList.size(); i++)
		{
			xOffset = waveFrameList[i].left() + 1;
			xOffset += tPosition * xAxisLength / xScale;

			// Set clipping region
			adjustedFrame = waveFrameList[i];
			adjustedFrame.adjust(1, 1, 0, 0);
			painter.setClipRect(adjustedFrame);

			// Erase segment of old waveform
			eraseBlock = adjustedFrame;
			eraseBlock.setLeft(xOffset - 1);
			eraseBlock.setRight(xScaleFactor * length + xOffset);
			painter.fillRect(eraseBlock, backgroundColor);

			// Redraw y = 0 axis
			painter.setPen(Qt::yellow);
			painter.drawLine(waveFrameList[i].left(), waveFrameList[i].bottom() - 5, waveFrameList[i].right(), waveFrameList[i].bottom() - 5);
			yScaleFactor = -yAxisLength / yScale;
			yOffset = waveFrameList[i].bottom() - 5;

			// build waveform
			for (int j = 0; j < length; ++j)
			{
				polyline[j + 1] = QPointF(xScaleFactor * j + xOffset, yScaleFactor * inputData_buffer.at(i).at(j) + yOffset);
			}

			// join to old waveform
			if (tPosition == 0.0) {
				polyline[0] = polyline[1];
			}
			else {
				polyline[0] =
					QPointF(xScaleFactor * -1 + xOffset,
						yScaleFactor * plotDataOld.at(i) + yOffset);
			}

			// save last point in waveform to join to next segment
			plotDataOld[i] = inputData_buffer.at(i).at(numInputBuffer - 1);

			// draw waveform
			QPen pen = QPen(plotColor);
			//pen.setWidth(3);
			painter.setPen(pen);

			painter.drawPolyline(polyline, length + 1);

			painter.setClipping(false);

		}

		// draw play bar
		pen = QPen(frameColor);
		painter.setPen(pen);

		painter.drawLine(xScaleFactor * length + 1 + xOffset, frameList[0].top(), xScaleFactor * length + 1 + xOffset, frameList[frameList.size() - 1].bottom());
	}


	tStepMsec = 1000.0 / sampleRate;
	tPosition += length * tStepMsec;
	if (tPosition >= xScale) {
		tPosition = 0.0;
	}

	delete[] polyline;
	bPlotWaveform = false;

	update();
}

QSize PlotWidget::sizeHint() const
{
	int frameH = this->geometry().y() - this->y();
	QRect availGeoRect = QGuiApplication::screens()[0]->availableGeometry();

	return QSize(availGeoRect.width() / 4, availGeoRect.height() / 2 - frameH);
}

void PlotWidget::createLayout()
{
#ifdef DEBUG
	cout << "PlotWidget::createLayout()" << endl;
#endif // DEBUG
	startButton = new QPushButton(tr("&Start"));
	connect(startButton, &QAbstractButton::clicked, this, &PlotWidget::startButton_clicked);
	stopButton = new QPushButton(tr("&Stop"));
	connect(stopButton, &QAbstractButton::clicked, this, &PlotWidget::stopButton_clicked);
	resetButton = new QPushButton(tr("&Reset"));
	connect(resetButton, &QAbstractButton::clicked, this, &PlotWidget::resetButton_clicked);

	modeCombBbox = new QComboBox();
	modeCombBbox->addItem(tr("Dark"));
	modeCombBbox->addItem(tr("Bright"));
	modeCombBbox->setCurrentIndex(0);
	xScaleComboBox = new QComboBox();
	xScaleComboBox->addItem(tr("1"));
	xScaleComboBox->addItem(tr("2"));
	xScaleComboBox->setCurrentIndex(0);
	yScaleComboBox = new QComboBox();
	yScaleComboBox->addItem(tr("1"));
	yScaleComboBox->addItem(tr("2"));
	yScaleComboBox->setCurrentIndex(0);
	
	connect(modeCombBbox, SIGNAL(currentIndexChanged(int)), this, SLOT(modeComboBox_changed(int)));
	connect(xScaleComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(xScaleComboBox_changed(int)));
	connect(yScaleComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(yScaleComboBox_changed(int)));

	plotAreaFrame = new QFrame();

	QHBoxLayout *displayLayout = new QHBoxLayout;
	displayLayout->addWidget(startButton);
	displayLayout->addWidget(stopButton);
	displayLayout->addStretch(1);
	displayLayout->addWidget(new QLabel(tr("mode:")));
	displayLayout->addWidget(modeCombBbox);
	displayLayout->addWidget(new QLabel(tr("xScale:")));
	displayLayout->addWidget(xScaleComboBox);
	displayLayout->addWidget(new QLabel(tr("yScale:")));
	displayLayout->addWidget(yScaleComboBox);
	displayLayout->addWidget(resetButton);

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addLayout(displayLayout);
	mainLayout->addWidget(plotAreaFrame);

	setLayout(mainLayout);
}

void PlotWidget::startButton_clicked()
{
#ifdef DEBUG
	cout << "PlotWidget::start()" << endl;

	for (int k = 0; k < 1; k++)
	{

		for (int i = 0; i < inputData_buffer.size(); i++)
		{
			for (int j = 1; j < numInputBuffer; j++)
			{
				inputData_buffer[i][j] = inputData_buffer.at(i).at(j - 1);
			}
			inputData_buffer[i][0] = k / 2;
		}
		drawWaveforms();
		update();
	}
#endif // DEBUG
	keepGoing = true;
	plotThread->startElapsedTimer();
}

void PlotWidget::stopButton_clicked()
{
#ifdef DEBUG
	cout << "PlotWidget::stop()" << endl;
#endif // DEBUG
	keepGoing = false;
	plotThread->resetUpdateCount();
}

void PlotWidget::resetButton_clicked()
{
#ifdef DEBUG
	cout << "PlotWidget::reset()" << endl;
#endif // DEBUG
}

void PlotWidget::xScaleComboBox_changed(int index)
{
#ifdef DEBUG
	cout << "PlotWidget::xScale(" << index << ")" << endl;
#endif // DEBUG
}

void PlotWidget::yScaleComboBox_changed(int index)
{
#ifdef DEBUG
	cout << "PlotWidget::yScale((" << index << ")" << endl;
#endif // DEBUG
}

void PlotWidget::modeComboBox_changed(int index)
{
#ifdef DEBUG
	cout << "PlotWidget::mode((" << index << ")" << endl;
#endif // DEBUG
}

void PlotWidget::paintEvent(QPaintEvent * /* event */)
{
	QStylePainter stylePainter(this);
	QPoint pt = plotAreaFrame->pos();

	stylePainter.drawPixmap(pt.rx(), pt.ry(), pixmap);
}

void PlotWidget::resizeEvent(QResizeEvent*)
{
	// Pixel map used for double buffering.

	QSize sz = plotAreaFrame->size();
	QRect plotRect = plotAreaFrame->rect();

	pixmap = QPixmap(sz);

	pixmap.fill(backgroundColor);

	initializeDisplay();
}

void PlotWidget::initializeDisplay()
{
	const int rectWidth = plotAreaFrame->width() - 110;
	const int rectHeight = (plotAreaFrame->height() - 10) / frameList.size();

	for (int i = 0; i < frameList.size(); i++)
	{
		frameList[i] = QRect(5, 5 + rectHeight*i, width() - 10, rectHeight);
		waveFrameList[i] = QRect(105, 5 + rectHeight*i, rectWidth, rectHeight);
		textFrameList[i] = QRect(5, 5 + rectHeight*i, 100, rectHeight);
	}

	QPainter painter(&pixmap);

	if (!painter.isActive())
	{
		qDebug() << "drawDragIndicator: Painter is not active!!!";
		return;
	}

	painter.initFrom(this);

	for (int i = 0; i < waveFrameList.size(); i++)
	{
		painter.setPen(frameColor);
		painter.drawRect(waveFrameList.at(i));
		painter.setPen(textColor);
		painter.drawRect(textFrameList.at(i));
		painter.drawText(QPoint(textFrameList[i].left() + 5, textFrameList[i].center().y() + 5), signalSources->signalGroup[id].channelByNativeOrder(i)->customChannelName);
	}


}

// Draw axis lines inside a frame.
void PlotWidget::drawAxisLines(QPainter &painter, int frameNumber)
{
	QRect frame = waveFrameList[frameNumber];
	painter.setPen(Qt::yellow);

	// Draw V = 0V axis line.
	painter.drawLine(frame.left(), frame.center().y(), frame.right(), frame.center().y());
}

bool PlotWidget::isPlotWindow()
{
	return bUpdatePlot;
}

void PlotWidget::setInputData(double * inputdata)
{
#ifdef DEBUG
	cout << "PlotWidget::setInputData(double * inputdata)" << endl;
#endif // DEBUG
	for (int i = 0; i < numChannels; i++)
	{
		for (int j = 1; j < numInputBuffer; j++)
		{
			inputData_buffer[i][j] = inputData_buffer.at(i).at(j - 1);
		}
		inputData_buffer[i][0] = inputdata[i];
	}
}