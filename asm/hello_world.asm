PORTB = $6000
PORTA = $6001
DDRB  = $6002
DDRA  = $6003
PCR   = $600C ; Perripheral control register
IFR   = $600D ; Interrup flags register
IER   = $600E ; Interrup enable register

E   = %10000000
RWB = %01000000
RSB = %00100000

  .org $8000

reset:
  ldx #$ff
  txs
  cli            ; Clear interrupt dissable bit so that irq will be handled
  ;sei           ; Set interrupt dissable bit

  lda #%10000010 ; bit8: Set, bit2: CA1 enable
  sta IER
  lda #%00000000 ; bit2: CA1 control = 0, trigger on negative edge
  sta PCR


  lda #%11111111 ; Set all pins on port B to output
  sta DDRB
  lda #%11100000 ; Set top 3 pins on port A to output
  sta DDRA

  ; Enable the CA1 bit

; NOTE -- if you want to set to 4 bit mode, need to set 8 bit mode 3 times, then switch to 4 bit mode (see patreon)
  lda #%00111000 ; Set 8-bit mode; 2-line display; 5x8 font
  jsr lcd_instruction
  lda #%00001110 ; Display on; cursor on; blink off
  jsr lcd_instruction
  lda #%00000110 ; Increment and shift cursor; don't shift display
  jsr lcd_instruction
  lda #$00000001 ; Clear display
  jsr lcd_instruction

  ldx #0
print:
  lda message,x
  beq loop
  jsr print_char
  inx
  jmp print

loop:
  jmp loop

message: .asciiz "Hello, world!"

lcd_wait:
  pha             ; Push the lcd_instruction (in acc) on the stack
  lda #%00000000  ; Port B is input
  sta DDRB
lcdbusy:
  lda #RWB
  sta PORTA
  lda #(RWB | E)
  sta PORTA
  lda PORTB
  and #%10000000
  bne lcdbusy

  lda #RWB
  sta PORTA
  lda #%11111111  ; Port B is output
  sta DDRB
  pla             ; Pop the lcd_instruction off the stack (to acc)
  rts

lcd_instruction:
  jsr lcd_wait   ; Communicate with lcd and wait while receiving BUSY
  sta PORTB
  lda #0         ; Clear RS/RW/E bits
  sta PORTA
  lda #E         ; Set E bit to send instruction
  sta PORTA
  lda #0         ; Clear RS/RW/E bits
  sta PORTA
  rts

print_char:
  jsr lcd_wait
  sta PORTB
  lda #RSB        ; Set RS; Clear RW/E bits
  sta PORTA
  lda #(RSB | E)   ; Set E bit to send instruction (we are toggling the enable bit to 'send' the instruction sitting on PORTB)
  sta PORTA
  lda #RSB         ; Clear E bits
  sta PORTA
  rts

nmi:
irq:
; store context
  pha ; push a
  txa
  pha ; push x
  tya
  pha ; push y
  ;inc counter
  ;bne exit_irq
  ;inc counter + 1
exit_irq:
;debouncing loop
  ldx #$ff
  ldy #$4f
delay:
  dex
  bne delay
  dey
  bne delay

  bit PORTA ; read port-a, set flags, etc.

  ; restore context
  pla
  tay ;pull y
  pla
  tax ;pull x
  pla ;pull a
  rti



  .org $fffc
  .word nmi
  .word reset
  .word irq
