INCLUDE "hardware.inc"

SECTION "Header", ROM0[$100]

	jp EntryPoint

	ds $150 - @, 0 ; Make room for the header

EntryPoint:
	ld b, $01
	ld c, $02
	ld d, $03
	ld e, $04
Loop:
	push bc
	push de
	pop bc
	pop de
	inc bc
	inc de
	jp Loop
