#!/usr/bin/perl -w

use warnings;
use strict;
use v5.10;

die "I need parameters!" if @ARGV < 2;

my $n = $ARGV[0];
my $w = $ARGV[1];

say "N = $n\nW = $w";

open(OUTPUT, ">", "tests/input2.txt")
or die "Impossible to create the file";

print OUTPUT "$n $w ";

for(my $i = 0; $i < $n*$w; $i++)
{
    my $rand    = rand(200) - 100;
    print OUTPUT "$rand ";
}

close(OUTPUT);
