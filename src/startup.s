//     Copyright (C) 2023 AlanCui4080

//     This program is free software: you can redistribute it and/or modify
//     it under the terms of the GNU Affero General Public License as
//     published by the Free Software Foundation, either version 3 of the
//     License, or (at your option) any later version.

//     This program is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//     GNU Affero General Public License for more details.

//     You should have received a copy of the GNU Affero General Public License
//     along with this program.  If not, see <https://www.gnu.org/licenses/>.

/* SPDX-License-Identifier: AGPL-3.0-or-later */
.syntax unified
.cpu cortex-m0plus
.fpu softvfp
.thumb

.type _entry, %function
.section .text
.globl _entry
_entry:
    ldr r0, =_high_stack
    mov sp, r0

    bl _clava
loop:
    b loop

.section .vector_table
.word _high_stack
.word _entry
.word _entry
.word _entry
.fill 12,4,0
