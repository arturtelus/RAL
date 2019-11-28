#pragma once

#include "ral_device.h"

namespace ral
{
	class Context
	{
		///Closes openal context
		static void AudioContextDeleter(ALCcontext* context_ptr) noexcept;

		///Pointer to openal context
		std::unique_ptr<ALCcontext, decltype(&Context::AudioContextDeleter)> audio_context_ptr_;

	public:

		///Creates context for openal device. Context is current after creation.
		Context(Device& device) noexcept;

		///Makes context current
		void MakeCurrent() const noexcept;
	};
}