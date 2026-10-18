// SPDX-License-Identifier: GPL-3.0-or-later
// FSUIPC AI/TCAS table offsets, kept in numeric order.
#pragma once

#include "offset_types.h" // OffsetEntry, put<>, take<>, DataRefCache
#include "impl/TCAS_tables.h"

inline const std::vector<OffsetEntry> &fsuipc_offset_table_ai_traffic_tcas_tables()
{
    static const std::vector<OffsetEntry> table = {
        // Ground extra records: 96 contiguous 20-byte records, spanning
        // 0xD040-0xD7BF. In record 0, legacy fields map as follows:
        // 0xD040 ID, 0xD044 file ID, 0xD046 pitch, 0xD048 departure ICAO,
        // 0xD04C arrival ICAO, 0xD050 runway number, 0xD051 runway designator,
        // 0xD052 bank. Only ID, pitch, and bank have X-Plane sources; the rest
        // remain zero. Each subsequent record starts 20 bytes later.
        {0xD040, tcas_tables::kSlots * tcas_tables::kExtraSize, &tcas_tables::rd_extra<0>, nullptr,
         "AI ground traffic extra data (per slot)", RefreshRate::Low},
        // Airborne extra records use the same layout at 0xD840, spanning
        // 0xD840-0xDFBF. The corresponding record-0 fields are 0xD840 ID,
        // 0xD844 file ID, 0xD846 pitch, 0xD848 departure ICAO, 0xD84C arrival
        // ICAO, 0xD850 runway number, 0xD851 runway designator, and 0xD852 bank.
        {0xD840, tcas_tables::kSlots * tcas_tables::kExtraSize, &tcas_tables::rd_extra<1>, nullptr,
         "AI airborne traffic extra data (per slot)", RefreshRate::Low},
        // Slot record size in bytes; fixed at 40.
        {0xE000, 2, &tcas_tables::rd_slot_size<0>, nullptr, "AI ground traffic slot size", RefreshRate::Low},
        // Ground table capacity; fixed at 96 slots.
        {0xE002, 2, &tcas_tables::rd_slot_count<0>, nullptr, "AI ground traffic slot count", RefreshRate::Low},
        // Number of ground slots used so far; does not decrease when slots are freed.
        {0xE004, 2, &tcas_tables::rd_used<0>, nullptr, "AI ground traffic slots used so far", RefreshRate::Low},
        // Table-wide counter incremented when any ground slot changes or is freed.
        {0xE006, 2, &tcas_tables::rd_counter<0>, nullptr, "AI ground traffic changes counter", RefreshRate::Low},
        // One byte per ground slot; increments when that slot changes or is freed.
        {0xE008, 96, &tcas_tables::rd_changed<0>, nullptr, "AI ground traffic slot changed ctr", RefreshRate::Low},
        // Ground-traffic range in NM when the user aircraft is airborne; 0 disables the limit.
        {0xE068, 1, nullptr,
         [](const uint8_t *src, uint32_t, DataRefCache &)
         { tcas_tables::config().ground_range_user_in_air = src[0]; },
         "TCAS ground range user in air"},
        // Ground-traffic range in NM when the user aircraft is on the ground; 0 disables the limit.
        {0xE069, 1, nullptr,
         [](const uint8_t *src, uint32_t, DataRefCache &)
         { tcas_tables::config().ground_range_user_on_ground = src[0]; },
         "TCAS ground range user on ground"},
        // Ground-table ATC ID format: 0=tail, 1=airline+flight, 2=type,
        // 3=title, 4=type+tail, 5=model.
        {0xE06A, 1, nullptr,
         [](const uint8_t *src, uint32_t, DataRefCache &)
         { tcas_tables::config().ground_id_option = src[0]; },
         "TCAS ground id option"},
        // Traffic preference: 0=near-ground preference, 1=active traffic preferred.
        // Retained for compatibility; currently not used for slot selection.
        {0xE06B, 1, nullptr,
         [](const uint8_t *src, uint32_t, DataRefCache &)
         { tcas_tables::config().active_traffic_preferred = src[0]; },
         "TCAS active traffic preference"},
        // Absolute offset of the nearest occupied ground slot; 0 means no occupied slots.
        {0xE07E, 2, &tcas_tables::rd_nearest<0>, nullptr, "Slot offset of nearest ground AI traffic", RefreshRate::Low},
        // Ground slots: 96 contiguous 40-byte records, spanning 0xE080-0xEF7F.
        // Slot 0 fields: 0xE080 ID, 0xE084 latitude, 0xE088 longitude, 0xE08C
        // altitude, 0xE090 heading, 0xE092 ground speed, 0xE094 vertical speed,
        // 0xE096 ATC ID (15 bytes), 0xE0A5 state, 0xE0A6-0xE0A7 COM1 frequency
        // (zero; unavailable in X-Plane). Subsequent slots start 40 bytes apart.
        {0xE080, tcas_tables::kSlots * tcas_tables::kSlotSize, &tcas_tables::rd_slots<0>, nullptr,
         "AI ground traffic slots", RefreshRate::Low},
        // Slot record size in bytes; fixed at 40.
        {0xF000, 2, &tcas_tables::rd_slot_size<1>, nullptr, "TCAS traffic slot size", RefreshRate::Low},
        // Airborne table capacity; fixed at 96 slots.
        {0xF002, 2, &tcas_tables::rd_slot_count<1>, nullptr, "TCAS traffic slot count", RefreshRate::Low},
        // Number of airborne slots used so far; does not decrease when slots are freed.
        {0xF004, 2, &tcas_tables::rd_used<1>, nullptr, "TCAS traffic slots used so far", RefreshRate::Low},
        // Table-wide counter incremented when any airborne slot changes or is freed.
        {0xF006, 2, &tcas_tables::rd_counter<1>, nullptr, "TCAS traffic changes counter", RefreshRate::Low},
        // One byte per airborne slot; increments when that slot changes or is freed.
        {0xF008, 96, &tcas_tables::rd_changed<1>, nullptr, "TCAS traffic slot changed ctr", RefreshRate::Low},
        // Airborne-traffic range in NM; 0 disables the limit.
        {0xF068, 1, nullptr,
         [](const uint8_t *src, uint32_t, DataRefCache &)
         { tcas_tables::config().air_range = src[0]; },
         "TCAS air range"},
        // Airborne-table ATC ID format: 0=tail, 1=airline+flight, 2=type,
        // 3=title, 4=type+tail, 5=model. Offset 0xF069 is unused.
        {0xF06A, 1, nullptr,
         [](const uint8_t *src, uint32_t, DataRefCache &)
         { tcas_tables::config().air_id_option = src[0]; },
         "TCAS air id option"},
        // Absolute offset of the nearest occupied airborne slot; 0 means none.
        {0xF07E, 2, &tcas_tables::rd_nearest<1>, nullptr, "Slot offset of nearest airborne AI traffic", RefreshRate::Low},
        // Airborne slots use the same 96-record layout, spanning 0xF080-0xFF7F.
        // Slot-0 legacy fields: 0xF080 ID, 0xF084 latitude, 0xF088 longitude,
        // 0xF08C altitude, 0xF090 heading, 0xF092 ground speed, 0xF094 vertical
        // speed, 0xF096 ATC ID (15 bytes), 0xF0A5 state, 0xF0A6-0xF0A7 COM1
        // frequency (zero; unavailable in X-Plane).
        {0xF080, tcas_tables::kSlots * tcas_tables::kSlotSize, &tcas_tables::rd_slots<1>, nullptr,
         "TCAS traffic slots", RefreshRate::Low},
    };
    return table;
}