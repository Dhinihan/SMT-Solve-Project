#!/usr/bin/perl -w

use warnings;
use strict;
use v5.10;

my $w;
my $line;
my $file;
my $i = 0;

die "I need a file!" if @ARGV == 0;

$file = shift @ARGV;

open(MODEL, "<", "tests/model.txt") 
or die "Impossible to open the model";

open(OUTPUT, ">", "output.cvc")
or die "Impossible to create the temporary file";

#Running the program that typify the text

$w = `cat $file | ./dist/prog`;

say "The struct: \n" . $w;

#Print the header in the cvc4 file
while($line = <MODEL>)
{
    print OUTPUT $line; 
}

print OUTPUT "\n % The input % \n";

#Print the input in the model.
while($w =~ s/(\w)//)
{
    given ($1)
    {
        when("V") { print OUTPUT "ASSERT v($i);\n"; }
        when("N") { print OUTPUT "ASSERT n($i);\n"; }
        when("D") { print OUTPUT "ASSERT d($i);\n"; }
    }
    $i++;
}

$i--;

print OUTPUT "\n % The output % \n";

#Print the formula for the answers in the model 
say OUTPUT "ASSERT x = sum_col_vn($i,$i);";
say OUTPUT "ASSERT y = sum_col_nd($i,$i);";
say OUTPUT "ASSERT z = sum_col_dv($i,$i);";
print OUTPUT "CHECKSAT;\nCOUNTERMODEL;\n";

#Find the answers in the CVC4's output

say "Processing...";
my $output = `cvc4 -im -L LANG_CVC4 output.cvc`;
my @dist;
$output =~ m/x : REAL = (.*);/;
$dist[0] = $1;
$output =~ m/y : REAL = (.*);/;
$dist[1] = $1;
$output =~ m/z : REAL = (.*);/;
$dist[2] = $1;

#Print the answers.
say "The answers:";
say "distance VN = " . $dist[0];
say "distance ND = " . $dist[1];
say "distance DV = " . $dist[2];
