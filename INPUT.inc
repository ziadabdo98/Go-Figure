.code 
;=============================================================;
GETPLAYERNAME PROC					;gets player name

		MOV AX, 0EH
		INT 10H
		
		CALL CLEARINPUTBUFFER
		
		MOV AH,2          			;Move Cursor to upper middle of screen
		MOV DX,0A1FH      		
		INT 10H           		
		
		MOV AH, 9					;Display 'Please enter your name:'
		MOV DX, OFFSET ENTERNAME	
		INT 21H 
		
		MOV AH,2          			;Move Cursor to lower middle of screen
		MOV DX,0E1DH      		
		INT 10H           		

		MOV AH, 9					;Display 'press enter to continue'
		MOV DX, OFFSET PRESSENTER	
		INT 21H 
		
		MOV AH,2          			;Move Cursor, to middle of screen
		MOV DX,0C1FH      		
		INT 10H 
		emptyname:
		
		MOV AH,0AH       			;Read name from keyboard
		MOV DX,OFFSET PLAYERNAME                  
		INT 21H
		
		cmp playername+1,0
		je emptyname
		
		RET	
GETPLAYERNAME ENDP
;=============================================================;

;=============================================================;
CLEARINPUTBUFFER PROC
		
		MOV AL,0
		MOV AH,0CH
		INT 21H 			;this clears the buffer, then moves al to ah and executes the int 21h again only if al=1,6,7,8,0AH
		
		RET
CLEARINPUTBUFFER ENDP
;=============================================================;
ABOUTINPUT PROC					;handles input for about mode
		
		
		
		MOV AH,0				;get key input
		INT 16H
		MOV MODE,2H
		
		RET
ABOUTINPUT ENDP
;=============================================================;
MENUINPUT PROC					;handles input for main menu
		
		GETMODE:
		
		MOV AH,0				;get key input
		INT 16H
		
		CMP AH,48H						;cmp with Up arrow
		JZ UPARROW		
		
		CMP AH,50H						;cmp with Dn arrow
		JZ DOWNARROW		
		
		CMP AH,01H						;cmp with esc
		JZ ESCAPE		
		
		CMP AH,1CH						;cmp with ENTER
		JZ ENTER
		
		JMP GETMODE

		UPARROW:
		CALL UPSELECTION				;Up Arrow Pressed
		JMP GETMODE
		
		DOWNARROW:
		CALL DOWNSELECTION				;Down Arrow Pressed
		JMP GETMODE
		
		ENTER:							;Enter key is pressed
		CMP SELECTION,2
		JE ESCAPE
		; NOTEXIT:
		cmp selection,1H
		jne notgame
		
		;ask for game levels here, then check if want to quit to main menu
		
		call getgametype
		cmp mode,2
		je returrr
		
		call gettimerspeed
		cmp mode,2
		je returrr
	
		CALL TUTORIAL
		
		call initializegame
		
		call newshape
		
		call showmouse
		
		notgame:
		MOV AL,SELECTION
		MOV MODE,AL
		
		returrr:
		RET
		
		ESCAPE:
		CALL OUTRO
		
MENUINPUT ENDP
;=============================================================;
initializegame proc						;intilializes game

		MOV AX, 0EH						;graphics mode
		INT 10H
		; call drawgrid
		call drawoutline
		CALL DRAWFIGURES
		
		ret
initializegame endp
;=============================================================;

;=============================================================;
newshape proc							;gets a new shape when the user clicks on a correct shape
		
		call writeclick					;pick all
		
		cmp gametype,1
		je nocolortoclick
		call getcolortoclick
		call displaycolortopickmes		;green
		nocolortoclick:
		
		cmp gametype,0
		je nofiguretoclick
		call getfiguretoclick
		call displayfiguretopickmes		;squares
		nofiguretoclick:
		
		cmp gametype,1
		je dontwritefigures
		call writefigures				;figures (displayed if not in figures' word wasn't displayed)
		dontwritefigures:
		
		ret
