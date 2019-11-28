#pragma once

#include<string>
#include<memory>

#include<AL/al.h>
#include<AL/alc.h>

namespace ral
{
	using alStringT = std::basic_string<ALchar>;

	///OpenAL audio playback device
	class Device
	{
		///Closes openal device
		static void AudioDeviceDeleter(ALCdevice* device_ptr) noexcept;

		///Pointer to openal device
		std::unique_ptr<ALCdevice, decltype(&Device::AudioDeviceDeleter)> audio_device_ptr_;

		///ral::Context can access stored device ptr
		friend class Context;

	public:

		///Opens default openal device
		Device();

		///Opens new openal device using provided name
		Device(const alStringT& device_name);

		///Get default audio playback device name
		static const alStringT DefaultDeviceName();

		//TODO: enumerate all playback devices
	};

	///OpenAL audio capture device
	class CaptureDevice
	{
		///Closes openal capture device
		static void CaptureAudioDeviceDeleter(ALCdevice* capture_device_ptr) noexcept;

		///Pointer to openal capture device
		std::unique_ptr<ALCdevice, decltype(&CaptureDevice::CaptureAudioDeviceDeleter)> capture_device_ptr_;

		//TODO: internal capture buffer?

	public:

		///Opens default openal capture device
		CaptureDevice(ALCuint freq, ALCenum fmt, ALCsizei bufsize);

		///Opens openal device using provided name
		CaptureDevice(const alStringT& device_name, ALCuint freq, ALCenum fmt, ALCsizei bufsize);

		///Starts openal capture (alcCaptureStart)
		void Start() noexcept;

		///Stops audio capturing (alcCaptureStop)
		void Stop() noexcept;

		///Get size of captured data (alcGetIntegerv + ALC_CAPTURE_SAMPLES)
		ALCint CaptureSamples() noexcept;

		///Copy captured samples
		void CaptureSamples(ALCvoid* buffer, const ALCsizei samples) noexcept;

		//TODO: enumerate all capture devices
	};
}