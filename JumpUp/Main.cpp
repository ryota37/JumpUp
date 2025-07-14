# include <Siv3D.hpp> // Siv3D v0.6.15

class Scaffold
{
private:
	Rect m_rect;
public:
	Scaffold(int x, int y, int width, int height)
		: m_rect(x, y, width, height) {}

	void draw() const
	{
		m_rect.draw(Palette::Green);
	}
	bool isColliding(const Circle& player) const
	{
		return m_rect.intersects(player);
	}
};

class Player
{
private:
	Circle m_circle;
	bool m_isGrounded;
	int m_jumpFrame;
public:

	Player(double x, double y, double radius)
		: m_circle(x, y, radius), m_isGrounded(false), m_jumpFrame(0) {
	}

	void checkGround(const Array<Scaffold> scaffolds)
	{
		m_isGrounded = false; // Reset grounded state
		for (const auto& scaffold : scaffolds)
		{
			if (scaffold.isColliding(m_circle))
			{
				m_isGrounded = true;
				break;
			}
		}
	}

	void draw(const ColorF& color) const
	{
		m_circle.draw(color);
	}
	void update()
	{
		if (KeyLeft.pressed()) m_circle.moveBy(-5, 0);
		if (KeyRight.pressed()) m_circle.moveBy(5, 0);
		if (m_isGrounded)
		{
			if (KeySpace.down() && m_jumpFrame <= 0)
			{
				m_jumpFrame = 30;
			}
		}
		else
		{
			m_circle.moveBy(0, +5); // Gravity
		}

		if (m_jumpFrame > 0)
		{
			m_circle.moveBy(0, -10);
			m_jumpFrame--;
		}
	}

};

void Main()
{
	Window::Resize(600, 800);

	Player player(300, 700, 20);

	Scaffold scaffold(0, 750, 600, 50);
	Scaffold scaffold2(100, 600, 400, 20);
	Scaffold scaffold3(200, 450, 200, 20);

	Array<Scaffold> scaffolds = { scaffold, scaffold2, scaffold3 };

	int jumpFrame = 0;

	while (System::Update())
	{


		player.draw(Palette::Blue);
		player.update();
		player.checkGround(scaffolds);

		for (auto& scaffold : scaffolds)
		{
			scaffold.draw();
		}



	}
}

