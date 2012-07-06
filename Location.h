#ifndef LOCATION_H_
#define LOCATION_H_

/*
    struct for representing locations in the grid.
*/

#include <ostream>

struct Location
{
    int row, col;

    Location()
    {
        row = col = 0;
    };

    Location(int r, int c)
    {
        row = r;
        col = c;
    };

	bool operator==(const Location& other)
	{ return row == other.row && col == other.col; }

	bool operator!=(const Location& other)
	{ return row != other.row || col != other.col; }

	std::ostream& operator<<(std::ostream& out)
	{
		out << "[" << row << "," << col << "]";
		return out;
	}
};

#endif //LOCATION_H_
