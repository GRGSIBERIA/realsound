#ifndef CLSOURCE_HPP
#define CLSOURCE_HPP

#include <string>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

namespace cl
{
	enum SourceType
	{
		Text,
		Binary
	};

	/**
	* �\�[�X�R�[�h���������߂̃N���X
	*/
	class CLSource
	{
	private:
		SourceType type;
		std::string fileName;
		std::string code;

	private:
		void OpenFile()
		{
			std::ifstream ifst(fileName, std::ifstream::binary);
			if (ifst.fail())
			{
				throw L"�t�@�C���̓ǂݍ��݂Ɏ��s���܂���";
			}
			code = std::string(
				std::istreambuf_iterator<char>(ifst),
				std::istreambuf_iterator<char>());
			ifst.close();
		}

	public:
		inline const char* Code() const {
			return code.c_str();
		}

		inline const std::size_t Size() const {
			return code.size();
		}

		inline const std::string FileName() const {
			return fileName;
		}

		inline const SourceType Type() const {
			return type;
		}

	public:
		CLSource(const char* filename, SourceType type = SourceType::Text)
			: type(type)
		{
			fileName = std::string(filename);
			OpenFile();
		}
	};

	/**
	* �����\�[�X�R�[�h���g�������ꍇ�̔z��
	*/
	class CLSourceArray
	{
	private:
		std::vector<CLSource> sources;
		std::vector<size_t> sourceSizes;
		std::vector<const char*> sourcePtrs;
		SourceType type;

	public:
		/**
		* �\�[�X�R�[�h�̃|�C���^��Ԃ��܂�
		*/
		inline const char** Pointers() const {
			// ������S���ǂ����킩��Ȃ��Ȃ��c�c
			return sourcePtrs.begin()._Ptr;
		}

		inline const size_t* Sizes() const {
			return sourceSizes.begin()._Ptr;
		}

		inline const SourceType Type() const {
			return type;
		}

		/**
		* ���p�������\�[�X�R�[�h��ǉ����܂�
		*/
		inline void Append(const char* filename) {
			sources.push_back(CLSource(filename, type));
			auto s = sources[sources.size() - 1];
			sourcePtrs.push_back(s.Code());
			sourceSizes.push_back(s.Size());
		}

	public:
		CLSourceArray(SourceType useType) : type(useType)
		{
			
		}
	};
}

#endif