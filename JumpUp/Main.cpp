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
	int jumpFrame = 0;

	while (System::Update())
	{
		if (KeyLeft.pressed()) player.moveBy(-5, 0);
		if (KeyRight.pressed()) player.moveBy(5, 0);

		if (scaffold.isColliding(player))
		{
			if (KeySpace.down() && jumpFrame <= 0)
			{
				jumpFrame = 30;
			}
		}
		else
		{
			player.moveBy(0, +5); // Gravity
		}

		if (jumpFrame > 0)
		{
			player.moveBy(0, -10);
			jumpFrame--;
		}

		player.draw(Palette::Blue);

		scaffold.draw();


	}
}

