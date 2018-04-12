#pragma once

#include <QWidget>
#include <QImage>
#include <QColor>
#include <QtWidgets>
#include <QMessageBox>

struct S {
	double xz;
	double yz;
	double yk;
	double w;

	bool operator <(const S& P);
};

struct aktivneH {
	int riadok;
	int hrana;
};

class QtClass : public QWidget
{
	Q_OBJECT

protected:
	void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
	void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
public:
	QtClass(QWidget *parent = Q_NULLPTR);
	~QtClass();
	void newImage(int x, int y);
	QImage *img;
	int row;
	QRgb* data;
	QVector<QPoint> Point;
	QColor colorSpoje;
	QColor vypln;
	QVector<S> TH;
	QVector<aktivneH> TAH;
	int ymin,ymax;
	bool coloring = 0;

	void vyber_farby();
	void initImage();
	void setPixel(int x, int y, QColor color);
	void DDA(QPoint A, QPoint B, QColor color);
	void vyfarbenie();
	void tabulkaHran();
	void tabulkaAktivnychHran();
	void min_max();


	void vymaz();
	void spoje();
	
};

