#include <iostream>
#include <math.h>
#include "lab5task1.h"
#include <math.h>
#include <SDL.h>
#include <stdlib.h>
#define SDL_MAIN_HANDLED
using namespace std;


Point2D::Point2D(float xValue, float yValue) {
	x = xValue;
	y = yValue;
}

Point2D::Point2D(Point2D& o) {
	x = o.x;
	y = o.y;
}

Point2D::Point2D() {
	x = 0;
	y = 0;
};

void Point2D::newPoint(float xValue, float yValue) {
	x = xValue;
	y = yValue;
}
double Point2D::distance(Point2D point2) {
	float distance, deltaX = x - point2.x, deltaY = y - point2.y;
	distance = pow(deltaX, 2) + pow(deltaY, 2);
	return sqrt(distance);
}


void Shape::printRGB()
{
	cout << "r:" << rgb[0] << " g:" << rgb[1] << " b:" << rgb[2] << " alpha:" << rgb[3] << endl;
}

void Shape::setRGB(int r, int g, int b, int alpha)
{
	if (r > 255 || r < 0)
	{
		rgb[0] = 255;
	}
	else
	{
		rgb[0] = r;
	}
	if (g > 255 || g < 0)
	{
		rgb[1] = 255;
	}
	else
	{
		rgb[1] = g;
	}
	if (b > 255 || b < 0)
	{
		rgb[2] = 255;
	}
	else
	{
		rgb[2] = b;
	}
	if (alpha < 0 || alpha > 1 )
	{
		rgb[3] = 1;
	}
	else
	{
		rgb[3] = alpha;
	}
}

void Shape::setPoint(float x, float y)
{
	if (float (-999 < x < 999) && float (-999 < y < 999) )
	{
		line.newPoint(x, y);
	}
	else
	{
		cout << "the point you've set was out of range. Setting point to (0 , 0)" << endl;
	}
}

Shape::Shape(float x, float y, float r, float g, float b, float alpha) {
	setPoint(x,y);
	setRGB(r, g, b, alpha);
}

Shape::Shape()
{
	setPoint(0, 0);
	setRGB(255, 255, 255, 1);
}

int Shape::returnRGB(int index) {
	return rgb[index];
}

void Shape::render(SDL_Renderer* renderer)
{
}

Rectangle::Rectangle(float xValue, float yValue, float rectBase, float rectHeight, int r, int g, int b, int alpha) : base(rectBase), height(rectHeight), Shape(xValue, yValue, r, g, b, alpha)  {  }

Rectangle::Rectangle() : base(0), height(0), Shape() {  }

	void Rectangle::render(SDL_Renderer * renderer) {
		int rectangle[4] = { line.x, line.y, line.x + base, line.y + height };
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, returnRGB(0), returnRGB(1), returnRGB(2), 255);
		SDL_RenderDrawLine(renderer, rectangle[0], rectangle[1], rectangle[2], rectangle[1]);
		SDL_RenderDrawLine(renderer, rectangle[2], rectangle[1], rectangle[2], rectangle[3]);
		SDL_RenderDrawLine(renderer, rectangle[2], rectangle[3], rectangle[0], rectangle[3]);
		SDL_RenderDrawLine(renderer, rectangle[0], rectangle[3], rectangle[0], rectangle[1]);
		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);
	}



Triangle::Triangle(float xValue, float yValue, float triBase, float triHeight, int r, int g, int b, int alpha) : base(triBase), height(triHeight), Shape(xValue, yValue, r, g, b, alpha) { }

Triangle::Triangle() : base(), height(), Shape() { }


void Triangle::render(SDL_Renderer* renderer) {
	int triangle[5] = { line.x, line.y, line.x + base, line.x / 2, line.y + height};
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, returnRGB(0), returnRGB(1), returnRGB(2), 255);
	SDL_RenderDrawLine(renderer, triangle[0], triangle[1], triangle[2], triangle[1]);
	SDL_RenderDrawLine(renderer, triangle[2], triangle[1], triangle[3], triangle[4]);
	SDL_RenderDrawLine(renderer, triangle[3], triangle[4], triangle[0], triangle[1]);
	SDL_RenderPresent(renderer);
	SDL_RenderClear(renderer);
}

Circle::Circle(float xValue, float yValue, float circleRadius, int r, int g, int b, int alpha) : radius(circleRadius), Shape(xValue, yValue, r, g, b, alpha) { };
Circle::Circle() : radius(), Shape() { };

void Circle::render(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, returnRGB(0), returnRGB(1), returnRGB(2), 255);
	
	int theta = 0; // angle that will be increased each loop
	float h = line.x; // x coordinate of circle center
	float k = line.y; // y coordinate of circle center
	int step = 1; // amount to add to theta each time (degrees)
	int circleX, circleY;
	while (theta <= 360)
	{
			circleX = h + radius * cos(theta);
			circleY = k + radius * sin(theta);
			SDL_RenderDrawLine(renderer, h, k, circleX, circleY);
			theta += step;
			SDL_RenderPresent(renderer);
	}
	
}

/*
int main(int argc, char* args[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_SetMainReady();

	Rectangle rectangle(200,200,200,200,255,0,255,1);
	Circle circle(300,50,50,250,0,250,1);
	Triangle triangle(200, 200, 200, 200, 255, 0, 255, 1);

	Shape* shapeArray[3];
	shapeArray[0] = &rectangle;
	shapeArray[1] = &circle;
	shapeArray[2] = &triangle;
	shapeArray[1]->render();
	shapeArray[1]->render();
	shapeArray[2]->render();
	return 0;
}

*/
int main(int argc, char* args[]) {
	bool quit = false;
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_SetMainReady();
	SDL_Event event;
	SDL_Window* window = SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	
	
	
	
	Shape* shapeArray[3];
	
	while (!quit)
	{
		if (SDL_PollEvent(&event))
		{
			switch (event.type) {
			case SDL_QUIT:
				break;
			case SDL_KEYDOWN:
				float x = rand() % 400 + 1, y = rand() % 400 + 1, width = rand() % 200 + 100, hight = rand() % 200 + 100;
				int r = rand() % 256, g = rand() % 256, b = rand() % 256;
				switch (event.key.keysym.sym)
				{
				case SDLK_r: Rectangle rect(x, y, width, hight, r, g, b, 1); shapeArray[0] = &rect; shapeArray[0]->render(renderer); break;
				}
				
				switch (event.key.keysym.sym) {
				case SDLK_c: Circle cir(x, y, width, r, g, b, 1); shapeArray[1] = &cir; shapeArray[1]->render(renderer); break;
				}
				
				switch (event.key.keysym.sym) {
				case SDLK_t: Triangle tri(x, y, width,hight, r, g, b, 1); shapeArray[2] = &tri; shapeArray[2]->render(renderer); break;
				}
				
				switch (event.key.keysym.sym)
				{
				case SDLK_q: quit = true; break; SDL_DestroyRenderer(renderer); SDL_DestroyWindow(window); SDL_Quit();
				}
			
				switch (event.key.keysym.sym)
				{

				case SDLK_x: for (int i = 0; i < 3; i++)
				{
					shapeArray[i] = nullptr;
				} break;
				}
			}
		};
		

		
	}
	return 0;
}