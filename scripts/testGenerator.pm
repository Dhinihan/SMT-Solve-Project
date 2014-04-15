#!/usr/bin/perl -w

use warnings;
use strict;
use v5.10;

die "I need parameters!" if @ARGV < 1;

my $n = $ARGV[0];

say "N = $n";

open(OUTPUT, ">", "tests/input.txt")
or die "Impossible to create the file";

print OUTPUT "$n ";

for(my $i = 0; $i < $n; $i++)
{
    my $rand    = int(rand(200) - 150);
    print OUTPUT "$rand ";
}

close(OUTPUT);
