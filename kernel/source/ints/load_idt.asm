  extern idtr
  global load_idt

load_idt:
  lidt [idtr]
  sti
  ret
