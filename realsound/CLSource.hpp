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
	* ソースコードを扱うためのクラス
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
				throw L"ファイルの読み込みに失敗しました";
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
	* 複数ソースコードを使いたい場合の配列
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
		* ソースコードのポインタを返します
		*/
		inline const char** Pointers() const {
			// これ安全かどうかわからないなぁ……
			return sourcePtrs.begin()._Ptr;
		}

		inline const size_t* Sizes() const {
			return sourceSizes.begin()._Ptr;
		}

		inline const SourceType Type() const {
			return type;
		}

		/**
		* 利用したいソースコードを追加します
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