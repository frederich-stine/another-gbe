INCLUDE "hardware.inc"

SECTION "Header", ROM0[$100]

	jp EntryPoint

	ds $150 - @, 0 ; Make room for the header

EntryPoint:
	ld h, 20
	ld l, 0
	ld a, 0
Loop:
	add a, l
	inc l
	dec h
	jp nz, Loop
Done:
	jp Done