newshape endp
;=============================================================;

;=============================================================;
writeclick proc							;writes the string "click on a"
		
		mov ah,2          		;Move Cursor
		mov dx,031BH		
		int 10h 
		
		mov ah,9	      				
		mov dx,offset CLICKMESSAGE                  
		int 21h
		
		ret
writeclick endp
;=============================================================;

;=============================================================;
writefigures proc						;writes the string of the figure
		
		mov ah,2          		;Move Cursor
		mov dx,032CH
		int 10h 
		
		mov ah,9	      				
		mov dx,offset FIGURESSTR                  
		int 21h
		
		ret
writefigures endp
;=============================================================;

;=============================================================;
getfiguretoclick proc					;gets a random color and sets how many shapes have that color
		
		chooseanotherfigure:
		call random
		
		and eax,0FFH

		mov cl,6
		div cl							;now ah has the remainder of the division
		mov al,ah
		mov ah,00h
		mov bx,ax
		mov dl,SQUAREcount+bx
		cmp dl,0
		je chooseanotherfigure
		
		mov figuretoclick,bl
		mov numfiguretoclick,dl
		
		ret
getfiguretoclick	endp
;=============================================================;

;=============================================================;
getcolortoclick proc					;gets a random figure and sets how many shapes have that figure
		
		chooseanothercolor:
		call random
		
		and eax,0FFH

		mov cl,6
		div cl							;now ah has the remainder of the division
		mov al,ah
		mov ah,00h
		mov bx,ax
		mov dl,bluecount+bx
		cmp dl,0
		je chooseanothercolor
		
		mov colortoclick,bl
		inc colortoclick
		mov numcolortoclick,dl
		
		ret
getcolortoclick	endp
;=============================================================;

;=============================================================;
getgametype proc						;asks the user for the gametype
		
		
		MOV AX, 0EH						;graphics mode
		INT 10H
		
		call notificationdivider
		
		mov bh,0			
		mov ah,2          				;Move Cursor to upper middle of screen
		mov dx,0A1Eh      				
		int 10h 			
		
		mov ah, 9						;Display '->To see more about the game press F1$'
		mov dx, offset GAMETYPESTR	
		int 21h 
		
		mov ah,2          				;Move Cursor to lower middle of screen
		mov dx,0C1Eh      		
		int 10h           		

		mov ah, 9						;Display '->To play GO FIGURE!! press F2$'
		mov dx, offset TYPECOLOR	
		int 21h 
		
		mov ah,2          				;Move Cursor, to middle of screen
		mov dx,0E1Eh      		
		int 10h           		
		
		mov ah,9	      				;Display '->To exit the game press ESC$'
		mov dx,offset TYPEFIGURE                  
		int 21h
		
		mov ah,2          				;Move Cursor, to middle of screen
		mov dx,170Fh      		
		int 10h           		
		
		mov ah,9	      				;Display '->To exit the game press ESC$'
		mov dx,offset instructions                  
		int 21h
		
		gettype:
		
		MOV AH,0						;get key input
		INT 16H
		
		CMP Al,31H						;cmp with 1
		JZ typclr		
		
		CMP Al,32H						;cmp with 2
		JZ typfig		
		
		
		CMP Ah,01H						;cmp with esc
		JZ escapetomenu
		
		jmp gettype
		
		typclr:
		mov gametype,0
		mov mode,1
		ret
		
		typfig:
		mov gametype,1
		mov mode,1
		ret
		
		escapetomenu:
		mov mode,2
		ret
		
		ret
		
getgametype endp
;=============================================================;

