#!/usr/bin/perl -w

use warnings;
use strict;
use v5.10;

die "I need parameters!" if @ARGV < 2;

my $n = $ARGV[0];
my $w = $ARGV[1];

say "N = $n";
say "W = $w";

open(OUTPUT, ">", "tests/input.txt")
or die "Impossible to create the file";

print OUTPUT "$n $w ";

for(my $i = 0; $i < $n*$w + 1; $i++)
{
    my $rand    = int(rand(200) - 150);
    print OUTPUT "$rand ";
}

close(OUTPUT);
