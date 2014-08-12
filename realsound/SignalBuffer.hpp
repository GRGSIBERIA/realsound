#include <vector>
#include "Signal.hpp"

namespace sound
{
	/**
	* �������Ƃ̔g�`��~�ς���N���X
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
		* �o�b�t�@�ɒ~�ς���Ă���l���擾����
		*/
		inline const Signal& Buffer(const unsigned pos) const {
			return signals[pos];
		}

		/**
		* �o�b�t�@�ɓ����Ă���Spectrum�̎��Ԃ��擾����
		* �P�ʂ̓}�C�N���b
		*/
		inline const unsigned Time(const unsigned pos) const {
			return microSecs[pos];
		}

		/**
		* �o�b�t�@�̈ʒu���擾
		*/
		inline unsigned Position() const {
			return position;
		}

		/**
		* back�����k���ăo�b�t�@�̈ʒu���擾
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
		* �o�b�t�@�̑傫�����擾
		*/
		inline unsigned BufferSize() const {
			return bufferSize;
		}

		/**
		* �o�b�t�@�����t�ɂȂ��������ׂ�
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
		* �o�b�t�@�ɐM����ǉ�����
		*/
		void Append(const float signal[], const unsigned microSec)
		{
			signals[position] = Signal(signal, sampleSize);
			microSecs[position] = microSec;
			RoundPosition();
		}

		/**
		* �o�b�t�@�ɐM����ǉ�����
		*/
		void Append(const float signal[])
		{
			signals[position] = Signal(signal, sampleSize);
			microSecs[position] = 0;
			RoundPosition();
		}

		/**
		* �o�b�t�@�̈ʒu������������
		*/
		void Clear()
		{
			position = 0;
		}
	};
}