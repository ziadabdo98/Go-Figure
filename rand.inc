.386

.DATA
align 4
random_32 label dword
dd 0ff7f29FCh  ; any seed except 0

.CODE
setrandomseed proc

		MOV AH,00H			
		INT 1AH	
		add random_32,EDX
		
		ret
setrandomseed endp

random proc

		push edx
		mov eax,[random_32]
		mov edx,0019660Dh
		mul edx
		add eax,3C6EF35Fh
		mov [random_32],eax
		pop edx
		
		ret
random endp