#include <chrono>
namespace Utility
{
    template <class Clock = std::chrono::steady_clock, class Duration = std::chrono::milliseconds>
    class Timer
    {
    public:
        Timer ();// 
        void start (); //
        void reset (); //
        void stop (); //
        Duration report (); //
    private:
        Duration _duration; //
        std::chrono::time_point<Clock, Duration> _timePoint;
        bool _on;
    };
};

//===================implement=================================
template <class Clock, class Duration>
Utility::Timer<Clock, Duration>::Timer (): _duration (), _timePoint (), _on (false)
{

}

template <class Clock, class Duration>
void Utility::Timer<Clock, Duration>::start ()
{
    _on = true;
    _timePoint = std::chrono::time_point_cast<Duration> (Clock::now ());
}

template <class Clock, class Duration>
void Utility::Timer<Clock, Duration>::stop ()
{
    if (!_on)
        return;
    _on = false;
    _duration += std::chrono::duration_cast <Duration> (std::chrono::time_point_cast<Duration> (Clock::now ()) - _timePoint);
}

template <class Clock, class Duration>
void Utility::Timer<Clock, Duration>::reset ()
{
    _duration = Duration::zero ();
}

template <class Clock, class Duration>
Duration Utility::Timer<Clock, Duration>::report ()
{
    Duration duration;
    if (_on)
    {
        stop ();
        duration = _duration;
        start ();
    }
    else
        duration = _duration;
    return duration;
}
