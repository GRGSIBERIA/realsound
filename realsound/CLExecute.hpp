#include "CLInformation.hpp"
#include "CLSource.hpp"

namespace cl
{
	/**
	* ソースコードの実行を扱うためのクラス
	*/
	class CLExecute
	{
	public:
		cl_command_queue commandQueue;
		cl_program program;
		cl_kernel kernel;

	private:
		void LoadSingleProgram(CLInformation& info, CLSource& source) 
		{
			size_t sourceSize = source.Size();
			switch (source.Type())
			{
			case SourceType::Text:
				clCreateProgramWithSource(
					info.context, 1,
					(const char**)source.Code(), (size_t*)&sourceSize,
					&info.result);
				break;

			case SourceType::Binary:
				clCreateProgramWithBinary(
					info.context, info.numDevices, info.deviceIds,
					(size_t*)sourceSize, (const unsigned char**)source.Code(),
					NULL, &info.result);
				break;

			default:
				throw L"なんかよくわからんソースコードの形式を投げられた";
			}
		}

		void LoadMultiProgram(CLInformation info, CLSourceArray& sourceArray)
		{
			switch (sourceArray.Type())
			{
			case SourceType::Text:
				clCreateProgramWithSource(
					info.context, 1,
					sourceArray.Pointers(), sourceArray.Sizes(),
					&info.result);
				break;

			case SourceType::Binary:
				clCreateProgramWithBinary(
					info.context, info.numDevices, info.deviceIds,
					sourceArray.Sizes(), (const unsigned char**)sourceArray.Pointers(),
					NULL, &info.result);
				break;

			default:
				throw L"なんかよくわからんソースコードの形式を投げられた";
			}
		}

	public:
		CLExecute(CLInformation& info, CLSource& source, std::string kernelName, int useDeviceId)
		{
			// コマンドキューの設定
			commandQueue = clCreateCommandQueue(info.context, info.deviceIds[useDeviceId], 0, &info.result);

			// プログラムの読み込み
			LoadSingleProgram(info, source);

			// プログラムのビルド
			kernel = clCreateKernel(program, kernelName.c_str(), &info.result);
		}

		CLExecute(CLInformation& info, CLSourceArray& sourceArray, std::string kernelName, int useDeviceId)
		{
			// コマンドキューの設定
			commandQueue = clCreateCommandQueue(info.context, info.deviceIds[useDeviceId], 0, &info.result);

			// プログラムの読み込み
			LoadMultiProgram(info, sourceArray);

			// プログラムのビルド
			kernel = clCreateKernel(program, kernelName.c_str(), &info.result);
		}

		virtual ~CLExecute()
		{
			clFlush(commandQueue);
			clFinish(commandQueue);
			clReleaseKernel(kernel);
			clReleaseProgram(program);
			clReleaseCommandQueue(commandQueue);
		}
	};

}