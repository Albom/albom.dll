
#Include Once "albom_lib.bi"

Dim As Double acf(0 To 18)

acf_3_full(1, 4, 16, 0.8, 0.1, 600, 600, 1, 0, @acf(0), 19, 30.555e-6)

for tau as Integer = 0 To 18
	Print acf(tau)
Next


Print
Print "OK"
break
