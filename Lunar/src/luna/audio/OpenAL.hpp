#include <AL/al.h>
#include <AL/alc.h>

#include <luna/core/Log.h>

namespace luna
{
	namespace audio
	{
        void check_al_errors(const std::string& filename, const std::uint_fast32_t line)
        {
            ALCenum error = alGetError();
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
                    std::cerr << "UNKNOWN AL ERROR: " << error;
                    LNA_CORE_ERROR("UNKNOWN AL ERROR: {}", error);
                    break;
                }
            }
        }

        template<typename alFunction, typename... Params>
        auto alCallImpl(const char* filename, const std::uint_fast32_t line, alFunction function, Params... params)
            -> typename std::enable_if<std::is_same<void, decltype(function(params...))>::value, decltype(function(params...))>::type
        {
            function(std::forward<Params>(params)...);
            check_al_errors(filename, line);
        }

        template<typename alFunction, typename... Params>
        auto alCallImpl(const char* filename, const std::uint_fast32_t line, alFunction function, Params... params)
            -> typename std::enable_if<!std::is_same<void, decltype(function(params...))>::value, decltype(function(params...))>::type
        {
            auto ret = function(std::forward<Params>(params)...);
            check_al_errors(filename, line);
            return ret;
        }

        template<typename alcFunction, typename... Params>
        auto alcCallImpl(const char* filename, const std::uint_fast32_t line, alcFunction function, Params... params)
            -> typename std::enable_if<std::is_same<void, decltype(function(params...))>::value, decltype(function(params...))>::type
        {
            function(std::forward<Params>(params)...);
            check_al_errors(filename, line);
        }

        template<typename alcFunction, typename... Params>
        auto alcCallImpl(const char* filename, const std::uint_fast32_t line, alcFunction function, Params... params)
            -> typename std::enable_if<!std::is_same<void, decltype(function(params...))>::value, decltype(function(params...))>::type
        {
            auto ret = function(std::forward<Params>(params)...);
            check_al_errors(filename, line);
            return ret;
        }
    }


#define alCall(function, ...) audio::alCallImpl(__FILE__, __LINE__, function, __VA_ARGS__)
#define alcCall(function, device, ...) audio::alcCallImpl(__FILE__, __LINE__, function, device, __VA_ARGS__)
}
