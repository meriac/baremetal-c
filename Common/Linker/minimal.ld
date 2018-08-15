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
	} >FLASH

	.bss (NOLOAD):
	{
		*(COMMON)
		StackTop = ORIGIN(RAM) + LENGTH(RAM);
	} > RAM
}
