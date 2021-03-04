#ifndef STDAFX_H
#define STDAFX_H

//#define DEBUG

#include <QtWidgets>
#include <QDialog>
#include <QTime>
#include <QDir>
#include <qmath.h>
#include "QtConcurrent\qtconcurrentrun.h"

#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <fstream>
#include <map>

using namespace std;

//////////////////////////////////////////////////////
#define NUM_SIGNAL_GROUP 2
#define NUM_SignalType_1 4
#define NUM_SignalType_2 8
#define NUM_SignalType_3 3

#define BUFF_SIZE 1024
//////////////////////////////////////////////////////
const QString signalGroup_Name = "Group ";


enum SignalType {
	SignalType_1,
	SignalType_2,
	SignalType_3,
};

typedef pair<SignalType, string> stringpair_t;

const stringpair_t map_start_values[] = {
	stringpair_t(SignalType_1, "SignalType_1"),
	stringpair_t(SignalType_2, "SignalType_2"),
	stringpair_t(SignalType_3, "SignalType_3"),
};

const int map_start_values_size = sizeof(map_start_values) / sizeof(map_start_values[0]);

extern map <SignalType, string> SignalType_to_string_map;

//////////////////////////////////////////////////////
const QColor backgroundColor = Qt::black;
const QColor frameColor = Qt::darkGray;
const QColor frameSelectColor = Qt::darkRed;
const QColor textColor = Qt::yellow;
const QColor plotColor = Qt::cyan;

#endif 