#pragma once
#include <array>
#include <cassert>
#include <vector>
#include <string>

#include "geom.h"

class Tile {
public:
    // Размер тайла 8*8 пикселей.
    constexpr static int SIZE = 8;

    // Конструктор по умолчанию. Заполняет тайл указанным цветом.
    Tile(char color = ' ') noexcept : tile_(SIZE, std::vector<char>(SIZE, color)) {

        // -------------- не удалять ------------
        assert(instance_count_ >= 0);
        ++instance_count_;  // Увеличиваем счётчик тайлов (для целей тестирования)
        // -------------- не удалять ------------
    }

    Tile(const Tile& other) {
        if (other.tile_.empty()) {
            return;
        }
        tile_ = other.tile_;

        // -------------- не удалять ------------
        assert(instance_count_ >= 0);
        ++instance_count_;  // Увеличиваем счётчик тайлов (для целей тестирования).
        // -------------- не удалять ------------
    }

    ~Tile() {
        // -------------- Не удалять ------------
        --instance_count_;  // Уменьшаем счётчик тайлов.
        assert(instance_count_ >= 0);
        // -------------- не удалять ------------
    }

    /**
     * Изменяет цвет пикселя тайла.
     * Если координаты выходят за пределы тайла, метод ничего не делает.
     */
    void SetPixel(Point p, char color) noexcept {
        if (p.x >= 0 || p.y >= 0) {
            p = { p.x % SIZE, p.y % SIZE };
            if (p.x <= SIZE || p.y <= SIZE) {
                tile_[p.y][p.x] = color;
            }
        }
    }

    /**
     * Возвращает цвет пикселя. Если координаты выходят за пределы тайла, возвращается пробел.
     */
    char GetPixel(Point p) const noexcept {
        if (p.x >= 0 || p.y >= 0) {
            p = { p.x % SIZE, p.y % SIZE };
            if (p.x <= SIZE || p.y <= SIZE) {
                return tile_[p.y][p.x];
            }
        }
        return ' ';
    }

    // Возвращает количество экземпляра класса Tile в программе.
    static int GetInstanceCount() noexcept {
        // -------------- не удалять ------------
        return instance_count_;
        // -------------- не удалять ------------
    }

    int SizeInInt(const size_t s) const {
        return s;
    }

private:
    // -------------- не удалять ------------
    inline static int instance_count_ = 0;
    // -------------- не удалять ------------

    std::vector < std::vector<char> > tile_;

};