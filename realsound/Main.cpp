
# include <Siv3D.hpp>
# include "SignalBuffer.hpp"


void Main()
{
	const Font font(30);

	Window::Resize(1024, 1024);

	Recorder::SetBufferLengthBySec(s3d::RecorerSamplingRate::S44100, 60 * 5);

	//sound::SignalBuffer buffer = sound::SignalBuffer(1024, 8194);

	Image image = Image(1024, 1024, Color(0, 0, 0));
	DynamicTexture texture = DynamicTexture(image);

	if (!Recorder::Start())
	{
		return;
	}

	int count = 0;

	while (System::Update())
	{
		if (Recorder::IsEnd())
		{
			Recorder::Restart();
		}

		Waving::FFT(Recorder::GetWave(), Recorder::GetPos(), Waving::SampleLength::SL4K);

		const float* p = Waving::FFTBuffer();
		//buffer.Put(p);

		for (int i = 0; i < Window::Height(); ++i)
		{
			image[i][count] = HSV(-log(p[i]) * 10);
		}

		texture.fill(image);
		texture.draw();

		Line(count, 0, count, Window::Height()).draw();
		if (++count >= 1024)
			count = 0;
	}
	return;
}
