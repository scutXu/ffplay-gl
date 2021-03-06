#include "Clock.h"

extern "C" {
    #include "libavutil/time.h"
    #include "libavutil/mathematics.h"
}

double Clock::get_clock()
{
	if(*queue_serial != serial) {
		return NAN;
	}
	if(paused) {
		return pts;
	}
    double current_time = av_gettime_relative();
    
    return pts_drift + current_time - (current_time - last_updated) * (1.0 - speed);
}
void Clock::set_clock_at(double pts,int serial,double time)
{
    this->pts = pts;
    this->last_updated = time;
    this->pts_drift = pts - time;
    this->serial = serial;
}
void Clock::set_clock(double pts,int serial)
{
    double time = av_gettime_relative() / 1000000.0;
    set_clock_at(pts, serial, time);
}
void Clock::set_clock_speed(double speed)
{
    
}
void Clock::init_clock(int * queue_serial)
{
    speed = 1.0;
    paused = 0;
    this->queue_serial = queue_serial;
    set_clock(NAN,-1);
}
void Clock::sync_clock_to_slave(Clock * slave)
{
    double clock = get_clock();
    double slave_clock = slave->get_clock();
    if(!isnan(slave_clock) && )
}
