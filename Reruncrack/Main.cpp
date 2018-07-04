#include <iostream>
#include <Windows.h>
#include "Strings.h"

// because both change the stack size
// may vary by compiler options
#ifdef _DEBUG
#define STACK_OFFSET 0x28
#else
#define STACK_OFFSET 0x20
#endif

bool relative_checks(char* out) {
	DWORD sum = 0;
	
	// embedded text
	out[0] -= 0x2f;
	out[1] -= 0x61;
	out[2] -= 0x4f;
	out[3] -= 0x5c;
	out[4] += 0x12;
	out[5] -= 0x37;
	out[6] -= 0x04;
	out[7] -= 0x10;
	out[8] -= 0x22;
	out[9] += 0x03;
	out[10] += 0x1a;
	out[11] -= 0x5a;
	out[12] -= 0x6e;
	out[13] += 0x11;
	out[14] -= 0xc5;
	out[15] -= 0x1f;
	out[16] -= 0x60;
	out[17] += 0x0a;
	out[18] += 0x38;
	out[19] += 0x73;
	// "hash" part
	out[20] -= 0x7a;
	out[21] += 0x84;
	out[22] += 0xac;
	out[23] -= 0xf2;
	out[24] -= 0x06;
	out[25] -= 0x58;
	out[26] += 0x68;
	out[27] -= 0xbe;
	out[28] += 0xc2;
	out[29] += 0x0c;
	out[30] -= 0x54;

	for (int i = 0; i < 0x1F; i++) {
		sum = (out[i] + sum) ^ i;
	}

	return sum == 0x1DC; // meme
}

bool flow_obfus(char* out, int key) {
	DWORD oldprotect = 0;
	PBYTE start = 0;
	PBYTE end = 0;
	BYTE inst[0xFF];
	bool flag = false;

	__asm {
		lea eax, __start
		mov start, eax
		lea eax, __end
		mov end, eax
		jmp eax
	}

__start:
	/* // real block
	__asm {
		mov ebx, 0 // count
		mov ecx, [esp + 4] // out
		mov edx, [esp + 8] // key
	lblloop:
		mov al, byte ptr [ecx + ebx]
		cmp al, 0
		jz loopbreak
		imul eax, key
		mov byte ptr [ecx + ebx], al
		inc ebx
		cmp ebx, 0x1F
		jnz lblloop
	loopbreak:
		mov ebx, [esp + 12] // func
		push ecx
		call ebx
		add esp, 4
		ret
	}
	*/
	__asm { // function code
		_emit 0xbb
		_emit 0x02
		_emit 0x04
		_emit 0x06
		_emit 0x08
		_emit 0x81
		_emit 0x40
		_emit 0x2a
		_emit 0x14
		_emit 0x99
		_emit 0x40
		_emit 0x32
		_emit 0x10
		_emit 0x90
		_emit 0x18
		_emit 0x07
		_emit 0x1c
		_emit 0x22
		_emit 0x50
		_emit 0x2b
		_emit 0x27
		_emit 0x85
		_emit 0x69
		_emit 0x22
		_emit 0xb8
		_emit 0x36
		_emit 0x2d
		_emit 0x75
		_emit 0xbb
		_emit 0xc1
		_emit 0x23
		_emit 0x4b
		_emit 0xac
		_emit 0xc9
		_emit 0x18
		_emit 0x62
		_emit 0x44
		_emit 0x1b
		_emit 0xb3
		_emit 0x9d
		_emit 0xd3
		_emit 0x96
		_emit 0x50
		_emit 0x95
	}
__end:

	// decrypt the new function into the stack
	for (int idx = 0; (start + idx) < end; idx++) {
		inst[idx] = start[idx];
		inst[idx] ^= ((idx * 2) & 0xFF);
	}

	VirtualProtect(inst, sizeof(inst), PAGE_EXECUTE_READWRITE, &oldprotect);
	flag = ((bool(*)(char*, int, void*))&inst)(out, key, relative_checks); // call new function
	VirtualProtect(inst, sizeof(inst), oldprotect, &oldprotect);

	for (int idx = 0; idx < 0x1F; idx++) { // "overflows" into the second array
		out[idx] ^= out[idx + STACK_OFFSET];
	}

	return flag;
}

// reru loves 2d girls
int main() {
	char output[0x28];
	char outtoo[0x1F]; // lesser addy
	bool success = false;
	DWORD sum = 0;

	ZeroMemory(output, sizeof(output));
	ZeroMemory(outtoo, sizeof(outtoo));
	extract_enter(output);
	printf(output);
	std::cin.getline(outtoo, sizeof(outtoo));
	sum = outtoo[2] ^ outtoo[1] * outtoo[5] * outtoo[0] / (outtoo[6] | 1); // soft "hash"

	if (!memcmp(outtoo, "reru", 4) && (sum == 0x2BB0)) {
		success = flow_obfus(outtoo, sum); // returns success flag + edits the output if so
	}

	if (!success) {
		extract_failure(outtoo);
	}

	extract_dialog(output);
	printf(output, outtoo);
}