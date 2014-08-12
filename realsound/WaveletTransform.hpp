#include "Scale.hpp"

namespace sound
{
	class WaveletTransform
	{
	private:
		typedef std::vector<Scale> ScaleArray;
		ScaleArray scales;
		unsigned numberOfScales;

	public:
		inline const Scale& Scales(const unsigned long i) const {
			return scales[i];
		}

		inline unsigned NumberOfScales() const {
			return numberOfScales;
		}

	public:
		WaveletTransform(const float signals[], unsigned long length)
		{
			numberOfScales = (unsigned)log2((float)length);
			scales = ScaleArray(numberOfScales);

			scales[0] = Scale(signals, length);
			for (unsigned long i = 1; i < numberOfScales; ++i) 
			{
				scales[i] = Scale(scales[i - 1]);
			}
		}
	};
}