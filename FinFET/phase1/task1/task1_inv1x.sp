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
.param pfin = 4*num
.param nfin = 3*num
.param LoadCap = 1f

VSS Gnd 0 'vss'
VDD Vdd 0 'vdd'

*add transistors 
*pfet is for the finfet nfet 
mp1 Z A Vdd A pfet L=lg NFIN=pfin
mn1 Z A Gnd A nfet L=lg NFIN=nfin

*add cap
Cz Z Gnd 'LoadCap'

*add voltage sourse
VA A 0 PULSE(0 Vdd 0.5n 10p 10p 0.49n 1n)

*define the initial condition of V(Z)
.IC V(Z)='vdd'
.IC V(A)=0

*do transient analysis
	*syntax: .TRAN tiner tstop START=stval 
	*tiner - time step
	*tstop - final time
	*stval - initial time (default 0)
.tran 0.01n 5n 

*print the V(Z) to waveform file *.tr0
.print V(Z)
.print V(A)

*simulation options (you can modify this. Post is needed for .tran analysis)
.OPTION Post Brief NoMod probe measout

*measurement
.measure tran Rise_delay TRIG V(A) VAL=Vdd/2 TD=0 FALL=1 TARG V(Z) VAL=Vdd/2 RISE=1
.measure tran Fall_delay TRIG V(A) VAL=Vdd/2 TD=0 RISE=1 TARG V(Z) VAL=Vdd/2 FALL=1
.measure tran Fall_time TRIG V(Z) VAL=0.8*Vdd TD=0 FALL=1 TARG V(Z) VAL=0.2*Vdd FALL=1
.measure tran Rise_time TRIG V(Z) VAL=0.2*Vdd TD=0 RISE=1 TARG V(Z) VAL=0.8*Vdd RISE=1
*.measure tran RTL TRIG AT=0 TARG v(Z) VAL=0.55 FALL=1
*.measure tran avg_current AVG I(Cz) from 0 to 'RTL'
*.measure tran avg_power AVG p(Cz) 

.end