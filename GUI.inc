.code 
intro proc
		
		CALL GETPLAYERNAME
		CALL MENUGUI
		
		ret
intro endp
;=============================================================;

;=============================================================;
notificationdivider proc				;horizontal line to divide notification area from menu area
		
		mov bh,00
		mov AH,0CH			;draw pixel int condition
		mov al,09h          ;set the white colour
		mov dx,166         
		outl12:
			mov cx,04
			outl11:
				int 10h
				inc cx
				cmp cx,636
			jne outl11
			inc dx
			cmp dx,167
		jne outl12
		
		ret
notificationdivider endp
;=============================================================;

;=============================================================;
DRAWNOTIFICATION PROC					;draws notification for main menu
		
		call notificationdivider
		
		mov bh,0
		mov ah,2          				;Move Cursor to upper middle of screen
		mov dx,1506h      					
		int 10h           				
		
		mov ah, 9						;Display 'Hi'
		mov dx, offset hi				
		int 21h 			
		
		mov bh,0			
		mov ah,2          				;Move Cursor to upper middle of screen
		mov dx,1509h      		
		int 10h           		
		
		mov ah,9	      		
		mov dx,offset PLAYERNAME+2                  
		int 21h
		
		mov bh,0			
		mov ah,2          				;Move Cursor to upper middle of screen
		mov dx,1706h      				
		int 10h 
		
		mov ah, 9						
		mov dx, offset welcomemessage	
		int 21h 
		
		ret
DRAWNOTIFICATION ENDP
;=============================================================;

;=============================================================;
ABOUTGUI PROC							;draws about game screen
		
		MOV AX, 0EH
		INT 10H
		
		mov bh,0
		mov ah,2          				;Move Cursor to upper middle of screen
		mov dx,0300h      					
		int 10h           				
		
		mov ah, 9						;Display '->To see more about the game press F1$'
		mov dx, offset ABOUT				
		int 21h 		
		
		CALL NOTIFICATIONDIVIDER
		
		mov bh,0
		mov ah,2          				;Move Cursor to upper middle of screen
		mov dh,17h 
		MOV DL,24
		int 10h           				
		
		mov ah, 9						;Display '->To see more about the game press F1$'
		mov dx, offset ABOUTIN				
		int 21h
		
		RET
ABOUTGUI ENDP
;=============================================================;

;=============================================================;
showmouse proc							;shows mouse and defines horizontal range for it
		
		mov ax,1						;show mouse cursor
		int 33h
		
		mov ax,8h						;define horizontal range for mouse
		mov cx,40
		mov dx,200
		int 33h
		
		ret
showmouse endp
;=============================================================;

;=============================================================;
hidemouse proc						
		
		mov ax,2						;show mouse cursor
		int 33h
		
		ret
hidemouse endp
;=============================================================;

;=============================================================;
outro proc						;outro screen
		MOV AH,0				;CHANGE TO GRAPHICS MODE, THIS CLEARS THE SCREEN
		MOV AL,02H				;640x200 pixels and 80x25 text but only 16 colors, al=13h 320x200 and 256 colors
		INT 10H	
		
		mov ax,4c00h
		int 21h
		
		RET
outro ENDP
;=============================================================;

;=============================================================;
initializecounters proc					;initializes counters each time the user goes to main menu to prepare for game mode
		
		mov BLUECOUNT,0
		mov GREENCOUNT,0
		mov CYANCOUNT,0
		mov REDCOUNT,0
		mov PINKCOUNT,0
		mov BROWNCOUNT,0
		
		mov SQUARECOUNT,0
		mov TRIANGLECOUNT,0
		mov PARALLELOGRAMCOUNT,0
		mov ARROWCOUNT,0
		mov HEXAGONCOUNT,0
		mov CROSSCOUNT,0
		
		mov numcolortoclick,0
		mov numfiguretoclick,0
		mov colortoclick,0
		mov figuretoclick,0
		mov ah,startinglives
		mov lives,ah
		mov timerbuffer,0
		mov timerpos,479
		
		ret
		
initializecounters endp
;=============================================================;

