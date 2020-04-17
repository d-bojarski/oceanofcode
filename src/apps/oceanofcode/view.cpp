#include "view.h"

#include <iostream>

#include <qstring.h>
#include <qpainter.h>
#include <qgridlayout.h>
#include <qapplication.h>
#include <qdir.h>
#include <qtconcurrentrun.h>
#include <qevent.h>
#include <QtCore\qfuture.h>

View::View(QWidget* parent) :
	QWidget(parent),
	player0(nullptr),
	player1(nullptr),
	_gridRect(),
	_snapshotImage(),
	_backgroundImage(),
	_ratio(0.8),
	_offsetX(513),
	_offsetY(93),
	_borderBoxSize(55 + 1),
	_insideBoxSize(57 + 1),
	_smallMargin(2),
	_largeMargin(6)
{
	_backgroundImage.load(":/images/background.jpg");

	setFixedWidth(_backgroundImage.width() * _ratio);
	setFixedHeight(_backgroundImage.height() * _ratio);
	setMouseTracking(true);


	_regenerateButton = new QPushButton("Regenerate", this);
	_regenerateButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	QGridLayout* layout = new QGridLayout(this);
	layout->setMargin(0);

	QGridLayout* buttonLayout = new QGridLayout();
	buttonLayout->addWidget(_regenerateButton, 0, 0);
	buttonLayout->setMargin(20);
	layout->addLayout(buttonLayout, 0, 0);

	// Horizontal spacer.
	QWidget* empty = new QWidget(this);
	empty->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	layout->addWidget(empty, 0, 1);

	// Vertical spacer.
	empty = new QWidget(this);
	empty->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
	layout->addWidget(empty, 1, 0);

	this->setLayout(layout);

	_tooltip = new QLabel(this);
	_tooltip->setStyleSheet("background-color: rgba(18,18,18,1); color: white");
	_tooltip->setAlignment(Qt::AlignCenter);
	_tooltip->setFixedSize(110, 25);
	_tooltip->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	QFont font = _tooltip->font();
	font.setPointSize(14);
	_tooltip->setFont(font);
	layout->addWidget(_tooltip, 2, 2);

	// Remove snapshot folder.
	QDir dir(QStringLiteral("%1/images").arg(QString(IMAGE_PATH)));
	bool removed = dir.removeRecursively();

}

void View::fillGround(const Grid& grid, const std::vector<Tile>& tiles)
{
	QPainter painter;
	int y = _offsetY;
	for (int yGrid = 0; yGrid < grid.height; yGrid++)
	{
		int verticalBoxSize = groundBoxSize(yGrid);
		int x = _offsetX;

		for (int xGrid = 0; xGrid < grid.width; xGrid++)
		{
			int horizontalBoxSize = groundBoxSize(xGrid);

			// Search groud image.
			auto tile = std::find_if(tiles.begin(), tiles.end(), TileComparator(xGrid, yGrid));

			if (tile != tiles.end())
			{
				painter.begin(&_backgroundImage);
				QRect r(x, y, horizontalBoxSize, verticalBoxSize);
				painter.drawImage(r, QImage(QStringLiteral(":/images/%1").arg(tile->imageName)));

				painter.end();
			}
			x += horizontalBoxSize + groundMargin(xGrid);
		}
		y += verticalBoxSize + groundMargin(yGrid);
	}

	int size5x5Rect = (_borderBoxSize * 2) + (_insideBoxSize * 3) + (_smallMargin * 4);
	int gridSize = (size5x5Rect * 3) + (_largeMargin * 2) + 2;
	_gridRect = QRect(_offsetX - 1, _offsetY - 1, gridSize, gridSize);
	_snapshotImage = _backgroundImage.copy(_gridRect);
	_gridRect.setRect(
		_gridRect.x() * _ratio,
		_gridRect.y() * _ratio,
		_gridRect.width() * _ratio,
		_gridRect.height() * _ratio);
}

