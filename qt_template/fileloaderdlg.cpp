#include "stdafx.h"
#include "fileloaderdlg.h"
#include "maincontroller.h"

FileLoaderDlg::FileLoaderDlg(MainController * initMainController, QWidget *parent)
	: QDialog(parent)
{
#ifdef DEBUG
	cout << "FileLoaderDlg::FileLoaderDlg(MainController * initMainController, QWidget *parent)" << endl;
#endif // DEBUG
	mainController = initMainController;

	createActions();
	createLayout();
	adjustSize();

	ifstream readFile("modelsetting.txt");

	if (readFile.is_open())
	{
		readFile >> buff;
		modelDirEdit->setText(QString(buff).replace("\n", " "));
		QTableWidgetItem *dirItem = new QTableWidgetItem(QString("Model Directory: ") + modelDirEdit->text(), 0);
		int row = notePadTable->rowCount();
		notePadTable->insertRow(row);
		notePadTable->setItem(row, 0, dirItem);

		readFile >> buff;
		modelTagEdit->setText(QString(buff).replace("\n", " "));
		QTableWidgetItem *tagItem = new QTableWidgetItem(QString("Model Tag: ") + modelTagEdit->text(), 0);
		row = notePadTable->rowCount();
		notePadTable->insertRow(row);
		notePadTable->setItem(row, 0, tagItem);

		readFile >> buff;
		modelKeyEdit->setText(QString(buff).replace("\n", " "));
		QTableWidgetItem *keyItem = new QTableWidgetItem(QString("Model Key: ") + modelKeyEdit->text(), 0);
		row = notePadTable->rowCount();
		notePadTable->insertRow(row);
		notePadTable->setItem(row, 0, keyItem);

		readFile >> buff;
		inputNameEdit->setText(QString(buff).replace("\n", " "));
		QTableWidgetItem *inputNameItem = new QTableWidgetItem(QString("Input Tag: ") + inputNameEdit->text(), 0);
		row = notePadTable->rowCount();
		notePadTable->insertRow(row);
		notePadTable->setItem(row, 0, inputNameItem);

		readFile >> buff;
		inputDimEdit->setText(QString(buff).replace("\n", " "));
		QTableWidgetItem *inputDimItem = new QTableWidgetItem(QString("Input Dimension: ") + inputDimEdit->text(), 0);
		row = notePadTable->rowCount();
		notePadTable->insertRow(row);
		notePadTable->setItem(row, 0, inputDimItem);

		readFile >> buff;
		inputTypeCBox->setCurrentIndex(QString(buff).toInt());
		QTableWidgetItem *inputTypeItem = new QTableWidgetItem(QString("Input Data Type: ") + outputTypeCBox->currentData().toString(), 0);
		row = notePadTable->rowCount();
		notePadTable->insertRow(row);
		notePadTable->setItem(row, 0, inputTypeItem);

		readFile >> buff;
		outputNameEdit->setText(QString(buff).replace("\n", " "));
		QTableWidgetItem *outputNameItem = new QTableWidgetItem(QString("output Tag: ") + outputNameEdit->text(), 0);
		row = notePadTable->rowCount();
		notePadTable->insertRow(row);
		notePadTable->setItem(row, 0, outputNameItem);

		readFile >> buff;
		outputDimEdit->setText(QString(buff).replace("\n", " "));
		QTableWidgetItem *outputDimItem = new QTableWidgetItem(QString("output Dimension: ") + outputDimEdit->text(), 0);
		row = notePadTable->rowCount();
		notePadTable->insertRow(row);
		notePadTable->setItem(row, 0, outputDimItem);

		readFile >> buff;
		outputTypeCBox->setCurrentIndex(QString(buff).toInt());
		QTableWidgetItem *outputTypeItem = new QTableWidgetItem(QString("output Data Type: ") + outputTypeCBox->currentData().toString(), 0);
		row = notePadTable->rowCount();
		notePadTable->insertRow(row);
		notePadTable->setItem(row, 0, outputTypeItem);

		QStringList strlist = QString(inputDimEdit->text()).split(',');
		inputDim_int.resize(strlist.count());
		for (int i = 0; i < strlist.count(); i++)
		{
			inputDim_int[i] = strlist[i].toInt();
		}

		strlist = QString(outputDimEdit->text()).split(',');
		outputDim_int.resize(strlist.count());
		for (int i = 0; i < strlist.count(); i++)
		{
			outputDim_int[i] = strlist[i].toInt();
		}
	}
}

