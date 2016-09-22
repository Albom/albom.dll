
#Include Once "albom_lib.bi"

Dim Shared As ZString*256 buffer

Dim As Double x(0 To 3) => {4.186, 3.33, 2.56, 1.08}

buffer_clear(buffer)
buffer_add_d(buffer, @x(0), 4, "%5.2f")

Print buffer

Print
Print "OK"
break
