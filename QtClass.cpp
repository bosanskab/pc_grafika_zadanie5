#include "QtClass.h"


bool S::operator< (const S &P) {

		if (P.yz < yz) {

			return true;
		}
		else if (P.xz < xz && P.yz == yz) {
		
			return true;
		}
		else if (P.w < w && P.xz == xz && P.yz == yz) {

			return true;
		}
		else return false;
	
}


QtClass::QtClass(QWidget *parent)
	: QWidget(parent)
{
	vyber_farby();
}

QtClass::~QtClass(){
}

void QtClass::vyber_farby() {
	QMessageBox msgBox;
	msgBox.setText(QStringLiteral("Zadaj farbu spojov  "));
	msgBox.exec();
	colorSpoje = QColorDialog::getColor(Qt::magenta, this);
	
	msgBox.setText(QStringLiteral("Zadaj farbu vypln   "));
	msgBox.exec();
	vypln = QColorDialog::getColor(Qt::blue, this);
	coloring = 1;
}

void QtClass::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	QRect area = event->rect();
	painter.drawImage(area, *img, area);
}

void QtClass::vymaz() {
	Point.clear();
	TH.clear();
	TAH.clear();
	ymin = 0;
	ymax = 0;
	coloring = 1;
}


void QtClass::newImage(int x, int y){
	img = new QImage(x, y, QImage::Format_ARGB32);
	img->fill(Qt::white);
	this->setMinimumSize(img->size()); 

	update(); 
}

void QtClass::setPixel(int x, int y, QColor color) {
	data[x + y * row] = color.rgb();
}


void QtClass::mousePressEvent(QMouseEvent *event) {
	if (coloring == 1) {
		if (event->button() == Qt::LeftButton) {
			Point.push_back(event->pos());
			setPixel(event->pos().x(), event->pos().y(), colorSpoje);
			setPixel(event->pos().x() + 1, event->pos().y(), colorSpoje);
			setPixel(event->pos().x(), event->pos().y() + 1, colorSpoje);
			setPixel(event->pos().x(), event->pos().y() - 1, colorSpoje);
			setPixel(event->pos().x() - 1, event->pos().y(), colorSpoje);
			setPixel(event->pos().x() + 1, event->pos().y() + 1, colorSpoje);
			setPixel(event->pos().x() - 1, event->pos().y() - 1, colorSpoje);
			setPixel(event->pos().x() + 1, event->pos().y() - 1, colorSpoje);
			setPixel(event->pos().x() - 1, event->pos().y() + 1, colorSpoje);

		}

		update();
	}
}


void QtClass::DDA(QPoint A, QPoint B, QColor color) {
	double m, x, y;
	QPoint C;

	m = (B.y() - A.y()) / (double)(B.x() - A.x());

	if ((fabs(m)) <= 1) {
		if (A.x() > B.x()) {
			C = B;
			B = A;
			A = C;
		}
		x = A.x();
		y = A.y();
		for (int i = A.x(); i < B.x(); i++) {
			x = x + 1;
			y = y + m;
			setPixel(x, y, color);
		}

	}
	else {
		if (A.y() > B.y()) {
			C = B;
			B = A;
			A = C;
		}
		x = A.x();
		y = A.y();
		for (int i = A.y(); i < B.y(); i++) {
			x = x + 1 / m;
			y = y + 1;
			setPixel(x, y, color);
		}

	}
}
	

