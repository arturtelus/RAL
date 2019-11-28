#include "ral_device.h"

#ifdef DEBUG
#include<iostream>
#endif

#include "ral_error.h"

namespace ral
{
	const alStringT ral::Device::DefaultDeviceName()
	{
		if (alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT") == ALC_TRUE)
		{
			ALC_CHECK_CALL();
			const ALchar* default_device_name{ alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER) };
			ALC_CHECK_CALL();
			return alStringT{ default_device_name };
		}
		return {};
	}

	void Device::AudioDeviceDeleter(ALCdevice* device_ptr) noexcept
	{
#ifdef DEBUG
		std::clog << "[OpenAL] Closing device. " << device_ptr << '\n';
#endif // DEBUG
		if (alcCloseDevice(device_ptr) == ALC_FALSE)
		{
#ifdef DEBUG
			std::cerr << "[OpenAL] alcCloseDevice failed! Release contexts and buffers fist! " << device_ptr << '\n';
#endif // DEBUG
		}
		else
		{
#ifdef DEBUG
			std::clog << "[OpenAL] Device closed...\n";
#endif // DEBUG
			device_ptr = nullptr;
		}
	}

	Device::Device()
		: audio_device_ptr_(alcOpenDevice(nullptr), AudioDeviceDeleter)
	{
#ifdef DEBUG
		std::clog << "[OpenAL] Default device opened. " << audio_device_ptr_.get() << '\n';
#endif // DEBUG
	}

	///Opens new openal device using provided name
	Device::Device(const alStringT& device_name)
		: audio_device_ptr_(alcOpenDevice((device_name.empty() ? nullptr : device_name.data())), AudioDeviceDeleter)
	{
#ifdef DEBUG
		std::clog << "[OpenAL] Device opened. " << audio_device_ptr_.get() << '\n';
#endif // DEBUG
	}

	void CaptureDevice::CaptureAudioDeviceDeleter(ALCdevice* capture_device_ptr) noexcept
	{
#ifdef DEBUG
		std::clog << "[OpenAL] Closing capture device. " << capture_device_ptr << '\n';
#endif // DEBUG
		if (alcCaptureCloseDevice(capture_device_ptr) == ALC_FALSE)
		{
#ifdef DEBUG
			std::cerr << "[OpenAL] alcCaptureCloseDevice failed! \n";
#endif // DEBUG
		}
		else
		{
#ifdef DEBUG
			std::clog << "[OpenAL] Device closed... \n";
#endif // DEBUG
			capture_device_ptr = nullptr;
		}
	}

	CaptureDevice::CaptureDevice(ALCuint freq, ALCenum fmt, ALCsizei bufsize)
		: capture_device_ptr_(alcCaptureOpenDevice(nullptr, freq, fmt, bufsize), CaptureAudioDeviceDeleter)
	{
#ifdef DEBUG
		std::clog << "[OpenAL] Default capture device opened. " << capture_device_ptr_.get() << '\n';
#endif // DEBUG
	}

	CaptureDevice::CaptureDevice(const alStringT& device_name, ALCuint freq, ALCenum fmt, ALCsizei bufsize)
		: capture_device_ptr_(alcCaptureOpenDevice((device_name.empty() ? nullptr : device_name.data()), freq, fmt, bufsize), CaptureAudioDeviceDeleter)
	{
#ifdef DEBUG
		std::clog << "[OpenAL] Capture device opened. " << capture_device_ptr_.get() << '\n';
#endif // DEBUG
	}

	void CaptureDevice::Start() noexcept
	{
		alcCaptureStart(capture_device_ptr_.get());
		ALC_CHECK_CALL();
	}

	void CaptureDevice::Stop() noexcept
	{
		alcCaptureStop(capture_device_ptr_.get());
		ALC_CHECK_CALL();
	}

	ALCint CaptureDevice::CaptureSamples() noexcept
	{
		ALCint ivalue{};
		alcGetIntegerv(capture_device_ptr_.get(), ALC_CAPTURE_SAMPLES, ALCsizei{ 1 }, &ivalue);
		return ivalue;
	}

	void CaptureDevice::CaptureSamples(ALCvoid* buffer, const ALCsizei samples) noexcept
	{
		alcCaptureSamples(capture_device_ptr_.get(), buffer, samples);
		ALC_CHECK_CALL();
	}
}