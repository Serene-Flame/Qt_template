#ifndef MAINCONTROL_H
#define MAINCONTROL_H

#include <QThread>

class MainWindow;
class SignalProcessor;
class SignalSources;

class MainController :public QThread
{
	Q_OBJECT
public:
	MainController(MainWindow *initMainWindow);
	~MainController();

	void connect();

	MainWindow *mainWindow;
	SignalProcessor *signalProcessor;
	SignalSources *signalSources;
private:
	void run();
};
#endif // !MAINCONTROL_H


