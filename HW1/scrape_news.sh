#!/bin/bash

wget -q https://www.ynetnews.com/category/3082 -O all_links 

cat all_links | grep -Eo "(https)://(www.ynetnews.com/article/)[a-zA-Z0-9]*" | \
sort | uniq > sorted_links

touch results.csv

#count unique urls:
count=$(cat sorted_links | wc -l)
echo "$count,,,," > results.csv 

bibi_count=0;
bennett_count=0;

for (( i=1; i < count; i++ )); do
	
	#for each url, count number of "Netanyahu"'s and "Bennett"'s:
	line=$(head -n $i sorted_links | tail -n 1)
	wget $line -qO tmp_link
	
	bibi_count=$(cat tmp_link | grep -Eo "Netanyahu" | wc -l)
	bennett_count=$(cat tmp_link | grep -Eo "Bennett" | wc -l)

	#print to file:
	if [[ ($bibi_count -eq 0) && ($bennett_count -eq 0) ]]; then
		echo "$line, -,,," >> results.csv
	else
		echo "$line, Netanyahu,$bibi_count, Bennett,$bennett_count" >> results.csv
	fi
	
	rm tmp_link
done 

rm sorted_links
rm all_links
