#include "stdafx.h"
#include "mainwindow.h"
#include "maincontroller.h"

#include "signalsources.h"
#include "fileloaderdlg.h"
#include "plotwidget.h"
#include "plotthread.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	mainController = new MainController(this);
	
	fileLoaderDlg = nullptr;
	for (int i = 0; i < NUM_SIGNAL_GROUP; i++)	plotWidget[i] = nullptr;

	initUIs();
}

MainWindow::~MainWindow()
{

}

void MainWindow::closeEvent(QCloseEvent * event)
{
#ifdef DEBUG
	cout << "MainWindow::close()" << endl;
#endif // DEBUG

	if (fileLoaderDlg) fileLoaderDlg->close();
	for (int i = 0; i < NUM_SIGNAL_GROUP; i++)	plotWidget[i]->close();

	event->accept();
}

void MainWindow::initUIs()
{
	createActions();
	createMenus();
	createLayout();

	QString message = tr("get ready");
	statusBar()->showMessage(message);

	setMinimumSize(160, 160);
	resize(280, 240);
}

void MainWindow::createActions()
{
	newAct = new QAction(tr("&New"), this);
	newAct->setShortcuts(QKeySequence::New);
	newAct->setStatusTip(tr("Create a new file"));
	connect(newAct, &QAction::triggered, this, &MainWindow::newFile);

	openAct = new QAction(tr("&Open..."), this);
	openAct->setShortcuts(QKeySequence::Open);
	openAct->setStatusTip(tr("Open an existing file"));
	connect(openAct, &QAction::triggered, this, &MainWindow::open);

	saveAct = new QAction(tr("&Save"), this);
	saveAct->setShortcuts(QKeySequence::Save);
	saveAct->setStatusTip(tr("Save the document to disk"));
	connect(saveAct, &QAction::triggered, this, &MainWindow::save);

	exitAct = new QAction(tr("E&xit"), this);
	exitAct->setShortcuts(QKeySequence::Quit);
	exitAct->setStatusTip(tr("Exit the application"));
	connect(exitAct, &QAction::triggered, this, &QWidget::close);

	resetAct = new QAction(tr("&Reset"), this);
	resetAct->setStatusTip(tr("Reset the application"));
	connect(resetAct, &QAction::triggered, this, &MainWindow::reset);
}

void MainWindow::createMenus()
{
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(newAct);
	fileMenu->addAction(openAct);
	fileMenu->addAction(saveAct);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAct);

	editMenu = menuBar()->addMenu(tr("&Edit"));
	editMenu->addAction(resetAct);
}

void MainWindow::createLayout()
{
	QWidget *topFiller = new QWidget;
	topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	PushButton1 = new QPushButton(tr("&PushButton1(file loader sample)"));
	PushButton2 = new QPushButton(tr("&PushButton2(device connect sample)"));
	PushButton3 = new QPushButton(tr("&PushButton3(plot window sample)"));
	PushButton4 = new QPushButton(tr("&PushButton4(plot start sample)"));
	PushButton3->setEnabled(false);
	PushButton4->setEnabled(false);

	connect(PushButton1, SIGNAL(clicked()), this, SLOT(PushButton1_clicked()));
	connect(PushButton2, SIGNAL(clicked()), this, SLOT(PushButton2_clicked()));
	connect(PushButton3, SIGNAL(clicked()), this, SLOT(PushButton3_clicked()));
	connect(PushButton4, SIGNAL(clicked()), this, SLOT(PushButton4_clicked()));

	QWidget *bottomFiller = new QWidget;
	bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	QVBoxLayout *pushButtonLayout = new QVBoxLayout;
	pushButtonLayout->setMargin(5);
	pushButtonLayout->addWidget(PushButton1);
	pushButtonLayout->addWidget(PushButton2);
	pushButtonLayout->addWidget(PushButton3);
	pushButtonLayout->addWidget(PushButton4);

	mainWidget = new QWidget;
	mainWidget->setLayout(pushButtonLayout);

	setCentralWidget(mainWidget);
	adjustSize();
}

