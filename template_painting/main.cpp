#include <GLFW/glfw3.h>
#include <cstring>
#include <stdlib.h>		  // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include "math.h"
#include <iostream>
#include <vector>

using namespace std;

const int width = 1000;
const int height = 800;

float* pixels = new float[width*height * 3];
void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue);
void drawLine(int i0, int j0, int i1, int j1, const int t, const float& red, const float& green, const float& blue);
void drawRect(int x0, int y0, int x1, int y1, int t, float r1, float g1, float b1);
void drawRectF(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue);
void drawCirc(const int& i0, const int& j0, const int& r, const int& t, const float& red, const float& green, const float& blue);
void drawIcon(const int& i0, const int& j0, const int& r, const int& t, const float& r1, const float& g1, const float& b1, const float& r2, const float& g2, const float& b2, double xpos, double ypos);
void drawIcon2(int x0, int y0, int x1, int y1, int t, float r1, float g1, float b1, float r2, float g2, float b2, double xpos, double ypos);

template<class T_HOW_TO_DRAW>
class GeometricObjectInColor : public Draw
{
public:
	void draw()
	{
		T_HOW_TO_DRAW draw_in_color;
		draw_in_color.draw();
	}
};

class Draw
{
public:
	virtual void draw()
	{
	}
};

class DrawYellowCircle
{
public:
	void draw()
	{
		drawCirc(250, 200, 150, 3, 0.95, 0.95, 0);
	}
};

class DrawRedBox
{
public:
	void draw()
	{
		drawRect(500, 50, 800, 350, 3, 1, 0, 0);
	}
};

template<class T_CLASS>
void print(const T_CLASS &i)
{
	cout << i << endl;
}

template<class T_CLASS2>
class Vector2D
{
public:
	T_CLASS2 x, y;
};


void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue)
{
	pixels[(i + width* j) * 3 + 0] = red;
	pixels[(i + width* j) * 3 + 1] = green;
	pixels[(i + width* j) * 3 + 2] = blue;
}

void drawLine(int i0, int j0, int i1, int j1, const int t, const float& red, const float& green, const float& blue)
{
	int i, j, k;
	int itmp, jtmp;
	if (i0 > i1)
	{
		itmp = i0;
		i0 = i1;
		i1 = itmp;
		jtmp = j0;
		j0 = j1;
		j1 = jtmp;
	}
	if (i0 == i1)
	{
		if (j0 < j1)
			j = j0;
		else
			j = j1;
		for (;j <= j1 || j <= j0;j++)
			for (k = i0 - t;k <= i0 + t;k++)
				drawPixel(k, j, red, green, blue);
	}
	else
	{
		if (j0 == j1)
		{
			for (i = i0; i <= i1; i++)
				for (k = j0 - t;k <= j0 + t;k++)
					drawPixel(i, k, red, green, blue);
		}
		else
		{
			for (i = i0; i <= i1; i++)
			{
				if (j0 < j1)
					j = j0;
				else
					j = j1;
				for (;j <= j1 || j <= j0;j++)
				{
					if (i == (i1 - i0)*(j - j0) / (j1 - j0) + i0 || j == (j1 - j0)*(i - i0) / (i1 - i0) + j0)
					{
						for (k = -t;k <= t;k++)
						{
							drawPixel(i + k, j, red, green, blue);
							drawPixel(i, j + k, red, green, blue);
						}
					}
				}
			}
		}
	}
}

void drawRect(int x0, int y0, int x1, int y1, int t, float r1, float g1, float b1)
{
	for (int i = x0;i <= x1;i++)
	{
		for (int j = y0;j <= y1;j++)
		{
			if (i <= x0 + t || i >= x1 - t || j <= y0 + t || j >= y1 - t)
			{
				drawPixel(i, j, r1, g1, b1);
			}
		}
	}
}

void drawRectF(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	int i, j;
	for (i = i0;i <= i1;i++)
	{
		for (j = j0;j <= j1;j++)
		{
			drawPixel(i, j, red, green, blue);
		}
	}
}