;=============================================================;
gettimerspeed proc						;asks user for timer speed
		
		MOV AX, 0EH						;graphics mode
		INT 10H
		
		call notificationdivider
		
		mov bh,0			
		mov ah,2          				;Move Cursor to upper middle of screen
		mov dx,0A1Eh      				
		int 10h 			
		
		mov ah, 9						;Display '->To see more about the game press F1$'
		mov dx, offset TIMIERSTR0	
		int 21h 
		
		mov ah,2          				;Move Cursor to lower middle of screen
		mov dx,0C01h      		
		int 10h           		

		mov ah, 9						;Display '->To play GO FIGURE!! press F2$'
		mov dx, offset TIMIERSTR1	
		int 21h 
		
		mov ah,2          				;Move Cursor, to middle of screen
		mov dx,170Eh      		
		int 10h           		
		
		mov ah,9	      				;Display '->To exit the game press ESC$'
		mov dx,offset TIMIERSTR2                  
		int 21h
		
		GETTIMER:
		
		MOV AH,0						;get key input
		INT 16H
		
		CMP Al,31H						;cmp with 1
		JZ SLOW		
		
		CMP Al,32H						;cmp with 2
		JZ MED		
		
		CMP Al,33H						;cmp with 3
		JZ FAST
		
		CMP Al,34H						;cmp with 4
		JZ INSANE
		
		CMP Ah,01H						;cmp with esc
		JZ escapetomenut
		
		jmp GETTIMER
		
		SLOW:
		mov TIMERBUFFERLIMIT,3FFh
		mov mode,1
		ret
		
		MED:
		mov TIMERBUFFERLIMIT,1FFh
		mov mode,1
		ret
		
		FAST:
		mov TIMERBUFFERLIMIT,350
		mov mode,1
		ret
		
		INSANE:
		mov TIMERBUFFERLIMIT,0FFh
		mov mode,1
		ret
		
		escapetomenut:
		mov mode,2
		ret
		
		ret
		
gettimerspeed endp
;=============================================================;

;=============================================================;
UPSELECTION PROC						;moves the selectionmark up and changes selection accordingly

		cmp selection,0
		je RETUP
		
		CMP selection,1
		JE UPTOMODE0
		
		CMP selection,2
		JE UPTOMODE1

		UPTOMODE0:
		MOV SELECTION,0
		CALL DRAWSELECTIONMARK 
		RET
		
		UPTOMODE1:
		MOV SELECTION,1
		CALL DRAWSELECTIONMARK 
		RET
		
		RETUP:
		RET
		
UPSELECTION ENDP
;=============================================================;

;=============================================================;
DOWNSELECTION PROC						;moves the selectionmark down and changes selection accordingly
		
		
		cmp selection,0
		je DNTOMODE1
		
		CMP selection,1
		JE DNTOMODE2
		
		CMP selection,2
		JE RETDN

		DNTOMODE1:
		MOV SELECTION,1
		CALL DRAWSELECTIONMARK 
		RET
		
		DNTOMODE2:
		MOV SELECTION,2
		CALL DRAWSELECTIONMARK
		RET
		
		RETDN:
		RET
		
DOWNSELECTION ENDP
;=============================================================;

;=============================================================;
DRAWSELECTIONMARK PROC					;Clears the area where the selection marks should be and redraws it based on current selection
		
		mov bh,0
		mov ah,2          		;Move Cursor to upper middle of screen
		mov dx,0A1Ch      		
		int 10h           		
		
		mov ah, 2				;Clear one character
		mov dL, 0	
		int 21h 
		
		mov ah,2          		;Move Cursor to lower middle of screen
		mov dx,0C1Ch      		
		int 10h           		

		mov ah, 2				;Clear one character
		mov dL, 0	
		int 21h 
		
		mov ah,2          		;Move Cursor, to middle of screen
		mov dx,0E1Ch      		
		int 10h 
		
		mov ah, 2				;Clear one character
		mov dL, 0	
		int 21h 
		
		CMP SELECTION,0			;cmp with selection to see where to set the cursor of the selectionmark
		JNE SELNOT0
		
		mov bh,0
		mov ah,2          		;Move Cursor to upper middle of screen
		mov dx,0A1Ch      		
		int 10h           		
		JMP DRAWMARK
		
		SELNOT0:
		
		CMP SELECTION,1
		JNE SELNOT1
		
		mov bh,0
		mov ah,2          		;Move Cursor to lower middle of screen
		mov dx,0C1Ch      		
		int 10h           		
		JMP DRAWMARK

		SELNOT1:
		
		mov bh,0
		mov ah,2          		;Move Cursor, to middle of screen
		mov dx,0E1Ch      		
		int 10h           		
		
		DRAWMARK:
		mov ah,9				;int condition			
		mov bh,0				;page number
		mov al,10H				;arrow sign  			
		mov cx,1H				;1 time
		mov bl,004h				;red on black background
		int 10h 
		
		
		RET
