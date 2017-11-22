echo $1 $2 $3 $4 $5 $6  | gawk 'BEGIN{print "begindevices sgf"}{
	hour=$1-$1%2;t0=$1%2*3600+$2*60+$3;t1=t0+1024;
	print "cut",t0,t1;
	printf ("r 2016_%s/2016_%s_%02d*%s*\n",$4,$4,hour,$6);
#	print "r",2016"_"$5"/"2016"_"$5"_"hour"*"$7"*";
	print "fft;keepam;xlim 0.01 0.06;";
	print "title 2016-"$4"-"$1"-"$2"_snr"$5;
	print "p"
}
	END{print "q";}' | sac
echo "sgftops *.sgf" $6_$4-$1-$2_$5.ps | sh
echo "psconvert" $6_$4-$1-$2_$5.ps | sh 
echo "rm" $6_$4-$1-$2_$5.ps | sh
echo "rm" *.sgf | sh
