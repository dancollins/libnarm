/*   Copyright 2015 Dan Collins & Tim Dawson
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */

/* Entry Point */
ENTRY(Reset_Handler)

/* Point this to the end of RAM */
_estack = 0x20001FFF;

/* This will create a linker error if the heap and stack wont fit in RAM */
_Min_Heap_Size = 0; /* required amount of heap  */
_Min_Stack_Size = 256; /* required amount of stack */

/* Give us a pointer to where we expect the end of the stack to be */
stack_end = _estack - _Min_Stack_Size;

/* Specify the address for flash and RAM */
MEMORY
{
	FLASH (rx) : ORIGIN = 0x8000000, LENGTH = 64K
	RAM (xrw) : ORIGIN = 0x20000000, LENGTH = 8K
}

/* Define output sections */
SECTIONS
{
  /* Make sure the first thing in flash is our vector table! */
  .isr_vector :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector))
    . = ALIGN(4);
  } >FLASH

  .text :
  {
    . = ALIGN(4);
    /* This is the actual application code */
    *(.text)
    *(.text*)
    /* XXX: These sections will be empty in ARM Cortex projects, but we need
     * them to satisfy the linker? */
    *(.glue_7)
    *(.glue_7t)
    /* These are for exceptions, which aren't used in C. However, it would
     * have data into a C++ project. */
    *(.eh_frame)

    KEEP (*(.init))
    KEEP (*(.fini))

    /* This just points to the end of the text section */
    . = ALIGN(4);
    _etext = .;
  } >FLASH

  /* This is where we store all the initialised variables. The startup script
   * will copy this data out into the RAM. This is for read-only data. */
  .rodata :
  {
    . = ALIGN(4);
    *(.rodata)
    *(.rodata*)
    . = ALIGN(4);
  } >FLASH

  /* XXX: This has something to do with loop unwinding? I couldn't find much
   * information, but everyone seems to have this. So do we! */
  .ARM.extab : { *(.ARM.extab* .gnu.linkonce.armextab.*) } >FLASH
  .ARM : {
    __exidx_start = .;
    *(.ARM.exidx*)
    __exidx_end = .;
  } >FLASH

  /* This points to the data section for the startup script */
  _sidata = LOADADDR(.data);

  /* This is where we store all the initialised variables. The startup script
   * will copy this data out into the RAM. */
  .data :
  {
    . = ALIGN(4);
    _sdata = .; /* Start of the data section */
    *(.data)
    *(.data*)

    . = ALIGN(4);
    _edata = .; /* End of the data section */
  } >RAM AT> FLASH


  /* This is where we store uninitialised data. It will get zeroed by the
   * start up script */
  . = ALIGN(4);
  .bss :
  {
    _sbss = .; /* Start of the uninitialised data section */
    __bss_start__ = _sbss;
    *(.bss)
    *(.bss*)
    *(COMMON)

    . = ALIGN(4);
    _ebss = .; /* End of the uninitialised data section */
    __bss_end__ = _ebss;
  } >RAM

  /* We use this to ensure that the user heap wont collide with the stack */
  ._user_heap_stack :
  {
    . = ALIGN(4);
    PROVIDE ( end = . );
    PROVIDE ( _end = . );
    . = . + _Min_Heap_Size;
    . = . + _Min_Stack_Size;
    . = ALIGN(4);
  } >RAM

  /* XXX: What? */
  /* Remove information from the standard libraries */
  /DISCARD/ :
  {
    libc.a ( * )
    libm.a ( * )
    libgcc.a ( * )
  }

  .ARM.attributes 0 : { *(.ARM.attributes) }
}
