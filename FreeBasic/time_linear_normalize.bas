
#Include Once "albom_lib.bi"

Dim As Double a(0 To 5) => {0, 1, 2, 4, 2, 5}

For i As Integer = 0 To 5
	Print a(i)
Next
Print

time_linear(@a(0), 6)

For i As Integer = 0 To 5
	Print a(i)
Next
Print

time_normalize(@a(0), 6)

For i As Integer = 0 To 5
	Print a(i)
Next

Print
Print "OK"
break
