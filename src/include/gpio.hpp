/**
 * @file gpio
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

#include <clava/io.hpp>
#include <clava/rcc.hpp>
#include <clava/reg.hpp>

namespace clava
{
    typedef struct {
        uintptr_t base;

        rw_reg<uint32_t>& clock_reg;
        uint32_t          clock_bit;
    } gpio_config_t;

    template <gpio_config_t _Cfg> class gpio : public io_group {
        clava_clock_sink(CLK,clock::SYSCLK,_Cfg.clock_reg,_Cfg.clock_bit);
    public:
        gpio()
            : io_group(_Cfg.base)
        {
        }
    };

    rw_reg<uint32_t> RCC_IOPENR(0x40021000 + 0x34);

    gpio<gpio_config_t{0x50000000,RCC_IOPENR,0}> GPIOA;
}