;=============================================================;
TUTORIAL PROC							;tutorial to teach the user how to play
		
		MOV AX, 0EH						;graphics mode
		INT 10H
		
		call notificationdivider
		
		mov bh,0			
		mov ah,2          				;Move Cursor to upper middle of screen
		mov dh,06h
		mov dl,36
		int 10h 			
		
		mov ah, 9
		mov dx, offset TUTORIALSTR	
		int 21h 
		
		mov bh,0			
		mov ah,2          				;Move Cursor to upper middle of screen
		mov dx,0A10h      				
		int 10h 			
		
		mov ah, 9
		mov dx, offset TUTORIALSTR0	
		int 21h 
		
		mov ah,2          				;Move Cursor to lower middle of screen
		mov dx,0C10h      		
		int 10h           		

		mov ah, 9
		mov dx, offset TUTORIALSTR1	
		int 21h 
		
		mov ah,2          				;Move Cursor, to middle of screen
		mov dx,0E10h      		
		int 10h           		
		
		mov ah,9
		mov dx,offset TUTORIALSTR2                  
		int 21h
		
		mov ah,2          				;Move Cursor, to middle of screen
		mov dx,1715h      		
		int 10h           		
		
		mov ah,9
		mov dx,offset TUTORIALSTR3                  
		int 21h
		
		
		CALL SHOWMOUSE
		
		WAITFORRELEASE:
		mov ax,3
		int 33h
		test bx, 00000001b  ; perform bitwise AND with 00000001b
		jz WAITFORRELEASE 
		
		RET
TUTORIAL ENDP
;=============================================================;

;=============================================================;
MENUGUI PROC							;draws menu gui
		
		MOV AH,0				;CHANGE TO GRAPHICS MODE, THIS CLEARS THE SCREEN
		MOV AL,0EH				;640x200 pixels and 80x25 text but only 16 colors, al=13h 320x200 and 256 colors
		INT 10H	
		
		MOV SELECTION,0
		CALL DRAWSELECTIONMARK
		
		call initializecounters
		
		CALL DRAWNOTIFICATION
		
		mov bh,0			
		mov ah,2          				;Move Cursor to upper middle of screen
		mov dx,0A1Eh      				
		int 10h 			
		
		mov ah, 9						;Display '->To see more about the game press F1$'
		mov dx, offset mainscreen1	
		int 21h 
		
		mov ah,2          				;Move Cursor to lower middle of screen
		mov dx,0C1Eh      		
		int 10h           		

		mov ah, 9						;Display '->To play GO FIGURE!! press F2$'
		mov dx, offset mainscreen2	
		int 21h 
		
		mov ah,2          				;Move Cursor, to middle of screen
		mov dx,0E1Eh      		
		int 10h           		
		
		mov ah,9	      				;Display '->To exit the game press ESC$'
		mov dx,offset mainscreen3                  
		int 21h
		
		ret
		
MENUGUI ENDP
;=============================================================;

;=============================================================;
GAMEGUI PROC							;this runs every frame the update timer
		
		
		; call drawgrid					;uncomment this the see the grid that divides the screen
		
		call updatetimer
		
		ret
GAMEGUI ENDP
;=============================================================;

;=============================================================;
updatetimer	proc						;draws a black line that "decrements" the timer when timer buffer reaches timerbufferlimit
		
		inc timerbuffer
		MOV AX,TIMERBUFFERLIMIT
		cmp timerbuffer,AX
		jne notyet
		
		cmp timerpos,162
		je lost
		
		cmp timerpos,320
		jne notredyet
		
		call redtimer
		
		notredyet:

		
		mov bh,00
		mov AH,0CH						;draw pixel int condition
		mov al,0h          				;set black colour
		
		mov dx,14	
		mov cx,timerpos
		sh3bolaloop:
			int 10h
			inc dx
			cmp dx,19
		jnz sh3bolaloop
		
		dec timerpos
		mov timerbuffer,00h
		
		notyet:
		ret
		
		lost:
		call playerlost
		ret
updatetimer	endp
;=============================================================;

;=============================================================;
resettimer proc						;resets the timer back to full
		
		call drawtimer
		mov timerpos,479
		mov timerbuffer,0
		ret
		
resettimer endp
;=============================================================;

