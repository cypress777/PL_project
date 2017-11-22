ls SAC_PZs_* | gawk '{split($1,aa,"_");print "mv",$1,aa[4]"_"aa[5]"_"aa[6]}'  | sh
ls *SAC | gawk '{
                  split($1,aa,".");print "r",$1;print "rtr";print "rmean";
		  print "transfer from polezero subtype",aa[8]"_"aa[10]"_"aa[9],"to none freq 0.001 0.002 0.45 0.49";
                  print "w over";}END{print "q";}' | sac
rm *_?H?_??
rm *_?H?_
