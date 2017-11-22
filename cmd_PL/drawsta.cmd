gmtset PS_MEDIA Custom_800x640 
pscoast -R-90/60/-50/40 -JM-40/10/22 -K -W1/0.2p -A5000  -N3  -S10/0/0/10 -P -Ba20/a20WeSn > 1.ps 
cat sta.dat | gawk '{print $2,$3,0.4 }' | psxy  -R -JM -St  -W1.2/0/0/255  -P  -O -K  >> 1.ps
cat sta.dat | gawk '{print $2-1,$3,"10 0 4 RB",$1}' | pstext -R -JM -P -G -O >> 1.ps
mv 1.ps sta.ps
#gs sta.ps
