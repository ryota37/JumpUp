# include <Siv3D.hpp> // Siv3D v0.6.15

class Scaffold
{
private:
	Rect m_rect;
public:
	Scaffold(int x, int y, int width, int height)
		: m_rect(x, y, width, height) {
	}

	void draw() const
	{
		m_rect.draw(Palette::Green);
	}
	bool isColliding(const Circle& player) const
	{
		return m_rect.intersects(player);
	}
};

void Main()
{
	Window::Resize(600, 800);

	Circle player(300, 700, 20);
	Scaffold scaffold(0, 750, 600, 50);

	while (System::Update())
	{

		player.draw(Palette::Blue);

		if (KeyLeft.pressed()) player.moveBy(-5, 0);
		if (KeyRight.pressed()) player.moveBy(5, 0);

		if (KeySpace.pressed()) player.moveBy(0, -5);

		scaffold.draw();


	}
}

