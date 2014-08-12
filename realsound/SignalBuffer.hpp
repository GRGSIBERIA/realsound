#include <vector>
#include "Signal.hpp"

namespace sound
{
	class SignalBuffer
	{
	private:
		typedef std::vector<Signal> SignalArray;
		typedef std::vector<unsigned> TimeArray;
		SignalArray signals;
		TimeArray microSecs;

		unsigned bufferSize;
		unsigned position;
		unsigned spectrumLength;
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

	public:
		SignalBuffer(unsigned bufferSize, unsigned spectrumLength)
			: position(0), isFull(false), spectrumLength(spectrumLength), bufferSize(bufferSize)
		{
			signals = SignalArray(bufferSize);
			microSecs = TimeArray(bufferSize);
		}

		/**
		* バッファに周波数スペクトルを追加する
		*/
		void Append(float signal[], unsigned microSec)
		{
			signals[position] = Signal(signal, spectrumLength);
			microSecs[position] = microSec;

			if (++position >= bufferSize) 
			{
				position = 0;
				isFull = true;
			}
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