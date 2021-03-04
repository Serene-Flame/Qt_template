#include "stdafx.h"
#include "mainwindow.h"
#include <QtWidgets/QApplication>

map<SignalType, string> SignalType_to_string_map(map_start_values, map_start_values + map_start_values_size);


int main(int argc, char *argv[])
{

#ifdef DEBUG
	for (map<SignalType, string>::const_iterator i = SignalType_to_string_map.begin(); i != SignalType_to_string_map.end(); ++i) {
		cout << i->first << " is " << i->second << endl;
	}
#endif // DEBUG

	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();
}
