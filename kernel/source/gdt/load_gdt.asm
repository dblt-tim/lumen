  global load_gdt
  extern gdtr
reload_Segments:
   PUSH 0x08      
   LEA RAX, [rel .reload_CS]
   PUSH RAX               
   RETFQ            
.reload_CS:
   MOV   AX, 0x10
   MOV   DS, AX
   MOV   ES, AX
   MOV   FS, AX
   MOV   GS, AX
   MOV   SS, AX
   RET

load_gdt:
  lgdt [gdtr]
  jmp reload_Segments
  ret
