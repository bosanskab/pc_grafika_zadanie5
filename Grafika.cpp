#include "Grafika.h"

Grafika::Grafika(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.scrollArea->setWidget(&this->widgetNaKreslenie);

	widgetNaKreslenie.newImage(719, 485); 
	widgetNaKreslenie.initImage();

	ui.vymaz->setVisible(false);
	
}

void Grafika::on_vymaz_clicked() {
	widgetNaKreslenie.newImage(719, 485);
	widgetNaKreslenie.vymaz();

	widgetNaKreslenie.initImage();

	ui.spoje->setVisible(true);
	ui.vymaz->setVisible(false);

}

void Grafika::createImage(){
	ui.scrollArea->setWidget(&widgetNaKreslenie);
	ui.scrollArea->setBackgroundRole(QPalette::Dark);
	widgetNaKreslenie.newImage(ui.scrollArea->width(), ui.scrollArea->height());
}

void Grafika::on_spoje_clicked() {
	if (widgetNaKreslenie.Point.size()<3) {
		widgetNaKreslenie.spoje();
	}
	else {
		ui.vymaz->setVisible(true);
		ui.spoje->setVisible(false);
		widgetNaKreslenie.tabulkaHran();
		widgetNaKreslenie.min_max();
		widgetNaKreslenie.tabulkaAktivnychHran();
		widgetNaKreslenie.vyfarbenie();
		widgetNaKreslenie.spoje();
		widgetNaKreslenie.coloring = 0;
	}
}
