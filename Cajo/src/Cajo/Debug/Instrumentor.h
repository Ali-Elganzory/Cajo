#pragma once

#include <string>
#include <chrono>
#include <algorithm>
#include <fstream>
#include <thread>
#include <mutex>

#define CAJO_PROFILE 1
#ifdef CAJO_PROFILE
    // Resolve which function signature macro will be used. Note that this only
    // is resolved when the (pre)compiler starts, so the syntax highlighting
    // could mark the wrong one in your editor!
    #if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
        #define CAJO_FUNC_SIG __PRETTY_FUNCTION__
    #elif defined(__DMC__) && (__DMC__ >= 0x810)
        #define CAJO_FUNC_SIG __PRETTY_FUNCTION__
    #elif defined(__FUNCSIG__)
        #define CAJO_FUNC_SIG __FUNCSIG__
    #elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
        #define CAJO_FUNC_SIG __FUNCTION__
    #elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
        #define CAJO_FUNC_SIG __FUNC__
    #elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
        #define CAJO_FUNC_SIG __func__
    #elif defined(__cplusplus) && (__cplusplus >= 201103)
        #define CAJO_FUNC_SIG __func__
    #else
        #define CAJO_FUNC_SIG "CAJO_FUNC_SIG unknown!"
    #endif

    #define CAJO_PROFILE_BEGIN_SESSION(name, filepath)    ::Cajo::Instrumentor::Get().BeginSession(name, filepath)
    #define CAJO_PROFILE_END_SESSION()                    ::Cajo::Instrumentor::Get().EndSession()
    #define CAJO_PROFILE_SCOPE(name)                      ::Cajo::InstrumentationTimer timer##__LINE__(name)
    #define CAJO_PROFILE_FUNCTION()                       CAJO_PROFILE_SCOPE(CAJO_FUNC_SIG)
#else
    #define CAJO_PROFILE_BEGIN_SESSION(name, filepath)
    #define CAJO_PROFILE_END_SESSION()
    #define CAJO_PROFILE_SCOPE(name)
    #define CAJO_PROFILE_FUNCTION()
#endif

namespace Cajo {

    struct ProfileResult
    {
        const std::string name;
        long long start, end;
        std::thread::id threadID;
    };

    class Instrumentor
    {
        Instrumentor() { }

    public:
        static Instrumentor& Get()
        {
            static Instrumentor instance;
            return instance;
        }

        ~Instrumentor()
        {
            EndSession();
        }

        void BeginSession(const std::string& name, const std::string& filepath = "results.json")
        {
            if (m_ActiveSession)
            {
                EndSession();
                if (Log::GetCoreLogger())  // Edge case: BeginSession() might be before Log::Init()
                    CAJO_CORE_ERROR("Instrumentor::BeginSession('{0}') when session '{1}' already open.", name, m_SessionName);
            }

            m_OutputStream.open(filepath);
            if (m_OutputStream.is_open())
            {
                m_ActiveSession = true;
                WriteHeader();
                m_SessionName = name;
            }
            else 
            {
                if (Log::GetCoreLogger())  // Edge case: BeginSession() might be before Log::Init()
                    CAJO_CORE_ERROR("Instrumentor could not open results file '{0}'.", filepath);
            }
        }

        void EndSession()
        {
            if (!m_ActiveSession)
                return;

            m_ActiveSession = false;
            std::lock_guard lock(m_Lock);
            WriteFooter();
            m_OutputStream.close();
        }

        void WriteProfile(const ProfileResult& result)
        {
            std::stringstream json;

            std::string name = result.name;
            std::replace(name.begin(), name.end(), '"', '\'');

            json << "{";
            json << "\"cat\":\"function\",";
            json << "\"dur\":" << (result.end - result.start) << ',';
            json << "\"name\":\"" << name << "\",";
            json << "\"ph\":\"X\",";
            json << "\"pid\":0,";
            json << "\"tid\":" << result.threadID << ",";
            json << "\"ts\":" << result.start;
            json << "},";

            std::lock_guard<std::mutex> lock(m_Lock);
            if (m_ActiveSession)
                m_OutputStream << json.str();
        }

        void WriteHeader()
        {
            m_OutputStream << "{\"otherData\": {},\"traceEvents\":[";
        }

        void WriteFooter()
        {
            m_OutputStream << "{}]}";
        }

    private:
        std::string     m_SessionName = "None";
        std::ofstream   m_OutputStream;
        std::mutex      m_Lock;
        bool            m_ActiveSession = false;


    };

    class InstrumentationTimer
    {
    public:
        InstrumentationTimer(const std::string& name)
            : m_Result({ name, 0, 0, std::this_thread::get_id() })
            , m_Stopped(false)
        {
            m_StartTimepoint = std::chrono::high_resolution_clock::now();
        }

        ~InstrumentationTimer()
        {
            if (!m_Stopped)
                Stop();
        }

        void Stop()
        {
            auto endTimepoint = std::chrono::high_resolution_clock::now();

            m_Result.start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
            m_Result.end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();
            Instrumentor::Get().WriteProfile(m_Result);

            m_Stopped = true;
        }

    private:
        ProfileResult m_Result;

        std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
        bool m_Stopped;
    };

}