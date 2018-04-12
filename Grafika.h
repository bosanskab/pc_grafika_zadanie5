#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Grafika.h"
#include <QDebug>
#include "QtClass.h"

class Grafika : public QMainWindow
{
	Q_OBJECT

public:
	Grafika(QWidget *parent = Q_NULLPTR);
public slots:
	void createImage();
	void on_vymaz_clicked();
	void on_spoje_clicked();
private:
	Ui::GrafikaClass ui;
	QtClass widgetNaKreslenie; 
};
