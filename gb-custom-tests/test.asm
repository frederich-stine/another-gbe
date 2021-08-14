INCLUDE "hardware.inc"

SECTION "Header", ROM0[$100]

	jp EntryPoint

	ds $150 - @, 0 ; Make room for the header

EntryPoint:
	ld a, $FF
	ld b, $1
Loop:
	dec a
	inc b
	ld c, a
	ld d, c
	ld e, d
	ld h, e
	ld l, h
	jp Loop

