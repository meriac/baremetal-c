ENTRY(OnReset)

MEMORY
{
	FLASH (rx) : ORIGIN = (0x00000000), LENGTH = 0x80000
	RAM (rwx)  : ORIGIN = (0x20000000), LENGTH = 0x10000
}

SECTIONS
{
	.text :
	{
		/* interrupt vector table at the start of flash */
		KEEP(*(.vtor))

		/* rest of code & const data */
		*(.text*)
		*(.rodata*)

		. = ALIGN(4);
		__end_of_text__ = .;
	} >FLASH

	.data : 
	{
		__data_beg_src__ = __end_of_text__;
		__data_beg__ = .;
		*(.data*)
		. = ALIGN(4);
		__data_end__ = .;
	} >RAM AT>FLASH

	.bss (NOLOAD):
	{
		__bss_beg__ = .;
		*(.bss*)
		__bss_end__ = .;
		StackTop = ORIGIN(RAM) + LENGTH(RAM);
	} > RAM
}
