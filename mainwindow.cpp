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
	//timer = new QTimer(this);
	//connect(timer, SIGNAL(timeout()), this, SLOT(update()));
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
