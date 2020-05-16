#include <iostream>
#include <algorithm>

namespace Game
{
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
    T dist(Game::Coord<T> size, Game::Coord<T> a, Game::Coord<T> b) {
        T height = abs(a.row - b.row);
        T width = abs(a.column - b.column);

        bool check = a.row > b.row ? a.column % 2 : b.column % 2;

        if ((width + check) / 2 >= height) {
            return width;
        } else {
            return width + height - (width + check) / 2;
        }
    }
}
