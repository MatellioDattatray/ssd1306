/*
    MIT License

    Copyright (c) 2018, Alexey Dynda

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/
/**
 * @file rect.h Rectangle class
 */

#ifndef _NANO_RECT_H_
#define _NANO_RECT_H_

#include "point.h"
#include "ssd1306_hal/io.h"

/**
 * NanoRect structure describes rectangle area.
 */
typedef struct _NanoRect
{
    /** top-left point of the rectangle area */
    NanoPoint p1;

    /** right-bottom point of the rectangle area */
    NanoPoint p2;

    /** returns width of NanoRect */
    lcdint_t width() const
    {
        return p2.x - p1.x + 1;
    }

    /** returns size of NanoRect */
    const NanoPoint size() const
    {
        return {width(), height()};
    }

    /** returns height of NanoRect */
    lcdint_t height() const
    {
        return p2.y - p1.y + 1;
    }

    /**
     * Shifts rectangle area by dx;dy pixels.
     * @param dx - delta on x-axis
     * @param dy - delta on y-axis
     */
    void move(lcdint_t dx, lcdint_t dy)
    {
        p1.x += dx; p2.x += dx;
        p1.y += dy; p2.y += dy;
    }

    /**
     * Shifts rectangle area by dx pixels.
     * @param dx - delta on x-axis
     */
    void addH(lcdint_t dx)
    {
        p1.x += dx; p2.x += dx;
    }

    /**
     * Shifts rectangle area by dy pixels.
     * @param dy - delta on y-axis
     */
    void addV(lcdint_t dy)
    {
        p1.y += dy;
        p2.y += dy;
    }

    /**
     * Initializes NanoRect with specified values
     * @param l - left position
     * @param t - top position
     * @param r - right position
     * @param b - bottom position
     */
    void setRect(lcdint_t l, lcdint_t t, lcdint_t r, lcdint_t b)
    {
        p1.x = l; p1.y = t;
        p2.x = r; p2.y = b;
    }

    /**
     * Returns true if specified x position is between left and right borders.
     * @param x - position to check
     */
    bool collisionX(lcdint_t x) const
    {
        return (x >= p1.x) && (x <= p2.x);
    }

    /**
     * Returns true if specified y position is between left and right borders.
     * @param y - position to check
     */
    bool collisionY(lcdint_t y) const { return (y >= p1.y) && (y <= p2.y); };

    /**
     * Returns true if specified point is inside rectangle area.
     * @param p - point to check.
     */
    bool collision(const NanoPoint &p) const { return collisionX(p.x) && collisionY(p.y); };

    /**
     * Returns true if specified point is above rectangle area.
     * @param p - point to check.
     */
    bool above(const NanoPoint &p) const { return (p.y < p1.y); };

    /**
     * Returns true if specified point is below rectangle area.
     * @param p - point to check.
     */
    bool below(const NanoPoint &p) const { return (p.y > p2.y); };

    /**
     * Returns true if specified point is above rectangle area.
     * @param p - point to check.
     */
    _NanoRect operator-(const _NanoPoint &p)
    {
        return { {static_cast<lcdint_t>(p1.x - p.x), static_cast<lcdint_t>(p1.y - p.y) },
                 {static_cast<lcdint_t>(p2.x - p.x), static_cast<lcdint_t>(p2.y - p.y) } };
    }

    /**
     * Add point to all points of rectangle.
     * @param p - point to add.
     */
    _NanoRect operator+(const _NanoPoint &p)
    {
        return { {static_cast<lcdint_t>(p1.x + p.x), static_cast<lcdint_t>(p1.y + p.y) },
                 {static_cast<lcdint_t>(p2.x + p.x), static_cast<lcdint_t>(p2.y + p.y) } };
    }

    /**
     * Subtracts point to all points of rectangle.
     * @param p - point to subtract.
     */
    _NanoRect& operator+=(const _NanoPoint &p)
    {
        p1.x += p.x;
        p1.y += p.y;
        p2.x += p.x;
        p2.y += p.y;
        return *this;
    }

} NanoRect;

#endif
