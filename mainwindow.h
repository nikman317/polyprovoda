#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <qwt_plot.h>
#include <qwt_plot_grid.h>
#include <qwt_legend.h>
#include <qwt_plot_curve.h>
#include <qwt_symbol.h>
#include <qwt_plot_magnifier.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_picker.h>
#include <qwt_picker_machine.h>
#include <qwt_plot_zoomer.h>
#include <QPushButton>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void on_chooseElectronHole_clicked();

	void on_chooseDonorAkceptor_clicked();

	void on_chooseMobility_clicked();

	void update();


	void on_mintemp_editingFinished();

	void on_maxtemp_editingFinished();

	void on_mc_editingFinished();

	void on_mv_editingFinished();

private:
	Ui::MainWindow *ui;

	QwtPlot *currentPlot;
	QPushButton * currentbutton;
	QTimer* timer;
	double* concentrationElectronData;
	double* concentrationHolesData;
	double* temperature;
	int temperatureInterval;
	int firstTempValue;
	double m0Electron;
	double m0Heoles;
void createGraphs();
void createMenu();
};

#endif // MAINWINDOW_H