DRAWSELECTIONMARK ENDP
;=============================================================;

;=============================================================;
gameinput proc							;handles input for game
		
		call checkkeyboard
		
		mov ax,5
		mov bx,0
		int 33h
		
		cmp bx,0
		je reet
		
		mov ax,3
		int 33h
		test bx,1						;first bit in bx is for left mouse click
		jz reet
		
		mov ax,5
		mov bx,0
		int 33h
		
		cmp bx,0
		ja reet
		
		mov x,cx
		mov y,dx
		
		
		
		call getpixelcolor				;puts pixel color in clickedcolor
		call getclickedfigure			;puts figure in clickedfigure
		
		cmp y,40						;this is to make sure user didn't click on text
		jbe reet
		
		
		cmp clickedcolor,00				;if user clicked on black pixel in play area
		je reet
	
		
		cmp GAMETYPE,0
		jne notclr
		call colormodeinput
		notclr:
		
		cmp GAMETYPE,1
		jne notfigure
		call figuremodeinput
		notfigure:
		
		reet:
		
		ret
gameinput endp
;=============================================================;

;=============================================================;
getclickedfigure proc					;sets clickedfigureindex from the mouse click
		
		cmp x,160
		jae notcfirstquad
		cmp y,120
		jae atffig4
		;here at fig 0
		mov clickedfigureindex,0
		jmp fdone
		atffig4:
		;here at fig 4
		mov clickedfigureindex,4
		jmp fdone
		notcfirstquad:
		

		cmp x,320
		jae notcsecondquad
		cmp y,120
		jae atffig5
		;here ar fig 1
		mov clickedfigureindex,1
		jmp fdone
		atffig5:
		;here at fig 5
		mov clickedfigureindex,5
		jmp fdone
		notcsecondquad:
		
		cmp X,480
		jae notcthirdquad
		cmp Y,120
		jae atffig6
		;here ar fig 2
		mov clickedfigureindex,2
		jmp fdone
		atffig6:
		;here at fig 6
		mov clickedfigureindex,6
		jmp fdone
		notcthirdquad:
		;if not at any of these quads then it is at last quads
		
		cmp y,120
		jae atffig7
		;here ar fig 3
		mov clickedfigureindex,3
		jmp fdone
		atffig7:
		;here at fig 7
		mov clickedfigureindex,7
		jmp fdone
		
		fdone:
		xor bh,bh
		mov bl,clickedfigureindex
		mov ah,figures[bx]
		mov clickedfigure,ah
		ret
		
getclickedfigure endp
;=============================================================;

;=============================================================;
declives proc							;decrements number of lives of player
		
		dec lives
		
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
declives endp
;=============================================================;

