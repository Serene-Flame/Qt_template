#ifndef FILELOADERDLG_H
#define FILELOADERDLG_H

class MainController;

class FileLoaderDlg : public QDialog
{
	Q_OBJECT
public:
	FileLoaderDlg(MainController * initMainController, QWidget *parent = 0);
	~FileLoaderDlg();
	void closeEvent(QCloseEvent *event);

private:
	MainController *mainController;

	void createActions();
	void createLayout();

	char  buff[BUFF_SIZE];

	QLineEdit *modelDirEdit;
	QLineEdit *modelTagEdit;
	QLineEdit *modelKeyEdit;
	QLineEdit *inputNameEdit;
	QLineEdit *inputDimEdit;
	QLineEdit *outputNameEdit;
	QLineEdit *outputDimEdit;

	QPushButton *browseButton;
	QPushButton *setTagButton;
	QPushButton *setKeyButton;
	QPushButton *resetButton;
	QPushButton *loadButton;

	QComboBox *inputTypeCBox;
	QComboBox *outputTypeCBox;
	QTableWidget *notePadTable;

	QVector<int64_t> inputDim_int;
	QVector<int64_t> outputDim_int;

	private slots:
	void browse();
	void setTag();
	void setKey();
	void reset();
	void load();
};

#endif // !FILELOADERDLG_H