#include <vector>

namespace sound
{
	/**
	* 汎用的な波形クラス
	*/
	class Signal
	{
	private:
		typedef std::vector<float> PowerArray;
		PowerArray buffer;
		unsigned length;

	public:
		/**
		* 波形の長さを取得する
		*/
		inline unsigned Length() const {
			return length;
		}

		/**
		* 波形を取得する
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