;=============================================================;
playerwon proc							;when the player wins

		MOV AH,0						;CHANGE TO GRAPHICS MODE, THIS CLEARS THE SCREEN
		MOV AL,0EH						;640x200 pixels and 80x25 text but only 16 colors, al=13h 320x200 and 256 colors
		INT 10H	
		
		call notificationdivider
		
		mov bh,0
		mov ah,2          				;Move Cursor to upper middle of screen
		mov dx,0A1Ah      		
		int 10h   
		
		mov ah, 9						;Display 'SORRY'
		mov dx, offset WONMESSAGE0	
		int 21h 
		
		mov bh,0
		mov ah,2          				;Move Cursor to upper middle of screen
		mov dx,0A1Ah
		add dl,16
		int 10h 
		
		mov ah, 9						;Display PLAYERNAME
		mov dx, offset PLAYERNAME+2	
		int 21h 
		
		mov bh,0
		mov ah,2          			;Move Cursor to upper middle of screen
		mov dx,0C1Ah      		
		int 10h           		
		
		mov ah, 9					;Display 'Press ESC to exit the game'
		mov dx, offset WONMESSAGE1	
		int 21h 
		
		mov bh,0
		mov ah,2          			;Move Cursor to upper middle of screen
		mov dx,0D1Ah      		
		int 10h           		
		
		mov ah, 9					;Display 'Press SPACE to go to main menu'
		mov dx, offset WONMESSAGE2	
		int 21h 
		
		
		mov bh,0
		mov ah,2          			;Move Cursor to upper middle of screen
		mov dh,17h  
		mov dl,13
		int 10h           		
		
		mov ah, 9					;Display 'Press SPACE to go to main menu'
		mov dx, offset LOSTMESSAGE3	
		int 21h 
		
		GAMEOVERWON:
		
		mov ah,0			;get key input
		int 16h
		
		cmp ah,39h			;cmp with space
		jz WONSPACE
	
		cmp ah,01h			;cmp with esc
		jz WONQUIT
		
		jmp GAMEOVERWON
		
		WONSPACE:
		MOV MODE,2H
		ret
		
		WONQUIT:
		CALL OUTRO
		RET
		
playerwon endp
;=============================================================;

;=============================================================;
playerlost proc							;when the player loses
		
		MOV AH,0						;CHANGE TO GRAPHICS MODE, THIS CLEARS THE SCREEN
		MOV AL,0EH						;640x200 pixels and 80x25 text but only 16 colors, al=13h 320x200 and 256 colors
		INT 10H	
		
		call notificationdivider
		
		mov bh,0
		mov ah,2          				;Move Cursor to upper middle of screen
		mov dx,0A1Ah      		
		int 10h   
		
		mov ah, 9						;Display 'SORRY'
		mov dx, offset LOSTMESSAGE0	
		int 21h 
		
		mov bh,0
		mov ah,2          				;Move Cursor to upper middle of screen
		mov dx,0A1Ah
		add dl,6
		int 10h 
		
		mov ah, 9						;Display PLAYERNAME
		mov dx, offset PLAYERNAME+2	
		int 21h 
		
		mov bh,0
		mov ah,2          			;Move Cursor to upper middle of screen
		mov dx,0C1Ah      		
		int 10h           		
		
		mov ah, 9					;Display 'Press ESC to exit the game'
		mov dx, offset LOSTMESSAGE1	
		int 21h 
		
		mov bh,0
		mov ah,2          			;Move Cursor to upper middle of screen
		mov dx,0D1Ah      		
		int 10h           		
		
		mov ah, 9					;Display 'Press SPACE to go to main menu'
		mov dx, offset LOSTMESSAGE2	
		int 21h 
		
		
		mov bh,0
		mov ah,2          			;Move Cursor to upper middle of screen
		mov dh,17h  
		mov dl,13
		int 10h           		
		
		mov ah, 9					;Display 'Press SPACE to go to main menu'
		mov dx, offset LOSTMESSAGE3	
		int 21h 
		
		GAMEOVER:
		
		mov ah,0			;get key input
		int 16h
		
		cmp ah,39h			;cmp with space
		jz lostSPACE
	
		cmp ah,01h			;cmp with esc
		jz lostQUIT
		
		jmp GAMEOVER
		
		lostSPACE:
		MOV MODE,2H
		call menugui
		ret
		
		lostQUIT:
		CALL OUTRO
		RET
		