FileLoaderDlg::~FileLoaderDlg()
{
#ifdef DEBUG
	cout << "FileLoaderDlg::~FileLoaderDlg()"  << endl;
#endif // DEBUG
}

void FileLoaderDlg::closeEvent(QCloseEvent * event)
{
#ifdef DEBUG
	cout << "FileLoaderDlg::closeEvent(QCloseEvent * event)" << endl;
#endif // DEBUG
	notePadTable->setRowCount(0);

	ofstream writeFile("modelsetting.txt", ios_base::out);

	if (writeFile.is_open())
	{
		writeFile << modelDirEdit->text().toStdString() << '\n';

		writeFile << modelTagEdit->text().toStdString() << '\n';


		writeFile << modelKeyEdit->text().toStdString() << '\n';


		writeFile << inputNameEdit->text().toStdString() << '\n';


		writeFile << inputDimEdit->text().toStdString() << '\n';


		writeFile << inputTypeCBox->currentIndex() << '\n';


		writeFile << outputNameEdit->text().toStdString() << '\n';


		writeFile << outputDimEdit->text().toStdString() << '\n';


		writeFile << outputTypeCBox->currentIndex() << '\n';


		writeFile << "\n";
		writeFile.close();

		return;
	}

	QTableWidgetItem *sizeItem = new QTableWidgetItem(QString("SAVE ERROR!!"), 0);
	int row = notePadTable->rowCount();
	notePadTable->insertRow(row);
	notePadTable->setItem(row, 0, sizeItem);
}

void FileLoaderDlg::createActions()
{
#ifdef DEBUG
	cout << "FileLoaderDlg::createActions()" << endl;
#endif // DEBUG
}

