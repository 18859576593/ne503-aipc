#include "af_temporal_profile.h"

#include <cassert>
#include <string>

int main() {
    const std::string list = "AI_ISP_Gen2_Basic,AI_ISP_Gen3_Basic";

    // Exact names only: Gen1 is a different pipeline and must not match a
    // prefix, a substring, or a different case.
    assert(autofocus_profile_has_temporal_statistic(list, "AI_ISP_Gen2_Basic"));
    assert(autofocus_profile_has_temporal_statistic(list, "AI_ISP_Gen3_Basic"));
    assert(!autofocus_profile_has_temporal_statistic(list, "AI_ISP_Gen1_Basic"));
    assert(!autofocus_profile_has_temporal_statistic(list, "AI_ISP_Gen3"));
    assert(!autofocus_profile_has_temporal_statistic(list, "ai_isp_gen3_basic"));
    assert(!autofocus_profile_has_temporal_statistic(list, "Daylight_Basic"));
    assert(!autofocus_profile_has_temporal_statistic(list, "AI_ISP_Gen3_Basic_FG2009"));

    // An unresolvable profile (HAL reported nothing) and an empty list both
    // leave the overrides off.
    assert(!autofocus_profile_has_temporal_statistic(list, ""));
    assert(!autofocus_profile_has_temporal_statistic("", "AI_ISP_Gen3_Basic"));
    assert(!autofocus_profile_has_temporal_statistic("", ""));

    // Whitespace around entries and stray separators are tolerated.
    assert(autofocus_profile_has_temporal_statistic(
        " AI_ISP_Gen3_Basic , Daylight_Basic", "AI_ISP_Gen3_Basic"));
    assert(autofocus_profile_has_temporal_statistic(
        "Daylight_Basic, AI_ISP_Gen3_Basic\t", "AI_ISP_Gen3_Basic"));
    assert(autofocus_profile_has_temporal_statistic(
        ",,AI_ISP_Gen3_Basic,,", "AI_ISP_Gen3_Basic"));
    assert(!autofocus_profile_has_temporal_statistic(",,,   ,", ""));
    return 0;
}
