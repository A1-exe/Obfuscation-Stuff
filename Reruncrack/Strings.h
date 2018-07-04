#pragma once

// Extract strings using self-referencing code xoring
// Please input the password:
__forceinline void extract_enter(char* arr) {
	__asm {
		lea eax, string
		add eax, after
		mov ch, 27 // length
		add ebx, esp
		jnz fakelabel
		mov edx, ebx
	fakelabel:
		mov edx, eax
		sub edx, string
		jz string
		jmp edx // edx = after, ecx = length, ebx = nothing, eax = str+aft
	string:
		_emit 0xd1 ; P
		_emit 0x81
		_emit 0xcb ; l
		_emit 0xa7
		_emit 0x1b ; e
		_emit 0x7e
		_emit 0x7b ; a
		_emit 0x1a
		_emit 0x06 ; s
		_emit 0x75
		_emit 0x7e ; e
		_emit 0x1b
		_emit 0xe1 ;
		_emit 0xc1
		_emit 0xae ; i
		_emit 0xc7
		_emit 0x55 ; n
		_emit 0x3b
		_emit 0x34 ; p
		_emit 0x44
		_emit 0x87 ; u
		_emit 0xf2
		_emit 0x61 ; t
		_emit 0x15
		_emit 0x75 ;
		_emit 0x55
		_emit 0xd4 ; t
		_emit 0xa0
		_emit 0x20 ; h
		_emit 0x48
		_emit 0x17 ; e
		_emit 0x72
		_emit 0xff ;
		_emit 0xdf
		_emit 0xf7 ; p
		_emit 0x87
		_emit 0x2f ; a
		_emit 0x4e
		_emit 0x7a ; s
		_emit 0x09
		_emit 0xf1 ; s
		_emit 0x82
		_emit 0x47 ; w
		_emit 0x30
		_emit 0x26 ; o
		_emit 0x49
		_emit 0x0e ; r
		_emit 0x7c
		_emit 0xd2 ; d
		_emit 0xb6
		_emit 0x64 ; :
		_emit 0x5e
		_emit 0xc2 ;
		_emit 0xe2
	after:
		sub eax, after // addy
		mov edx, arr
		mov cl, 0 // counter
	lblloop:
		mov bh, [eax]
		mov bl, [eax + 1]
		xor bh, bl
		mov byte ptr [edx], bh
		add eax, 2
		inc cl
		inc edx
		cmp ch, cl
		jnz lblloop
		mov byte ptr [edx], 0
	}
}

// Hmm, seems like your answer was %s!\n
__forceinline void extract_dialog(char* arr) {
	__asm {
		lea eax, string
		add eax, after
		mov ch, 36 // length
		add ebx, esp
		jnz fakelabel
		mov edx, ebx
	fakelabel:
		mov edx, eax
		sub edx, string
		jz string
		jmp edx // edx = after, ecx = length, ebx = nothing, eax = str+aft
	string:
		_emit 0xca ; H
		_emit 0x82
		_emit 0x78 ; m
		_emit 0x15
		_emit 0xed ; m
		_emit 0x80
		_emit 0xeb ; ,
		_emit 0xc7
		_emit 0xcc ;
		_emit 0xec
		_emit 0x26 ; s
		_emit 0x55
		_emit 0xb1 ; e
		_emit 0xd4
		_emit 0x1f ; e
		_emit 0x7a
		_emit 0xf4 ; m
		_emit 0x99
		_emit 0x3d ; s
		_emit 0x4e
		_emit 0x17 ;
		_emit 0x37
		_emit 0x5f ; l
		_emit 0x33
		_emit 0x36 ; i
		_emit 0x5f
		_emit 0x3e ; k
		_emit 0x55
		_emit 0xd5 ; e
		_emit 0xb0
		_emit 0xc6 ;
		_emit 0xe6
		_emit 0xf0 ; y
		_emit 0x89
		_emit 0x7c ; o
		_emit 0x13
		_emit 0x0b ; u
		_emit 0x7e
		_emit 0xf3 ; r
		_emit 0x81
		_emit 0xcd ;
		_emit 0xed
		_emit 0xe6 ; a
		_emit 0x87
		_emit 0xb5 ; n
		_emit 0xdb
		_emit 0xfb ; s
		_emit 0x88
		_emit 0xed ; w
		_emit 0x9a
		_emit 0xae ; e
		_emit 0xcb
		_emit 0xf7 ; r
		_emit 0x85
		_emit 0x3a ;
		_emit 0x1a
		_emit 0x2d ; w
		_emit 0x5a
		_emit 0x77 ; a
		_emit 0x16
		_emit 0x93 ; s
		_emit 0xe0
		_emit 0x04 ;
		_emit 0x24
		_emit 0xf5 ; %
		_emit 0xd0
		_emit 0x87 ; s
		_emit 0xf4
		_emit 0xd5 ; !
		_emit 0xf4
		_emit 0xb6 ; \n
		_emit 0xbc
	after:
		sub eax, after // addy
		mov edx, arr
		mov cl, 0 // counter
	lblloop:
		mov bh, [eax]
		mov bl, [eax + 1]
		xor bh, bl
		mov byte ptr [edx], bh
		add eax, 2
		inc cl
		inc edx
		cmp ch, cl
		jnz lblloop
		mov byte ptr [edx], 0
	}
}

// not actually right...
__forceinline void extract_failure(char* arr) {
	__asm {
		lea eax, string
		add eax, after
		mov ch, 21 // length
		add ebx, esp
		jnz fakelabel
		mov edx, ebx
	fakelabel:
		mov edx, eax
		sub edx, string
		jz string
		jmp edx // edx = after, ecx = length, ebx = nothing, eax = str+aft
	string:
		_emit 0x63 ; n
		_emit 0x0d
		_emit 0xb8 ; o
		_emit 0xd7
		_emit 0x13 ; t
		_emit 0x67
		_emit 0x98 ;
		_emit 0xb8
		_emit 0x9c ; a
		_emit 0xfd
		_emit 0x22 ; c
		_emit 0x41
		_emit 0xcc ; t
		_emit 0xb8
		_emit 0x06 ; u
		_emit 0x73
		_emit 0xcc ; a
		_emit 0xad
		_emit 0xae ; l
		_emit 0xc2
		_emit 0xda ; l
		_emit 0xb6
		_emit 0xe9 ; y
		_emit 0x90
		_emit 0xfd ;
		_emit 0xdd
		_emit 0xa0 ; r
		_emit 0xd2
		_emit 0x58 ; i
		_emit 0x31
		_emit 0xe0 ; g
		_emit 0x87
		_emit 0x0f ; h
		_emit 0x67
		_emit 0x8c ; t
		_emit 0xf8
		_emit 0xbd ; .
		_emit 0x93
		_emit 0xf1 ; .
		_emit 0xdf
		_emit 0xc5 ; .
		_emit 0xeb
	after:
		sub eax, after // addy
		mov edx, arr
		mov cl, 0 // counter
	lblloop:
		mov bh, [eax]
		mov bl, [eax + 1]
		xor bh, bl
		mov byte ptr [edx], bh
		add eax, 2
		inc cl
		inc edx
		cmp ch, cl
		jnz lblloop
		mov byte ptr [edx], 0
	}
}