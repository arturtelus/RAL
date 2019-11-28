#pragma once

namespace ral
{
	///Check for openAL errors after function call. Prints error to std::cerr
	bool ALCheckError(const char* file = nullptr, const int line = int{});

#ifdef DEBUG
#define AL_CHECK_CALL() ALCheckError(__FILE__, __LINE__)
#else
#define AL_CHECK_CALL()
#endif // DEBUG

	///Checks openal context errors.
	bool ALCCheckError(const char* file = nullptr, const int line = int{}) noexcept;

#ifdef DEBUG
#define ALC_CHECK_CALL() ALCCheckError(__FILE__, __LINE__)
#else
#define ALC_CHECK_CALL()
#endif
}