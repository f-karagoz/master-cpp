//
//  main.cpp
//  DPB_02
//
//  Created by Furkan Karagöz on 11.03.2023.
//  Topic:      The Command Pattern
//  Example:    Make buttons in an interface resuble

#include <iostream>
#include <vector>

class Canvas
{
    std::vector<std::string> shapes;
public:
    void addShape(const std::string & newShape) {
        shapes.push_back(newShape);
    }
    
    void clearAll() {
        shapes.clear();
    }
    
    std::vector<std::string> getShapes() {
        return shapes;
    }
};

class Button
{
public:
    virtual ~Button() {};
    virtual void click() = 0;
};

class AddTriangleButton : public Button
{
    Canvas *canvas;
public:
    void click() override {
        canvas->addShape("triangle");
    }
};

class AddAquareButton : public Button
{
    Canvas *canvas;
public:
    void click() override {
        canvas->addShape("square");
    }
};

class ClearButton : public Button
{
    Canvas *canvas;
public:
    ClearButton(Canvas *canvas) : canvas(canvas) {};
    
    void click () override {
        canvas->clearAll();
    }
};

int main (void)
{
    return 0;
}
