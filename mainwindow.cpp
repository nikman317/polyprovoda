#include "mainwindow.h"
#include "ui_mainwindow.h"
#
MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{


	ui->setupUi(this);
	ui->concentationDonor->hide();
	ui->mobilityElectron->hide();
	this->currentbutton = ui->chooseElectronHole;
	this->currentPlot = ui->concentationElectron;
	//createMenu();
	createGraphs();

	temperatureInterval = 200;
	firstTempValue = 100;
	temperature = new double[ui->maxtemp->maximum()];
	concentrationElectronData = new double[ui->maxtemp->maximum()];
	concentrationHolesData = new double[ui->maxtemp->maximum()];

	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
	ui->chooseElectronHole->setStyleSheet(QString::fromUtf8("border-style:solid;"
														 "border-width: 2px;"
														 "border-color: #999999;"
														 "border-radius: 10px;"
														 "background-color: navy;"
														 "color: white"));
	ui->chooseDonorAkceptor->setStyleSheet(QString::fromUtf8("border-style:solid;"
														 "border-width: 2px;"
														 "border-color: #999999;"
														 "border-radius: 10px;"
														 "background-color: white;"
														 "color: black"));
	ui->chooseMobility->setStyleSheet(QString::fromUtf8("border-style:solid;"
														 "border-width: 2px;"
														 "border-color: #999999;"
														 "border-radius: 10px;"
														 "background-color: white;"
														 "color: black"));

	m0Electron = 1.06;
	m0Heoles = 0.56;

	timer->start(500);

}


void MainWindow::createMenu()
{
	QMenu*   pmnu   = new QMenu("&Menu");

	pmnu->addAction("&About Qt");

	pmnu->addSeparator();

	QMenu* pmnuSubMenu = new QMenu("&choose window", pmnu);


	pmnu->addMenu(pmnuSubMenu);

	pmnu->addSeparator();

	pmnu->addAction("&Exit", qApp, SLOT(quit()));

	ui->menuBar->addMenu(pmnu);
	//mnuBar.show();

}


MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::createGraphs()
{

	ui->concentationElectron->setTitle( "Electron concentration" );
	ui->concentationElectron->setCanvasBackground( Qt::white );
	ui->concentationElectron->setAxisTitle(QwtPlot::yLeft, "Concentration");
	ui->concentationElectron->setAxisTitle(QwtPlot::xBottom, "temp");
	ui->concentationElectron->insertLegend( new QwtLegend() );
	QwtPlotGrid *gridTemp = new QwtPlotGrid();
	gridTemp->setMajPen(QPen( Qt::gray, 5 ));
	gridTemp->attach( ui->concentationElectron );
	ui->concentationElectron->setAxisAutoScale(QwtPlot::yLeft);
	ui->concentationElectron->setAxisAutoScale(QwtPlot::xBottom);

	ui->concentationDonor->setTitle( "Donor concentraion" );
	ui->concentationDonor->setCanvasBackground( Qt::white );
	ui->concentationDonor->setAxisTitle(QwtPlot::yLeft, "Concetraion");
	ui->concentationDonor->setAxisTitle(QwtPlot::xBottom, "temp");
	ui->concentationDonor->insertLegend( new QwtLegend() );
	QwtPlotGrid *gridRefl = new QwtPlotGrid();
	gridRefl->setMajPen(QPen( Qt::gray, 5 ));
	gridRefl->attach( ui->concentationDonor );


	ui->mobilityElectron->setTitle( "Mobility Electron" );
	ui->mobilityElectron->setCanvasBackground( Qt::white );
	ui->mobilityElectron->setAxisTitle(QwtPlot::yLeft, "Mobility");
	ui->mobilityElectron->setAxisTitle(QwtPlot::xBottom, "temp");
	ui->mobilityElectron->insertLegend( new QwtLegend() );
	QwtPlotGrid *gridRele = new QwtPlotGrid();
	gridRele->setMajPen(QPen( Qt::gray, 2 ));
	gridRele->attach( ui->mobilityElectron );


}

void MainWindow::on_chooseElectronHole_clicked()
{
	ui->chooseElectronHole->setStyleSheet(QString::fromUtf8("border-style:solid;"
														 "border-width: 2px;"
														 "border-color: #999999;"
														 "border-radius: 10px;"
														 "background-color: navy;"
														 "color: white"));
	this->currentbutton->setStyleSheet(QString::fromUtf8("border-style:solid;"
														 "border-width: 2px;"
														 "border-color: #999999;"
														 "border-radius: 10px;"
														 "background-color: white;"
														 "color: black"));
	this->currentbutton = ui->chooseElectronHole;
	this->currentPlot->hide();
	this->currentPlot = ui->concentationElectron;
	this->currentPlot->show();
}

