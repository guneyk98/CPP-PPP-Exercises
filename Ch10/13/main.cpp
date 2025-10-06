#include "PPP/Simple_window.h"
#include "PPP/Graph.h"
#include <cmath>
#include <numbers>

constexpr double pi = numbers::pi_v<double>;

struct Line_redrawable : Line {
	using Line::Line;
	void set_points(Point p1, Point p2) {
		set_point(0, p1);
		set_point(1, p2);
	}
};

std::vector<Point> superellipse(double a, double b, double m, double n, int N)
{
	std::vector<Point> points;
	for (int i = 0; i < N; ++i) {
		double t = 2.0*pi * i/N;
		double x = a * std::copysign(std::pow(std::abs(std::cos(t)), 2.0/m), std::cos(t));
		double y = b * std::copysign(std::pow(std::abs(std::sin(t)), 2.0/n), std::sin(t));
		points.push_back(Point{static_cast<int>(std::lround(x)),
							   static_cast<int>(std::lround(y))});
	}
	return points;
}

int main()
{
	using namespace Graph_lib;
	Application app;

	constexpr int win_x = 0, win_y = 0;
	constexpr int win_w = 1280, win_h = 720;

	Simple_window win(Point{win_x, win_y}, win_w, win_h, "Ch10 Ex12");

	//window is dark by default (OS dark-mode?), fill it white
	Rectangle background_fill{Point{0, 0}, win_w, win_h};
	background_fill.set_fill_color(Color::white);
	win.attach(background_fill);

	constexpr int num_points = 400;
	std::vector<Point> points = superellipse(win.x_max()/2, win.y_max()/2, 0.3, 0.3, num_points);
	for (size_t i = 0; i < points.size(); ++i) {
		points[i].x += win.x_max()/2;
		points[i].y += win.y_max()/2;
	}

	std::vector<Line_redrawable*> lines;
	lines.reserve(num_points);
	for (size_t i = 0; i < num_points; ++i) {
		size_t j = (i+1) % num_points;
		Line_redrawable* line = new Line_redrawable(points[i], points[j]);
		line->set_color(i%13 == 4 ? 13 : i%13); //all colours but white
		win.attach(*line);
		lines.push_back(line);
	}

	//increment k by 2% each time the next button is pressed
	for (size_t k = 1; k < points.size(); k += points.size()/50) {
		for (size_t i = 0; i < points.size(); ++i) {
			size_t j = (i+k)%points.size();
			lines[i]->set_points(points[i], points[j]);
		}
		win.wait_for_button();
	}
}
