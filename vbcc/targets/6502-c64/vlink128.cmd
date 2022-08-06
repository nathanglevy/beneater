STACKLEN   = 0x200;
STACKSTART = 0xc000 - 0x200;


MEMORY
{
 zero : org = 2 , len = 0x8d
 ram : org = 0x1C01, len=0xbfff-0x1c01-STACKLEN
 stack : org = STACKSTART, len=STACKLEN
}

SECTIONS
{
  .rdummy 0 : { *(.rdummy) }
  text : {*(text)} >ram
  .dtors : { *(.dtors) } > ram
  .ctors : { *(.ctors) } > ram
  rodata : {*(rodata)} >ram
  data: {*(data)} >ram
  init : {*(init)} >ram
  zpage (NOLOAD) : {*(zpage) *(zp1) *(zp2)} >zero
  bss (NOLOAD): {*(bss)} >ram

  __BB = ADDR(bss);
  __BE = ADDR(bss)+SIZEOF(bss);
  __SE = STACKSTART+STACKLEN;
  ___heap = ADDR(bss)+SIZEOF(bss);
  ___heapend = STACKSTART-1;
}