void QtClass::tabulkaHran(){
	
	S s;

	for (int i = 1; i <= Point.size(); i++) {
		if (i < Point.size()) {
			if (Point[i - 1].y()== Point[i].y()) {

			}
			else {
				if (Point[i - 1].y() < Point[i].y()) {
					s.xz = Point[i - 1].x();
					s.yz = Point[i - 1].y();
					s.yk = Point[i].y() - 1;
					s.w = (Point[i - 1].x() - Point[i].x()) / (double)(Point[i - 1].y() - Point[i].y());
				}
				else {
					s.xz = Point[i].x();
					s.yz = Point[i].y();
					s.yk = Point[i - 1].y() - 1;
					s.w = (Point[i - 1].x() - Point[i].x()) / (double)(Point[i - 1].y() - Point[i].y());
				}
				TH.push_back(s);
			}
		}
		else {
			if (Point[Point.size() - 1].y() == Point[0].y()) {

			}
			else {
				if (Point[Point.size() - 1].y() < Point[0].y()) {
					s.xz = Point[Point.size() - 1].x();
					s.yz = Point[Point.size() - 1].y();
					s.yk = Point[0].y() - 1;
					s.w = (Point[Point.size() - 1].x() - Point[0].x()) / (double)(Point[Point.size() - 1].y() - Point[0].y());
				}
				else {
					s.xz = Point[0].x();
					s.yz = Point[0].y();
					s.yk = Point[Point.size() - 1].y()-1;
					s.w = (Point[Point.size() - 1].x() - Point[0].x()) / (double)(Point[Point.size() - 1].y() - Point[0].y());

				}
				TH.push_back(s);
			}
		}
	}

	std::sort(TH.begin(), TH.end());

}

void QtClass::min_max() {
	if (TH[0].yz>TH[0].yk) {
		ymin = TH[0].yk;
		ymax = TH[0].yz;
	}
	else {
		ymin = TH[0].yz;
		ymax = TH[0].yk;
	}

	for (int i = 0; i < TH.size(); i++) {
		if (TH[i].yz>ymax) {
			ymax = TH[i].yz;
		}
		if (TH[i].yk>ymax) {
			ymax = TH[i].yk;
		}
		if (TH[i].yz<ymin) {
			ymin = TH[i].yz;
		}
		if (TH[i].yk<ymin) {
			ymin = TH[i].yk;
		}
	}
}



void QtClass::tabulkaAktivnychHran() {
	aktivneH H;

	for (int j = ymin; j <= ymax; j++) {
		for (int i = 0; i < TH.size(); i++) {
			if ((TH[i].yz >= j && TH[i].yk <= j) || (TH[i].yk >= j && TH[i].yz <= j)) {
				H.riadok = j;
				H.hrana = i;
				TAH.push_back(H);
			}

		}
	}	
	
}

void QtClass::vyfarbenie(){	
	QVector<int> spoj;

	for (int j = ymin; j <= ymax; j++) {
		for (int i = 0; i < TAH.size(); i++) {
			if (TAH[i].riadok == j)
				spoj.push_back(i);
		}
		

		double *xn= new double[spoj.size()];

		for (int o = 0; o < spoj.size(); o++) {
			xn[o] = TH[TAH[spoj[o]].hrana].xz + (TH[TAH[spoj[o]].hrana].w*(j - TH[TAH[spoj[o]].hrana].yz));
		}

		
		for (int i = 0; i < spoj.size() - 1; i++) {
			for (int o = 0; o < spoj.size() - i - 1; o++) {
				if (xn[i] > xn[i + 1])
					std::swap(xn[i], xn[i + 1]);
			}
		}
		
		for (int i = 0; i < spoj.size() - 1; i++) {
			for (int o = 0; o < spoj.size() - i - 1; o++) {
				if (xn[i] > xn[i + 1])
					std::swap(xn[i], xn[i + 1]);
			}
		}

		for (int i = 0; i < spoj.size()-1; i+=2) {
			if (xn[i] < xn[i + 1]) {
				for (int x = xn[i]; x < xn[i + 1]; x++) {
					setPixel(round(x), j, vypln);
				}
			}
			else {
				for (int x = xn[i+1]; x <xn[i]; x++) {
					setPixel(round(x), j, vypln);
				}
			}
		}	
		
		spoj.clear();
		delete[] xn;
	}

}


void QtClass::spoje() {
	if (Point.size() < 3){
		QMessageBox msgBox;
		msgBox.setText(QStringLiteral("Malo bodov!"));
		msgBox.exec();
	}
	else {
		
		for (int i = 1; i <= Point.size(); i++) {
			if (i != Point.size()) {
				DDA(Point[i-1],Point[i], colorSpoje);
			}
			else {
				DDA(Point[i-1], Point[0], colorSpoje);
			}
		}
	}
	update();
}


void QtClass::initImage(){
	this->resize(img->size());
	this->setMinimumSize(img->size());

	row = img->bytesPerLine() / 4;
	data = (QRgb *)img->bits();
}



