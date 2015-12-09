#!/usr/bin/perl -w
use strict;
use warnings;

use config;
use myutils;

our $build;
our $srcdir;

if ($#ARGV != 3) {
  print "Usage: microbench_run_thread_iters.pl <bench-name> <max-threads> <num-iters>\n";
  exit(1);
}

my $bench = $ARGV[0];
my $max_threads = $ARGV[1];
my $num_iters = $ARGV[2];

for (my $t = 1; $t <= $max_threads; $t *= 2) {
  for (my $iter = 0; $iter <= $num_iters; $iter++) {
    my $command = "$build/mytime $bench.threads$t.iter$iter $build/$bench $t";
    my $ec = xsystem($command);
    if ($ec != 0) {
      print "Command failed: $command\n";
      exit(1);
    }
  }
}
