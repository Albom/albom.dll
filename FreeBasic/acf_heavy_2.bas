
#Include Once "albom_lib.bi"

Dim As Double ti_s = 1000
Dim As Double te_s = 3200

Const As Integer N = 19

Dim As Double acf(0 To N-1)
Dim As Double acf_teor(0 To N-1)

acf_3_full(16, 30.5, 30.5, 0.8, 0, ti_s, te_s, 1, 0, @acf(0), N, 30.555e-6)

Dim As Double d_c = 1e200
Dim As Integer ti_c, te_c

For ti As Integer = 500 To 4000 Step 20
	Print ti
	For te As Integer = ti To 4000 Step 20
		If te/ti < 4 Then

			acf_3_full(16, 30.5, 30.5, 1, 0, ti, te, 1, 0, @acf_teor(0), N, 30.555e-6)
			Dim As Double d = 0
			For tau As Integer = 1 To N-1
				d += (acf(tau) - acf_teor(tau))^2
			Next
			If d < d_c Then
				d_c = d
				ti_c = ti
				te_c = te
			EndIf

		EndIf
	Next
Next

Print ti_c, te_c


Print
Print "OK"
break
