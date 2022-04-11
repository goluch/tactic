#pragma once
#include <vector>
#include <cassert>

template <typename Type>
class Board {
    std::size_t world_size_;
    std::vector<Type> data_;

public:
    Board(std::size_t size)
        : world_size_(size)
        , data_(size* size) {}

    short& operator()(std::size_t x, std::size_t y) {
        assert(x < world_size_&& y < world_size_);

        return _data[y + x * world_size_];
    }

    const short& operator()(std::size_t x, std::size_t y) const {
        assert(x < world_size_&& y < world_size_);

        return _data[y + x * world_size_];
    }
};
