/**
 * @file af_temporal_profile.h
 * @brief Declares whether an imaging profile yields a temporal AF statistic.
 */

#pragma once

#include <string>

// True when `profile` is one of the comma-separated, exact names in
// `profile_list` (whitespace around an entry is ignored, an empty entry never
// matches, and so does an empty `profile`).
inline bool autofocus_profile_has_temporal_statistic(const std::string& profile_list,
                                                     const std::string& profile) {
    if (profile.empty()) return false;
    size_t begin = 0;
    for (;;) {
        const size_t comma = profile_list.find(',', begin);
        const size_t end = comma == std::string::npos ? profile_list.size() : comma;
        const size_t first = profile_list.find_first_not_of(" \t", begin);
        if (first != std::string::npos && first < end) {
            const size_t last = profile_list.find_last_not_of(" \t", end - 1);
            if (profile.compare(0, std::string::npos,
                                profile_list, first, last - first + 1) == 0) {
                return true;
            }
        }
        if (comma == std::string::npos) return false;
        begin = comma + 1;
    }
}
