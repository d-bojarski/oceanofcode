#include "path.h"

//---------------------------------------
//------- Constructors/Destructors ------
//---------------------------------------
Path::Path()
{
}

Path::~Path()
{
}

bool Path::addPoint(const Point& point)
{
	bool success = contains(point);
	if (!success)
	{
		_way.push_back(point);
	}
	return success;
}

const Point& Path::at(int i) const
{
	return _way.at(i);
}

unsigned int Path::size() const
{
	return _way.size();
}

bool Path::contains(const Point& point)
{
	auto result = std::find_if(_way.begin(), _way.end(), ComparePoint(point));
	return (result != _way.end());
}

std::string Path::toString()
{
	std::string result = "";
	for (size_t i = 0; i < _way.size(); i++)
	{
		const Point& p = _way.at(i);
		if (result.size() > 0)
		{
			result += "->";
		}
		result += "(" + std::to_string(p.x) + "," + std::to_string(p.y) + ")";
	}

	return result;
}
