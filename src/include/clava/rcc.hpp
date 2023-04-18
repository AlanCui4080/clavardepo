/**
 * @file rcc.hpp
 *
 * @attention
 * <h2> Copyright (C) 2023 clavardepo authors </h2>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General License for more details.
 *
 * You should have received a copy of the GNU Affero General License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

/* SPDX-License-Identifier: AGPL-3.0-or-later */

#pragma once

#include <type_traits>
#include <cstdint>

#include <clava/utility.hpp>
#include <clava/reg.hpp>

namespace clava
{
    namespace config
    {
    }
    namespace clock
    {

        template <class _Clk> struct converter : public _Clk {
        };
        template <class _Clk> struct source : public _Clk {
        };
        template <class _Clk> struct sink : public _Clk {
        };

        struct SYSCLK {};

        template <class _Reg, class _From>
        class converter_helper : converter<_From> {
        private:
            using reg_type = decltype(_Reg)::value_type;
            _Reg&    reg;
            reg_type msk;
            reg_type low_bit;
            reg_type high_bit;
            index2_t idx;

            reg_type before;

        public:
            converter_helper(index2_t idx, _Reg& cfg, reg_type mask,
                             reg_type highest_bit, reg_type lowest_bit)
                : reg(cfg)
                , idx(idx)
                , msk(mask)
                , high_bit(highest_bit)
                , low_bit(lowest_bit)
            {
                this->before      = this->reg.read();
                reg_type to_write = this->idx >= 0 ?
                                        (((this->idx) << this->low_bit) |
                                         0b1 << this->high_bit) :
                                        (0);
                this->reg.cover(this->msk, to_write);
            }
            ~converter_helper()
            {
                this->reg.cover(this->msk, this->before);
            }
        };

        template <class _Reg, class _Clk> class sink_helper : sink<_Clk> {
        private:
            using reg_type = decltype(_Reg)::value_type;
            _Reg&    reg;
            reg_type bit;

        public:
            sink_helper(_Reg& cfg, reg_type bit_pos)
                : reg(cfg)
                , bit(bit_pos)
            {
                reg_type to_write = 0b1 << this->bit;
                this->reg.cover(to_write, to_write);
            };
            ~sink_helper()
            {
                reg_type to_write = 0b1 << this->bit;
                this->reg.cover(to_write, 0);
            };
        };
#define clava_clock_converter(name, from, to, reg, mask, highest_bit, \
                              lowest_bit)                             \
    class name : public converter_helper<decltype(reg), from> {};     \
    struct to : source<name> {}
#define clava_clock_sink(name, clk, reg, bit) \
    class name : public sink_helper<decltype(reg), clk>
    }
}