int View::groundBoxSize(int index)
{
	if (index > 9)
	{
		index -= 10;
	}
	else if (index > 4)
	{
		index -= 5;
	}

	int boxSize;
	switch (index % 4)
	{
	case 0:
		boxSize = _borderBoxSize;
		break;

	case 1:
	case 2:
	case 3:
	default:
		boxSize = _insideBoxSize;
		break;
	}
	return boxSize;
}

int View::groundMargin(int index)
{
	int margin;
	switch (index)
	{
	case 4:
	case 9:
		margin = _largeMargin;
		break;

	default:
		margin = _smallMargin;
		break;
	}
	return margin;
}

void View::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.drawImage(0, 0, _backgroundImage.scaled(
		_backgroundImage.width() * _ratio,
		_backgroundImage.height() * _ratio,
		Qt::KeepAspectRatio,
		Qt::FastTransformation));
}

void View::mouseMoveEvent(QMouseEvent* event)
{
	if (_gridRect.contains(event->pos()))
	{
		int xOffset = _offsetX - _largeMargin / 2;
		int yOffset = _offsetY - _largeMargin / 2;
		int xEvent = (event->x() / _ratio) - xOffset;
		int yEvent = (event->y() / _ratio) - yOffset;
		int size5x5Rect = (_borderBoxSize * 2) + (_insideBoxSize * 3) + (_smallMargin * 4) + _largeMargin;
		int xGrid = std::min(std::max(xEvent / size5x5Rect, 0), 2);
		int yGrid = std::min(std::max(yEvent / size5x5Rect, 0), 2);

		int x5x5Rect = xEvent - (xGrid * size5x5Rect);
		int y5x5Rect = yEvent - (yGrid * size5x5Rect);

		int xi = -1;
		int yi = -1;
		int max = _smallMargin / 2;
		int i = 0;
		while (i < 5)
		{
			max += groundBoxSize(i) + _smallMargin;
			if (xi < 0 && x5x5Rect < max)
			{
				xi = i;
			}
			if (yi < 0 && y5x5Rect < max)
			{
				yi = i;
			}
			i++;
		}
		if (xi < 0)
		{
			xi = 4;
		}
		if (yi < 0)
		{
			yi = 4;
		}

		int x = (xGrid * 5) + xi;
		int y = (yGrid * 5) + yi;

		_tooltip->setText(QStringLiteral("x=%1, y=%2").arg(x).arg(y));

		if (!_tooltip->isVisible())
		{
			_tooltip->setVisible(true);
		}
	}
	else if (_tooltip->isVisible())
	{
		_tooltip->setVisible(false);
	}
}

void View::snapshot(int turnCount, const QString& name, const Grid& grid)
{
	QFuture<void> future = QtConcurrent::run(this, &View::snapshotThreaded, turnCount, name, grid);
}

void View::snapshotThreaded(int turnCount, const QString& name, const Grid& grid)
{
	QPainter painter;
	QImage& image = _snapshotImage.copy();

	int y = 1;
	for (int yGrid = 0; yGrid < grid.height; yGrid++)
	{
		int verticalBoxSize = groundBoxSize(yGrid);
		int x = 1;

		for (int xGrid = 0; xGrid < grid.width; xGrid++)
		{
			int horizontalBoxSize = groundBoxSize(xGrid);

			painter.begin(&image);
			QRect r(x, y, horizontalBoxSize, verticalBoxSize);

			QPen pen;
			pen.setColor(Qt::black);
			pen.setWidth(10);
			painter.setPen(pen);

			QFont font = painter.font();
			font.setPointSize(20);
			painter.setFont(font);

			painter.setBrush(Qt::black);
			painter.drawText(r, Qt::AlignCenter, QStringLiteral("%1").arg(grid[yGrid][xGrid]));

			painter.end();

			x += horizontalBoxSize + groundMargin(xGrid);
		}
		y += verticalBoxSize + groundMargin(yGrid);
	}

	const QString& path = QStringLiteral("%1/images/turn-%2")
		.arg(QString(IMAGE_PATH))
		.arg(turnCount);
	QDir dir;
	if (!dir.exists(path))
	{
		dir.mkpath(path);
	}

	bool saved = image.save(QStringLiteral("%1/%2.png").arg(path).arg(name));
}

void View::updateView()
{
	repaint();
}