#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>

#include <luna/core/Log.h>

namespace luna
{
	namespace audio
	{
        bool check_al_errors(const std::string& filename, const std::uint_fast32_t line)
        {
            ALenum error = alGetError();
            if (error != AL_NO_ERROR)
            {
                LNA_CORE_ERROR("ERROR In file {} at line {}!", filename, line);

                switch (error)
                {
                case AL_INVALID_NAME:
                    LNA_CORE_ERROR("AL_INVALID_NAME: a bad name (ID) was passed to an OpenAL function");
                    break;
                case AL_INVALID_ENUM:
                    LNA_CORE_ERROR("AL_INVALID_ENUM: an invalid enum value was passed to an OpenAL function");
                    break;
                case AL_INVALID_VALUE:
                    LNA_CORE_ERROR("AL_INVALID_VALUE: an invalid value was passed to an OpenAL function");
                    break;
                case AL_INVALID_OPERATION:
                    LNA_CORE_ERROR("AL_INVALID_OPERATION: the requested operation is not valid");
                    break;
                case AL_OUT_OF_MEMORY:
                    LNA_CORE_ERROR("AL_OUT_OF_MEMORY: the requested operation resulted in OpenAL running out of memory");
                    break;
                default:
                    LNA_CORE_ERROR("UNKNOWN AL_ERROR: {}", error);
                    break;
                }

                return false;
            }

            return true;
        }

        template<typename alFunction, typename... Params>
        auto alCallImpl(const char* filename, const std::uint_fast32_t line, alFunction function, Params... params)
            -> typename std::enable_if_t<!std::is_same_v<void, decltype(function(params...))>, decltype(function(params...))>
        {
            auto ret = function(std::forward<Params>(params)...);
            check_al_errors(filename, line);
            return ret;
        }

        template<typename alFunction, typename... Params>
        auto alCallImpl(const char* filename, const std::uint_fast32_t line, alFunction function, Params... params)
            -> typename std::enable_if_t<std::is_same_v<void, decltype(function(params...))>, bool>
        {
            function(std::forward<Params>(params)...);
            return check_al_errors(filename, line);
        }

        bool check_alc_errors(const std::string& filename, const std::uint_fast32_t line, ALCdevice* device)
        {
            ALCenum error = alcGetError(device);
            if (error != ALC_NO_ERROR)
            {
                LNA_CORE_ERROR("ERROR In file {} at line {}!", filename, line);

                switch (error)
                {
                case ALC_INVALID_DEVICE:
                    LNA_CORE_ERROR("ALC_INVALID_DEVICE: a bad name (ID) was passed to an OpenAL function");
                    break;
                case ALC_INVALID_ENUM:
                    LNA_CORE_ERROR("ALC_INVALID_ENUM: an invalid enum value was passed to an OpenAL function");
                    break;
                case ALC_INVALID_VALUE:
                    LNA_CORE_ERROR("ALC_INVALID_VALUE: an invalid value was passed to an OpenAL function");
                    break;
                case ALC_INVALID_CONTEXT:
                    LNA_CORE_ERROR("ALC_INVALID_CONTEXT: the requested operation is not valid");
                    break;
                case ALC_OUT_OF_MEMORY:
                    LNA_CORE_ERROR("ALC_OUT_OF_MEMORY: the requested operation resulted in OpenAL running out of memory");
                    break;
                default:
                    LNA_CORE_ERROR("UNKNOWN AL_ERROR: {}", error);
                    break;
                }

                return false;
            }

            return true;
        }

        template<typename alcFunction, typename... Params>
        auto alcCallImpl(const char* filename, const std::uint_fast32_t line, alcFunction function, ALCdevice* device, Params... params)
            -> typename std::enable_if_t<std::is_same_v<void, decltype(function(params...))>, bool>
        {
            function(std::forward<Params>(params)...);
            return check_alc_errors(filename, line, device);
        }

        template<typename alcFunction, typename ReturnType, typename... Params>
        auto alcCallImpl(const char* filename, const std::uint_fast32_t line, alcFunction function, ReturnType& returnValue, ALCdevice* device, Params... params)
            -> typename std::enable_if_t<!std::is_same_v<void, decltype(function(params...))>, bool>
        {
            returnValue = function(std::forward<Params>(params)...);
            return check_alc_errors(filename, line, device);
        }
    }


#define alCall(function, ...) audio::alCallImpl(__FILE__, __LINE__, function, __VA_ARGS__)
#define alcCall(function, device, ...) audio::alcCallImpl(__FILE__, __LINE__, function, device, __VA_ARGS__)
}
