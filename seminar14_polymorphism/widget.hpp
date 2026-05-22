#pragma once

class Widget
{
public:
    virtual ~Widget() = default;
    virtual void draw() const = 0;
    virtual bool update() = 0;
};