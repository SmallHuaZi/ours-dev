/// Copyright(C) 2024 smallhuazi
///
/// This program is free software; you can redistribute it and/or modify
/// it under the terms of the GNU General Public License as published
/// by the Free Software Foundation; either version 2 of the License, or
/// (at your option) any later version.
///
/// For additional information, please refer to the following website:
/// https://opensource.org/license/gpl-2-0
///
#ifndef GKTL_COUNTER_HPP
#define GKTL_COUNTER_HPP 1

#include <ours/types.hpp>

namespace gktl {
    class Counter {

    };

} // namespace gktl

#define GKTL_COUNTER_GROUP(NAME)
#define GKTL_COUNTER(VAR, NAME, GROUP) \
    usize g_counter_##VAR LINK_SECTION(".bss.init.kernel.counters");

#endif // #ifndef GKTL_COUNTER_HPP