void FileLoaderDlg::createLayout()
{
#ifdef DEBUG
	cout << "FileLoaderDlg::createLayout()" << endl;
#endif // DEBUG
	modelDirEdit = new QLineEdit("*");
	modelTagEdit = new QLineEdit("*");
	modelTagEdit->setMaximumWidth(100);
	modelKeyEdit = new QLineEdit("*");
	modelKeyEdit->setMaximumWidth(100);
	inputNameEdit = new QLineEdit("*");
	inputDimEdit = new QLineEdit("*");
	inputDimEdit->setMaximumWidth(100);
	outputNameEdit = new QLineEdit("*");
	outputDimEdit = new QLineEdit("*");
	outputDimEdit->setMaximumWidth(100);

	browseButton = new QPushButton(tr("&Browse"));
	browseButton->setMaximumWidth(100);
	connect(browseButton, &QAbstractButton::clicked, this, &FileLoaderDlg::browse);
	setTagButton = new QPushButton(tr("&Set Tag"));
	setTagButton->setMaximumWidth(100);
	connect(setTagButton, &QAbstractButton::clicked, this, &FileLoaderDlg::setTag);
	setKeyButton = new QPushButton(tr("&Set Key"));
	setKeyButton->setMaximumWidth(100);
	connect(setKeyButton, &QAbstractButton::clicked, this, &FileLoaderDlg::setKey);
	resetButton = new QPushButton(tr("&Reset"));
	resetButton->setMaximumWidth(100);
	connect(resetButton, &QAbstractButton::clicked, this, &FileLoaderDlg::reset);
	loadButton = new QPushButton(tr("&load"));
	loadButton->setMaximumWidth(100);
	connect(loadButton, &QAbstractButton::clicked, this, &FileLoaderDlg::load);

	inputTypeCBox = new QComboBox();
	outputTypeCBox = new QComboBox();

	notePadTable = new QTableWidget(0, 1);
	notePadTable->setSelectionBehavior(QAbstractItemView::SelectRows);

	QStringList labels;
	labels << tr("Note");
	notePadTable->setHorizontalHeaderLabels(labels);
	notePadTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
	notePadTable->verticalHeader()->hide();
	notePadTable->setShowGrid(false);
	notePadTable->setContextMenuPolicy(Qt::CustomContextMenu);

	QGridLayout *mainLayout = new QGridLayout(this);
	mainLayout->addWidget(new QLabel(tr("Model Dirictory:")), 0, 0);
	mainLayout->addWidget(modelDirEdit, 0, 1, 1, 4);
	mainLayout->addWidget(browseButton, 0, 5);

	mainLayout->addWidget(new QLabel(tr("Model Tag:")), 1, 0);
	mainLayout->addWidget(modelTagEdit, 1, 1);
	mainLayout->addWidget(setTagButton, 1, 2);
	mainLayout->addWidget(new QLabel(tr("Signature Key:")), 1, 3);
	mainLayout->addWidget(modelKeyEdit, 1, 4);
	mainLayout->addWidget(setKeyButton, 1, 5);

	mainLayout->addWidget(new QLabel(tr("Input Tag:")), 2, 0);
	mainLayout->addWidget(inputNameEdit, 2, 1, 1, 2);
	mainLayout->addWidget(new QLabel(tr("Input Dimention:")), 2, 3);
	mainLayout->addWidget(inputDimEdit, 2, 4);
	mainLayout->addWidget(inputTypeCBox, 2, 5);

	mainLayout->addWidget(new QLabel(tr("Output Tag:")), 3, 0);
	mainLayout->addWidget(outputNameEdit, 3, 1, 1, 2);
	mainLayout->addWidget(new QLabel(tr("Output Dimention:")), 3, 3);
	mainLayout->addWidget(outputDimEdit, 3, 4);
	mainLayout->addWidget(outputTypeCBox, 3, 5);

	mainLayout->addWidget(notePadTable, 4, 0, 1, 6);

	mainLayout->addWidget(resetButton, 5, 4);
	mainLayout->addWidget(loadButton, 5, 5);

	setWindowTitle(tr("Modle Loader"));
	const QRect screenGeometry = QApplication::desktop()->screenGeometry(this);
	resize(screenGeometry.width() / 2, screenGeometry.height() / 3);

}

void FileLoaderDlg::browse()
{
#ifdef DEBUG
	cout << "FileLoaderDlg::browse()" << endl;
#endif // DEBUG
	notePadTable->setRowCount(0);

	QString directory =
		QDir::toNativeSeparators(QFileDialog::getExistingDirectory(this, tr("Find Files"), QDir::currentPath()));

	if (!directory.isEmpty()) {
		modelDirEdit->setText(directory);
	}

}

void FileLoaderDlg::setTag()
{
#ifdef DEBUG
	cout << "FileLoaderDlg::setTag()" << endl;
#endif // DEBUG

}

void FileLoaderDlg::setKey()
{
#ifdef DEBUG
	cout << "FileLoaderDlg::setKey()" << endl;
#endif // DEBUG
}

void FileLoaderDlg::reset()
{
#ifdef DEBUG
	cout << "FileLoaderDlg::reset()" << endl;
#endif // DEBUG
	notePadTable->setRowCount(0);

	modelDirEdit->setText("*");
	modelTagEdit->setText("*");
	modelKeyEdit->setText("*");
	inputNameEdit->setText("*");
	inputDimEdit->setText("*");
	outputNameEdit->setText("*");
	outputDimEdit->setText("*");
}

void FileLoaderDlg::load()
{
#ifdef DEBUG
	cout << "FileLoaderDlg::load()" << endl;
#endif // DEBUG
}