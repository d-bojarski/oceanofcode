#pragma once

#include <qwidget.h>
#include <qpixmap.h>
#include <qpushbutton.h>

#include "grid.h"
#include "tile.h"

class View : public QWidget
{
public:
	View(QWidget *parent = nullptr);

	void fillGround(const Grid& grid, const std::vector<Tile>& tiles);
	int groundBoxSize(int index);
	int groundMargin(int index);

	void paintEvent(QPaintEvent* event) override;


private:
	QImage backgroundImage;
	double ratio;
	int offsetX;
	int offsetY;
	int borderBoxSize;
	int insideBoxSize;
	int smallMargin;
	int largeMargin;

	QPushButton* regenerateButton;
};