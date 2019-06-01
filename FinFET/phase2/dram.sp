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
.param numfin = 1
.param LoadCap = 1f

VSS Gnd 0 'vss'
VDD Vdd 0 'vdd'

*add transistors 
*pfet is for the finfet nfet 
mp1 Z Y X Vdd pfet L=lg NFIN=numfin

*add cap
Cz Z Gnd 'LoadCap'

*add voltage sourse
VX X 0 'vdd/2'
VY Y 0 'vdd'

*define the initial condition of V(Z)
.IC V(Z)='vdd'

*do transient analysis
	*syntax: .TRAN tiner tstop START=stval 
	*tiner - time step
	*tstop - final time
	*stval - initial time (default 0)
.tran 0.1m 200m

*print the V(Z) to waveform file *.tr0
.print V(Z)

*simulation options (you can modify this. Post is needed for .tran analysis)
.OPTION Post Brief NoMod probe measout

*measurement
.measure tran RTL TRIG AT=0 TARG v(Z) VAL=0.55 FALL=1
.measure tran avg_current AVG I(Cz) from 0 to 'RTL'
.measure tran avg_power AVG p(Cz)
.end