#pragma once

#include <QTime>

typedef QTime Time;

class RenderCount : public Time{
    unsigned int m_FramesPerSecond, m_UpdatesPerSecond;
    float time_previous;
    float updateTimer;
    float updateTick;
    unsigned int renders;
    unsigned int updates;
public:
    bool timetoTick;
    bool timetoUpdate;

public:
    RenderCount(float updateTick = 1.0f / 60.0f)
        : m_FramesPerSecond(0), m_UpdatesPerSecond(0), time_previous(0), updateTimer(0), updateTick(updateTick), renders(0), updates(0), timetoTick(false), timetoUpdate(false) {}

    inline void count(){
        if ((float)elapsed()/1000 - updateTimer > updateTick) {
            updates++;
            updateTimer += updateTick;
            timetoUpdate = true;
        }
        renders++;
        if ((float)elapsed()/1000 - time_previous > 1.0f) {
            time_previous += 1.0f;
            m_FramesPerSecond = renders;
            m_UpdatesPerSecond = updates;
            updates = 0;
            renders = 0;
            timetoTick = true;
        }
    }

    inline unsigned int getFPS() const { return m_FramesPerSecond; }
    inline unsigned int getUPS() const { return m_UpdatesPerSecond; }

};
