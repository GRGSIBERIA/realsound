#include <vector>

namespace sound
{
	class Cepstrum
	{
	private:
		typedef std::vector<float> FloatArray;

	private:
		FloatArray cepstrum;

		unsigned sampleLength;
		unsigned samplingFreq;
		unsigned cepstrumLength;

	public:
		Cepstrum(const float* p, unsigned sampleLength, unsigned samplingFreq)
			: sampleLength(sampleLength), samplingFreq(samplingFreq), cepstrumLength(sampleLength >> 1)
		{
			const float pi = 3.14159265359f;
			FloatArray signal(p, p + sampleLength);
			
#pragma omp parallel for
			for (int i = 0; i < sampleLength; ++i)
			{
				// ハミング窓を取る
				signal[i] = 0.54f - 0.46f * cosf(signal[i] * 2.0f * pi);

				// 対数振幅スペクトルへ変換
				signal[i] = log10f(signal[i]);
			}

			cepstrum = FloatArray(sampleLength >> 1);
#pragma omp parallel for
			for (int i = 0; i < sampleLength >> 1; ++i)
			{
				// フーリエ変換をかける
			}

		}
	};
}