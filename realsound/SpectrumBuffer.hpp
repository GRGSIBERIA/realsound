#include <vector>
#include "Spectrum.hpp"

namespace sound
{
	class SpectrumBuffer
	{
	private:
		typedef std::vector<Spectrum> SpectrumArray;
		typedef std::vector<unsigned> TimeArray;
		SpectrumArray spectrums;
		TimeArray microSecs;

		unsigned bufferSize;
		unsigned position;
		unsigned spectrumLength;
		bool isFull;

	public:
		inline const Spectrum& Spectrums(const unsigned pos) const {
			return spectrums[pos];
		}

		inline const unsigned Times(const unsigned pos) const {
			return microSecs[pos];
		}

		inline unsigned Position() const {
			return position;
		}

		inline unsigned BufferSize() const {
			return bufferSize;
		}

		inline bool IsFull() const {
			return isFull;
		}

	public:
		SpectrumBuffer(unsigned bufferSize, unsigned spectrumLength)
			: position(0), isFull(false), spectrumLength(spectrumLength), bufferSize(bufferSize)
		{
			spectrums = SpectrumArray(bufferSize);
			microSecs = TimeArray(bufferSize);
		}

		void Append(float spectrum[], unsigned microSec)
		{
			spectrums[position] = Spectrum(spectrum, spectrumLength);
			microSecs[position] = microSec;

			if (++position >= bufferSize) 
			{
				position = 0;
				isFull = true;
			}
		}

		void Clear()
		{
			position = 0;
		}
	};
}