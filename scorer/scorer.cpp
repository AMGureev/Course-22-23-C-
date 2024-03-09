#include "scorer.h"

bool MySort(const std::pair<EventType, time_t>& a, const std::pair<EventType, time_t>& b) {
    return a.second < b.second;
}

ScoreTable GetScoredStudents(const Events& events, time_t score_time) {
    std::map<StudentName, std::set<TaskName>> score_table;
    std::map<StudentName, std::map<TaskName, std::vector<std::pair<EventType, time_t>>>> students_table;

    std::vector<Event> sorted_events = events;
    std::sort(sorted_events.begin(), sorted_events.end(),
              [](const Event& a, const Event& b) { return a.time < b.time; });

    for (const auto& event : sorted_events) {
        students_table[event.student_name][event.task_name].emplace_back(event.event_type, event.time);
    }

    for (auto& [student, tasks] : students_table) {
        for (auto& [task, actions] : tasks) {
            std::sort(actions.begin(), actions.end(), MySort);

            bool done = false;
            bool merge_open = false;

            for (const auto& [eventType, time] : actions) {
                if (time <= score_time) {
                    if (eventType == EventType::CheckFailed) {
                        done = false;
                    } else if (eventType == EventType::CheckSuccess) {
                        done = true;
                    } else if (eventType == EventType::MergeRequestOpen) {
                        merge_open = true;
                    } else if (eventType == EventType::MergeRequestClosed) {
                        merge_open = false;
                    }
                }
            }

            if (done && !merge_open) {
                score_table[student].insert(task);
            }
        }
    }

    return score_table;
}