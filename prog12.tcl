set ns [new Simulator]
set tf [open lab2.tr w]
$ns trace-all $tf
set nf [open lab2.nam w]
$ns namtrace-all $nf
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
# The below code is used to set the color and name's to the #nodes.
$ns color 1 "red"
$ns color 2 "blue"
$n0 label "source/TCP"
$n1 label "source/UDP"
$n2 label "Router"
$n3 label "destination"
$ns duplex-link $n0 $n2 100Mb 1ms DropTail
$ns duplex-link $n1 $n2 100Mb 1ms DropTail
$ns duplex-link $n2 $n3 100Mb 1ms DropTail
# The below code is used to set the color and labels to the #links.
$ns duplex-link-op $n0 $n2 color "green"
$ns duplex-link-op $n0 $n2 label "from 0-2"
$ns duplex-link-op $n1 $n2 color "green"
$ns duplex-link-op $n1 $n2 label "from 1-2"
$ns duplex-link-op $n2 $n3 color "green"
$ns duplex-link-op $n2 $n3 label "from 2-3"
# The below code is used create TCP and UDP agents and the
# traffic ftp & cbr respectively.
set tcp0 [new Agent/TCP]
$ns attach-agent $n0 $tcp0
set ftp0 [new Application/FTP]
$ftp0 attach-agent $tcp0
set sink3 [new Agent/TCPSink]
$ns attach-agent $n3 $sink3
set udp1 [new Agent/UDP]
$ns attach-agent $n1 $udp1
set cbr1 [new Application/Traffic/CBR]
$cbr1 attach-agent $udp1
set null3 [new Agent/Null]
$ns attach-agent $n3 $null3
#The below code is used to set the packet size of ftp and #udp.
$ftp0 set packetSize_ 500
$ftp0 set interval_ 0.001
#The below code is used to increase the data rate(if the #interval is more then the more
number of packets goes to #destination).
$cbr1 set packetSize_ 500
$cbr1 set interval_ 0.001
#This code is used give a color red->tcp and blue ->udp.
$tcp0 set class_ 1
$udp1 set class_ 2
# The below code is used connect the agents.
$ns connect $tcp0 $sink3
$ns connect $udp1 $null3
proc finish { } {
global ns nf tf
$ns flush-trace
exec nam lab2.nam &
close $nf
close $tf
exit 0
}
$ns at 0.1 "$cbr1 start"
$ns at 0.2 "$ftp0 start"
$ns at 5.0 "finish"
$ns run


awk file
BEGIN{
#include<stdio.h>
tcp=0;
udp=0;
}
{
 if($1=="r"&&$3=="2"&&$4=="3"&& $5=="tcp")
 tcp++;
 if($1=="r"&&$3=="2"&&$4=="3"&&$5=="cbr")
 udp++;
}
END{
printf("\n Total number of packets sent by TCP : %d\n",tcp);
printf("\n Total number of packets sent by UDP : %d\n",udp);
}