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
				// �n�~���O�������
				signal[i] = 0.54f - 0.46f * cosf(signal[i] * 2.0f * pi);

				// �ΐ��U���X�y�N�g���֕ϊ�
				signal[i] = log10f(signal[i]);
			}

			cepstrum = FloatArray(sampleLength >> 1);
#pragma omp parallel for
			for (int i = 0; i < sampleLength >> 1; ++i)
			{
				// �t�[���G�ϊ���������
			}

		}
	};
}