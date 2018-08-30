#!/usr/bin/perl -w
use strict;
use warnings;
use File::Compare;

my $num_args = $#ARGV + 1;
if ($num_args < 3) {
  print "usage: compare_commands.pl \"<command1>\" \"<command2>\" ... \"<commandN>\" \"<command-args>\"\n";
  exit(1);
}

my (@commands);
my ($command_args);
#print "Commands:\n";
for (my $i = 0; $i < $num_args - 1; $i++) {
  #print $ARGV[$i] . "\n";
  push(@commands, $ARGV[$i]);
}

#print "Command-args:\n";
#print $ARGV[$num_args - 1] . "\n";
$command_args = $ARGV[$num_args - 1];

my $i = 0;
foreach my $command (@commands) {
  my $outfile = "out.$i";
  truncate $outfile, 0;
  #my $shcmd = "time $command $command_args > $outfile 2>&1";
  my $shcmd = "time $command $command_args > $outfile";
  print $shcmd."\n";
  system($shcmd);
  system("cat $outfile");
  $i++;
}

my $num_outfiles = $i;
for (my $i = 1; $i < $num_outfiles; $i++) {
  my $prev_i = $i - 1;
  my $outfile0 = "out.$prev_i";
  my $outfile1 = "out.$i";
  if (compare($outfile0, $outfile1) != 0) {
    print "outfiles $outfile0 and $outfile1 differ\n";
    exit(1);
  }
}
exit(0);
