gmtset PS_MEDIA Custom_800x640 
pscoast -R-90/60/-50/40 -JM-40/10/22 -W1/0.2p -A5000  -N3  -S10/0/0/10 -P -Ba20/a20WeSn -K > 1.ps 
cat $1 | gawk '{print $8,$9,$6 }' | psxy  -R -JM -Sc  -W2/0/0/255  -P -O -K  >> 1.ps
cat $1 | gawk '{print $8-1,$9,"10 0 4 RB",$1}' | pstext -R -JM -P -G -O -K >> 1.ps
echo "-15 35 10 0 4 RB" $1 | pstext -R -JM -P -G -O >> 1.ps
mv 1.ps $1.ps
#gs sta.ps
