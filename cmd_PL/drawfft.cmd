echo $*  | gawk -F"T|:| " '{print $2,$3,$4,$6,$8,$9}' 
echo $*  | gawk -F"T|:| " '{print $2,$3,$4,$6,$8,$9}' | gawk 'BEGIN{print "begindevices sgf"}{
	hour=$1-$1%2;t0=$1%2*3600+$2*60+$3;t1=t0+1024;
	print "cut",t0,t1;
	printf ("r 2016_%s/2016_%s_%02d*%s*\n",$4,$4,hour,$6);
	print "qdp off";
#	print "r",2016"_"$5"/"2016"_"$5"_"hour"*"$7"*";
	print "fft;keepam;xlim 0.01 0.1;";
	print "title 2016-"$4"-"$1"-"$2"-"$3"_snr"$5;
	print "p"
}
	END{print "q";}' 
echo $*  | gawk -F"T|:| " '{print $9"_"$5"-"$6"-"$2"-"$3"-"$4"_"$8".ps" }'
echo $*  | gawk -F"T|:| " '{print "sgftops *.sgf "$9"_"$5"-"$6"-"$2"-"$3"-"$4"_"$8".ps" }' 
echo $*  | gawk -F"T|:| " '{print "psconvert",$9"_"$5"-"$6"-"$2"-"$3"-"$4"_"$8".ps" }' 
echo $*  | gawk -F"T|:| " '{print "rm",$9"_"$5"-"$6"-"$2"-"$3"-"$4"_"$8".ps" }' 
echo $*  | gawk -F"T|:| " '{print "rm *.sgf"}' 