playerlost endp
;=============================================================;

;=============================================================;
colormodeinput proc						;handles input in color gametype
		
		mov ah,colortoclick
		cmp clickedcolor,ah
		jne wrongcolor
		
		cmp x,160
		jae notfirstquad
		cmp y,120
		jae atfig4
		;here at fig 0
		mov XPOS,0
		mov YPOS,0
		mov color,0
		call hidemouse
		DELETE XPOS,YPOS,color			;draw black DELETE over the shape to hide it
		call showmouse
		call deccolorcounter			;dec the counter of the clicked color
		dec figurecount
		cmp figurecount,0
		je colorgamewon
		mov figures,?					;remove figures from figures array
		call newshape
		call resettimer
		ret
		
		atfig4:
		;here at fig 4
		mov XPOS,0
		mov YPOS,1
		mov color,0
		call hidemouse
		DELETE XPOS,YPOS,color			;draw black DELETE over the shape to hide it
		call showmouse
		call deccolorcounter			;dec the counter of the clicked color
		dec figurecount
		cmp figurecount,0
		je colorgamewon
		mov figures[4],?
		call newshape
		call resettimer
		ret
		notfirstquad:
		

		cmp x,320
		jae notsecondquad
		cmp y,120
		jae atfig5
		;here ar fig 1
		mov XPOS,1
		mov YPOS,0
		mov color,0
		call hidemouse
		DELETE XPOS,YPOS,color			;draw black DELETE over the shape to hide it
		call showmouse
		call deccolorcounter			;dec the counter of the clicked color
		dec figurecount
		cmp figurecount,0
		je colorgamewon
		mov figures[1],?
		call newshape
		call resettimer
		ret
		atfig5:
		;here at fig 5
		mov XPOS,1
		mov YPOS,1
		mov color,0
		call hidemouse
		DELETE XPOS,YPOS,color			;draw black DELETE over the shape to hide it
		call showmouse
		call deccolorcounter			;dec the counter of the clicked color
		dec figurecount
		cmp figurecount,0
		je colorgamewon
		mov figures[5],?
		call newshape
		call resettimer
		ret
		notsecondquad:
		
		cmp X,480
		jae notthirdquad
		cmp Y,120
		jae atfig6
		;here ar fig 2
		mov XPOS,2
		mov YPOS,0
		mov color,0
		call hidemouse
		DELETE XPOS,YPOS,color			;draw black DELETE over the shape to hide it
		call showmouse
		call deccolorcounter			;dec the counter of the clicked color
		dec figurecount
		cmp figurecount,0
		je colorgamewon
		mov figures[2],?
		call newshape
		call resettimer
		ret
		atfig6:
		;here at fig 6
		mov XPOS,2
		mov YPOS,1
		mov color,0
		call hidemouse
		DELETE XPOS,YPOS,color			;draw black DELETE over the shape to hide it
		call showmouse
		call deccolorcounter			;dec the counter of the clicked color
		dec figurecount
		cmp figurecount,0
		je colorgamewon
		mov figures[6],?
		call newshape
		call resettimer
		ret
		notthirdquad:
		;if not at any of these quads then it is at last quads
		
		cmp y,120
		jae atfig7
		;here ar fig 3
		mov XPOS,3
		mov YPOS,0
		mov color,0
		call hidemouse
		DELETE XPOS,YPOS,color			;draw black DELETE over the shape to hide it
		call showmouse
		call deccolorcounter			;dec the counter of the clicked color
		dec figurecount
		cmp figurecount,0
		je colorgamewon
		mov figures[3],?
		call newshape
		call resettimer
		ret
		atfig7:
		;here at fig 7
		mov XPOS,3
		mov YPOS,1
		mov color,0
		call hidemouse
		DELETE XPOS,YPOS,color			;draw black DELETE over the shape to hide it
		call showmouse
		call deccolorcounter			;dec the counter of the clicked color
		dec figurecount
		cmp figurecount,0
		je colorgamewon
		mov figures[7],?
		call newshape
		call resettimer
		ret
		
		colorgamewon:
		call playerwon
		ret
		
		wrongcolor:
		call declives
		
		cmp lives,30H
		jne stillalivecolor
		call playerlost
		
		stillalivecolor:
		
		ret
		
