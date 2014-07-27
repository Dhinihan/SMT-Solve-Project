#!/usr/bin/perl -w

use warnings;
use strict;
use v5.10;

my $file;
my $i;
my $j;
my @data;

die "I need a file!" if @ARGV == 0;

$file = shift @ARGV;

for($i = 1; $i <= 5; $i++)
{
    open(INPUT, "<", $file . $i . '.txt')
    or die "Impossible to open file\n";
    
    while(my $line = <INPUT>)
    {
        my $unid;
        my $dec;
        my $value;
        
        $line =~ m/(\d+)[.]?(\d)?\s(\d+[.]?\d*)/;
        
        $unid = $1;
        if (defined($2))
        {
            $dec = $2;
        }  
        else 
        {
            $dec = 0;
        } 
        $value = $3;
        $data[$unid][$dec] += $value/5;
    }
    close INPUT;
}

open(OUTPUT, ">", $file . "_final" . '.txt')
    or die "Impossible to create output file\n";
    

for($i = 1; $i < 10; $i++)
{
    for($j = 0; $j < 10; $j++)
    {
        print OUTPUT  ($i . '.' . $j . " " . $data[$i][$j] . "\n");
        print ($i . '.' . $j . " " . $data[$i][$j] . "\n");
    }
}

print OUTPUT  ('10.0'. " " . $data[10][0] . "\n");
print ('10.0'. " " . $data[10][0] . "\n");


close INPUT;
