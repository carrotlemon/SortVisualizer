#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;

namespace qt {
    template<typename T>
    class Box
    {
    public:
        T left;
        T top;
        T width;
        T height;

        constexpr Box(T Left = 0, T Top = 0, T Width = 0, T Height = 0) noexcept :
            left(Left), top(Top), width(Width), height(Height)
        { // directly assigns variables (more efficient)
            // = 0 -> defaults to 0
            // noexcept -> no exceptions -> more safe and more efficient
        }
        constexpr Box(const Vector2<T>& position, const Vector2<T>& size) noexcept :
            left(position.x), top(position.y), width(size.x), height(size.y)
        {

        }

        constexpr T getRight() const noexcept
        { // const -> does not affect the object its called on
            return left + width;
        }

        constexpr T getBottom() const noexcept
        {
            return top + height;
        }

        constexpr Vector2<T> getTopLeft() const noexcept
        {
            return Vector2<T>(left, top);
        }

        constexpr Vector2<T> getCenter() const noexcept
        {
            return Vector2<T>(left + width / 2, top + height / 2);
        }

        constexpr Vector2<T> getSize() const noexcept
        {
            return Vector2<T>(width, height);
        }

        constexpr bool contains(const Box<T>& box) const noexcept
        {
            return left <= box.left && box.getRight() <= getRight() &&
                top <= box.top && box.getBottom() <= getBottom();
        }

        constexpr bool contains(Vector2<T> point) const noexcept
        {
            return left <= point.x && point.x <= getRight() &&
                top <= point.y && point.y <= getBottom();
        }

        constexpr bool intersects(const Box<T>& box) const noexcept
        {
            return !(left >= box.getRight() || getRight() <= box.left ||
                top >= box.getBottom() || getBottom() <= box.top);
        }

        friend std::ostream& operator<< (std::ostream& os, const Box& v) {
            return os << v.left << " " << v.top << " " << v.width << " " << v.height;
        }
    };
}


