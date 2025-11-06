#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

struct Group : Shape {
	void push_back(Shape& s) { v.push_back(s); }
	void push_back(std::unique_ptr<Shape> s) { v.push_back(std::move(s)); }
	virtual void draw_specifics(Painter& painter) const override;
	virtual void move(int dx, int dy) override;
	int size() const { return v.size(); }

	Shape& operator[](int idx) { return v[idx]; }
	const Shape& operator[](int idx) const { return v[idx]; }
private:
	Vector_ref<Shape> v;
};

int main()
{
	Application app;
	Simple_window win(Point{50, 50}, 800, 800, "Ch12 Ex11");
	//window is dark by default (OS dark-mode?), fill it white
	Rectangle background_fill{Point{0, 0}, win.x_max(), win.y_max()};
	background_fill.set_fill_color(Color::white);
	win.attach(background_fill);

	const int size = 8;
	const int square_size = win.x_max()/size;
	const Color w_colour = Color(245, 230, 191);
	const Color b_colour = Color(102, 68, 57);

	Group board;
	for (int j = 0; j < size; ++j) {
		const int y = j*square_size;
		for (int i = 0; i < size; ++i) {
			const int x = i*square_size;
			board.push_back(make_unique<Rectangle>(Point{x, y}, square_size, square_size));
			board[board.size()-1].set_fill_color((i+j)%2 ? b_colour : w_colour);
			board[board.size()-1].set_color(Color::invisible);
		}
	}
	
	const int piece_rad = square_size/3;

	Group w_pieces;
	for (int j = 0; j < 3; ++j) {
		const int y = j*square_size + square_size/2;
		for (int i = 0; i < size; ++i) {
			if ((i+j)%2 == 0)
				continue;
			const int x = i*square_size + square_size/2;
			w_pieces.push_back(make_unique<Circle>(Point{x, y}, piece_rad));
			w_pieces[w_pieces.size()-1].set_fill_color(Color::white);
		}
	}

	Group b_pieces;
	for (int j = size-3; j < size; ++j) {
		const int y = j*square_size + square_size/2;
		for (int i = 0; i < size; ++i) {
			if ((i+j)%2 == 0)
				continue;
			const int x = i*square_size + square_size/2;
			b_pieces.push_back(make_unique<Circle>(Point{x, y}, piece_rad));
			b_pieces[b_pieces.size()-1].set_fill_color(Color::black);
		}
	}

	win.attach(board);
	win.attach(w_pieces);
	win.attach(b_pieces);
	win.wait_for_button();
}

void Group::draw_specifics(Painter& painter) const
{
	for (int i = 0; i < v.size(); ++i)
		v[i].draw(painter);
}

void Group::move(int dx, int dy)
{
	for (int i = 0; i < v.size(); ++i)
		v[i].move(dx, dy);
}
