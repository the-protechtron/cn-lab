set ns [new Simulator]
#create trace file
set trace_file [open lab3.tr w]
$ns trace-all $trace_file
#create nam trace file
set nam_file [open lab3.nam w]
$ns namtrace-all $nam_file
# Creating nodes.
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]
set n5 [$ns node]
$n0 label "Ping0"
$n4 label "Ping4"
$n1 label "Ping1"
$n5 label "Ping5"
$ns color 1 "blue"
$ns color 2 "orange"
#establish communication links
$ns duplex-link $n0 $n2 0.5mb 10ms DropTail
$ns duplex-link $n1 $n2 0.5mb 10ms DropTail
$ns duplex-link $n2 $n3 0.5mb 10ms DropTail
$ns duplex-link $n3 $n4 0.5mb 10ms DropTail
$ns duplex-link $n3 $n5 0.5mb 10ms DropTail
# connect the ping agents
set ping0 [new Agent/Ping]
$ns attach-agent $n0 $ping0
set ping4 [new Agent/Ping]
$ns attach-agent $n4 $ping4
set ping1 [new Agent/Ping]
$ns attach-agent $n1 $ping1
set ping5 [new Agent/Ping]
$ns attach-agent $n5 $ping5
$ping0 set packetSize_ 500
$ping0 set interval_ 0.001
$ping1 set packetSize_ 500
$ping1 set interval_ 0.001
$ping4 set packetSize_ 500
$ping4 set interval_ 0.001
$ping5 set packetSize_ 500
$ping5 set interval_ 0.001
set udp0 [new Agent/UDP]
set null [new Agent/Null]
$ns attach-agent $n0 $udp0
$ns attach-agent $n4 $null
set cbr [new Application/Traffic/CBR]
$cbr set packetSize_ 512
$cbr set interval_ 0.001
$cbr attach-agent $udp0
$ns connect $udp0 $null
$ping0 set class_ 1
$ping1 set class_ 2
#ping the receiver from other nodes
$ns connect $ping0 $ping4
$ns connect $ping1 $ping5
#The below function is executed when the ping agent receives a reply from the destination
Agent/Ping instproc recv {from rtt} {
$self instvar node_
puts " The node [$node_ id] received a reply from $from with round trip time of $rtt ms"
}
#define finish procedure
proc finish { } {
global ns nam_file trace_file
$ns flush-trace
exec nam lab3.nam &
close $trace_file
close $nam_file
exit 0
}
#schedule events to start sending the ping packets
$ns at 0.1 "$ping0 send"
$ns at 0.2 "$ping0 send"
$ns at 0.3 "$ping0 send"
$ns at 0.4 "$ping0 send"
$ns at 0.5 "$ping0 send"
$ns at 0.6 "$ping0 send"
$ns at 0.7 "$ping0 send"
$ns at 0.8 "$ping0 send"
$ns at 0.9 "$ping0 send"
$ns at 1.0 "$ping0 send"
$ns at 0.2 "$cbr start"
$ns at 4.0 "$cbr stop"
$ns at 0.1 "$ping1 send"
$ns at 0.2 "$ping1 send"
$ns at 0.3 "$ping1 send"
$ns at 0.4 "$ping1 send"
$ns at 0.5 "$ping1 send"
$ns at 0.6 "$ping1 send"
$ns at 0.7 "$ping1 send"
$ns at 0.8 "$ping1 send"
$ns at 0.9 "$ping1 send"
$ns at 1.0 "$ping1 send"
$ns at 5.5 "finish"
$ns run
Awk file
BEGIN{
#include<stdio.h>
count=0
}
{
 if($1=="d")
 count++
}
END{
  printf("The Total no of Packets Dropped due toCongestion:%d ", count)
}
