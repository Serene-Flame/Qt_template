#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>

class MainController;
class FileLoaderDlg;
class PlotWidget;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();
	void closeEvent(QCloseEvent *event);

private:
	void initUIs();
	void createActions();
	void createMenus();
	void createLayout();

	MainController *mainController;

	FileLoaderDlg *fileLoaderDlg;
	PlotWidget *plotWidget[NUM_SIGNAL_GROUP];
	
	QAction *newAct;
	QAction *openAct;
	QAction *saveAct;
	QAction *exitAct;
	QAction *resetAct;

	QMenu *fileMenu;
	QMenu *editMenu;

	QPushButton *PushButton1;
	QPushButton *PushButton2;
	QPushButton *PushButton3;
	QPushButton *PushButton4;

	QWidget *mainWidget;

private slots:
	void newFile();
	void open();
	void save();
	void reset();

	void PushButton1_clicked();
	void PushButton2_clicked();
	void PushButton3_clicked();
	void PushButton4_clicked();

};

#endif // MAINWINDOW_H
