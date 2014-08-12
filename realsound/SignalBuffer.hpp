#include <vector>

namespace sound
{
	/**
	* 時刻ごとの波形を蓄積するクラス
	*/
	class SignalBuffer
	{
	public:
		typedef std::vector<float> Signal;

	private:
		typedef std::vector<Signal> SignalArray;
		typedef std::vector<unsigned> MicroSecs;

	private:
		SignalArray buffer;
		unsigned bufferSize;
		unsigned signalLength;
		unsigned position;
		bool isFulled;

	private:
		/**
		* positionを前進させる
		* 末端に到達したら，自動的に始端まで移動させる
		*/
		inline void AdvancePosition()
		{
			if (++position >= bufferSize)
			{
				position = 0;
				isFulled = true;
			}
		}

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
		inline unsigned Position(const unsigned back) const {
			int buf = (int)position - back;
			if (buf < 0)
			{
				if (isFulled)
					return bufferSize - buf;
				return 0;
			}
			return buf;
		}

		/**
		* バッファ内の信号を返す
		* \param[in] pos バッファの位置
		* \return 信号
		*/
		inline const Signal& operator[](const unsigned pos) const {
			return buffer[pos];
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
				buffer[i].resize(signalLength, 0);
			}
		}

		/**
		* バッファに配列の中身を追加する
		* \param[in] p 信号の配列
		*/
		void Put(const float* p) 
		{
			buffer[position].assign(p, p + signalLength);
			AdvancePosition();
		}

		/**
		* ある位置の信号を置き換える
		* \param[in] pos 位置
		* \param[in] signal 置き換えたい信号
		*/
		void Replace(const unsigned pos, const Signal& signal)
		{
			buffer[pos].assign(signal.begin(), signal.end());
		}

		/**
		* ある位置の信号を置き換える
		* \param[in] pos 位置
		* \param[in] signal 置き換えたい信号
		*/
		void Replace(const unsigned pos, const float* signal)
		{
			buffer[pos].assign(signal, signal + pos);
		}
	};
}