void MainWindow::newFile()
{
#ifdef DEBUG
	cout << "MainWindow::newFile()" << endl;
#endif // DEBUG
}

void MainWindow::open()
{
#ifdef DEBUG
	cout << "MainWindow::open()" << endl;
#endif // DEBUG
}

void MainWindow::save()
{
#ifdef DEBUG
	cout << "MainWindow::save()" << endl;
#endif // DEBUG
}

void MainWindow::reset()
{
#ifdef DEBUG
	cout << "MainWindow::reset()" << endl;
#endif // DEBUG
}

void MainWindow::PushButton1_clicked()
{
#ifdef DEBUG
	cout << "MainWindow::PushButton1_clicked()" << endl;
#endif // DEBUG

	if (!fileLoaderDlg)	fileLoaderDlg = new FileLoaderDlg(mainController);

	fileLoaderDlg->show();
}

void MainWindow::PushButton2_clicked()
{
#ifdef DEBUG
	cout << "MainWindow::PushButton2_clicked()" << endl;
#endif // DEBUG

	mainController->connect();

	for (size_t i = 0; i < NUM_SIGNAL_GROUP; i++)
		plotWidget[i] = new PlotWidget(i, mainController, this, this);

	PushButton3->setEnabled(true);
	PushButton4->setEnabled(true);
}

void MainWindow::PushButton3_clicked()
{
#ifdef DEBUG
	cout << "MainWindow::PushButton3_clicked()" << endl;
#endif // DEBUG

	for (size_t i = 0; i < NUM_SIGNAL_GROUP; i++)
	{
		plotWidget[i]->show();
		plotWidget[i]->setWindowTitle(QString("PlotWindow ") + mainController->signalSources->signalGroup[i].name);
	}
}

void MainWindow::PushButton4_clicked()
{
#ifdef DEBUG
	cout << "MainWindow::PushButton4_clicked()" << endl;
	QElapsedTimer timer;
	timer.start();
#endif // DEBUG
	QElapsedTimer timer;
	timer.start();

	if (false)
	{
		for (int k = 0; k < 100; k++)
		{
			for (int i = 0; i <NUM_SIGNAL_GROUP; i++)
			{
				if (plotWidget[i] != nullptr)
				{
					double input[15] = { k%10,  k % 10, k % 10, k % 10, k % 10, k % 10, k % 10, k % 10, k % 10 ,k % 10 ,k % 10 / 2,k % 10 / 2,k % 10 / 2,k % 10 / 2,k % 10 / 2 };
					plotWidget[i]->setInputData(input);
					plotWidget[i]->plotThread->start();
					plotWidget[i]->plotThread->wait();
				}
			}
			qApp->processEvents();  // Stay responsive to GUI events during this loop
		}
	}
	else
	{
		QFutureWatcher<void> *watcherListWaveform = new QFutureWatcher<void>[NUM_SIGNAL_GROUP];

		for (int k = 0; k < 100; k++)
		{
			for (int i = 0; i <NUM_SIGNAL_GROUP; i++)
			{
				if (plotWidget[i] != nullptr)
				{
					double input[15] = { k % 10,  k % 10, k % 10, k % 10, k % 10, k % 10, k % 10, k % 10, k % 10 ,k % 10 ,k % 10 / 2,k % 10 / 2,k % 10 / 2,k % 10 / 2,k % 10 / 2 };
					plotWidget[i]->setInputData(input);

					QFuture<void> task = QtConcurrent::run(PlotThread::runThread, plotWidget[i]->plotThread);
					watcherListWaveform[i].setFuture(task);

					watcherListWaveform[i].waitForFinished();
				}
			}
			qApp->processEvents();  // Stay responsive to GUI events during this loop
		}

		delete[]watcherListWaveform;
	}

	cout << "thread 100 loop time : " << timer.elapsed() << endl;;

#ifdef DEBUG
	cout << "thread 100 loop time : " << timer.elapsed() << endl;;
#endif // DEBUG

}
