#include <iostream>
#include <algorithm>

template <class value_type>
class Coord {
public:
    value_type row, column;
    Coord(value_type row = value_type(), value_type column = value_type()) {
        Coord::row = row;
        Coord::column = column;
    }
};

template <class T>
T dist(Coord<T> size, Coord<T> a, Coord<T> b) {
    T height = std::min((T)abs(a.row - b.row), std::min(a.row, b.row) + size.row - std::max(a.row, b.row));
    T width = std::min((T)abs(a.column - b.column), std::min(a.column, b.column)
            + size.column - std::max(a.column, b.column));
    return std::max(height, width);
}