void MainWindow::on_chooseDonorAkceptor_clicked()
{
	ui->chooseDonorAkceptor->setStyleSheet(QString::fromUtf8("border-style:solid;"
														 "border-width: 2px;"
														 "border-color: #999999;"
														 "border-radius: 10px;"
														 "background-color: navy;"
														 "color: white"));
	this->currentbutton->setStyleSheet(QString::fromUtf8("border-style:solid;"
														 "border-width: 2px;"
														 "border-color: #999999;"
														 "border-radius: 10px;"
														 "background-color: white;"
														 "color: black"));
	this->currentbutton = ui->chooseDonorAkceptor;
	this->currentPlot->hide();
	this->currentPlot = ui->concentationDonor;
	this->currentPlot->show();
}

void MainWindow::on_chooseMobility_clicked()
{
	ui->chooseMobility->setStyleSheet(QString::fromUtf8("border-style:solid;"
														 "border-width: 2px;"
														 "border-color: #999999;"
														 "border-radius: 10px;"
														 "background-color: navy;"
														 "color: white"));
	this->currentbutton->setStyleSheet(QString::fromUtf8("border-style:solid;"
														 "border-width: 2px;"
														 "border-color: #999999;"
														 "border-radius: 10px;"
														 "background-color: white;"
														 "color: black"));
	this->currentbutton = ui->chooseMobility;
	this->currentPlot->hide();
	this->currentPlot = ui->mobilityElectron;
	this->currentPlot->show();
}

void MainWindow::update()
{
	if (currentPlot->title().text() == "Electron concentration")
	{
		ui->concentationElectron->clear();
		QwtPlotCurve *curveC = new QwtPlotCurve("electrones");
		QwtPlotCurve *curveV = new QwtPlotCurve("holes");
		QPen pen(Qt::red, 3, Qt::SolidLine, Qt::SquareCap, Qt::RoundJoin);
		QPen pen2(Qt::blue, 3, Qt::SolidLine, Qt::SquareCap, Qt::RoundJoin);
		curveC->setPen(pen);
		curveV->setPen(pen2);
		for (int i = firstTempValue; i <= firstTempValue + temperatureInterval; i++)
		{
			temperature[i-firstTempValue] = i;
			concentrationElectronData[i-firstTempValue] = 2.51 * pow (10,19)*pow (m0Electron, 1.5)*pow(i/300.,1.5);
			concentrationHolesData[i-firstTempValue] = 2.51 * pow (10,19)*pow (m0Heoles, 1.5)*pow(i/300.,1.5);
		}
		curveC->setData(this->temperature,this->concentrationElectronData, temperatureInterval-1);
		curveC->attach(ui->concentationElectron);
		curveV->setData(this->temperature,this->concentrationHolesData, temperatureInterval-1);
		curveV->attach(ui->concentationElectron);
		ui->concentationElectron->updateAxes();
		ui->concentationElectron->replot();
	}
}

void MainWindow::on_mintemp_editingFinished()
{
	if (ui->maxtemp->value() > ui->mintemp->value())
	{
		if ((ui->maxtemp->value() - ui->mintemp->value()) != temperatureInterval)
		{
			temperatureInterval = (ui->maxtemp->value() - ui->mintemp->value());
			firstTempValue = ui->mintemp->value();
			/*delete[] temperature;
			delete[] concentrationElectronData;
			delete[] concentrationHolesData;

			temperature = new double[temperatureInterval];
			concentrationElectronData = new double[temperatureInterval];
			concentrationHolesData = new double[temperatureInterval];*/
		}
	}
	else
	{
		ui->mintemp->setValue(temperature[0]);
	}
}

void MainWindow::on_maxtemp_editingFinished()
{
	if (ui->maxtemp->value() > ui->mintemp->value())
	{
		if ((ui->maxtemp->value() - ui->mintemp->value()) != temperatureInterval)
		{
			temperatureInterval = (ui->maxtemp->value() - ui->mintemp->value());
			firstTempValue = ui->mintemp->value();
			/*delete temperature;
			delete concentrationElectronData;
			delete concentrationHolesData;

			temperature = new double[temperatureInterval];
			concentrationElectronData = new double[temperatureInterval];
			concentrationHolesData = new double[temperatureInterval];*/
		}
	}
	else
	{
		ui->maxtemp->setValue(temperature[0]);
	}
}

void MainWindow::on_mc_editingFinished()
{
	m0Electron = ui->mc->value();
}

void MainWindow::on_mv_editingFinished()
{
	m0Heoles = ui->mv->value();
}
