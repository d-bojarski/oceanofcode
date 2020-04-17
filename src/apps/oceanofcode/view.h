#pragma once

#include "grid.h"
#include "player.h"
#include "tile.h"

#include <string>

#include <qwidget.h>
#include <qrect.h>
#include <qpixmap.h>
#include <qpushbutton.h>
#include <qlabel.h>

class View : public QWidget
{
	Q_OBJECT
public:
	View(QWidget *parent = nullptr);

	void fillGround(const Grid& grid, const std::vector<Tile>& tiles);
	int groundBoxSize(int index);
	int groundMargin(int index);

	void paintEvent(QPaintEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;

public slots:
	void updateView();
	void snapshot(int turnCount, const QString& name, const Grid& grid);


private:
	void snapshotThreaded(int turnCount, const QString& name, const Grid& grid);


public:
	Player* player0;
	Player* player1;

private:
	QRect _gridRect;
	QImage _snapshotImage;
	QImage _backgroundImage;
	double _ratio;
	int _offsetX;
	int _offsetY;
	int _borderBoxSize;
	int _insideBoxSize;
	int _smallMargin;
	int _largeMargin;

	QPushButton* _regenerateButton;
	QLabel* _tooltip;
};