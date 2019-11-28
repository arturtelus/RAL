#include "ral_listener.h"

#include "ral_error.h"

namespace ral
{
	ALfloat Listener::GetPropertyFloat(const ALenum prop_enum) noexcept
	{
		ALfloat prop_val{};
		alGetListenerf(prop_enum, &prop_val);
		AL_CHECK_CALL();
		return prop_val;
	}

	void Listener::SetProperty(const ALenum prop_enum, const ALfloat f_value) noexcept
	{
		alListenerf(prop_enum, f_value);
		AL_CHECK_CALL();
	}

	Listener::ALfloat3T Listener::GetProperty3Float(const ALenum prop_enum) noexcept
	{
		ALfloat v_1{}, v_2{}, v_3{};
		alGetListener3f(prop_enum, &v_1, &v_2, &v_3);
		AL_CHECK_CALL();
		return std::make_tuple(v_1, v_2, v_3);
	}

	void Listener::SetProperty(const ALenum prop_enum, const ALfloat val_1, const ALfloat val_2, const ALfloat val_3) noexcept
	{
		alListener3f(prop_enum, val_1, val_2, val_3);
		AL_CHECK_CALL();
	}

	std::vector<ALfloat> Listener::GetPropertyFloatVector(const ALenum prop_enum)
	{
		std::vector<ALfloat> property_values((prop_enum == AL_ORIENTATION) ? std::size_t{ 6 } : std::size_t{ 3 });
		alGetListenerfv(prop_enum, property_values.data());
		AL_CHECK_CALL();
		return property_values;
	}

	void Listener::SetProperty(const ALenum prop_enum, const std::vector<ALfloat>& values)
	{
		alListenerfv(prop_enum, values.data());
		AL_CHECK_CALL();
	}

	void Listener::SetProperty(const ALenum prop_enum, const ALfloat* data_ptr) noexcept
	{
		alListenerfv(prop_enum, data_ptr);
		AL_CHECK_CALL();
	}
}