;=============================================================;
drawoutline proc					;draws outline of game and writes player name and lives
		
		call drawtimer
		
		mov ah,2                 		;move cursor at desired destination
		mov bh,0
		mov dl,1             
		mov dh,56             
		int 10h
		
		mov ah,09
		mov dx,offset ESCTOPAUSE 
		int 21h
		
		
		mov bh,00
		mov AH,0CH						;draw pixel int condition
		mov al,0Dh          			;set the white colour
		mov dx,9        
		mov cx,04
		outl111:
			int 10h
			inc cx
			cmp cx,636
		jne outl111
		
		mov ah,2                 		;move cursor at desired destination
		mov bh,0
		mov dx,1             
		int 10h
		
		mov ah,09
		mov dx,offset PLAYERNAME+2 
		int 21h
		
		mov ah,2                		;move cursor at desired destination
		mov bh,0
		mov dx,1h           	 	    ;a5er el screen
		add dl,PLAYERNAME+1	 			;add playername length
		int 10h
		
		mov ah,09
		mov dx,offset LIVESSTR			;write "'s lives" after playername
		int 21h
		
		mov ah,2                		;move cursor at desired destination
		mov bh,0
		mov dx,1h      		      		
		add dl,PLAYERNAME+1
		add dl,0Ah              		;add length of lives to cursor
		int 10h
		
		mov ah,02
		mov dl, lives					;then write the lives after adding all that
		int 21h
		
		ret
drawoutline endp
;=============================================================;

;=============================================================;
redtimer proc							;when the timer passes the middle point the color turns red

		MOV AH,0CH			;interrupt condition
		MOV BH,0
		MOV AL,04H			;draw red rectangle
		MOV DX,14
		red1:
			MOV CX,162
			
			red2:
				INT 10H
				INC CX
				CMP CX,320	
			JNZ red2
			INC DX
			CMP Dx,19
		JNZ red1
		
		ret
redtimer endp
;=============================================================;

;=============================================================;
drawtimer proc							;draws the timer rectangle and yellow outline of the timer

		MOV AL,0EH			;draw yellow rectangle
		MOV AH,0CH			;interrupt condition
		MOV BH,0
		MOV DX,12
		firstw:
			MOV CX,160
			
			firstl:
				INT 10H
				INC CX
				CMP CX,480	
			JNZ firstl
			INC DX
			CMP Dx,13
		JNZ firstw
		
		MOV DX,20
		secondw:
			MOV CX,160
			
			secondl:
				INT 10H
				INC CX
				CMP CX,480	
			JNZ secondl
			INC DX
			CMP Dx,21
		JNZ secondw	
		
		MOV DX,12
		thirdw:
			MOV CX,159
			
			thirdl:
				INT 10H
				INC CX
				CMP CX,160	
			JNZ thirdl
			INC DX
			CMP Dx,21
		JNZ thirdw	
		
		MOV DX,12
		fourthw:
			MOV CX,480
			
			fourthl:
				INT 10H
				INC CX
				CMP CX,481	
			JNZ fourthl
			INC DX
			CMP Dx,21
		JNZ fourthw
		
		MOV AL,0FH			;draw white rectangle
		MOV DX,14
		fourthwq:
			MOV CX,162
			
			fourthlq:
				INT 10H
				INC CX
				CMP CX,478	
			JNZ fourthlq
			INC DX
			CMP Dx,19
		JNZ fourthwq
		
		
		
		ret
drawtimer endp
;=============================================================;

;=============================================================;
drawgrid proc							;this doesn't actually get invoked but it shows the grid that divides the screen						
		
		mov bh,00
		mov AH,0CH			;draw pixel int condition
		mov al,09h          ;set the white colour
		mov dx,119        
		qoutl12:
			mov cx,04
			qoutl11:
				int 10h
				inc cx
				cmp cx,636
			jne qoutl11
			inc dx
			cmp dx,120
		jne qoutl12
		
		mov bh,00
		mov AH,0CH			;draw pixel int condition
		mov al,09h          ;set the white colour
		mov dx,39        
		weqoutl12:
			mov cx,04
			weqoutl11:
				int 10h
				inc cx
				cmp cx,636
			jne weqoutl11
			inc dx
			cmp dx,40
		jne weqoutl12
		
		mov bh,00
		mov AH,0CH			;draw pixel int condition
		mov al,09h          ;set the white colour
		mov dx,04        
		aqoutl12:
			mov cx,159
			aqoutl11:
				int 10h
				inc cx
				cmp cx,160
			jne aqoutl11
			inc dx
			cmp dx,198
		jne aqoutl12
		
		mov bh,00
		mov AH,0CH			;draw pixel int condition
		mov al,09h          ;set the white colour
		mov dx,04        
		sqoutl12:
			mov cx,319
			sqoutl11:
				int 10h
				inc cx
				cmp cx,320
			jne sqoutl11
			inc dx
			cmp dx,198
		jne sqoutl12
		
		mov bh,00
		mov AH,0CH			;draw pixel int condition
		mov al,09h          ;set the white colour
		mov dx,04        
		wsqoutl12:
			mov cx,479
			wsqoutl11:
				int 10h
				inc cx
				cmp cx,480
			jne wsqoutl11
			inc dx
			cmp dx,198
		jne wsqoutl12
	
		ret
