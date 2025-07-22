# include <Siv3D.hpp> // Siv3D v0.6.15

class Scaffold
{
private:
	Rect m_rect;
public:
	Scaffold(int x, int y, int width, int height)
		: m_rect(x, y, width, height) {}

	void draw(Color color) const
	{
		m_rect.draw(color);
	}
	bool isColliding(const Circle& player) const
	{
		return m_rect.intersects(player);
	}
	int get_y() const
	{
		return m_rect.y;
	}
	void Scroll()
	{
		m_rect.y += 700;
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
			if (scaffold.isColliding(m_circle) && m_circle.y < scaffold.get_y())
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

	void Scroll()
	{
		m_circle.y = 700;
	}

};

void GenerateNewStage(Array<Scaffold>& scaffolds)
{
	Scaffold scaffold6(200, 650, 300, 20);
	Scaffold scaffold7(100, 500, 400, 20);
	Scaffold scaffold8(0, 350, 200, 20);
	Scaffold scaffold9(150, 200, 200, 20);
	Scaffold Goal(300, 50, 100, 20);

	scaffolds << scaffold6 << scaffold7 << scaffold8 << scaffold9 << Goal;
}

void Main()
{
	Window::Resize(600, 800);

	Player player(300, 700, 20);

	bool isNewStage = false;

	Scaffold scaffold(0, 750, 600, 50);
	Scaffold scaffold2(100, 600, 400, 20);
	Scaffold scaffold3(200, 450, 200, 20);
	Scaffold scaffold4(0, 300, 200, 20); 
	Scaffold scaffold5(150, 150, 200, 20);

	Scaffold mid_goal(300, 50, 100, 20);

	Array<Scaffold> scaffolds = { scaffold, scaffold2, scaffold3, scaffold4, scaffold5, mid_goal};

	int jumpFrame = 0;

	while (System::Update())
	{
		player.draw(Palette::Blue);
		player.update();
		player.checkGround(scaffolds);

		for (int i=0;i<5;i++)
		{
			scaffolds[i].draw(Palette::Green);
		}
		scaffolds[5].draw(Palette::Red);

		if (isNewStage)
		{
			for (int i = 6; i < 10; i++)
			{
				scaffolds[i].draw(Palette::Yellow);
			}
			scaffolds[10].draw(Palette::Red);
		}


		// Debug
		if (KeyT.down())
		{
			player.Scroll();
			for (auto& scaffold : scaffolds)
			{
				scaffold.Scroll();
			}
			GenerateNewStage(scaffolds);
			isNewStage = true;
		}

	}
}

