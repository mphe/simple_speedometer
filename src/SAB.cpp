#include "SAB.hpp"

auto SABBossTracker::CategorizeBoss(const cbtevent&  /*ev*/, const ag& dst) -> std::optional<SABBossInfo>
{
    switch (dst.prof)
    {
        case 0x2eb4: // storm wizard phase 1
            _hasHitStormWizard = true;
            return std::nullopt;

        case 0xffff32c8: // w1z1
        case 0xffff69f6: // w1z1
        case 0xfffff7f3: // w2z1
        case 0xffff0e2b: // w2z2
            _hasHitStormWizard = false;
            _toadRubyID = 0;
            return SABBossInfo{ 1500, dst.prof, SABBossType::Cage };

        case 0xffff0000:            // toad / wizard
            if (_hasHitStormWizard) // storm dragon
            {
                _toadRubyID = 0;
                return SABBossInfo{ 1500, dst.prof, SABBossType::Wizard };
            }

            _hasHitStormWizard = false;
            return std::nullopt;

            // FIXME: Find a reliable way to distinguish ruby and frog entities
            // // before attacking the toad, we must first attack the ruby (which has the same ID as toad)
            // if (_toadRubyID == 0)
            // {
            //     _toadRubyID = ev.dst_instid;
            //     return std::nullopt;
            // }
            //
            // // attacking ruby
            // if (ev.dst_instid == _toadRubyID)
            //     return std::nullopt;
            //
            // // attack on toad but not the ruby
            // return SABBossInfo { 625, dst.prof, SABBossType::Toad };

        default:
            return std::nullopt;
    }
}

void SABBossTracker::Reset()
{
    _hasHitStormWizard = false;
    _toadRubyID = 0;
}
