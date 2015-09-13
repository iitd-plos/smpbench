#!/usr/bin/perl -w
use strict;
use warnings;
use config_host;
use Data::Random qw(:all);

if ($#ARGV != 0) {
  usage();
}

my $file = $ARGV[0];

if ($file =~/^randfile\.(\d+)\./) {
  my $size = $1;
  gen_randfile($file, $size * 1e+6);
}
exit(0);


sub gen_randfile {
  my $file = shift;
  my $size = shift;
  open(my $fp, ">$file") or die;
  while ((-s $file) < $size) {
    for (my $i = 0; $i < 10000; $i++) {
      my @random_words = rand_words( size => 10 );
      print $fp "@random_words\n";
    }
  }
  close($fp);
}

sub min {
  my $a = shift;
  my $b = shift;
  if ($a < $b) {
    return $a;
  } else {
    return $b;
  }
}

sub usage {
  print "gen_randfile.pl randfile.SIZE.SUFFIX\n";
  print "    SIZE is in MB.\n";
  exit(1);
}
