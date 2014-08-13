#include "CLInformation.hpp"
#include "CLSource.hpp"

namespace cl
{
	/**
	* �\�[�X�R�[�h�̎��s���������߂̃N���X
	*/
	class CLExecute
	{
	public:
		cl_command_queue commandQueue;
		cl_program program;
		cl_kernel kernel;

	public:
		CLExecute(CLInformation& info, CLSource& source, std::string kernelName, int useDeviceId)
		{
			// �R�}���h�L���[�̐ݒ�
			commandQueue = clCreateCommandQueue(info.context, info.deviceIds[useDeviceId], 0, &info.result);

			// �v���O�����̓ǂݍ���
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
				throw L"�Ȃ񂩂悭�킩���\�[�X�R�[�h�̌`���𓊂���ꂽ";
			}

			// �v���O�����̃r���h
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