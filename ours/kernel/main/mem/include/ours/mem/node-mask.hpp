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
#ifndef OURS_MEM_NODE_MASK_HPP
#define OURS_MEM_NODE_MASK_HPP 1

#include <ours/status.hpp>
#include <ours/mem/types.hpp>

#include <ustl/bitset.hpp>
#include <ustl/function/invoke.hpp>
#include <ustl/traits/is_invocable.hpp>

namespace ours::mem {
    struct NodeMask
        : public ustl::BitSet<MAX_NODE>
    {
        typedef ustl::BitSet<MAX_NODE>      Base;
        using Base::Base;

        template <typename F>
            requires ustl::traits::Invocable<F, NodeId>
        auto for_each(F &&functor) const -> void {
            auto const n = this->size();
            for (NodeId nid = 0; nid < n; ++nid) {
                if (this->test(nid)) {
                    ustl::function::invoke(functor, nid);
                }
            }
        }

        template <typename F>
            requires ustl::traits::Invocable<F, NodeId>
        auto for_each_if_noerr(F &&functor) const -> Status {
            auto const n = this->size();
            for (NodeId nid = 0; nid < n; ++nid) {
                if (this->test(nid)) {
                    auto status = ustl::function::invoke(functor, nid);
                    if (Status::Ok != status) {
                        return status;
                    }
                }
            }

            return Status::Ok;
        }

        template <typename F>
            requires ustl::traits::Invocable<F, NodeId>
        auto find(F &&matcher) const -> NodeId {
            auto const n = this->size();
            for (NodeId nid = 0; nid < n; ++nid) {
                if (this->test(nid)) {
                    continue;
                }

                if (matcher(nid)) {
                    return nid;
                }
            }
        }
    };

} // namespace ours::mem

#endif // #ifndef OURS_MEM_NODE_MASK_HPP