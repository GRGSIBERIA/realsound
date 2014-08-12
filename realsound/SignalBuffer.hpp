#include <vector>
#include "Signal.hpp"

namespace sound
{
	/**
	* 時刻ごとの波形を蓄積するクラス
	*/
	class SignalBuffer
	{
	private:
		typedef std::vector<Signal> SignalArray;
		typedef std::vector<unsigned> TimeArray;
		SignalArray signals;
		TimeArray microSecs;

		unsigned bufferSize;
		unsigned position;
		unsigned sampleSize;
		bool isFull;

	public:
		/**
		* バッファに蓄積されている値を取得する
		*/
		inline const Signal& Buffer(const unsigned pos) const {
			return signals[pos];
		}

		/**
		* バッファに入っているSpectrumの時間を取得する
		* 単位はマイクロ秒
		*/
		inline const unsigned Time(const unsigned pos) const {
			return microSecs[pos];
		}

		/**
		* バッファの位置を取得
		*/
		inline unsigned Position() const {
			return position;
		}

		/**
		* backだけ遡ってバッファの位置を取得
		*/
		inline unsigned Position(const unsigned back) const {
			int buf = position - back;
			if (buf < 0) 
			{
				if (!isFull)
					return 0;
				buf = bufferSize - buf - 1;
			}
			return buf;
		}

		/**
		* バッファの大きさを取得
		*/
		inline unsigned BufferSize() const {
			return bufferSize;
		}

		/**
		* バッファが満杯になったか調べる
		*/
		inline bool IsFull() const {
			return isFull;
		}

	private:
		inline void RoundPosition() 
		{
			if (++position >= bufferSize)
			{
				position = 0;
				isFull = true;
			}
		}

	public:
		SignalBuffer(unsigned bufferSize, unsigned sampleSize)
			: position(0), isFull(false), sampleSize(sampleSize), bufferSize(bufferSize)
		{
			signals = SignalArray(bufferSize);
			microSecs = TimeArray(bufferSize);
		}

		/**
		* バッファに信号を追加する
		*/
		void Append(const float signal[], const unsigned microSec)
		{
			signals[position] = Signal(signal, sampleSize);
			microSecs[position] = microSec;
			RoundPosition();
		}

		/**
		* バッファに信号を追加する
		*/
		void Append(const float signal[])
		{
			signals[position] = Signal(signal, sampleSize);
			microSecs[position] = 0;
			RoundPosition();
		}

		/**
		* バッファの位置を初期化する
		*/
		void Clear()
		{
			position = 0;
		}
	};
}