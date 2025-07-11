# include <Siv3D.hpp> // Siv3D v0.6.15





void Main()
{
	Window::Resize(600, 800);

	Circle player(300, 700, 20);

	while (System::Update())
	{

		player.draw(Palette::Blue);

		if (KeyLeft.pressed()) player.moveBy(-5, 0);
		if (KeyRight.pressed()) player.moveBy(5, 0);

		if (KeySpace.pressed()) player.moveBy(0, -5);


	}
}

