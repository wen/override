#!/usr/bin/perl
foreach (@ARGV) {
  my @arr = /../g;
  die "wrong format" unless (shift @arr eq "0x");
  foreach (reverse @arr) {
    print chr hex;
  }
}
print "\n";
