#include <vector>

namespace sound
{
	/**
	* 時刻ごとの波形を蓄積するクラス
	*/
	class SignalBuffer
	{
	private:
		typedef std::vector<float> Signal;
		typedef std::vector<Signal> SignalArray;
		typedef std::vector<unsigned> MicroSecs;

	private:
		SignalArray buffer;
		unsigned bufferSize;
		unsigned signalLength;
		unsigned position;
		bool isFulled;

	public:
		/**
		* バッファの大きさを取得する
		* \return バッファの大きさ
		*/
		inline unsigned BufferSize() const {
			return bufferSize;
		}

		/**
		* 信号の長さを取得する
		* \return 信号の長さ
		*/
		inline unsigned SignalLength() const {
			return signalLength;
		}

		/**
		* バッファが満たされているか確認する
		* \return バッファが満たされているかどうかのフラグ
		*/
		inline bool IsFulled() const {
			return isFulled;
		}

		/**
		* バッファの現在位置を取得する
		* \return バッファの現在位置
		*/
		inline unsigned Position() const {
			return position;
		}

		/**
		* バッファの現在位置からbackだけ下がった位置を取得する
		* \param[in] back 現在位置から下がる距離
		* \return backだけ下がったバッファの位置
		*/
		inline unsigned Position(unsigned back) const {
			int buf = (int)position - back;
			if (buf < 0)
			{
				if (isFulled)
					return bufferSize - buf;
				return 0;
			}
			return buf;
		}

	public:
		/**
		* 信号をバッファに記録する
		* \param[in] bufferSize バッファの大きさ
		* \param[in] signalLength 信号の長さ
		*/
		SignalBuffer(const unsigned bufferSize, const unsigned signalLength)
			: bufferSize(bufferSize), signalLength(signalLength), position(0), isFulled(false)
		{
			buffer = SignalArray(bufferSize);
			for (unsigned i = 0; i < bufferSize; ++i)
			{
				buffer[i].resize(signalLength);
			}
		}

		/**
		* バッファに配列の中身を追加する
		* \param[in] p 信号の配列
		*/
		void Append(const float* p) 
		{
			buffer[position].assign(p, p + signalLength);

			if (++position >= bufferSize)
			{
				position = 0;
				isFulled = true;
			}
		}
	};
}