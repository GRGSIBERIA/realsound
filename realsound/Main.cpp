
# include <Siv3D.hpp>

void Main()
{
	const Font font(30);

	while (System::Update())
	{
		font(L"ÇÊÇ§Ç±ÇªÅASiv3D ÇÃê¢äEÇ÷ÅI").draw();

		Circle(Mouse::Pos(), 50).draw({ 255, 0, 0, 127 });
	}
}
