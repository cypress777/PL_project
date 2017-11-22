gmtset PAPER_MEDIA Custom_800x1000 
pscoast -R-130/50/-50/70 -JM-40/10/22 -K -W1/0.2p -A5000  -N3  -S10/0/0/10 -P -Ba20/a20WeSn -Y15 > 1.ps 
#cat sta.dat | gawk '{print $2,$3,0.4 }' | psxy  -R -JM -St  -W1.2p/0/0/255  -P  -O -K  >> 1.ps
#cat $1 | gawk '{print $3-1,$2,"8 0 4 RB",$1}' | pstext -R -JB -P -G0/0/0 -O >> 1.ps
cat af13.dat | gawk '{print $2,$3,0.4 }' | psxy  -R -JM -Sx  -W1.2p/230/160/40  -P  -O -K  >> 1.ps 
cat az13.dat | gawk '{print $2,$3,0.4 }' | psxy  -R -JM -Sa  -W1.2p/0/0/255  -P  -O -K  >> 1.ps 
cat be13.dat | gawk '{print $2,$3,0.4 }' | psxy  -R -JM -Sc  -W1.2p/0/0/255  -P  -O -K  >> 1.ps 
cat c13.dat | gawk '{print $2,$3,0.4 }' | psxy  -R -JM -Sd  -W1.2p/0/255/0  -P  -O -K  >> 1.ps 
cat ch13.dat | gawk '{print $2,$3,0.4 }' | psxy  -R -JM -Si  -W1.2p/0/0/255  -P  -O -K  >> 1.ps 
cat cn13.dat | gawk '{print $2,$3,0.4 }' | psxy  -R -JM -Ss  -W1.2p/220/35/145  -P  -O -K  >> 1.ps 
cat cu13.dat | gawk '{print $2,$3,0.4 }' | psxy  -R -JM -St  -W1.2p/255/0/0  -P  -O -K  >> 1.ps 
cat cz13.dat | gawk '{print $2,$3,0.4 }' | psxy  -R -JM -Sa  -W1.2p/255/0/0  -P  -O -K  >> 1.ps 
cat ei13.dat | gawk '{print $2,$3,0.4 }' | psxy  -R -JM -Sc  -W1.2p/210/120/30  -P  -O -K  >> 1.ps 
cat ep13.dat | gawk '{print $2,$3,0.4 }' | psxy  -R -JM -Sd  -W1.2p/255/0/0  -P  -O -K  >> 1.ps 
cat g13.dat | gawk '{print $2,$3,0.4 }' | psxy  -R -JM -Si -W1.2p/40/170/230  -P  -O -K  >> 1.ps 
cat ge13.dat | gawk '{print $2,$3,0.4 }' | psxy  -R -JM -Sx  -W1.2p/0/0/0  -P  -O -K  >> 1.ps 
cat ii13.dat | gawk '{print $2,$3,0.4 }' | psxy  -R -JM -St  -W1.2p/0/0/255  -P  -O -K  >> 1.ps 
cat lb13.dat | gawk '{print $2,$3,0.4 }' | psxy  -R -JM -Sa  -W1.2p/0/255/0  -P  -O -K  >> 1.ps 
cat mn13.dat | gawk '{print $2,$3,0.4 }' | psxy  -R -JM -Sc  -W1.2p/110/40/180  -P  -O -K  >> 1.ps 
cat n413.dat | gawk '{print $2,$3,0.4 }' | psxy  -R -JM -Sd  -W1.2p/200/40/60  -P  -O -K  >> 1.ps 
cat nm13.dat | gawk '{print $2,$3,0.4 }' | psxy  -R -JM -Si  -W1.2p/230/160/40  -P  -O -K  >> 1.ps 

mv 1.ps allstaloc.ps
gs allstaloc.ps