void drawCirc(const int& i0, const int& j0, const int& r, const int& t, const float& red, const float& green, const float& blue)
{
	int i, j;
	int a, b, c;

	for (i = i0 - r;i <= i0 + r;i++)
	{
		for (j = j0 - r;j <= j0 + r;j++)
		{
			a = ((i - i0)*(i - i0)) + ((j - j0)*(j - j0));
			b = r*r;
			c = (r - t)*(r - t);
			if (a < b&&a >= c)
			{
				drawPixel(i, j, red, green, blue);
			}
		}
	}
}

void drawIcon(const int& i0, const int& j0, const int& r, const int& t, const float& r1, const float& g1, const float& b1, const float& r2, const float& g2, const float& b2, double xpos, double ypos)
{
	int i, j;
	int a, b, c;

	for (i = i0 - r;i <= i0 + r;i++)
	{
		for (j = j0 - r;j <= j0 + r;j++)
		{
			a = ((i - i0)*(i - i0)) + ((j - j0)*(j - j0));
			b = r*r;
			c = (r - t)*(r - t);
			if (a < b&&a >= c)
			{
				if (((xpos - i0)*(xpos - i0)) + ((ypos - j0)*(ypos - j0)) < b)
					drawPixel(i, j, r2, g2, b2);
				else
					drawPixel(i, j, r1, g1, b1);
			}
		}
	}
}

void drawIcon2(int x0, int y0, int x1, int y1, int t, float r1, float g1, float b1, float r2, float g2, float b2, double xpos, double ypos)
{
	for (int i = x0;i <= x1;i++)
	{
		for (int j = y0;j <= y1;j++)
		{
			if (i <= x0 + t || i >= x1 - t || j <= y0 + t || j >= y1 - t)
			{
				if (xpos >= x0 && xpos <= x1 && ypos >= y0 && ypos <= y1)
					drawPixel(i, j, r2, g2, b2);
				else
					drawPixel(i, j, r1, g1, b1);
			}
		}
	}
}

void drawOnPixelBuffer(double xpos, double ypos)
{
	//std::memset(pixels, 1.0f, sizeof(float)*width*height * 3); // doesn't work
	std::fill_n(pixels, width*height * 3, 1.0f);	// white background

													//const int i = rand() % width, j = rand() % height;
													//drawPixel(i, j, 0.0f, 0.0f, 0.0f);

													// drawing a line
													//TODO: anti-aliasing
													//for (int i = 0; i < width*height; i++)
													//{
													//	pixels[i * 3 + 0] = 1.0f; // red 
													//	pixels[i * 3 + 1] = 1.0f; // green
													//	pixels[i * 3 + 2] = 1.0f; // blue
													//}
	vector<Draw*> obj_list;
	obj_list.push_back(new GeometricObjectInColor<DrawRedBox>);
	obj_list.push_back(new GeometricObjectInColor<DrawYellowCircle>);
	for (auto itr : obj_list)
		itr->draw();

	//TODO: try moving object
}

int main(void)
{
	GLFWwindow* window;

	print(1);
	print(2.345f);
	print("Hello World!");

	Vector2D<int> my_vector2d_int;
	my_vector2d_int.x = 3;
	my_vector2d_int.y = 4;
	Vector2D<float> my_vector2d_float;
	my_vector2d_float.x = 3.5f;
	my_vector2d_float.y = 4.5f;
	Vector2D<double> my_vector2d_double;
	my_vector2d_double.x = 3.5;
	my_vector2d_double.y = 4.5;
	cout << my_vector2d_int.x << "	" << my_vector2d_int.y << endl;
	cout << my_vector2d_float.x << "	" << my_vector2d_float.y << endl;
	cout << my_vector2d_double.x << "	" << my_vector2d_double.y << endl;


	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glClearColor(1, 1, 1, 1); // while background

							  /* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		//glClear(GL_COLOR_BUFFER_BIT);
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		ypos = height - ypos - 1;
		

		drawOnPixelBuffer(xpos, ypos);

		//TODO: RGB struct
		//Make a pixel drawing function
		//Make a line drawing function

		glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	glfwTerminate();

	delete[] pixels; // or you may reuse pixels array 

	return 0;
}