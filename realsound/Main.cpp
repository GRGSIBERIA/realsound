
# include <Siv3D.hpp>
# include "SignalBuffer.hpp"

void Main()
{
	const Font font(30);

	Window::Resize(1024, 1024);

	Recorder::SetBufferLengthBySec(s3d::RecorerSamplingRate::S44100, 60 * 5);

	sound::SignalBuffer buffer = sound::SignalBuffer(1024, 44100 >> 1);

	Image image = Image(1024, 1024, Color(0, 0, 0));

	if (!Recorder::Start())
	{
		return;
	}

	int count = 1;

	while (System::Update())
	{
		if (Recorder::IsEnd())
		{
			Recorder::Restart();
		}

		Waving::FFT(Recorder::GetWave(), Recorder::GetPos(), Waving::SampleLength::Default);

		const float* p = Waving::FFTBuffer();
		buffer.Append(p);

		for (int i = 0; i < Window::Height(); ++i)
		{
			image[i][count] = HSV(-log(p[i]) * 10);
		}

		Texture(image).draw();

		Line(count, 0, count, Window::Height()).draw();
		if (count >= 1024)
			count = 0;
		count++;

		
	}
}
