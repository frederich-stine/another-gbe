INCLUDE "hardware.inc"

SECTION "Header", ROM0[$100]

	jp EntryPoint

	ds $150 - @, 0 ; Make room for the header

EntryPoint:
	ld a, $00
	ld b, $01
	ld c, $10
	bit 0, b
	bit 4, c
	res 0, b
	set 1, b
	res 4, c
	set 5, c
Done:
	jp Done
