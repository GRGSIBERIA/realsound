#include <vector>

namespace sound 
{
	class Scale 
	{
	private:
		typedef std::vector<float> WaveletArray;
		WaveletArray weights;
		WaveletArray differences;
		unsigned long size;
		int scaleNumber;

	private:
		void InitScale(const unsigned long s) {
			size = s;
			weights = WaveletArray(size);
			differences = WaveletArray(size);
		}

	public:
		inline float Weights(const unsigned long i) const {
			return weights[i];
		}

		inline float Differences(const unsigned long i) const {
			return differences[i];
		}

		inline unsigned long Size() const {
			return size;
		}

		inline int ScaleNumber() const {
			return scaleNumber;
		}

		Scale() {}

		Scale(const float signals[], const unsigned long length) 
		{
			InitScale(length);
			weights.assign(signals, signals + length);
			differences.assign(length, 0);
		}

		Scale(const Scale& prevScale)
		{
			InitScale(prevScale.size >> 1);

			for (unsigned long i = 0; i < size; ++i)
			{
				float a = prevScale.weights[i * 2];
				float b = prevScale.weights[i * 2 + 1];
				weights[i] = (a + b) * 0.5f;
				differences[i] = a - b;
			}
		}
	};
}