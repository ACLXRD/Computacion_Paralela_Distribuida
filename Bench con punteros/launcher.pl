#!/usr/bin/perl

#   Date: 09/03/2022
#   Author: Oscar Julian Reyes Torres
#   Subjebt: Paralell Computation.
#   Topic: Design of experiments, 
#   automation of execution (average and deviation).

$PATH = `pwd`;
chomp($PATH);
print("Source: ".$PATH. "\n\n");

#Varaible who represents the number of repetitions for each executable file   
$N = 31;
#Vector of executable benchmarks
@ejecutables = ("MM1c", "MM1f");

#Vector NxN for matrix
@matrix_size = ("500", "1000");

foreach $exe (@ejecutables){
    foreach $size (@matrix_size){
        $file = "$PATH/"."registros/"."$exe"."-$size".".txt";
        #print($file."\n");
        for ($i = 0; $i < $N; $i++){
            #print("$PATH/$exe $size \n");
            system "$PATH/$exe $size >> $file";
        }
        close $file; 
    }
}
exit(0);

# To make this file executable
#   chmod +x launcher.pl
