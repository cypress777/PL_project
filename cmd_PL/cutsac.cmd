echo year_begin,year_end,jday_begin,jday2_end and channel
year1=$1
year2=$2
jday1=$3
jday2=$4
channel=$5

for i in $(ls *.seed*)
do
gawk 'BEGIN{
 ARGC=0;
 fn=ARGV[1];
 year1=ARGV[2];
 year2=ARGV[3]
 jday1=ARGV[4];
 jday2=ARGV[5];
 channel=ARGV[6];
 delta=24
 for(year=year1;year<=year2;year++)
	 for(jday=jday1;jday<=jday2;jday=jday+2) 
      		 for(hour=0;hour<=0;hour=hour+delta) {
            		 print fn;
          		 printf "\n";
            		 printf "\n";
            		 printf "d\n";
            		 printf "\n"; 
			 printf "\n"; 
			 printf channel"\n";
			 printf "\n";
         		 printf "\n"; printf "\n"; printf "\n"; 
                         printf "Y\n";
             		 print "\n";
 		         print year "," jday "," hour ":00:00.0000";
            		 print year "," jday+1 "," hour+delta-1 ":59:59.9999";
      		         printf "\n";printf "\n";
          		  }
	 }' $i $year1  $year2  $jday1  $jday2  $channel | rdseed 
done 