colormodeinput endp
;=============================================================;

;=============================================================;
figuremodeinput proc					;handles input for figure gametype
		
		cmp clickedcolor,07h			;cmp with grey color
		jne returnn
		
		mov ah,figuretoclick
		cmp clickedfigure,ah
		jne wrongfigure
		
		cmp clickedfigureindex,0
		jne notzero
		mov XPOS,0
		mov YPOS,0
		mov color,0
		call hidemouse
		DELETE XPOS,YPOS,color			;draw black DELETE over the shape to hide it
		call showmouse
		call decfigurecounter
		dec figurecount
		cmp figurecount,0
		je figuregamewon
		call newshape
		mov figures[0],?
		call resettimer
		ret
		notzero:
		
		cmp clickedfigureindex,1
		jne notone
		mov XPOS,1
		mov YPOS,0
		mov color,0
		call hidemouse
		DELETE XPOS,YPOS,color			;draw black DELETE over the shape to hide it
		call showmouse
		call decfigurecounter
		dec figurecount
		cmp figurecount,0
		je figuregamewon
		call newshape
		mov figures[1],?
		call resettimer
		ret
		notone:
		
		cmp clickedfigureindex,2
		jne nottwo
		mov XPOS,2
		mov YPOS,0
		mov color,0
		call hidemouse
		DELETE XPOS,YPOS,color			;draw black DELETE over the shape to hide it
		call showmouse
		call decfigurecounter
		dec figurecount
		cmp figurecount,0
		je figuregamewon
		call newshape
		mov figures[2],?
		call resettimer
		ret
		nottwo:
		
		cmp clickedfigureindex,3
		jne notthree
		mov XPOS,3
		mov YPOS,0
		mov color,0
		call hidemouse
		DELETE XPOS,YPOS,color			;draw black DELETE over the shape to hide it
		call showmouse
		call decfigurecounter
		dec figurecount
		cmp figurecount,0
		je figuregamewon
		call newshape
		mov figures[3],?
		call resettimer
		ret
		notthree:
		
		cmp clickedfigureindex,4
		jne notfour
		mov XPOS,0
		mov YPOS,1
		mov color,0
		call hidemouse
		DELETE XPOS,YPOS,color			;draw black DELETE over the shape to hide it
		call showmouse
		call decfigurecounter
		dec figurecount
		cmp figurecount,0
		je figuregamewon
		call newshape
		mov figures[4],?
		call resettimer
		ret
		notfour:
		
		cmp clickedfigureindex,5
		jne notfive
		mov XPOS,1
		mov YPOS,1
		mov color,0
		call hidemouse
		DELETE XPOS,YPOS,color			;draw black DELETE over the shape to hide it
		call showmouse
		call decfigurecounter
		dec figurecount
		cmp figurecount,0
		je figuregamewon
		call newshape
		mov figures[5],?
		call resettimer
		ret
		notfive:
		
		cmp clickedfigureindex,6
		jne notsix
		mov XPOS,2
		mov YPOS,1
		mov color,0
		call hidemouse
		DELETE XPOS,YPOS,color			;draw black DELETE over the shape to hide it
		call showmouse
		call decfigurecounter
		dec figurecount
		cmp figurecount,0
		je figuregamewon
		call newshape
		mov figures[6],?
		call resettimer
		ret
		notsix:

		mov XPOS,3
		mov YPOS,1
		mov color,0
		call hidemouse
		DELETE XPOS,YPOS,color			;draw black DELETE over the shape to hide it
		call showmouse
		call decfigurecounter
		dec figurecount
		cmp figurecount,0
		je figuregamewon
		call newshape
		mov figures[7],?
		call resettimer
		ret
		
		figuregamewon:
		call playerwon
		ret
		
		wrongfigure:
		call declives
		
		cmp lives,30H
		jne stillalivefigure
		call playerlost
		
		stillalivefigure:
		
		returnn:
		ret
		
