#!/usr/bin/perl -w

use warnings;
use strict;
use v5.10;

my $line;
my $prefix = $ARGV[0];
my $aux;

open(OUT, '>', "time.txt");
select OUT;

for(my $i = 10; $i <=100; $i++)
{
    open(INPUT, "<", $aux = "$prefix/time/$i.txt") 
    or die "Impossible to open \"$aux\"";
    print <INPUT>;
}

close(OUT);

open(OUT, '>', "sat.txt");
select OUT;

for(my $i = 10; $i <=100; $i++)
{
    open(INPUT, "<", $aux = "$prefix/sat/$i.txt") 
    or die "Impossible to open \"$aux\"";
    print <INPUT>;
}

`mv time.txt data/`;
`mv sat.txt data/`;
