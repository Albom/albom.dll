
#Include Once "albom_lib.bi"

Dim As Double acf(0 To 22)
Dim As Double acf_22(0 To 22)

acf_3_full(1, 4, 16, 0.8, 0.1, 600, 600, 1, 0, @acf(0), 22, 30.555e-6)
acf_3_kharkiv_22(0.8, 0.1, 600, 600, @acf_22(0))

for tau as Integer = 0 To 21
	Print acf(tau)-acf_22(tau)
Next

Print
Print Time
For i As Integer = 0 To 5000 
	acf_3_full(1, 4, 16, 0.8, 0.1, 600, 600, 1, 0, @acf(0), 22, 30.555e-6)
Next
Print Time


Print
Print Time
For i As Integer = 0 To 5000 
	acf_3_kharkiv_22(0.8, 0.1, 600, 600, @acf_22(0))
Next
Print Time



Print
Print "OK"
break
