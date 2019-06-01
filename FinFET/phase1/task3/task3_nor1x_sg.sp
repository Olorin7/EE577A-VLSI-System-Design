*************************
*  lab3 hspice
*************************

.include './hp7nfet.pm'
.include './hp7pfet.pm'

*define parameters 
.param vdd=0.7 
.param vss=0 
.param fin_height=18n 
.param fin_width=7n 
.param lg=11n 
.param num=1 
.param pfin = 8*num
.param nfin = 3*num
.param LoadCap = 1f

VSS Gnd 0 'vss'
VDD Vdd 0 'vdd'

*add transistors 
*pfet is for the finfet nfet 
mp1 X A Vdd A pfet L=lg NFIN=pfin
mn1 Z A Gnd A nfet L=lg NFIN=nfin
mp2 Z B X B pfet L=lg NFIN=pfin
mn2 Z B Gnd B nfet L=lg NFIN=nfin

*add cap
*Cz Z Gnd 'LoadCap'

*add voltage sourse
*VX X 0 'vdd/2'
VA A 0 PULSE(0 Vdd 0.5n 10p 10p 0.49n 1n)
VB B 0 PULSE(0 Vdd 1n 10p 10p 0.99n 2n)
*VA A 0 0
*VB B 0 Vdd

*define the initial condition of V(Z)
.IC V(Z)="Vdd"

*do transient analysis
	*syntax: .TRAN tiner tstop START=stval 
	*tiner - time step
	*tstop - final time
	*stval - initial time (default 0)
.tran 0.01n 8n 

*print the V(Z) to waveform file *.tr0
.print V(Z)
.print V(A)
.print V(B)

*simulation options (you can modify this. Post is needed for .tran analysis)
.OPTION Post Brief NoMod probe measout

*measurement
.measure tran Rise_delay TRIG V(B) VAL=Vdd/2 TD=0 FALL=1 TARG V(Z) VAL=Vdd/2 RISE=1
.measure tran Fall_delay TRIG V(A) VAL=Vdd/2 TD=0 RISE=1 TARG V(Z) VAL=Vdd/2 FALL=1
.measure tran Fall_time TRIG V(Z) VAL=0.8*Vdd TD=0 FALL=1 TARG V(Z) VAL=0.2*Vdd FALL=1
.measure tran Rise_time TRIG V(Z) VAL=0.2*Vdd TD=0 RISE=1 TARG V(Z) VAL=0.8*Vdd RISE=1
*.measure tran ileak1 AVG I(mp1)
.measure tran Avg_power AVG power from 2n to 4n


.end
