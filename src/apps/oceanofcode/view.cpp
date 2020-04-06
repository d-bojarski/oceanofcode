#include "view.h"

#include <iostream>

#include <qstring.h>
#include <qpainter.h>
#include <qgridlayout.h>

View::View(QWidget* parent) :
	QWidget(parent),
	ratio(0.8),
	offsetX(513),
	offsetY(93),
	borderBoxSize(55 + 1),
	insideBoxSize(57 + 1),
	smallMargin(2),
	largeMargin(6)
{
	backgroundImage.load(":/images/background.jpg");

	setFixedWidth(backgroundImage.width() * ratio);
	setFixedHeight(backgroundImage.height() * ratio);

	QWidget* empty;

	regenerateButton = new QPushButton("Regenerate", this);
	regenerateButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	QGridLayout* layout = new QGridLayout(this);
	layout->addWidget(regenerateButton, 0, 0);

	// Horizontal spacer.
	empty = new QWidget(this);
	empty->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	layout->addWidget(empty, 0, 1);

	// Vertical spacer.
	empty = new QWidget(this);
	empty->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
	layout->addWidget(empty, 1, 0);

	this->setLayout(layout);
}

void View::fillGround(const Grid& grid, const std::vector<Tile>& tiles)
{
	QPainter painter;
	int y = offsetY;
	for (int yGrid = 0; yGrid < grid.height; yGrid++)
	{
		int verticalBoxSize = groundBoxSize(yGrid);
		int x = offsetX;

		for (int xGrid = 0; xGrid < grid.width; xGrid++)
		{
			int horizontalBoxSize = groundBoxSize(xGrid);

			if (grid[xGrid][yGrid] == 1)
			{
				// Search groud image.
				auto tile = std::find_if(tiles.begin(), tiles.end(), TileComparator(xGrid, yGrid));

				if (tile != tiles.end())
				{
					painter.begin(&backgroundImage);
					QRect r(x, y, horizontalBoxSize, verticalBoxSize);
					painter.drawImage(r, QImage(QStringLiteral(":/images/%1").arg(tile->imageName)));

#if 0
					painter.setBrush(Qt::black);
					QPen pen;
					pen.setColor(Qt::black);
					pen.setWidth(1);
					painter.setPen(pen);
					QFont font = painter.font();
					font.setPointSize(12);
					painter.setFont(font);
					painter.drawText(r, Qt::AlignCenter,
						QStringLiteral("%1,%2\n%3x%4")
						.arg(x)
						.arg(y)
						.arg(horizontalBoxSize - 1)
						.arg(verticalBoxSize - 1)
						);
#endif

					painter.end();
				}
			}
			x += horizontalBoxSize + groundMargin(xGrid);
		}
		y += verticalBoxSize + groundMargin(yGrid);
	}
	backgroundImage.save("image.bmp");
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
		boxSize = borderBoxSize;
		break;

	case 1:
	case 2:
	case 3:
	default:
		boxSize = insideBoxSize;
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
		margin = largeMargin;
		break;

	default:
		margin = smallMargin;
		break;
	}
	return margin;
}

void View::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.drawImage(0, 0, backgroundImage.scaled(
		backgroundImage.width() * ratio,
		backgroundImage.height() * ratio,
		Qt::KeepAspectRatio,
		Qt::FastTransformation));
}

