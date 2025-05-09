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
#ifndef OURS_PHYS_ACPI_HPP
#define OURS_PHYS_ACPI_HPP 1

#include <acpi/parser.hpp>

namespace ours::phys {
    auto make_apic_parser(PhysAddr rsdp) -> ktl::Result<acpi::AcpiParser>;

} // namespace ours::phys

#endif // #ifndef OURS_PHYS_ACPI_HPP