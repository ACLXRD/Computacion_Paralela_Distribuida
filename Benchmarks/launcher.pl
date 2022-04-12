#!/usr/bin/perl

#   Date: 17/02/2022
#   Author: Andres C. Lopez R.
#   Subjebt: Paralell Computation.
#   Topic: Design of experiments, 
#   automation of execution (average and deviation).

$PATH = `pwd`;
chomp($PATH);
print("Source: ".$PATH. "\n\n");

#Varaible who represents the number of repetitions for each executable file   
$N = 2;
#Vector of executable benchmarks
@ejecutables = ("exeBenchC", "exeBenchCPP");

#Vector NxN for matrix
@matrix_size = ("100", "200");

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