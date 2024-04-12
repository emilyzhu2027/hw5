#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool schedule_helper(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, int r, int c, std::vector<int>& shift_count_vec);
bool isValid(DailySchedule& sched, const AvailabilityMatrix& avail, const size_t maxShifts, unsigned int worker_id, int r, int c, const size_t dailyNeed, int shift_count);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    for (unsigned int i = 0; i < avail.size(); i++){
        std::vector<unsigned int> new_row(dailyNeed, INVALID_ID);
        sched.push_back(new_row);
    }

    std::vector<int> shift_count_vec(avail[0].size(), 0);
    bool sched_bool = schedule_helper(avail, dailyNeed, maxShifts, sched, 0, 0, shift_count_vec);

    return sched_bool;

}

bool schedule_helper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    int r,
    int c,
    std::vector<int>& shift_count_vec)
{
    if (r == (int)(sched.size()-1) && c == (int)(dailyNeed)){
        return true;
    }

    if (c == (int)(dailyNeed)) {
        r++;
        c = 0;
    }

    if (sched[r][c] != INVALID_ID){
        return schedule_helper(avail, dailyNeed, maxShifts, sched, r, c+1, shift_count_vec);
    }

    for (unsigned int i = 0; i < avail[0].size(); i++){
        sched[r][c] = i;
        shift_count_vec[i] += 1;
        if (isValid(sched, avail, maxShifts, i, r, c, dailyNeed, shift_count_vec[i])){
            bool status = schedule_helper(avail, dailyNeed, maxShifts, sched, r, c+1, shift_count_vec);
            if (status){
                return true;
            }
        }

        sched[r][c] = INVALID_ID;
        shift_count_vec[i] -= 1;
    }

    return false;
}

bool isValid(
    DailySchedule& sched,
    const AvailabilityMatrix& avail,
    const size_t maxShifts,
    unsigned int worker_id,
    int r,
    int c,
    const size_t dailyNeed,
    int shift_count)
{
    if (avail[r][worker_id] == 0){
        return false;
    }
    if (shift_count > (int)(maxShifts)){
        return false;
    }

    for(unsigned int i = 0; i < (unsigned int)(dailyNeed); i++){
      if (sched[r][i] == worker_id && (int)(i) != c){
        return false;
      }
    }

    return true;
}

