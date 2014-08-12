#include <vector>

namespace sound
{
	class Spectrum
	{
	private:
		typedef std::vector<float> PowerArray;
		PowerArray buffer;
		unsigned length;

	public:
		inline unsigned Length() const {
			return length;
		}

		inline float Buffer(const unsigned i) const {
			return buffer[i];
		}

	public:
		Spectrum(float spec[], unsigned length)
		{
			buffer = PowerArray(spec, spec + length);
			this->length = length;
		}

		Spectrum() {}
	};
}