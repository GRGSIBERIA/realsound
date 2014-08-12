#include <vector>

namespace sound
{
	/**
	* �ėp�I�Ȕg�`�N���X
	*/
	class Signal
	{
	private:
		typedef std::vector<float> PowerArray;
		PowerArray buffer;
		unsigned length;

	public:
		/**
		* �g�`�̒������擾����
		*/
		inline unsigned Length() const {
			return length;
		}

		/**
		* �g�`���擾����
		*/
		inline float Buffer(const unsigned i) const {
			return buffer[i];
		}

	public:
		Signal(const float spec[], const unsigned length)
		{
			buffer = PowerArray(spec, spec + length);
			this->length = length;
		}

		Signal() {}
	};
}