figuremodeinput endp
;=============================================================;

;=============================================================;
decfigurecounter proc					;check the clickedfigure and decrements it's count
		
		cmp clickedfigure,0
		jne dnotsquare
		dec SQUARECOUNT
		ret
		dnotsquare:
		
		cmp clickedfigure,1
		jne dnotTRIANGLE
		dec TRIANGLECOUNT
		ret
		dnotTRIANGLE:
		
		cmp clickedfigure,2
		jne dnotPARALLELOGRAM
		dec PARALLELOGRAMCOUNT
		ret
		dnotPARALLELOGRAM:
		
		cmp clickedfigure,3
		jne dnotARROW
		dec ARROWCOUNT
		ret
		dnotARROW:
		
		cmp clickedfigure,4
		jne dnotHEXAGON
		dec HEXAGONCOUNT
		ret
		dnotHEXAGON:
		
		dec CROSSCOUNT
		ret
		
decfigurecounter endp
;=============================================================;

;=============================================================;
deccolorcounter proc					;check clickedcolor and decrements it's count

		cmp colortoclick,1
		jne dnotblue
		dec bluecount
		ret
		dnotblue:
		
		cmp colortoclick,2
		jne dnotgreen
		dec greencount
		ret
		dnotgreen:
		
		cmp colortoclick,3
		jne dnotcyan
		dec cyancount
		ret
		dnotcyan:
		
		cmp colortoclick,4
		jne dnotred
		dec redcount
		ret
		dnotred:
		
		cmp colortoclick,5
		jne dnotpink
		dec pinkcount
		ret
		dnotpink:
		
		dec browncount
		ret
		
deccolorcounter endp
;=============================================================;

;=============================================================;
getpixelcolor proc						;puts the color pressed by the mouse in clickedcolor
		
		mov ah,0DH
		mov BH , 0
		mov cx,x
		sub cx,1
		mov dx,y
		sub dx,1
		int 10h
		mov clickedcolor,al
		
		ret
getpixelcolor endp
;=============================================================;

;=============================================================;
checkkeyboard proc						;checks keyboard input
		
		mov ah,1			;get key input
		int 16h				;this checks the keyboard buffer and clears zf if a key is pressed
		
		jz nokb				;if zf is set this means there is no input and buffer is empty
		
		cmp ah,01H			;cmp with esc
		jz escapegame
		call clearinputbuffer			;buffer will still have escape if not cleared
		ret
		
		
		
		escapegame:
		call pausegame
		ret
		
		nokb:
		ret
checkkeyboard endp
;=============================================================;

;=============================================================;
pausegame	proc						;pauses game
		
		call hidemouse
		call clearinputbuffer			;buffer will still have escape if not cleared
		call drawgamepausedtext
		gamepaused:
		
		mov ah,0			;get key input
		int 16h
		
		cmp ah,39h			;cmp with space
		jz space
	
		cmp ah,01h			;cmp with esc
		jz quit
		
		jmp gamepaused
		
		space:
		call cleargamepausedtext
		call showmouse
		ret
		
		quit:
		MOV AH,0			;CHANGE TO GRAPHICS MODE, THIS CLEARS THE SCREEN
		MOV AL,0EH			;640x200 pixels and 80x25 text but only 16 colors, al=13h 320x200 and 256 colors
		INT 10H
		mov mode,2h
		ret
		
pausegame endp