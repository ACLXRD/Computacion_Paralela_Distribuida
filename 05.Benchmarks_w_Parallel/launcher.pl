#!/usr/bin/perl

#   Date: 17/02/2022
#   Authors :Andres C. Lopez R., Luis F. Velasquez P.
#   Subjebt: Paralell Computation.
#   Topic: Design of experiments, 
#   automation of execution (average and deviation).

$PATH = `pwd`;
chomp($PATH);
print("Source: ".$PATH. "\n\n");

#Varaible who represents the number of repetitions for each executable file   
$N = 36;
#Vector of executable benchmarks
@ejecutables = ("MMPosix", "MM1cOMP", "MM1fOMP");

#Vector NxN for matrix
@matrix_size = ("100", "400", "800", "1600", "2400", "3200");
#Vector  threads to execute 
@threadsN = ("1", "2", "4", "6", "8");

foreach $exe (@ejecutables){
    foreach $size (@matrix_size){
        foreach $thread (@threadsN){
            $file = "$PATH/"."registros/"."$exe"."-$size"."-$thread".".txt";
            #print($file."\n");
            for ($i = 0; $i < $N; $i++){
                #print("$PATH/$exe $size $thread \n");
                system "$PATH/$exe $size $thread >> $file";
            }
            close $file; 
        }
    }
}
exit(0);

# To make this file executable
#   chmod +x launcher.pl