drawgrid endp
;=============================================================;

;=============================================================;
DRAWFIGURES proc						;draws 8 random figures on the screen
		
		call setrandomseed
		call setrandomcolseed
		mov ypos,0
		;loop on all cells and fill them with random figures
		FILLY:
			mov xpos,0
			FILLX:
				; getting random color
				CMP GAMETYPE,1
				JE BYFIGURE						;if gametype is by figure no need to get rand color, all figures will be grey
				
				call randomcol					;assign random value to eax
		
				and eax,0FFH
		
				mov cl,6
				div cl							;now ah has the remainder of the division
				inc ah							;to exclude color black (00) add 1
				; getting random color
				mov color,ah					;put random color in drawing color
				; mov color,0FH					;incase of byfigure gametype set color is always grey
				
				call setcolorcounter 			;sets color counter with color in ah register
				
				jmp BYCOLOR
				
				BYFIGURE:
				mov color,07H					;incase of byfigure gametype set color is always grey
				
				BYCOLOR:
				
				CALL DRAWRANDOMFIGURE			;DRAWS A RANDOM FIGURE AT XPOS AND YPOS WITH COLOR, AT SETS COUNTERS
				
				INC XPOS
				CMP XPOS,3
			JBE FILLX
			
			INC YPOS
			CMP YPOS,1
		JBE FILLY
		
		mov figurecount,8
		
		ret
DRAWFIGURES endp
;=============================================================;

;=============================================================;
setcolorcounter proc					;checks color in ah and increases the counter of that color
		
		cmp ah,1
		jne notblue
		inc bluecount
		ret
		notblue:
		
		cmp ah,2
		jne notgreen
		inc greencount
		ret
		notgreen:
		
		cmp ah,3
		jne notcyan
		inc cyancount
		ret
		notcyan:
		
		cmp ah,4
		jne notred
		inc redcount
		ret
		notred:
		
		cmp ah,5
		jne notpink
		inc pinkcount
		ret
		notpink:
		
		inc browncount
		ret
		
setcolorcounter endp
;=============================================================;

;=============================================================;
DRAWRANDOMFIGURE proc					;draws one random figure in xpos and ypos
		
		call random						;assign random value to eax
		
		and eax,0FFH
		
		mov cl,6
		div cl
		
		INC AH							;to exclude color black (00) add 1

		CMP AH,1
		JNE NOT1
		SQUARE XPOS,YPOS,COLOR
		INC SQUARECOUNT
		;fill figures array
		mov bl,xpos						;now bl is xpos and bh is ypos
		mov bh,0
		cmp ypos,0
		je dontadd1
		add bx,4
		dontadd1:
		mov figures[bx],0
		;fill figures array
		RET
		NOT1:
		
		CMP AH,2
		JNE NOT2
		ARROW XPOS,YPOS,COLOR
		INC ARROWCOUNT
		;fill figures array
		mov bl,xpos						;now bl is xpos and bh is ypos
		mov bh,0
		cmp ypos,0
		je dontadd2
		add bx,4
		dontadd2:
		mov figures[bx],3
		;fill figures array
		RET
		NOT2:
		
		CMP AH,3
		JNE NOT3
		PARALLELOGRAM XPOS,YPOS,COLOR
		INC PARALLELOGRAMCOUNT
		;fill figures array
		mov bl,xpos						;now bl is xpos and bh is ypos
		mov bh,0
		cmp ypos,0
		je dontadd3
		add bx,4
		dontadd3:
		mov figures[bx],2
		;fill figures array
		RET
		NOT3:
	
		CMP AH,4
		JNE NOT4
		TRIANGLE XPOS,YPOS,COLOR
		INC TRIANGLECOUNT
		;fill figures array
		mov bl,xpos						;now bl is xpos and bh is ypos
		mov bh,0
		cmp ypos,0
		je dontadd4
		add bx,4
		dontadd4:
		mov figures[bx],1
		;fill figures array
		RET
		NOT4:
	
		CMP AH,5
		JNE NOT5
		HEXAGON XPOS,YPOS,COLOR
		INC HEXAGONCOUNT
		;fill figures array
		mov bl,xpos						;now bl is xpos and bh is ypos
		mov bh,0
		cmp ypos,0
		je dontadd5
		add bx,4
		dontadd5:
		mov figures[bx],4
		;fill figures array
		RET
		NOT5:
	
		
		CROSS XPOS,YPOS,COLOR
		INC CROSSCOUNT
		;fill figures array
		mov bl,xpos						;now bl is xpos and bh is ypos
		mov bh,0
		cmp ypos,0
		je dontadd6
		add bx,4
		dontadd6:
		mov figures[bx],5
		;fill figures array
		RET
		
		
