#include <vector>

namespace sound
{
	/**
	* �������Ƃ̔g�`��~�ς���N���X
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
		* position��O�i������
		* ���[�ɓ��B������C�����I�Ɏn�[�܂ňړ�������
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
		* �o�b�t�@���̐M����Ԃ�
		* \param[in] pos �o�b�t�@�̈ʒu
		* \return �M��
		*/
		inline const Signal& operator[](const unsigned pos) const {
			return buffer[pos];
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
				buffer[i].resize(signalLength, 0);
			}
		}

		/**
		* �o�b�t�@�ɔz��̒��g��ǉ�����
		* \param[in] p �M���̔z��
		*/
		void Put(const float* p) 
		{
			buffer[position].assign(p, p + signalLength);
			AdvancePosition();
		}

		/**
		* ����ʒu�̐M����u��������
		* \param[in] pos �ʒu
		* \param[in] signal �u�����������M��
		*/
		void Replace(const unsigned pos, const Signal& signal)
		{
			buffer[pos].assign(signal.begin(), signal.end());
		}

		/**
		* ����ʒu�̐M����u��������
		* \param[in] pos �ʒu
		* \param[in] signal �u�����������M��
		*/
		void Replace(const unsigned pos, const float* signal)
		{
			buffer[pos].assign(signal, signal + pos);
		}
	};
}