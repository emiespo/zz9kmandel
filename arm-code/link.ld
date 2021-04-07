SECTIONS
{
  . = 0x03000000;
  .binstart : {
    *(.binstart)
  }
  .text : {
    *(.text) 
  }
  .bss : {
	  *(.bss)
  }
  .data : {
	  *(.data)
  }
}

