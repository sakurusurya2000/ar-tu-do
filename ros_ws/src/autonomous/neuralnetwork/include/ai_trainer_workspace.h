#pragma once

#include "ai_trainer.h"
#include "ai_math.h"

namespace ai_workspace
{
    using namespace ai_trainer;
    using namespace ai_math;
    using namespace std;

    // ################################################################
    // #    parameter functions
    // ################################################################
     
    // returns the fitness of the given test results m
    inline double fitness(meta* m)
    {
        double max_lap_time = 50.0;
        double lap_time = std::min(max_lap_time, m->lap_time);
        double lap_bonus = 0;

        if(lap_time > 0.0)
        {
            // completed lap
            lap_bonus =  (max_lap_time - lap_time); // smaller is better
        }

        double score = m->added_velocity / 100.0 + lap_bonus;
        return score;
    }

    // creates a mutation of a parent vector
    inline NetVector mutate(NetVector parent, double learning_rate)
    {
        auto r_uniform = r_normal_distribution(parent.size(), 0, learning_rate);
        // auto r_binary = r_binary_mutation(parent.size(), 2);
        // auto random = mult(r_uniform, r_binary);
        // auto m = add(parent, random);
        auto m = add(parent, r_uniform);
        return m;
    }

    // an event happend. return true to abort test
    inline bool event(meta *m, int reason)
    {
        switch(reason)
        {
            case REASON_TIMER:
            case REASON_CRASH:
            case REASON_LAP:
            {
                m->reason = reason;
                return true;
            }
            case REASON_OUTPUT:

            default:
            {
                return false;
            }
        }
    }

    // ################################################################
    // #    parameter output
    // ################################################################

    inline string get_test_output(meta* m, int m_gen, int m_index, int n)
    {
        std::string str = "generation: " + std::to_string(m_gen) //
                        + " | entity: " + std::to_string(m_index) + "/" + std::to_string(n)
                        // + " | time: " + std::to_string(m->time)
                        // + " | vel_sum: " +  std::to_string(m->added_velocity)
                        + " | score: " + std::to_string(m->score)
                        + " | vel_avg: " + std::to_string(m->avg_velocity)
                        + " | abort reason: " + std::to_string(m->reason)
                        + " | lap_time: " + std::to_string(m->lap_time);
        return str;
    }


}