#include "ral_error.h"

#ifdef USE_CREATIVE_OPENAL
#include<al.h>
#else 
#include<AL/al.h>
#include<AL/alc.h>
#endif
#include<iostream>

namespace ral
{
	bool ALCheckError(const char* file, const int line)
	{
		auto& out_stream{ std::cerr };

		bool success{ true };
		ALenum error{ AL_NO_ERROR };
		while (error = alGetError())
		{
			out_stream << "OpenAL error! File(" << file << ")(" << line << "): ";
			success = false;
			switch (error)
			{
			case AL_INVALID_NAME:
				out_stream << "AL_INVALID_NAME";
				break;
			case AL_INVALID_ENUM:
				out_stream << "AL_INVALID_ENUM";
				break;
			case AL_INVALID_VALUE:
				out_stream << "AL_INVALID_VALUE";
				break;
			case AL_INVALID_OPERATION:
				out_stream << "AL_INVALID_OPERATION";
				break;
			case AL_OUT_OF_MEMORY:
				out_stream << "AL_OUT_OF_MEMORY";
				break;
			default:
				break;
			}
		}
		return success;
	}

	bool ALCCheckError(const char* file, const int line) noexcept
	{
		auto& out_stream{ std::cerr };

		bool success{ true };
		ALenum error{ ALC_NO_ERROR };
		while (error = alGetError())
		{
			out_stream << "OpenAL context error! File(" << file << ")(" << line << "): ";
			success = false;
			switch (error)
			{
			case ALC_INVALID_DEVICE:
				out_stream << "ALC_INVALID_DEVICE";
				break;
			case ALC_INVALID_CONTEXT:
				out_stream << "ALC_INVALID_CONTEXT";
				break;
			case ALC_INVALID_ENUM:
				out_stream << "ALC_INVALID_ENUM";
				break;
			case ALC_INVALID_VALUE:
				out_stream << "ALC_INVALID_VALUE";
				break;
			case ALC_OUT_OF_MEMORY:
				out_stream << "ALC_OUT_OF_MEMORY";
				break;
			default:
				break;
			}
		}
		return success;
	}
}