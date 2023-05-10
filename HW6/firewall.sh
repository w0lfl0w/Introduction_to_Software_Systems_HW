#!/bin/bash

# don't forget to give premissions with
# sudo chmod +x ./firewall.sh

# if we call this script in this way : cat packets.txt | ./firewall.sh rules.in
# then $1 will be rules.in and packets.txt is in $(</dev/stdin)

# get all packets from stdin, save it in INPUT
INPUT=$(</dev/stdin)
# clean the rules. each AND rule is in one line
all_rules=$(cat $1|sed 's/\ //g'|sed -e 's/#.*//'|grep 's')
for line in $(echo "$all_rules"); do
	new_packets=""
	
	# go through each rule in an AND rule
	rule=$(echo "$line"|tr "," "\n" |sed -r '/^\s*$/d')
	for line in $(echo "$rule"); do
		#use the firewall on each seperate rule and add output to new_packets
		firewall_activator=$(echo "$INPUT"|./firewall.exe $line)
		new_packets="$new_packets"$'\n'"$firewall_activator"
	done
	
	#add only the packets that stands in all 4 rules to the output_packets
	new_packets=$(echo "$new_packets"|sort|uniq -c|
	sed 's/\ //g'|grep "^4"|cut -c2-)
	output_packets="$output_packets"$'\n'"$new_packets"
done


# print each packet once in the correct form
output_packets=$(echo "$output_packets"|sed -r '/^\s*$/d'|sort|uniq)
echo "$output_packets"