DRAWRANDOMFIGURE endp
;=============================================================;

;=============================================================;
drawgamepausedtext proc				;writes game paused text when game is paused
		
		MOV AH,2          			;Move Cursor to upper middle of screen
		MOV DX,030AH      		
		INT 10H           		
		
		MOV AH, 9					;Display 'Please enter your name:'
		MOV DX, OFFSET PAUSED	
		INT 21H 
		
		RET
drawgamepausedtext endp

;=============================================================;

;=============================================================;
displaycolortopickmes proc				;displays which figure the user should pick
		
		mov ah,2          				;Move Cursor
		mov dx,0326H		
		int 10h 
		
		mov ah,02
		mov dl,0 						;write null five times to clear old color name
		mov cx,5
		clearold:
		int 21h
		loop clearold
		
		mov ah,2          				;Move Cursor
		mov dx,0326H		
		int 10h 
		
		mov ah,9	      				;Display '->To exit the game press ESC$'
		
		cmp colortoclick,1
		jne COLNOTblue
		mov dx,offset bluecolor 
		int 21h
		ret
		COLNOTblue:
		
		cmp colortoclick,2
		jne COLNOTgreen
		mov dx,offset greencolor 
		int 21h
		ret
		COLNOTgreen:
		
		cmp colortoclick,3
		jne COLNOTcyan
		mov dx,offset cyancolor 
		int 21h
		ret
		COLNOTcyan:
		
		cmp colortoclick,4
		jne COLNOTRED
		mov dx,offset REDcolor 
		int 21h
		ret
		COLNOTRED:
		
		cmp colortoclick,5
		jne COLNOTPINK
		mov dx,offset PINKcolor 
		int 21h
		ret
		COLNOTPINK:
		
		mov dx,offset browncolor 
		int 21h
		ret
		
displaycolortopickmes endp
;=============================================================;

;=============================================================;
displayfiguretopickmes proc				;displays which figure the user should pick

		mov ah,2          				;Move Cursor
		mov dx,0326H		
		int 10h 
		
		mov ah,02
		mov dl,0 						;write null five times to clear old figure name
		mov cx,14
		clearoldfig:
		int 21h
		loop clearoldfig
		
		mov ah,2          				;Move Cursor
		mov dx,0326H		
		int 10h 
		
		mov ah,9	      				;Display '->To exit the game press ESC$'
		
		cmp figuretoclick,0
		jne notSQUARE
		mov dx,offset SQUAREfig 
		int 21h
		ret
		notSQUARE:
		
		cmp figuretoclick,1
		jne notTRIANGLE
		mov dx,offset TRIANGLEfig 
		int 21h
		ret
		notTRIANGLE:
		
		cmp figuretoclick,2
		jne notPARALLELOGRAM
		mov dx,offset PARALLELOGRAMfig 
		int 21h
		ret
		notPARALLELOGRAM:
		
		cmp figuretoclick,3
		jne notARROW
		mov dx,offset ARROWfig 
		int 21h
		ret
		notARROW:
		
		cmp figuretoclick,4
		jne notHEXAGON
		mov dx,offset HEXAGONfig 
		int 21h
		ret
		notHEXAGON:
		
		mov dx,offset CROSSfig 
		int 21h
		ret
		
displayfiguretopickmes endp
;=============================================================;

;=============================================================;
CLEARGAMEPAUSEDTEXT PROC				;clears text when game is resumed from pause
		
		MOV AH,2          			;Move Cursor to upper middle of screen
		MOV DX,030AH      		
		INT 10H
		
		MOV CX,59
		mov ah,02
		mov dl, 0	;then write the score after adding all that
		ERASE:
		int 21h
		LOOP ERASE
		
		call writeclick					;pick all
		
		cmp gametype,1
		je dontwritecolor
		call displaycolortopickmes		;green
		dontwritecolor:
		
		cmp gametype,0
		je dontwritefigure
		call displayfiguretopickmes		;squares
		dontwritefigure:
		
		cmp gametype,1
		je cdontwritefigures
		call writefigures				;figures (displayed if not in figures' word wasn't displayed)
		cdontwritefigures:
		
		RET
CLEARGAMEPAUSEDTEXT ENDP