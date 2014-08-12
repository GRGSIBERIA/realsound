#include <vector>

namespace sound
{
	/**
	* �������Ƃ̔g�`��~�ς���N���X
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
		* �o�b�t�@�̑傫�����擾����
		* \return �o�b�t�@�̑傫��
		*/
		inline unsigned BufferSize() const {
			return bufferSize;
		}

		/**
		* �M���̒������擾����
		* \return �M���̒���
		*/
		inline unsigned SignalLength() const {
			return signalLength;
		}

		/**
		* �o�b�t�@����������Ă��邩�m�F����
		* \return �o�b�t�@����������Ă��邩�ǂ����̃t���O
		*/
		inline bool IsFulled() const {
			return isFulled;
		}

		/**
		* �o�b�t�@�̌��݈ʒu���擾����
		* \return �o�b�t�@�̌��݈ʒu
		*/
		inline unsigned Position() const {
			return position;
		}

		/**
		* �o�b�t�@�̌��݈ʒu����back�������������ʒu���擾����
		* \param[in] back ���݈ʒu���牺���鋗��
		* \return back�������������o�b�t�@�̈ʒu
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
		* �M�����o�b�t�@�ɋL�^����
		* \param[in] bufferSize �o�b�t�@�̑傫��
		* \param[in] signalLength �M���̒���
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
		* �o�b�t�@�ɔz��̒��g��ǉ�����
		* \param[in] p �M���̔z��
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