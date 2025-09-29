#pragma once

#include "util/macros.h"

namespace AT::util {

    // @brief This is a lightest stopwatch that is automatically started when creating an instance.
    //        It can either store the elapsed time in a provided float pointer when the stopwatch is stopped/destroyed, 
    //        or it can allow retrieval of the elapsed time by manually calling [stop()] method.
    //        The time is measured in milliseconds.
    class stopwatch {
    public:

        stopwatch(f32* result_pointer, duration_precision precision = duration_precision::milliseconds)
            : m_result_pointer(result_pointer), m_precision(precision) { _start(); }

        ~stopwatch() { stop(); }

        GETTER_C(f32, result, *m_result_pointer);

        // @brief Stops the stopwatch and calculates the elapsed time.
        //        If a result pointer was provided, it will be updated with the elapsed time.
        // @return The elapsed time in milliseconds since the stopwatch was started.
        f32 stop();

        // @brief Restarts the stopped stopwatch
        void restart();

    private:

        void _start();

        f32*                                        m_result_pointer = &m_result;
        duration_precision                          m_precision;
        std::chrono::system_clock::time_point       m_start_point{};
        f32                                         m_result = 0.f;
    };

}
