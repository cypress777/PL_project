for ((i=1;i<157;i++));do for file in `ls *.list`; do gawk 'NR=="'$i'"' $file >> "$i".dat; done;done

