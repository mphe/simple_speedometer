#pragma once

#include "arcdps.h"
#include <optional>

enum class SABBossType
{
    Cage,
    Toad,
    Wizard,
};


struct SABBossInfo
{
    int32_t health;
    uint32_t id;
    SABBossType type;
};


class SABBossTracker
{
public:
    auto CategorizeBoss(const cbtevent& ev, const ag& dst) -> std::optional<SABBossInfo>;
    void Reset();

private:
    uint32_t _toadRubyID = 0;
    bool _hasHitStormWizard = false;
};
