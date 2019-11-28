#include "ral_context.h"

#ifdef DEBUG
#include<iostream>
#endif

#include "ral_error.h"

namespace ral
{
	void Context::AudioContextDeleter(ALCcontext* context_ptr) noexcept
	{
#ifdef DEBUG
		std::clog << "[OpenAL] Closing context. " << context_ptr << '\n';
#endif // DEBUG
		alcMakeContextCurrent(NULL);
		alcDestroyContext(context_ptr);
		context_ptr = nullptr;
	}

	Context::Context(Device& device) noexcept
		: audio_context_ptr_(alcCreateContext(device.audio_device_ptr_.get(), NULL), AudioContextDeleter)
	{
#ifdef DEBUG
		std::clog << "[OpenAL] Context created. " << audio_context_ptr_.get() << '\n';
#endif // DEBUG
		MakeCurrent();
	}

	void Context::MakeCurrent() const noexcept
	{
		alcMakeContextCurrent(audio_context_ptr_.get());
		AL_CHECK_CALL();
	}
}