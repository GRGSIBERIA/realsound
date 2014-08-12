#include <vector>

namespace sound
{
	class Signal
	{
	private:
		typedef std::vector<float> PowerArray;
		PowerArray buffer;
		unsigned length;

	public:
		/**
		* ”gŒ`‚Ì’·‚³‚ðŽæ“¾‚·‚é
		*/
		inline unsigned Length() const {
			return length;
		}

		/**
		*
		*/
		inline float Buffer(const unsigned i) const {
			return buffer[i];
		}

	public:
		Signal(float spec[], unsigned length)
		{
			buffer = PowerArray(spec, spec + length);
			this->length = length;
		}

		Signal() {}
	};
}