INCLUDE "hardware.inc"

SECTION "Header", ROM0[$100]

	jp EntryPoint

	ds $150 - @, 0 ; Make room for the header

EntryPoint:
	ld h, $03
	ld l, $00
	ld b, $04
	ld [hl], b
Loop:
	inc [hl]
	ld b, [hl]
	jp Loop
