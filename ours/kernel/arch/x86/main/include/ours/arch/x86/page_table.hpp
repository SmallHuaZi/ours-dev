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
#ifndef OURS_ARCH_X86_PAGE_TABLE_HPP
#define OURS_ARCH_X86_PAGE_TABLE_HPP 1

#include <ours/mem/mod.hpp>
#include <ours/mem/gaf.hpp>
#include <ours/mem/vm_page.hpp>
#include <ours/mem/memory_model.hpp>
#include <ours/mem/physmap.hpp>
#include <ours/mutex.hpp>

#include <arch/page_table.hpp>
#include <ustl/bitfields.hpp>

namespace ours::mem {
    struct X86PageAllocator;
    struct X86MmuPageSynchroniser;
    struct X86EptPageSynchroniser;

    /// TODO(SmallHuaZi) We need to make a tracker helper class to trace all mapping action.
    typedef arch::PageTable <
        arch::paging::PageAllocator<X86PageAllocator>,
        // A x86-custom option to give out a type of page synchroniser for MMU.
        arch::paging::X86MmuPageSynchroniser<X86MmuPageSynchroniser>,
        // A x86-custom option to give out a type of page synchroniser for EPT.
        arch::paging::X86EptPageSynchroniser<X86EptPageSynchroniser>,
        arch::paging::PhysToVirt<PhysMap>,
        arch::MutexT<Mutex>
    > PageTable;

    struct X86PageAllocator {
        static auto alloc_pages(usize nr_pages, usize align) -> PhysAddr {
            PhysAddr phys_addr;
            auto frame = alloc_frame(kGafKernel | Gaf::Zero, &phys_addr, 0); 
            if (!frame) {
                return 0;
            }
            auto page = role_cast<PfRole::Vmm>(frame);
            page->num_mappings += 1;

            return phys_addr;
        }

        static auto free_page(PhysAddr phys_addr, usize nr_pages) -> void {
            if (auto frame = phys_to_frame(phys_addr)) {
                auto page = role_cast<PfRole::Vmm>(frame);
                page->num_mappings -= 1;
                if (0 == page->num_mappings) {
                    free_frame(frame, 0);
                } 
            }
        }
    };

    struct X86MmuPageSynchroniser {
        typedef X86MmuPageSynchroniser  Self;
        X86MmuPageSynchroniser(PageTable::Mmu *mmu)
            : page_table_(mmu)
        {}

        auto sync(arch::paging::PendingInvalidationItems const &items) -> void;

        PageTable::Mmu *page_table_;
    };

} // namespace ours::mem

#endif // #ifndef OURS_ARCH_X86_PAGE_TABLE_HPP