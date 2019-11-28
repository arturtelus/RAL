#pragma once

#include<al.h>
#include<vector>

namespace ral
{
	///Set listener properties with error checking
	struct Listener
	{
		using ALfloat3T = std::tuple<ALfloat, ALfloat, ALfloat>;

		///Get float property of the listener. Properties: AL_GAIN
		static ALfloat GetPropertyFloat(const ALenum prop_enum) noexcept;
		
		///Sets ALfloat property of the listener. Properties: AL_GAIN
		static void SetProperty(const ALenum prop_enum, const ALfloat f_value) noexcept;

		///Gets 3x ALfloat property of the listener. Properties: AL_POSITION, AL_VELOCITY
		static ALfloat3T GetProperty3Float(const ALenum prop_enum) noexcept;

		///Sets 3x ALfloat property of the listener. Properties: AL_POSITION, AL_VELOCITY
		static void SetProperty(const ALenum prop_enum, const ALfloat val_1, const ALfloat val_2, const ALfloat val_3) noexcept;

		///Gets ALfloat vector property of the listener. Properties: AL_POSITION, AL_VELOCITY, AL_ORIENTATION
		static std::vector<ALfloat> GetPropertyFloatVector(const ALenum prop_enum);

		///Sets ALfloat vector property of the listener. Properties: AL_POSITION, AL_VELOCITY, AL_ORIENTATION
		static void SetProperty(const ALenum prop_enum, const std::vector<ALfloat>& values);

		///Sets ALfloat vector property of the listener. Properties: AL_POSITION, AL_VELOCITY, AL_ORIENTATION
		static void SetProperty(const ALenum prop_enum, const ALfloat* data_ptr) noexcept;
	};
}